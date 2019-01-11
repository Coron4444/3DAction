//================================================================================
//!	@file	 Sphere.cpp
//!	@brief	 球Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "Sphere.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* Sphere::getpPosition() 
{
	return &position_; 
}



float Sphere::getRadius()
{ 
	return radius_; 
}



void Sphere::setRadius(float value)
{ 
	radius_ = value;
}



//****************************************
// 関数定義
//****************************************
Sphere::Sphere()
	: CollisionShapeBase(CollisionShapeBase::Type::SPHERE)
{
}



void Sphere::Init(Vector3D position, float radius)
{
	// 座標
	position_ = position;

	// 半径
	radius_ = radius;
}