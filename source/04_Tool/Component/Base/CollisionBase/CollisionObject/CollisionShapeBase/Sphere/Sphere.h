//================================================================================
//!	@file	 Sphere.h
//!	@brief	 球Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_SPHERE_H_
#define _SPHERE_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   球Class
//!
//! @details 球のClass
//************************************************************
class Sphere : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Vector3D position_;		//!< 座標
	float radius_;			//!< 半径


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	Sphere() : CollisionShapeBase(CollisionShapeBase::Type::SPHERE) {}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param[in] position 始点座標
	//! @param[in] radius   半径
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, float radius)
	{
		// 座標
		position_ = position;

		// 半径
		radius_ = radius;
	}

	// プロパティ
	Vector3D* getpPosition() { return &position_; }
	float getRadius() { return radius_; }
	void setRadius(float value) { radius_ = value; }
};



#endif