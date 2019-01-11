//================================================================================
//!	@file	 Plane.cpp
//!	@brief	 平面Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "Plane.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* Plane::getpNormal()
{ 
	return &normal_; 
}



float Plane::getAdjustmetD()
{ 
	return adjustmet_d_; 
}



//****************************************
// 関数定義
//****************************************
Plane::Plane()
	: CollisionShapeBase(CollisionShapeBase::Type::PLANE)
{
}



void Plane::Init(Vector3D normal, Vector3D point)
{
	// 法線
	normal_ = normal;
	normal_.CreateNormalize();

	// D成分
	adjustmet_d_ = -((normal_.x * point.x) + (normal_.y * point.y) 
					 + (normal_.z * point.z));
}



void Plane::Init(Vec3 point0, Vec3 point1, Vec3 point2)
{
	// 法線の作成
	Vec3 temp_normal_vector = Point3_Cross(point0, point1, point2);

	// 初期化
	Init(temp_normal_vector, point0);
}