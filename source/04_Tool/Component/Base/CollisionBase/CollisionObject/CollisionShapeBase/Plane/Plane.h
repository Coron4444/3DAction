//================================================================================
//!	@file	 Plane.h
//!	@brief	 平面Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_PLANE_H_
#define _PLANE_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   平面Class
//!
//! @details 平面のClass
//************************************************************
class Plane : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Vector3D normal_;		//!< 法線
	float    adjustmet_d_;	//!< D成分


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	Plane() : CollisionShapeBase(CollisionShapeBase::Type::PLANE) {}

	//----------------------------------------
	//! @brief 初期化関数(法線と1点)
	//! @param[in] normal 法線
	//! @param[in] point  点
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D normal, Vector3D point)
	{
		// 法線
		normal_ = normal;
		normal_.CreateNormalize();

		// D成分
		adjustmet_d_ = -((normal_.x * point.x) + (normal_.y * point.y) + (normal_.z * point.z));
	}

	//----------------------------------------
	//! @brief 初期化関数(3点)
	//! @param[in] point0 点
	//! @param[in] point1 点
	//! @param[in] point2 点
	//! @retval void なし
	//----------------------------------------
	void Init(Vec3 point0, Vec3 point1, Vec3 point2)
	{
		// 法線の作成
		Vec3 temp_normal_vector = Point3_Cross(point0, point1, point2);

		// 初期化
		Init(temp_normal_vector, point0);
	}



	// プロパティ
	Vector3D* getpNormal() { return &normal_; }
	float getAdjustmetD() { return adjustmet_d_; }

};



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 平面と座標との長さ関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Length_Point(Plane* plane, Vec3* point)
{
	return (plane->getpNormal()->x * point->x) 
		+ (plane->getpNormal()->y * point->y) 
		+ (plane->getpNormal()->z * point->z) + plane->getAdjustmetD();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 座標が平面の表側にあるか判定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool IsFrontSide_Point(Plane* plane, Vec3* point)
{
	if (Length_Point(plane, point) < 0.0f) return false;

	return true;
}



#endif