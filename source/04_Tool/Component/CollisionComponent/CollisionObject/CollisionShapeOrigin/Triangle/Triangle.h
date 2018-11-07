//================================================================================
//
//    三角形クラス
//    Author : Araki Kai                                作成日 : 2017/11/28
//
//================================================================================

#ifndef	_TRIANGLE_H_
#define _TRIANGLE_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../CollisionShapeOrigin.h"
#include "../Plane/Plane.h"

#include <Vector3D.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Triangle : public CollisionShapeOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 3点引数コンストラクタ
	Triangle(Vec3 point0 = Vec3(0.0f, 0.0f, 0.0f), Vec3 point1 = Vec3(0.0f, 0.0f, 0.0f), Vec3 point2 = Vec3(0.0f, 0.0f, 0.0f));


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	virtual ~Triangle();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数	
	bool CheckInnerPoint( Vec3 point ) const;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ変数
	Vector3D point_[3];
	Plane    plane_;
};





//======================================================================
//
// 非静的メンバ関数定義( inline )
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 3点引数コンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Triangle::Triangle(Vec3 point0, Vec3 point1, Vec3 point2)
	: CollisionShapeOrigin(CollisionShapeOrigin::Type::TYPE_TRIANGLE),
	  plane_(point0, point1, point2)
{
	point_[0] = point0;
	point_[1] = point1;
	point_[2] = point2;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Triangle::~Triangle() 
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool Triangle::CheckInnerPoint( Vec3 point ) const
{
	// 任意の点から各頂点へのベクトルを算出
	Vector3D vector0 = point_[0] - point;
	Vector3D vector1 = point_[1] - point;
	Vector3D vector2 = point_[2] - point;


	// 3角形の辺をなぞるベクトルを算出
	Vector3D edge_vector0 = point_[0] - point_[1];
	Vector3D edge_vector1 = point_[1] - point_[2];
	Vector3D edge_vector2 = point_[2] - point_[0];


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