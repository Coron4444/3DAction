//================================================================================
//!	@file	 Collision.h
//!	@brief	 空白衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COLLISION_NULL_H_
#define _COLLISION_NULL_H_



//****************************************
// インクルード文
//****************************************
#include "../../Base/CollisionBase/CollisionBase.h"



//************************************************************														   
//! @brief   空白衝突Class
//!
//! @details 衝突の空白Class
//************************************************************
class CollisionNull : public CollisionBase
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デストラクタ
	//! @param void なし
	//----------------------------------------
	virtual ~CollisionNull() 
	{
		ReleaseAllCollisionObjectsFromArray();
	}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Init() override {}

	//----------------------------------------
	//! @brief 終了関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() override
	{
		// 複数衝突オブジェクトの判定OFF
		for (unsigned i = 0; i < getEndIndexOfArray(); i++)
		{
			getpCollisionObjects(i)->setIsJudgment(false);
		}
	}

	//----------------------------------------
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Update() {}

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void DebugDisplay() {}

	//----------------------------------------
	//! @brief 衝突時関数
	//! @param[in, out] hit_collision 相手の衝突基底クラス
	//! @param[in, out] hit_object    相手の衝突オブジェクト
	//! @param[in, out] hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject*  hit_object,
							  CollisionObject*  hit_my_object)
	{
		// 使われていない引数の処理
		hit_collision = hit_collision;
		hit_object = hit_object;
		hit_my_object = hit_my_object;
	}

	//----------------------------------------
	//! @brief 非衝突時関数
	//! @param[in, out] hit_collision 相手の衝突基底クラス
	//! @param[in, out] hit_object    相手の衝突オブジェクト
	//! @param[in, out] hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject*  hit_object,
								 CollisionObject*  hit_my_object)
	{
		// 使われていない引数の処理
		hit_collision = hit_collision;
		hit_object = hit_object;
		hit_my_object = hit_my_object;
	}

	//----------------------------------------
	//! @brief フィールドとの衝突時関数
	//! @param[in] position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	virtual void HitGround(float position_y) { position_y = position_y; }

	//----------------------------------------
	//! @brief フィールドとの非衝突時関数
	//! @param[in] position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	virtual void NotHitGround(float position_y) { position_y = position_y; }
};



#endif