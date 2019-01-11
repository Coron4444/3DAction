//================================================================================
//!	@file	 LineSegment.h
//!	@brief	 線分Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_SEGMENT_H_
#define _SEGMENT_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   線分Class
//!
//! @details 線分のClass
//************************************************************
class LineSegment : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Vector3D position_;		//!< 座標
	Vector3D vector_;		//!< 方向


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
	//! @brief 方向取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 方向
	//----------------------------------------
	Vector3D* getpVector();

	//----------------------------------------
	//! @brief 方向ベクトル加算済み座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 方向ベクトル加算済み座標
	//----------------------------------------
	Vector3D getAddVectorToPosition();

	//----------------------------------------
	//! @brief 2D線分の傾き取得関数
	//! @details
	//! @param void なし
	//! @retval float 2D線分の傾き
	//----------------------------------------
	float getSlopeOf2DLineSegment();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	LineSegment();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param position 座標
	//! @param vector   方向
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector);
};



//======================================================================
//
// 非メンバ関数宣言
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 点と直線最短距離を求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistancePointAndLine(Vec3* cross_point, float* t, Vector3D* point,
										  LineSegment* line_segment)
{
	// 点と線分の始点のベクトル
	Vector3D temp_vector = *point - *line_segment->getpPosition();

	// 線分が0以上かどうか
	if (line_segment->getpVector()->GetLengthSquare() > 0.0f)
	{
		// 交点のtの算出
		*t = line_segment->getpVector()->CreateVectorDot(temp_vector)
			/ line_segment->getpVector()->CreateVectorDot(*line_segment->getpVector());
	}
	else
	{
		*t = 0.0f;
	}

	// 交点のhの算出
	*cross_point = *line_segment->getpPosition() + *line_segment->getpVector() * (*t);

	// 距離を返す
	temp_vector = *cross_point - *point;
	return temp_vector.GetLength();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 点と線分の最短距離を求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistancePointAndLineSegment(Vec3* cross_point, float* t, Vector3D* point,
												 LineSegment* line_segment)
{
	// 線分の末端を保存
	Vec3 segment_position1 = line_segment->getAddVectorToPosition();

	// 直線と点の最短距離を算出
	float length = ShortestDistancePointAndLine(cross_point, t, point, line_segment);


	// 線分の始点より点が外側の時
	if (IsObtuseAngle(*point, *line_segment->getpPosition(), segment_position1))
	{
		*cross_point = *line_segment->getpPosition();

		Vector3D temp_vector = *line_segment->getpPosition() - *point;

		return temp_vector.GetLength();
	}

	// 線分の終点より点が外側の時
	if (IsObtuseAngle(*point, segment_position1, *line_segment->getpPosition()))
	{
		*cross_point = segment_position1;

		Vector3D temp_vector = *line_segment->getpPosition() - *point;

		return temp_vector.GetLength();
	}

	return length;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 2直線が平行かの判定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool Is_ParallelSegment(LineSegment* line_segment0, LineSegment* line_segment1)
{
	// 2直線が平行かどうか( 外積の長さが0かどうか )
	Vector3D temp_vector = line_segment0->getpVector()
		->CreateVectorCross(*line_segment1->getpVector());


	// 誤差範囲かどうか
	const float num_error = 0.000001f;

	bool is_error_range = -num_error < temp_vector.GetLengthSquare() && temp_vector.GetLengthSquare() < num_error;

	if (is_error_range) return true;

	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 直線と直線の最短距離を求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Line_Line(Vec3* cross_point0, Vec3* cross_point1,
										float* t0, float* t1,
										LineSegment* line_segment0,
										LineSegment* line_segment1)
{
	// 2直線が平行
	if (Is_ParallelSegment(line_segment0, line_segment1))
	{
		// 直線1と直線0の座標との最短距離を算出
		float length = ShortestDistancePointAndLine(cross_point1, t1,
													line_segment0->getpPosition(),
													line_segment1);
		*cross_point0 = *line_segment0->getpPosition();
		*t0 = 0.0f;

		return length;
	}

	// 平行でない
	Vector3D between_position_vector = *line_segment0->getpPosition()
		- *line_segment1->getpPosition();

	float dot_vector0_vector1 = line_segment0->getpVector()
		->CreateVectorDot(*line_segment1->getpVector());
	float dot_vector0_vector0 = line_segment0->getpVector()->GetLengthSquare();
	float dot_vector1_vector1 = line_segment1->getpVector()->GetLengthSquare();
	float dot_vector0_position = line_segment0->getpVector()
		->CreateVectorDot(between_position_vector);
	float dot_vector1_position = line_segment1->getpVector()
		->CreateVectorDot(between_position_vector);

	*t0 = (dot_vector0_vector1 * dot_vector1_position - dot_vector1_vector1 * dot_vector0_position) / (dot_vector0_vector0 * dot_vector1_vector1 - dot_vector0_vector1 * dot_vector0_vector1);
	*cross_point0 = *line_segment0->getpPosition() + *line_segment0->getpVector() * (*t0);

	Vector3D temp_vector = *cross_point0 - *line_segment1->getpPosition();

	*t1 = line_segment1->getpVector()->CreateVectorDot(temp_vector) / dot_vector1_vector1;

	*cross_point1 = *line_segment1->getpPosition() + *line_segment1->getpVector() * (*t1);

	temp_vector = *cross_point1 - *cross_point0;

	return temp_vector.GetLength();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 0～1の間に収める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void Clamp0_1(float* t)
{
	if (*t <= 0.0f)
	{
		*t = 0.0f;
	}
	else if (*t >= 1.0f)
	{
		*t = 1.0f;
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 線分と線分の最短距離を求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Segment_Segment(Vec3* cross_point0,
											  Vec3* cross_point1, float* t0, float* t1,
											  LineSegment* line_segment0,
											  LineSegment* line_segment1)
{
	// segment0が縮退している
	if (line_segment0->getpPosition()->GetLengthSquare() <= 0.0f)
	{
		if (line_segment1->getpVector()->GetLengthSquare() <= 0.0f)
		{
			// 点と点の距離
			Vector3D temp_vector = *line_segment1->getpPosition()
				- *line_segment0->getpPosition();
			*cross_point0 = *line_segment0->getpPosition();
			*cross_point1 = *line_segment1->getpPosition();
			*t0 = 0.0f;
			*t1 = 0.0f;

			return temp_vector.GetLength();
		}
		else
		{
			// segment0の座標とsegment1の最短距離
			float length = ShortestDistancePointAndLineSegment(cross_point1, t1, line_segment0->getpPosition(), line_segment1);
			*cross_point0 = *line_segment0->getpPosition();
			*t0 = 0.0f;
			Clamp0_1(t1);
			return length;
		}
	}


	// segment1が縮退してる
	if (line_segment1->getpVector()->GetLengthSquare() <= 0.0f)
	{
		// segment0の座標とsegment1の最短距離
		float length = ShortestDistancePointAndLineSegment(cross_point0, t0, line_segment1->getpPosition(), line_segment0);
		*cross_point1 = *line_segment1->getpPosition();
		*t1 = 0.0f;
		Clamp0_1(t0);
		return length;
	}

	// 線分同士
	// 平行の時
	if (Is_ParallelSegment(line_segment0, line_segment1))
	{
		// 垂線の端点の1つを仮決定
		float length = ShortestDistancePointAndLineSegment(cross_point1, t1, line_segment0->getpPosition(), line_segment1);
		*cross_point0 = *line_segment0->getpPosition();
		*t0 = 0.0f;

		// t1が収まってい居れば終了
		bool within_range = *t1 >= 0.0f && *t1 <= 1.0f;
		if (within_range) return length;

	}
	else
	{
		// 2直線の最短距離を求めて、t0,t1を仮決定
		float length = ShortestDistance_Line_Line(cross_point0, cross_point1, t0, t1, line_segment0, line_segment1);

		// 線分内に収まっていれば終了
		bool within_range = *t0 >= 0.0f && *t0 <= 1.0f && *t1 >= 0.0f && *t1 <= 1.0f;
		if (within_range) return length;
	}

	// segment0側のt0をクランプし、垂線を降ろす
	Clamp0_1(t0);
	*cross_point0 = *line_segment0->getpPosition() + *line_segment0->getpVector() * (*t0);
	Vector3D temp_point = *cross_point0;
	float length = ShortestDistancePointAndLineSegment(cross_point1, t1, &temp_point, line_segment1);

	// 降ろした垂線が線分内にあるか
	bool within_range = *t1 >= 0.0f && *t1 <= 1.0f;
	if (within_range) return length;

	// segment1をクランプし、垂線を降ろす
	Clamp0_1(t1);
	*cross_point1 = *line_segment1->getpPosition() + *line_segment1->getpVector() * (*t1);
	temp_point = *cross_point1;
	length = ShortestDistancePointAndLineSegment(cross_point0, t0, &temp_point, line_segment0);

	// 降ろした垂線が線分内にあるか
	within_range = *t0 >= 0.0f && *t0 <= 1.0f;
	if (within_range) return length;

	// 2直線の端点の距離が最短と判明
	Clamp0_1(t0);
	*cross_point0 = *line_segment0->getpPosition() + *line_segment0->getpVector() * (*t0);
	Vector3D temp_vector = *cross_point1 - *cross_point0;

	return temp_vector.GetLength();
}



#endif