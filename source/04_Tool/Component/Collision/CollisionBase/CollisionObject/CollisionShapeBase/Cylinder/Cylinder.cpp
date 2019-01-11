//================================================================================
//!	@file	 Cylinder.cpp
//!	@brief	 円柱Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "Cylinder.h"



//****************************************
// プロパティ定義
//****************************************
LineSegment* Cylinder::getpLineSegment()
{ 
	return &line_segment_; 
}



Vector3D* Cylinder::getpPosition()
{
	return line_segment_.getpPosition(); 
}



Vector3D* Cylinder::getpVector()
{ 
	return line_segment_.getpVector();
}



Vector3D Cylinder::getAddVectorToPosition()
{ 
	return line_segment_.getAddVectorToPosition(); 
}



float Cylinder::getRadius()
{ 
	return radius_;
}



void Cylinder::setRadius(float value)
{ 
	radius_ = value; 
}



//****************************************
// 関数定義
//****************************************
Cylinder::Cylinder() 
	: CollisionShapeBase(CollisionShapeBase::Type::CYLINDER) 
{
}



void Cylinder::Init(Vector3D position, Vector3D vector, float radius)
{
	// 線分
	line_segment_.Init(position, vector);

	// 半径
	radius_ = radius;
}