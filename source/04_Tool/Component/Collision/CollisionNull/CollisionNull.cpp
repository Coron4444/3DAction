//================================================================================
//!	@file	 Collision.cpp
//!	@brief	 空白衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "CollisionNull.h"



//****************************************
// 関数定義
//****************************************
CollisionNull::~CollisionNull()
{
	ReleaseAllCollisionObjectsFromArray();
}



void CollisionNull::Init()
{
}



void CollisionNull::Uninit()
{
	// 複数衝突オブジェクトの判定OFF
	for (unsigned i = 0; i < getEndIndexOfArray(); i++)
	{
		getpCollisionObjects(i)->setIsJudgment(false);
	}
}



void CollisionNull::Update()
{
}



void CollisionNull::DebugDisplay()
{
}



void CollisionNull::HitCollision(CollisionBase* hit_collision,
								 CollisionObject*  hit_object,
								 CollisionObject*  hit_my_object)
{
	// 使われていない引数の処理
	hit_collision = hit_collision;
	hit_object = hit_object;
	hit_my_object = hit_my_object;
}



void CollisionNull::NotHitCollision(CollisionBase*	hit_collision,
					 CollisionObject*  hit_object,
					 CollisionObject*  hit_my_object)
{
	// 使われていない引数の処理
	hit_collision = hit_collision;
	hit_object = hit_object;
	hit_my_object = hit_my_object;
}



void CollisionNull::HitGround(float position_y) 
{
	position_y = position_y; 
}



void CollisionNull::NotHitGround(float position_y)
{
	position_y = position_y; 
}