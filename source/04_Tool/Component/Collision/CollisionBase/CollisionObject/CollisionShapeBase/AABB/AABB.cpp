//================================================================================
//!	@file	 AABB.cpp
//!	@brief	 AABBClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "AABB.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* AABB::getpPositon()
{ 
	return &position_; 
}



Vector3D* AABB::getpLength()
{ 
	return &length_; 
}



void AABB::setLength(Vector3D value)
{ 
	length_ = value; 
};



Vector3D* AABB::getpMin()
{ 
	return &min_; 
}



Vector3D* AABB::getpMax()
{ 
	return &max_; 
}



//****************************************
// 関数定義
//****************************************
AABB::AABB() 
	: CollisionShapeBase(CollisionShapeBase::Type::AABB) 
{
}



void AABB::Init(Vector3D position, Vector3D length)
{
	// 座標を設定
	position_ = position;

	// 長さを設定
	length_ = length;

	// 最小値と最大値
	UpdateMinAndMax();
}



void AABB::Update()
{
	// 最小値と最大値
	UpdateMinAndMax();
}



void AABB::UpdateMinAndMax()
{
	min_ = position_ - length_;
	max_ = position_ + length_;
}