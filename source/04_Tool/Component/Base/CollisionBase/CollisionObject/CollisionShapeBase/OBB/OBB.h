//================================================================================
//!	@file	 OBB.h
//!	@brief	 円柱Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_OBB_H_
#define _OBB_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>
#include <Transform\AxisVector\AxisVector.h>



//************************************************************														   
//! @brief   OBBClass
//!
//! @details OBBのClass
//************************************************************
class OBB : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Vector3D position_;		//!< 座標
	Vector3D length_;		//!< 各辺の長さ
	AxisVector axis_;		//!< 軸ベクトル
	Vector3D math_vector_;	//!< 計算用ベクトル


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	OBB() : CollisionShapeBase(CollisionShapeBase::Type::OBB) {}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param[in] position 座標
	//! @param[in] length   各辺の長さ
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D length)
	{
		// 座標を設定
		position_ = position;

		// 長さを設定
		length_ = length;
	}

	// プロパティ
	Vector3D* getpPosition() { return &position_; }
	Vector3D* getpLength() { return &length_; }
	AxisVector* getpAxisVector() { return &axis_; }
	Vector3D getRightVector()
	{
		math_vector_ = *axis_.GetForawrd();
		math_vector_.AnyLengthVector(length_.x);
		return math_vector_;
	}
	Vector3D getUpVector()
	{
		math_vector_ = *axis_.GetForawrd();

		math_vector_.AnyLengthVector(length_.y);

		return math_vector_;
	}
	Vector3D getForwardVector()
	{
		math_vector_ = *axis_.GetForawrd();

		math_vector_.AnyLengthVector(length_.z);

		return math_vector_;
	}	
	Vector3D getRightVectorHalf()
	{
		return getRightVector() / 2;
	}
	Vector3D getUpVectorHalf()
	{
		return getUpVector() / 2;
	}
	Vector3D getForwardVectorHalf()
	{
		return getForwardVector() / 2;
	}
};

//======================================================================
//
// 非メンバ関数宣言
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 1次元線分と点のはみ出し部分のベクトルを求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void OverhangingPartOBB_Segment1D_Point(Vector3D* shortest_distance_vector,
											   Vector3D* obb_position,
											   Vector3D obb_vector_half,
											   Vector3D obb_axis_vector,
											   Vector3D* point)
{
	// 長さが0以上か
	float temp_length = obb_vector_half.GetLength();
	if (temp_length <= 0.0f) return;

	// 点から直線に垂線を降ろしたときの交点の位置を表す値(tとする)を算出
	Vector3D temp_vector = *point - *obb_position;
	float t = temp_vector.CreateVectorDot(obb_axis_vector) / temp_length;

	// はみ出した部分のベクトルを算出
	if (t < -1.0f)
	{
		*shortest_distance_vector += (t + 1.0f) * (obb_vector_half);
	}
	else if (t > 1.0f)
	{
		*shortest_distance_vector += (t - 1.0f) * (obb_vector_half);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ OBBと点の最短距離のベクトルを求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D ShortestDistance_OBB_Point(OBB* obb, Vector3D* point)
{
	// OBBまでの最短距離を求めるベクトル
	Vector3D temp_vector;

	// 各軸に対してはみ出し部分を算出
	OverhangingPartOBB_Segment1D_Point(&temp_vector,
									   obb->getpPosition(),
									   obb->getForwardVectorHalf(),
									   *obb->getpAxisVector()->GetForawrd(),
									   point);

	OverhangingPartOBB_Segment1D_Point(&temp_vector,
									   obb->getpPosition(),
									   obb->getUpVectorHalf(),
									   *obb->getpAxisVector()->GetUp(),
									   point);

	OverhangingPartOBB_Segment1D_Point(&temp_vector,
									   obb->getpPosition(),
									   obb->getRightVectorHalf(),
									   *obb->getpAxisVector()->GetRight(),
									   point);
	return temp_vector;
}



#endif