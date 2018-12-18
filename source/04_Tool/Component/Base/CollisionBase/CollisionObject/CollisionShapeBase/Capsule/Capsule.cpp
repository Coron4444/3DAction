//================================================================================
//!	@file	 Capsule.h
//!	@brief	 カプセルClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "Capsule.h"



//****************************************
// プロパティ定義
//****************************************
Sphere* Capsule::getpSphere0() 
{ 
	return &sphere0_;
}



Sphere* Capsule::getpSphere1() 
{ 
	return &sphere1_; 
}



Cylinder* Capsule::getpCylinder() 
{
	return &cylinder_;
}



LineSegment* Capsule::getpLineSegment()
{ 
	return cylinder_.getpLineSegment();
}



Vector3D* Capsule::getpPosition() 
{
	return cylinder_.getpPosition();
}



Vector3D* Capsule::getpVector()
{ 
	return cylinder_.getpVector();
}



Vector3D Capsule::getAddVectorToPosition() 
{
	return cylinder_.getAddVectorToPosition(); 
}



float Capsule::getRadius() 
{ 
	return cylinder_.getRadius(); 
}



void Capsule::setRadius(float value) 
{ 
	cylinder_.setRadius(value); 
}



//****************************************
// 関数定義
//****************************************
Capsule::Capsule()
	: CollisionShapeBase(CollisionShapeBase::Type::CAPSULE)
{
}



void Capsule::Init(Vector3D position, Vector3D vector, float radius)
{
	// 円柱
	cylinder_.Init(position, vector, radius);

	// 球
	sphere0_.Init(*cylinder_.getpPosition(), radius);
	sphere1_.Init(cylinder_.getAddVectorToPosition(), radius);
}



void Capsule::Update()
{
	// 球
	*sphere0_.getpPosition() = *cylinder_.getpPosition();
	sphere0_.setRadius(cylinder_.getRadius());
	*sphere1_.getpPosition() = cylinder_.getAddVectorToPosition();
	sphere1_.setRadius(cylinder_.getRadius());
}