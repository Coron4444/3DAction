//================================================================================
//
//    線分クラス
//    Author : Araki Kai                                作成日 : 2017/11/27
//
//================================================================================

#ifndef	_SEGMENT_H_
#define _SEGMENT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../CollisionShapeBase.h"

#include <Vector3D.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Segment : public CollisionShapeBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	Segment(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), Vec3 vector = Vec3(0.0f, 0.0f, 0.0f));


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	virtual ~Segment();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	float    GetSlopeSegment2D   () const;

	Vector3D GetAddVectorPosition() const {return position_ + vector_;}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ変数
	Vector3D position_;
	Vector3D vector_;
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

inline Segment::Segment(Vec3 position, Vec3 vector)
	: CollisionShapeOrigin(CollisionShapeOrigin::Type::TYPE_SEGMENT),
	  position_(position), 
	  vector_  (vector)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Segment::~Segment() 
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 2Dの線分の傾き作成関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Segment::GetSlopeSegment2D() const
{
	return vector_.y / vector_.x;
}



//======================================================================
//
// 非メンバ関数宣言
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 直線と点の最短距離を求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Line_Point(Vec3* cross_point, float* t, const Segment* segment, const Vector3D* point)
{
	// 線分の座標と点とのベクトル
	Vector3D temp_vector = *point - segment -> position_;

	// 交点のtを算出
	*t = 0.0f;
	bool is_not_zero_length = segment->vector_.GetLengthSquare() > 0.0f;

	if (is_not_zero_length)
	{
		*t = segment->vector_.CreateVectorDot(temp_vector) / segment->vector_.CreateVectorDot(segment->vector_);
	}
		
	// 交点のhを算出
	*cross_point = segment->position_ + (segment->vector_ * (*t));

	// 距離を返す
	temp_vector = *cross_point - *point;

	return temp_vector.GetLength();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 線分と点の最短距離を求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Segment_Point(Vec3* cross_point, float* t, const Segment* segment, const Vector3D* point)
{
	// 線分の末端を保存
	Vec3 segment_position1 = segment->GetAddVectorPosition();

	// 直線と点の最短距離を算出
	float length = ShortestDistance_Line_Point(cross_point, t, segment, point);


	// 線分の始点より点が外側の時
	if (IsObtuseAngle(*point, segment->position_, segment_position1))
	{
		*cross_point = segment->position_;

		Vector3D temp_vector = segment->position_ - *point;

		return temp_vector.GetLength();
	}
	
	// 線分の終点より点が外側の時
	if ( IsObtuseAngle(*point, segment_position1, segment->position_))
	{
		*cross_point = segment_position1;

		Vector3D temp_vector = segment->position_ - *point;

		return temp_vector.GetLength();
	}

	return length;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 2直線が平行かの判定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool Is_ParallelSegment(const Segment* segment0, const Segment* segment1)
{
	// 2直線が平行かどうか( 外積の長さが0かどうか )
	Vector3D temp_vector = segment0->vector_.CreateVectorCross(segment1->vector_);


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

inline float ShortestDistance_Line_Line(Vec3* cross_point0, Vec3* cross_point1, float* t0, float* t1, const Segment* segment0, const Segment* segment1)
{
	// 2直線が平行
	if(Is_ParallelSegment(segment0, segment1))
	{
		// 直線1と直線0の座標との最短距離を算出
		float length = ShortestDistance_Line_Point(cross_point1, t1, segment1, &segment0->position_);
		*cross_point0 = segment0->position_;
		*t0 = 0.0f;

		return length;
	}

	// 平行でない
	Vector3D between_position_vector = segment0->position_ - segment1->position_;

	float dot_vector0_vector1  = segment0->vector_.CreateVectorDot(segment1->vector_);
	float dot_vector0_vector0  = segment0->vector_.GetLengthSquare();
	float dot_vector1_vector1  = segment1->vector_.GetLengthSquare();
	float dot_vector0_position = segment0->vector_.CreateVectorDot(between_position_vector);
	float dot_vector1_position = segment1->vector_.CreateVectorDot(between_position_vector);

	*t0 = (dot_vector0_vector1 * dot_vector1_position - dot_vector1_vector1 * dot_vector0_position) / (dot_vector0_vector0 * dot_vector1_vector1 - dot_vector0_vector1 * dot_vector0_vector1);
	*cross_point0 = segment0->position_ + segment0->vector_ * (*t0);

	Vector3D temp_vector = *cross_point0 - segment1->position_;

	*t1 = segment1->vector_.CreateVectorDot(temp_vector) / dot_vector1_vector1;

	*cross_point1 = segment1->position_ + segment1->vector_ * (*t1);

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

inline float ShortestDistance_Segment_Segment(Vec3* cross_point0, Vec3* cross_point1, float* t0, float* t1, const Segment* segment0, const Segment* segment1)
{
	// segment0が縮退している
	if (segment0->vector_.GetLengthSquare() <= 0.0f)
	{
		if (segment1->vector_.GetLengthSquare() <= 0.0f)
		{
			// 点と点の距離
			Vector3D temp_vector = segment1->position_ - segment0->position_;
			*cross_point0 = segment0->position_;
			*cross_point1 = segment1->position_;
			*t0 = 0.0f;
			*t1 = 0.0f;

			return temp_vector.GetLength();
		}
		else
		{
			// segment0の座標とsegment1の最短距離
			float length = ShortestDistance_Segment_Point(cross_point1, t1, segment1, &segment0 -> position_);
			*cross_point0 = segment0->position_;
			*t0 = 0.0f;
			Clamp0_1(t1);
			return length;
		}
	}
	

	// segment1が縮退してる
	if (segment1->vector_.GetLengthSquare() <= 0.0f)
	{
		// segment0の座標とsegment1の最短距離
		float length = ShortestDistance_Segment_Point(cross_point0, t0, segment0, &segment1 -> position_);
		*cross_point1 = segment1->position_;
		*t1 = 0.0f;
		Clamp0_1(t0);
		return length;
	}

	// 線分同士
	// 平行の時
	if(Is_ParallelSegment(segment0, segment1))
	{
		// 垂線の端点の1つを仮決定
		float length = ShortestDistance_Segment_Point(cross_point1, t1, segment1, &segment0 -> position_);
		*cross_point0 = segment0->position_;
		*t0 = 0.0f;

		// t1が収まってい居れば終了
		bool within_range = *t1 >= 0.0f && *t1 <= 1.0f;
		if (within_range) return length;

	}
	else
	{
		// 2直線の最短距離を求めて、t0,t1を仮決定
		float length = ShortestDistance_Line_Line(cross_point0, cross_point1, t0, t1, segment0, segment1);

		// 線分内に収まっていれば終了
		bool within_range = *t0 >= 0.0f && *t0 <= 1.0f && *t1 >= 0.0f && *t1 <= 1.0f;
		if (within_range) return length;
	}

	// segment0側のt0をクランプし、垂線を降ろす
	Clamp0_1(t0);
	*cross_point0 = segment0->position_ + segment0->vector_ * (*t0);
	Vector3D temp_point = *cross_point0;
	float length  = ShortestDistance_Segment_Point(cross_point1, t1, segment1, &temp_point);
	
	// 降ろした垂線が線分内にあるか
	bool within_range = *t1 >= 0.0f && *t1 <= 1.0f;
	if (within_range) return length;

	// segment1をクランプし、垂線を降ろす
	Clamp0_1(t1);
	*cross_point1 = segment1->position_ + segment1->vector_ * (*t1);
	temp_point = *cross_point1;
	length  = ShortestDistance_Segment_Point(cross_point0, t0, segment0, &temp_point);
	
	// 降ろした垂線が線分内にあるか
	within_range = *t0 >= 0.0f && *t0 <= 1.0f;
	if (within_range) return length;

	// 2直線の端点の距離が最短と判明
	Clamp0_1(t0);
	*cross_point0 = segment0->position_ + segment0->vector_ * (*t0);
	Vector3D temp_vector = *cross_point1 - *cross_point0;

	return temp_vector.GetLength();
}



#endif