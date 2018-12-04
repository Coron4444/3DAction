//================================================================================
//!	@file	 CollisionBase.h
//!	@brief	 衝突BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COLLISION_BASE_H_
#define _COLLISION_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "../ComponentBase/ComponentBase.h"
#include "CollisionObjects/CollisionObjects.h"

#include <LimitedPointerArray/LimitedPointerArray.h>
#include <Transform/Transform.h>
#include <Vector3D.h>



//************************************************************														   
//! @brief   衝突BaseClass
//!
//! @details 衝突のBaseClass
//************************************************************
class CollisionBase : public ComponentBase
{
//====================
// 列挙型定義
//====================
public:
	// ステート
	enum State
	{
		NONE = -1,
		PLAYER,
		COIN,
		ENEMY,
		GOAL,
		MAX
	};


//====================
// 定数
//====================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< 配列数


//====================
// 変数
//====================
private:
	LimitedPointerArray<CollisionObjects*, ARRAY_NUM> collision_objects_;	//!< 複数衝突オブジェクト配列
	State state_ = State::NONE;			//!< ステート
	bool is_judgment_ground_ = true;	//!< 地面との判定フラグ


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @param void なし
	//----------------------------------------
	virtual ~CollisionBase() {}

	//----------------------------------------
	//! @brief 衝突時関数
	//! @param[in, out] hit_collision 相手の衝突基底クラス
	//! @param[in, out] hit_object    相手の衝突オブジェクト
	//! @param[in, out] hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject* hit_object,
							  CollisionObject* hit_my_object) = 0;

	//----------------------------------------
	//! @brief 非衝突時関数
	//! @param[in, out] hit_collision 相手の衝突基底クラス
	//! @param[in, out] hit_object    相手の衝突オブジェクト
	//! @param[in, out] hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject* hit_object,
								 CollisionObject* hit_my_object) = 0;

	//----------------------------------------
	//! @brief フィールドとの衝突時関数
	//! @param[in] position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	virtual void HitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief フィールドとの非衝突時関数
	//! @param[in] position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	virtual void NotHitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief 複数衝突オブジェクト追加関数
	//! @param[in] object 追加したい複数衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void AddCollisionObjectsToArray(CollisionObjects* object)
	{
		collision_objects_.AddToArray(object);
	}

	//----------------------------------------
	//! @brief 複数衝突オブジェクト上書き関数
	//! @param[in] object 古い複数衝突オブジェクト
	//! @param[in] object 新しい複数衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void OverwriteArrayCollisionsObject(CollisionObjects* old_object,
										CollisionObjects* new_object)
	{
		old_object->ReleaseAllCollisionObjectFromArray();
		collision_objects_.OverwriteArray(old_object, new_object);
	}

	//----------------------------------------
	//! @brief 複数衝突オブジェクト解放関数
	//! @param[in] object 消去したい複数衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void ReleaseCollisionObjectsFromArray(CollisionObjects* object)
	{
		object->ReleaseAllCollisionObjectFromArray();
		collision_objects_.DeleteFromArrayAndSortArray(object);
	}

	//----------------------------------------
	//! @brief 複数衝突オブジェクト全解放関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseAllCollisionObjectsFromArray()
	{
		for (unsigned i = 0; i < collision_objects_.GetEndPointer(); i++)
		{
			collision_objects_.GetArrayObject(i)
				->ReleaseAllCollisionObjectFromArray();
		}
		collision_objects_.ReleaseObjectAndResetArray();
	}

	//----------------------------------------
	//! @brief めり込み解消関数
	//! @param[in, out] transform  めり込みを解消したい状態
	//! @param[in]      hit_vector めり込みベクトル
	//! @retval void なし
	//----------------------------------------
	void EliminationOfNesting(Transform* transform, const Vec3* hit_vector)
	{
		*transform->GetPosition() += *hit_vector;
		transform->UpdateWorldMatrixISRT();
	}

	// プロパティ
	unsigned getEndIndexOfArray() { return collision_objects_.GetEndPointer(); }
	CollisionObjects* getpCollisionObjects(unsigned index) { return collision_objects_.GetArrayObject(index); }
	State getState() { return state_; }
	void setState(State value) { state_ = value; }
	bool getIsJudgmentGround() { return is_judgment_ground_; }
	void setIsJudgmentGround(bool value) { is_judgment_ground_ = value; }
};



#endif