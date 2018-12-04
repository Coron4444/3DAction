//================================================================================
//!	@file	 Capsule.h
//!	@brief	 カプセルClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_CAPSULE_H_
#define _CAPSULE_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"
#include "../Cylinder/Cylinder.h"
#include "../Sphere/Sphere.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   カプセルClass
//!
//! @details カプセルのClass
//************************************************************
class Capsule : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Cylinder cylinder_;		//!< 円柱
	Sphere sphere0_;		//!< 球
	Sphere sphere1_;		//!< 球


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	Capsule() : CollisionShapeBase(CollisionShapeBase::Type::CAPSULE) {}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param[in] position 始点座標
	//! @param[in] vector   方向
	//! @param[in] radius   半径
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector, float radius)
	{
		// 円柱
		cylinder_.Init(position, vector, radius);

		// 球
		sphere0_.Init(*cylinder_.getpPosition(), radius);
		sphere1_.Init(cylinder_.getAddVectorToPosition(), radius);
	}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update()
	{
		// 球
		*sphere0_.getpPosition() = *cylinder_.getpPosition();
		sphere0_.setRadius(cylinder_.getRadius());
		*sphere1_.getpPosition() = cylinder_.getAddVectorToPosition();
		sphere1_.setRadius(cylinder_.getRadius());
	}

	// プロパティ
	Sphere* getpSphere0() { return &sphere0_; }
	Sphere* getpSphere1() { return &sphere1_; }
	Cylinder* getpCylinder() { return &cylinder_; }
	LineSegment* getpLineSegment() { return cylinder_.getpLineSegment(); }
	Vector3D* getpPosition() { return cylinder_.getpPosition(); }
	Vector3D* getpVector() { return cylinder_.getpVector(); }
	Vector3D getAddVectorToPosition() { return cylinder_.getAddVectorToPosition(); }
	float getRadius() { return cylinder_.getRadius(); }
	void setRadius(float value) { cylinder_.setRadius(value); }
};



#endif