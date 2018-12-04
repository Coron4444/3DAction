//================================================================================
//!	@file	 Cylinder.h
//!	@brief	 円柱Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_CYLINDER_H_
#define _CYLINDER_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"
#include "../LineSegment/LineSegment.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   円柱Class
//!
//! @details 円柱のClass
//************************************************************
class Cylinder : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	LineSegment line_segment_;	//!< 線分
	float radius_;				//!< 半径


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	Cylinder() : CollisionShapeBase(CollisionShapeBase::Type::CYLINDER) {}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param[in] position 始点座標
	//! @param[in] vector   方向
	//! @param[in] radius   半径
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector, float radius)
	{
		// 線分
		line_segment_.Init(position, vector);

		// 半径
		radius_ = radius;
	}

	// プロパティ
	LineSegment* getpLineSegment() { return &line_segment_; }
	Vector3D* getpPosition() { return line_segment_.getpPosition(); }
	Vector3D* getpVector() { return line_segment_.getpVector(); }
	Vector3D getAddVectorToPosition() { return line_segment_.getAddVectorToPosition(); }
	float getRadius() { return radius_; }
	void setRadius(float value) { radius_ = value; }
};



#endif