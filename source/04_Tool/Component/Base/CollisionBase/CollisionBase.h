//================================================================================
//
//    衝突基底クラス
//    Author : Araki Kai                                作成日 : 2018/04/17
//
//================================================================================

#ifndef	_COLLISION_BASE_H_
#define _COLLISION_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "../ComponentBase/ComponentBase.h"
#include "CollisionObject\CollisionObject.h"

#include <LimitedPointerArray\LimitedPointerArray.h>
#include <Transform\Transform.h>

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



/*********************************************************//**
* @brief
* 衝突基底クラス
*
* 衝突の基底クラス
*************************************************************/
class CollisionBase : public ComponentBase
{
//==============================
// 定数
//==============================
private:
	static const unsigned ARRAY_NUM = 100;		//!< 配列数


//==============================
// 列挙型定義
//==============================
public:
	// ステート
	enum State
	{
		NONE = -1,
		PLAYER,
		COIN,
		ENEMY,
		MAX
	};


//==============================
// 非静的メンバ変数
//==============================
private:
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> all_collision_object_;	//!< 全衝突オブジェクト配列

	State state_;	//!< ステート

	bool is_judgment_;			//!< 判定フラグ
	bool is_judgment_ground_;	//!< 地面との判定フラグ


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* コンストラクタ
	*/
	CollisionBase(State state)
		: state_(state),
		is_judgment_(true),
		is_judgment_ground_(true)
	{
	}

	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~CollisionBase() {}

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit() = 0;

	/**
	* @brief
	* 更新関数
	*/
	virtual void Update() = 0;

	/**
	* @brief
	* デバッグ表示関数
	*/
	virtual void DebugDisplay() = 0;

	/**
	* @brief
	* 衝突時関数
	* @param
	* hit_collision : 相手の衝突基底クラス
	* hit_object :相手の衝突オブジェクト
	* hit_my_object : 自分の衝突オブジェクト
	*/
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject*  hit_object,
							  CollisionObject*  hit_my_object) = 0;

	/**
	* @brief
	* 非衝突時関数
	* @param
	* hit_collision : 相手の衝突基底クラス
	* hit_object :相手の衝突オブジェクト
	* hit_my_object : 自分の衝突オブジェクト
	*/
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject*  hit_object,
								 CollisionObject*  hit_my_object) = 0;

	/**
	* @brief
	* フィールドとの衝突時関数
	*/
	virtual void HitGround(float position_y) = 0;

	/**
	* @brief
	* フィールドとの非衝突時関数
	*/
	virtual void NotHitGround(float position_y) = 0;

	/**
	* @brief
	* 衝突オブジェクト追加関数
	*/
	void AddCollisionObjectToArray(CollisionObject* object)
	{
		all_collision_object_.AddToArray(object);
	}

	/**
	* @brief
	* 衝突オブジェクト上書き関数
	*/
	void OverwriteArrayCollisionObject(CollisionObject* old_object,
									   CollisionObject* new_object)
	{
		all_collision_object_.OverwriteArray(old_object, new_object);
	}

	/**
	* @brief
	* 衝突オブジェクト解放関数
	*/
	void ReleaseCollisionObjectFromArray(CollisionObject* object)
	{
		all_collision_object_.DeleteFromArrayAndSortArray(object);
	}

	/**
	* @brief
	* 衝突オブジェクト全解放関数
	*/
	void ReleaseAllCollisionObjectFromArray()
	{
		all_collision_object_.ReleaseObjectAndResetArray();
	}

	/**
	* @brief
	* 全ての衝突用データのリセット関数
	*/
	void ResetHitDataAllCollisionObject()
	{
		for (unsigned i = 0; i < all_collision_object_.GetEndPointer(); i++)
		{
			all_collision_object_.GetArrayObject(i)->ResetHitData();
		}
	}

	/**
	* @brief
	* めり込み解消関数
	*/
	void EliminationOfNesting(Transform* transform, const Vec3* hit_vector)
	{
		*transform->GetPosition() += *hit_vector;
		transform->UpdateWorldMatrixISRT();
	}

	// プロパティ
	unsigned GetEndIndexOfArray() { return all_collision_object_.GetEndPointer(); }
	CollisionObject* GetCollisionObject(unsigned index) { return all_collision_object_.GetArrayObject(index); }
	State GetState() { return state_; }
	bool GetIsJudgment() { return is_judgment_; }
	void SetIsJudgment(bool value) { is_judgment_ = value; }
	bool GetIsJudgmentGround() { return is_judgment_; }
	void SetIsJudgmentGround(bool value) { is_judgment_ = value; }
};



#endif