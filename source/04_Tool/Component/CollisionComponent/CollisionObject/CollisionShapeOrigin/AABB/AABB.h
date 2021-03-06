//================================================================================
//
//    AABBクラス
//    Author : Araki Kai                                作成日 : 2017/11/27
//
//================================================================================

#ifndef	_AABB_H_
#define _AABB_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../CollisionShapeOrigin.h"

#include <Vector3D.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class AABB : public CollisionShapeOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	AABB(Vec3 min = Vec3(0.0f, 0.0f, 0.0f), Vec3 max = Vec3(0.0f, 0.0f, 0.0f));


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	virtual ~AABB();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ変数
	Vector3D min_;
	Vector3D max_;
};






//======================================================================
//
// 非静的メンバ関数定義( inline )
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトコンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline AABB::AABB(Vec3 min, Vec3 max)
	: CollisionShapeOrigin(CollisionShapeOrigin::Type::TYPE_AABB),
	  min_(min), 
	  max_(max)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline AABB::~AABB() 
{
}



//======================================================================
//
// 非メンバ関数宣言
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 1次元線分と点の最短距離のべき乗を求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistanceSquareAABB_Segment1D_Point(const float* position_min, const float* position_max, const float* point_any)
{
	float length = 0.0f;
	
	// 線分より小さいとき
	if (*point_any < *position_min)
	{
		length += (*position_min - *point_any) * (*position_min - *point_any);
	}

	// 線分より大きいとき
	if (*point_any > *position_max)
	{
		length += (*position_max - *point_any) * (*position_max - *point_any);
	}

	return length;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ AABBと点の最短距離を求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_AABB_Point(const AABB* aabb, const Vector3D* point)
{
	// 長さのべき乗で計算していく
	float length = 0.0f;
	
	// 各軸に対してべき乗を計算する
	length = ShortestDistanceSquareAABB_Segment1D_Point(&aabb->min_.x, &aabb->max_.x, &point->x);
	length = ShortestDistanceSquareAABB_Segment1D_Point(&aabb->min_.y, &aabb->max_.y, &point->y);
	length = ShortestDistanceSquareAABB_Segment1D_Point(&aabb->min_.z, &aabb->max_.z, &point->z);

	return (float)sqrt(length);
}



#endif