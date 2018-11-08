//================================================================================
//
//    有限ポインター配列クラス(クラステンプレート)
//    Author : Araki Kai                                作成日 : 2018/04/18
//
//================================================================================

#ifndef	_LIMITED_POINTER_ARRAY_H_
#define _LIMITED_POINTER_ARRAY_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <unordered_map>
#include <assert.h>

#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// クラス定義
//
//======================================================================

template<class Type, unsigned ARRAY_NUM = 100000>
class LimitedPointerArray
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// デフォルトコンストラクタ
	LimitedPointerArray()
		: end_pointer_(0)
	{
		// 配列の初期化
		for (unsigned i = 0; i < ARRAY_NUM; i++)
		{
			array_[i] = nullptr;
		}

		// マップの初期化
		registration_map_.clear();
	}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:

	// 配列に追加
	void AddToArray(Type object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(object);
		if (iterator != registration_map_.end()) return;

		// 追加
		for (unsigned i = 0; i < ARRAY_NUM; i++)
		{
			if (array_[i] != nullptr) continue;

			// 配列に追加
			array_[i] = object;

			// マップに登録
			registration_map_.insert(std::make_pair(object, i));

			// エンドポインタの更新
			if (end_pointer_ < (i + 1))
			{
				end_pointer_ = (i + 1);
			}
			return;
		}
	}



	// 配列の上書き
	void OverwriteArray(Type old_object, Type new_object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(old_object);
		if (iterator != registration_map_.end())
		{
			// 配列の上書き
			array_[iterator->second] = new_object;

			// 新規オブジェクトを登録及び古いオブジェクトの削除
			registration_map_.insert(std::make_pair(new_object, iterator->second));
			registration_map_.erase(old_object);
		}
		else
		{
			// 古いオブジェクトがないため新規扱い
			AddToArray(new_object);
		}
	}



	// 配列の上書きと解放
	void OverwriteArrayAndReleaseOldObject(Type old_object, Type new_object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(old_object);
		if (iterator != registration_map_.end())
		{
			// 配列の上書き
			array_[iterator->second] = new_object;

			// 新規オブジェクトを登録及び古いオブジェクトの削除
			registration_map_.insert(std::make_pair(new_object, iterator->second));
			registration_map_.erase(old_object);

			// 古いオブジェクトの解放
			SafeRelease::Normal(&old_object);
		}
		else
		{
			// 古いオブジェクトがないため新規扱い
			AddToArray(new_object);
		}
	}



	// 配列リセット
	void ResetArray()
	{
		// 配列からの削除
		for (unsigned i = 0; i < end_pointer_; i++)
		{
			array_[i] = nullptr;
		}

		// マップのリセット
		registration_map_.clear();

		// エンドポインタをリセット
		end_pointer_ = 0;
	}

	// 登録先の解放と配列のリセット
	void ReleaseObjectAndResetArray()
	{
		// 登録先の解放と配列からの削除
		for (unsigned i = 0; i < end_pointer_; i++)
		{
			SafeRelease::Normal(&array_[i]);
			array_[i] = nullptr;
		}

		// マップのリセット
		registration_map_.clear();

		// エンドポインタをリセット
		end_pointer_ = 0;
	}

	// 配列から削除
	void DeleteFromArray(Type object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(object);
		if (iterator == registration_map_.end()) return;

		// 配列から削除及び、登録の解除
		array_[iterator->second] = nullptr;
		registration_map_.erase(object);
	}

	// 配列のソート
	void SortArray()
	{
		int temp_num = 0;

		for (unsigned i = 0; i < end_pointer_; i++)
		{
			if (array_[i] != nullptr) continue;

			temp_num++;

			for (unsigned k = (end_pointer_ - 1); k > i; k--)
			{
				if (array_[k] == nullptr) continue;

				// オブジェクトを入れ替える
				array_[i] = array_[k];
				array_[k] = nullptr;

				// マップの更新
				registration_map_.find(array_[i])->second = i;
				break;
			}
		}

		// エンドポインタの更新
		end_pointer_ -= temp_num;
	}

	// 配列からの削除とソート
	void DeleteFromArrayAndSortArray(Type object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(object);
		if (iterator == registration_map_.end()) return;

		// 削除先が配列の末端かどうか
		if (iterator->second == (end_pointer_ - 1))
		{
			// 配列から削除
			array_[iterator->second] = nullptr;
		}
		else
		{
			// ソート
			for (unsigned i = (end_pointer_ - 1); i > iterator->second; i--)
			{
				if (array_[i] == nullptr) continue;

				// オブジェクトを入れ替える
				array_[iterator->second] = array_[i];
				array_[i] = nullptr;

				// マップの更新
				registration_map_.find(array_[iterator->second])->second = iterator->second;

				break;
			}
		}

		// マップから削除
		registration_map_.erase(object);

		// エンドポインタの更新
		end_pointer_--;
	}

	// 配列の2つのオブジェクトを並び替え
	void SortTheTwoObject(unsigned index0, unsigned index1)
	{
		// インデックスがおかしいときに止める
		assert(!((index0 < 0) || (index0 > end_pointer_ - 1)) && "不正なインデックスです(LimitedPointerArray.h)");
		assert(!((index1 < 0) || (index1 > end_pointer_ - 1)) && "不正なインデックスです(LimitedPointerArray.h)");

		// オブジェクトがnullptrの時
		assert(array_[index0] != nullptr && "配列がnullptrです(LimitedPointerArray.h)");
		assert(array_[index1] != nullptr && "配列がnullptrです(LimitedPointerArray.h)");

		// マップの更新
		unsigned temp_index = registration_map_.find(array_[index0])->second;
		registration_map_.find(array_[index0])->second = registration_map_.find(array_[index1])->second;
		registration_map_.find(array_[index1])->second = temp_index;

		// 配列の並び替え
		Type temp = array_[index0];
		array_[index0] = array_[index1];
		array_[index1] = temp;
	}

	// 配列のゲッタ
	Type GetArrayObject(unsigned index)
	{
		// インデックスがおかしいときに止める
		assert(!((index < 0) || (index > ARRAY_NUM - 1)) && "不正なインデックスです(LimitedPointerArray.h)");
		return array_[index];
	}

	// エンドポインタのゲッタ
	unsigned GetEndPointer()
	{
		return end_pointer_;
	}

	// 配列数のゲッタ
	unsigned GetArrayNum()
	{
		return ARRAY_NUM;
	}

	// 登録インデックス番号のゲッタ
	unsigned GetIndexNum(Type object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(object);

		// 登録されていないオブジェクトが来たら止める
		assert(iterator != registration_map_.end() && "登録されていないオブジェクト(LimitedPointerArray.h)");

		// インデックス番号を返す
		if (iterator != registration_map_.end())
		{
			return iterator->second;
		}
	}

	// 登録数が最大かどうか
	bool IsMax()
	{
		return ARRAY_NUM == (end_pointer_ + 1);
	}



//------------------------------------------------------------
private:
	// メンバ変数
	Type array_[ARRAY_NUM];
	unsigned end_pointer_;
	std::unordered_map<Type, unsigned> registration_map_;
};



#endif
