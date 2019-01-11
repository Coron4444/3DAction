//================================================================================
//!	@file	 LinerOctree.h
//!	@brief	 線形8分木Class
//! @details template
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_LINER_OCTREE_H_
#define _LINER_OCTREE_H_



//****************************************
// インクルード文
//****************************************
#include <windows.h>
#include <vector>
#include <list>

#include "ObjectOfTree/ObjectOfTree.h"
#include "SpaceOfTree/SpaceOfTree.h"

#include <Vector3D.h>
#include <SafeRelease/SafeRelease.h>



//************************************************************														   
//! @brief   線形8分木Class
//!
//! @details 線形配列による8分木の管理Class(template)
//************************************************************
template <class Type>
class LinerOctree
{
//====================
// 定数
//====================
public:
	static const unsigned MAX_LEVEL = 9;	//!< 最大レベル


//====================
// 変数
//====================
private:
	unsigned power_of_eight_array_[MAX_LEVEL + 1] = {0};	//!< ８のべき乗数値配列
	SpaceOfTree<Type>** space_pointer_array_ = nullptr;		//!< 各空間ポインタ配列
	Vec3 octree_width_ = {1.0f, 1.0f, 1.0f};				//!< 8分木の幅
	Vec3 octree_width_min_ = {0.0f, 0.0f, 0.0f};			//!< 8分木の幅の最小値
	Vec3 octree_width_max_ = {1.0f, 1.0f, 1.0f};			//!< 8分木の幅の最大値
	Vec3 octree_unit_length_ = {1.0f, 1.0f, 1.0f};			//!< 8分木の単位長さ
	DWORD all_space_num_ = 0;								//!< 空間数
	unsigned  lowest_level_ = 0;							//!< 最下位レベル(一番末端のLevel数)


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param lowest_level     最下位レベル(一番末端のLevel数)
	//! @param octree_width_min 8分木の幅の最小値
	//! @param octree_width_max 8分木の幅の最大値
	//! @retval void なし
	//----------------------------------------
	void Init(unsigned lowest_level, Vec3 octree_width_min, Vec3 octree_width_max)
	{
		// 最下位レベルの確認
		if (lowest_level > MAX_LEVEL)
		{
			MessageBox(nullptr, "無効な最下位レベルです。(LinerOctree.cpp)", "Error", MB_OK);
			return;
		}

		// 最下位レベルの代入
		lowest_level_ = lowest_level;

		// 8のべき乗数値の格納
		power_of_eight_array_[0] = 1;
		for (unsigned i = 1; i < MAX_LEVEL + 1; i++)
		{
			power_of_eight_array_[i] = power_of_eight_array_[i - 1] * 8;
		}

		// 空間数の算出(等比級数の和の公式)
		all_space_num_ = (power_of_eight_array_[lowest_level_ + 1] - 1) / 7;

		// 各空間ポインタ配列の作成と初期化
		space_pointer_array_ = new SpaceOfTree<Type>*[all_space_num_];
		ZeroMemory(space_pointer_array_,
				   sizeof(SpaceOfTree<Type>*) * all_space_num_);

		// 8分木の幅算出
		octree_width_min_ = octree_width_min;
		octree_width_max_ = octree_width_max;
		octree_width_ = octree_width_max_ - octree_width_min_;
		octree_unit_length_ = octree_width_ / ((float)(1 << lowest_level_));	// 分母は1辺の空間数
	}

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit()
	{
		for (unsigned i = 0; i < all_space_num_; i++)
		{
			SafeRelease::PlusUninit(&space_pointer_array_[i]);
		}

		if (space_pointer_array_ == nullptr) return;

		delete[] space_pointer_array_;
	}

	//----------------------------------------
	//! @brief 衝突リスト更新関数
	//! @details
	//! @param *collision_list 衝突リスト
	//! @retval void なし
	//----------------------------------------
	void UpdateCollisionList(std::vector<Type>* collision_list)
	{
		// 初期化
		collision_list->clear();

		// ルート空間があるかどうか
		if (space_pointer_array_[0] == nullptr) return;

		// ルート空間から処理を開始
		std::list<Type> temp_stack;
		GetCollisionList(0, collision_list, &temp_stack);
	}

	//----------------------------------------
	//! @brief 追加関数
	//! @details
	//! @param object     追加したいオブジェクト
	//! @param object_min 追加したいオブジェクトの最小値
	//! @param object_max 追加したいオブジェクトの最大値
	//! @retval void なし
	//----------------------------------------
	void Add(ObjectOfTree<Type>* object, const Vec3* object_min, const Vec3* object_max)
	{
		// オブジェクトの所属空間の配列インデックスの取得
		DWORD array_index = GetArrayIndexOfBelonginSpace(object_min, object_max);
		if (array_index >= all_space_num_)
		{
			MessageBox(nullptr, "配列数を超えました(LinerOctree.h)", "Error", MB_OK);
		}

		// 空間が存在しない場合は作成
		if (space_pointer_array_[array_index] == nullptr)
		{
			CreateSpace(array_index);
		}

		// オブジェクトを登録
		space_pointer_array_[array_index]->AddObject(object);
	}


private:
	//----------------------------------------
	//! @brief 3bit間隔へ分離関数
	//! @details
	//! @param *num 分離したい数値
	//! @retval void なし
	//----------------------------------------
	void SeparateInto3BitIntervals(DWORD* num)
	{
		*num = (*num | *num << 8) & 0x0000f00f;	// 1Byteを4bitごとに分ける
		*num = (*num | *num << 4) & 0x000c30c3;	// 各4bitを２bitごとに分ける
		*num = (*num | *num << 2) & 0x00249249;	// 各2bitを1bitごとに分ける(3bit間隔)
	}

	//----------------------------------------
	//! @brief 3Dモートン空間番号取得関数
	//! @details
	//! @param *position モートン番号を取得したい座標
	//! @retval DWORD 算出した3Dモートン空間番号
	//----------------------------------------
	DWORD GetMortonNumber(const Vec3* position)
	{
		// 最下位レベル空間での座標へ変換
		DWORD temp_x = (DWORD)((position->x - octree_width_min_.x) / octree_unit_length_.x);
		DWORD temp_y = (DWORD)((position->y - octree_width_min_.y) / octree_unit_length_.y);
		DWORD temp_z = (DWORD)((position->z - octree_width_min_.z) / octree_unit_length_.z);

		// 3bit間隔へ分離
		SeparateInto3BitIntervals(&temp_x);
		SeparateInto3BitIntervals(&temp_y);
		SeparateInto3BitIntervals(&temp_z);

		// 1bitずつずらす
		return temp_x | (temp_y << 1) | (temp_z << 2);
	}

	//----------------------------------------
	//! @brief 所属空間の配列インデックス取得関数
	//! @details
	//! @param *object_min 所属空間の配列インデックスを取得したいオブジェクトの最小値
	//! @param *object_max 所属空間の配列インデックスを取得したいオブジェクトの最大値
	//! @retval DWORD 所属空間の配列番号
	//----------------------------------------
	DWORD GetArrayIndexOfBelonginSpace(const Vec3* object_min, const Vec3* object_max)
	{
		// 最小値と最大値のモートン番号のXORを算出
		DWORD converted_min = GetMortonNumber(object_min);
		DWORD converted_max = GetMortonNumber(object_max);
		DWORD temp = converted_min ^ converted_max;

		// 最上位の区切りから最小値と最大値の共有空間レベルを算出する
		unsigned shared_space_level = 0;
		for (unsigned i = 0; i < lowest_level_; i++)
		{
			// 3bitずつずらして(3Dな為)何かしら数値があるかをチェック
			DWORD check = temp >> (i * 3) & 0x7;
			if (check != 0) shared_space_level = i + 1;
		}

		// 共有空間レベルから所属空間番号を算出(共有空間レベル分3bitシフト)
		DWORD shared_space_num = converted_max >> (shared_space_level * 3);

		// 所属空間番号から配列インデックスに変換(等比級数の和の公式の分を加算)
		shared_space_num += (power_of_eight_array_[lowest_level_ - shared_space_level] - 1) / 7;

		return shared_space_num;
	}

	//----------------------------------------
	//! @brief 空間の生成関数
	//! @details
	//! @param array_index 配列インデックス
	//! @retval void なし
	//----------------------------------------
	void CreateSpace(DWORD array_index)
	{
		while (space_pointer_array_[array_index] == nullptr)
		{
			// 空間作成
			space_pointer_array_[array_index] = new SpaceOfTree<Type>();

			// 親空間へ移動
			array_index = (array_index - 1) >> 3;
			if (array_index >= all_space_num_) break;
		}
	}

	//----------------------------------------
	//! @brief 衝突リストの作成関数
	//! @details
	//! @param space_index      空間配列インデックス
	//! @param *collision_list  衝突オブジェクトリスト
	//! @param *collision_stack 衝突オブジェクトスタック
	//! @retval void なし
	//----------------------------------------
	void GetCollisionList(DWORD space_index, std::vector<Type>* collision_list,
						  std::list<Type>* collision_stack)
	{
		ObjectOfTree<Type>* temp01 = space_pointer_array_[space_index]->getFirstObject();
		while (temp01 != nullptr)
		{
			// 同空間内オブジェクト同士の衝突リスト作成
			ObjectOfTree<Type>* temp02 = temp01->getpNext();
			while (temp02 != nullptr)
			{
				// 衝突リスト作成
				collision_list->push_back(temp01->getObject());
				collision_list->push_back(temp02->getObject());

				// 次のオブジェクトへ
				temp02 = temp02->getpNext();
			}

			// スタックされているオブジェクトとの衝突リスト作成
			for (auto it = collision_stack->begin(); it != collision_stack->end(); it++)
			{
				collision_list->push_back(temp01->getObject());
				collision_list->push_back(*it);
			}

			// 次のオブジェクトへ
			temp01 = temp01->getpNext();
		}

		// 子空間へ移動
		bool child_flag = false;		// 子空間フラグ
		DWORD object_num = 0;
		DWORD next_space_index = 0;
		for (unsigned i = 0; i < 8; i++)
		{
			// 次の空間があるかどうか
			next_space_index = space_index * 8 + 1 + i;
			if (next_space_index >= all_space_num_) continue;
			if (space_pointer_array_[next_space_index] == nullptr) continue;

			// 親をプッシュ
			if (!child_flag)
			{
				temp01 = space_pointer_array_[space_index]->getFirstObject();
				while (temp01 != nullptr)
				{
					collision_stack->push_back(temp01->getObject());
					object_num++;
					temp01 = temp01->getpNext();
				}
			}

			// 子空間フラグON
			child_flag = true;

			// 子空間の再帰処理
			GetCollisionList(next_space_index, collision_list, collision_stack);
		}

		// スタックからオブジェクトを外す
		if (!child_flag) return;

		for (unsigned i = 0; i < object_num; i++)
		{
			collision_stack->pop_back();
		}
	}
};



#endif
