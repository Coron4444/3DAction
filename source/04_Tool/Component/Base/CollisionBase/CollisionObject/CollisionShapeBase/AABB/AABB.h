//================================================================================
//
//    AABBクラス
//    Author : Araki Kai                                作成日 : 2017/11/27
//
//================================================================================

#ifndef	_AABB_H_
#define _AABB_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"



/*********************************************************//**
* @brief
* AABBクラス
*
* AABBの基底クラス
*************************************************************/
class AABB : public CollisionShapeBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	Vector3D length_;	//!< 長さ
	Vector3D min_;		//!< 最小値
	Vector3D max_;		//!< 最大値


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* コンストラクタ
	*/
	AABB() : CollisionShapeBase(CollisionShapeBase::Type::AABB) {}

	/**
	* @brief
	* 初期化関数
	* @param
	* position : 座標
	* length : 各辺の長さ
	*/
	void Init(Vector3D position, Vector3D length)
	{
		// 座標を設定
		CollisionShapeBase::setPosition(position);

		// 長さを設定
		length_ = length;

		// 最小値と最大値
		UpdateMinAndMax();
	}

	/**
	* @brief
	* 更新関数
	*/
	void Update()
	{
		// 最小値と最大値
		UpdateMinAndMax();
	}

	// プロパティ
	const Vector3D* getLength() const { return &length_; }
	void setLength(Vector3D value) { length_ = value; };
	const Vector3D* getMin() const { return &min_; }
	const Vector3D* getMax() const { return &max_; }


private:
	/**
	* @brief
	* 最小値と最大値更新関数
	*/
	void UpdateMinAndMax()
	{
		min_ = *CollisionShapeBase::getPositon() - length_;
		max_ = *CollisionShapeBase::getPositon() + length_;
	}
};



//****************************************
// 非メンバ関数定義
//****************************************
//--------------------------------------------------
// +1次元線分と点の最短距離のべき乗を求める関数
//--------------------------------------------------
inline float ShortestDistanceSquareAABB_Segment1D_Point(float position_min,
														float position_max,
														float point_any)
{
	float length = 0.0f;

	// 線分より小さいとき
	if (point_any < position_min)
	{
		length += (position_min - point_any) * (position_min - point_any);
	}

	// 線分より大きいとき
	if (point_any > position_max)
	{
		length += (position_max - point_any) * (position_max - point_any);
	}

	return length;
}



//--------------------------------------------------
// +AABBと点の最短距離を求める関数
//--------------------------------------------------
inline float ShortestDistance_AABB_Point(const AABB* aabb, const Vector3D* point)
{
	// 長さのべき乗で計算していく
	float length = 0.0f;

	// 各軸に対してべき乗を計算する
	length = ShortestDistanceSquareAABB_Segment1D_Point(aabb->getMin()->x,
														aabb->getMax()->x,
														point->x);
	length = ShortestDistanceSquareAABB_Segment1D_Point(aabb->getMin()->y,
														aabb->getMax()->y,
														point->y);
	length = ShortestDistanceSquareAABB_Segment1D_Point(aabb->getMin()->z,
														aabb->getMax()->z,
														point->z);

	return (float)sqrt(length);
}



#endif