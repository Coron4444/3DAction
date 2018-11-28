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
#include "CollisionObjects/CollisionObjects.h"

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
	static const unsigned ARRAY_NUM = 10000;		//!< 配列数


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
		GOAL,
		MAX
	};


//==============================
// 非静的メンバ変数
//==============================
private:
	LimitedPointerArray<CollisionObjects*, ARRAY_NUM> collision_objects_;	//!< 複数衝突オブジェクト配列
	State state_ = State::NONE;			//!< ステート
	bool is_judgment_ground_ = true;	//!< 地面との判定フラグ


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~CollisionBase() {}

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
							  CollisionObject* hit_object,
							  CollisionObject* hit_my_object) = 0;

	/**
	* @brief
	* 非衝突時関数
	* @param
	* hit_collision : 相手の衝突基底クラス
	* hit_object :相手の衝突オブジェクト
	* hit_my_object : 自分の衝突オブジェクト
	*/
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject* hit_object,
								 CollisionObject* hit_my_object) = 0;

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
	* 複数衝突オブジェクト追加関数
	*/
	void AddCollisionObjectsToArray(CollisionObjects* object)
	{
		collision_objects_.AddToArray(object);
	}

	/**
	* @brief
	* 複数衝突オブジェクト上書き関数
	*/
	void OverwriteArrayCollisionsObject(CollisionObjects* old_object,
										CollisionObjects* new_object)
	{
		old_object->ReleaseAllCollisionObjectFromArray();
		collision_objects_.OverwriteArray(old_object, new_object);
	}

	/**
	* @brief
	* 複数衝突オブジェクト解放関数
	*/
	void ReleaseCollisionObjectsFromArray(CollisionObjects* object)
	{
		object->ReleaseAllCollisionObjectFromArray();
		collision_objects_.DeleteFromArrayAndSortArray(object);
	}

	/**
	* @brief
	* 複数衝突オブジェクト全解放関数
	*/
	void ReleaseAllCollisionObjectsFromArray()
	{
		for (unsigned i = 0; i < collision_objects_.GetEndPointer(); i++)
		{
			collision_objects_.GetArrayObject(i)
				->ReleaseAllCollisionObjectFromArray();
		}
		collision_objects_.ReleaseObjectAndResetArray();
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
	unsigned getEndIndexOfArray() { return collision_objects_.GetEndPointer(); }
	CollisionObjects* getCollisionObjects(unsigned index) { return collision_objects_.GetArrayObject(index); }
	State getState() { return state_; }
	void setState(State value) { state_ = value; }
	bool getIsJudgmentGround() { return is_judgment_ground_; }
	void setIsJudgmentGround(bool value) { is_judgment_ground_ = value; }
};



#endif