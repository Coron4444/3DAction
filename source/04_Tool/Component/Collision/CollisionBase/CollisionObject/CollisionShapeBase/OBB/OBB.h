//================================================================================
//!	@file	 OBB.h
//!	@brief	 OBBClass
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
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 座標
	//----------------------------------------
	Vector3D* getpPosition();

	//----------------------------------------
	//! @brief 各辺の取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 各辺の長さ
	//----------------------------------------
	Vector3D* getpLength();

	//----------------------------------------
	//! @brief 軸ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 軸ベクトル
	//----------------------------------------
	AxisVector* getpAxisVector();

	//----------------------------------------
	//! @brief 右ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 右ベクトル
	//----------------------------------------
	Vector3D getRightVector();

	//----------------------------------------
	//! @brief 上ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 上ベクトル
	//----------------------------------------
	Vector3D getUpVector();

	//----------------------------------------
	//! @brief 前ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 前ベクトル
	//----------------------------------------
	Vector3D getForwardVector();

	//----------------------------------------
	//! @brief 右ベクトルの半分取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 右ベクトルの半分
	//----------------------------------------
	Vector3D getRightVectorHalf();

	//----------------------------------------
	//! @brief 上ベクトルの半分取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 上ベクトルの半分
	//----------------------------------------
	Vector3D getUpVectorHalf();

	//----------------------------------------
	//! @brief 前ベクトルの半分取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 前ベクトルの半分
	//----------------------------------------
	Vector3D getForwardVectorHalf();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	OBB();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param position 座標
	//! @param length   各辺の長さ
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D length);
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