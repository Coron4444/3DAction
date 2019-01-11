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
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 法線取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 法線
	//----------------------------------------
	Vector3D* getpNormal();

	//----------------------------------------
	//! @brief D成分取得関数
	//! @details
	//! @param void なし
	//! @retval float D成分
	//----------------------------------------
	float getAdjustmetD();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	Plane();

	//----------------------------------------
	//! @brief 初期化関数(法線と1点)
	//! @details
	//! @param normal 法線
	//! @param point  点
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D normal, Vector3D point);

	//----------------------------------------
	//! @brief 初期化関数(3点)
	//! @details
	//! @param point0 点
	//! @param point1 点
	//! @param point2 点
	//! @retval void なし
	//----------------------------------------
	void Init(Vec3 point0, Vec3 point1, Vec3 point2);
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