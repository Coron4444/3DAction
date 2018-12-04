//================================================================================
//!	@file	 Triangle.h
//!	@brief	 三角形Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_TRIANGLE_H_
#define _TRIANGLE_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"
#include "../Plane/Plane.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   三角形Class
//!
//! @details 三角形のClass
//************************************************************
class Triangle : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Vector3D point0_;		//!< 点
	Vector3D point1_;		//!< 点
	Vector3D point2_;		//!< 点
	Plane plane_;			//!< 平面


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	Triangle() : CollisionShapeBase(CollisionShapeBase::Type::TRIANGLE) {}
	
	//----------------------------------------
	//! @brief 初期化関数
	//! @param[in] point0 点
	//! @param[in] point0 点
	//! @param[in] point0 点
	//! @retval void なし
	//----------------------------------------
	void Init(Vec3 point0, Vec3 point1, Vec3 point2)
	{
		// 3点
		point0_ = point0;
		point1_ = point1;
		point2_ = point2;

		// 平面
		plane_.Init(point0, point1, point2);
	}

	// プロパティ
	Vector3D* getpPoint0() { return &point0_; }
	Vector3D* getpPoint1() { return &point1_; }
	Vector3D* getpPoint2() { return &point2_; }
	Plane* getpPlane() { return &plane_; }
};



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 点が三角平面に含まれているかどうか ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CheckInnerPoint(Triangle* triangle, Vec3* point)
{
	// 任意の点から各頂点へのベクトルを算出
	Vector3D vector0 = *triangle->getpPoint0() - *point;
	Vector3D vector1 = *triangle->getpPoint1() - *point;
	Vector3D vector2 = *triangle->getpPoint2() - *point;


	// 3角形の辺をなぞるベクトルを算出
	Vector3D edge_vector0 = *triangle->getpPoint0() - *triangle->getpPoint1();
	Vector3D edge_vector1 = *triangle->getpPoint1() - *triangle->getpPoint2();
	Vector3D edge_vector2 = *triangle->getpPoint2() - *triangle->getpPoint0();


	// 外積の算出
	Vector3D Cross_vector0 = vector0.CreateVectorCross(edge_vector0);
	Vector3D Cross_vector1 = vector1.CreateVectorCross(edge_vector1);
	Vector3D Cross_vector2 = vector2.CreateVectorCross(edge_vector2);

	int zero_vector = 0;

	if (Cross_vector0.GetLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (Cross_vector1.GetLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (Cross_vector2.GetLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (zero_vector >= 2)
	{
		return true;
	}
	else if (zero_vector == 1)
	{
		float dot0 = 0.0f;

		if (Cross_vector0.GetLengthSquare() == 0.0f)
		{
			// 外積の向きがそろっているかのチェック
			dot0 = Cross_vector1.CreateVectorDot(Cross_vector2);
		}
		if (Cross_vector1.GetLengthSquare() == 0.0f)
		{
			// 外積の向きがそろっているかのチェック
			dot0 = Cross_vector0.CreateVectorDot(Cross_vector2);
		}
		if (Cross_vector2.GetLengthSquare() == 0.0f)
		{
			// 外積の向きがそろっているかのチェック
			dot0 = Cross_vector0.CreateVectorDot(Cross_vector1);
		}

		bool is_same_direction = dot0 > 0.0f;

		if (is_same_direction) return true;
	}
	else
	{
		// 外積の向きがそろっているかのチェック
		float dot0 = Cross_vector0.CreateVectorDot(Cross_vector1);
		float dot1 = Cross_vector1.CreateVectorDot(Cross_vector2);
		float dot2 = Cross_vector0.CreateVectorDot(Cross_vector2);

		bool is_same_direction0 = (dot0 * dot1) > 0.0f;
		bool is_same_direction1 = (dot0 * dot2) > 0.0f;
		bool is_same_direction2 = (dot1 * dot2) > 0.0f;

		int  same_count = 0;
		if (is_same_direction0 == is_same_direction1) same_count++;
		if (is_same_direction0 == is_same_direction2) same_count++;
		if (is_same_direction1 == is_same_direction2) same_count++;

		if (same_count == 3) return true;
	}

	return false;
}



#endif