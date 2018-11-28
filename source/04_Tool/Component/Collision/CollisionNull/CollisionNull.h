//================================================================================
//
//    空白衝突クラス
//    Author : Araki Kai                                作成日 : 2018/03/22
//
//================================================================================

#ifndef	_COLLISION_NULL_H_
#define _COLLISION_NULL_H_



//****************************************
// インクルード文
//****************************************
#include <assert.h>
#include "../../Base/CollisionBase/CollisionBase.h"



/*********************************************************//**
* @brief
* 空白衝突クラス
*
* 衝突の空白クラス
*************************************************************/
class CollisionNull : public CollisionBase
{
//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~CollisionNull() 
	{
		ReleaseAllCollisionObjectsFromArray();
	}

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit() override
	{
		// 複数衝突オブジェクトの判定OFF
		for (unsigned i = 0; i < getEndIndexOfArray(); i++)
		{
			getCollisionObjects(i)->setIsJudgment(false);
		}
	}

	/**
	* @brief
	* 更新関数
	*/
	virtual void Update() {}

	/**
	* @brief
	* デバッグ表示関数
	*/
	virtual void DebugDisplay() {}

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
							  CollisionObject*  hit_my_object)
	{
		// 使われていない引数の処理
		hit_collision = hit_collision;
		hit_object = hit_object;
		hit_my_object = hit_my_object;
	}

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
								 CollisionObject*  hit_my_object)
	{
		// 使われていない引数の処理
		hit_collision = hit_collision;
		hit_object = hit_object;
		hit_my_object = hit_my_object;
	}

	/**
	* @brief
	* フィールドとの衝突時関数
	*/
	virtual void HitGround(float position_y) { position_y = position_y; }

	/**
	* @brief
	* フィールドとの非衝突時関数
	*/
	virtual void NotHitGround(float position_y) { position_y = position_y; }
};



#endif