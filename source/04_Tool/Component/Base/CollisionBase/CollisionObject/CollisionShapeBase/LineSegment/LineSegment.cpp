//================================================================================
//!	@file	 LineSegment.cpp
//!	@brief	 線分Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "LineSegment.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* LineSegment::getpPosition()
{
	return &position_; 
}



Vector3D* LineSegment::getpVector()
{
	return &vector_; 
}



Vector3D LineSegment::getAddVectorToPosition()
{ 
	return position_ + vector_; 
}



float LineSegment::getSlopeOf2DLineSegment()
{ 
	return vector_.y / vector_.x;
}



//****************************************
// 関数定義
//****************************************
LineSegment::LineSegment() 
	: CollisionShapeBase(CollisionShapeBase::Type::LINE_SEGMENT) 
{
}



void LineSegment::Init(Vector3D position, Vector3D vector)
{
	position_ = position;
	vector_ = vector;
}