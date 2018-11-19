//================================================================================
//
//    衝突判定クラス(static)
//    Author : Araki Kai                                作成日 : 2017/11/27
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "CollisionJudgment.h"

#include "../../../Component/Base/CollisionBase/CollisionObject/CollisionShapeBase/AABB/AABB.h"
#include "../../../Component/Base/CollisionBase/CollisionObject/CollisionShapeBase/Capsule/Capsule.h"
#include "../../../Component/Base/CollisionBase/CollisionObject/CollisionShapeBase/Cylinder/Cylinder.h"
#include "../../../Component/Base/CollisionBase/CollisionObject/CollisionShapeBase/OBB/OBB.h"
#include "../../../Component/Base/CollisionBase/CollisionObject/CollisionShapeBase/Plane/Plane.h"
#include "../../../Component/Base/CollisionBase/CollisionObject/CollisionShapeBase/Segment/Segment.h"
#include "../../../Component/Base/CollisionBase/CollisionObject/CollisionShapeBase/Sphere/Sphere.h"
#include "../../../Component/Base/CollisionBase/CollisionObject/CollisionShapeBase/Triangle/Triangle.h"

#include <QuadraticEquation\QuadraticEquation.h>



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(2D線分：2D線分) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment2D_Segment2D(Vector3D* hit_position, const Segment* segment0, const Segment* segment1)
{
	// X軸方向のベクトルが0かどうか
	if (IsZeroOneSideSegmentVectorX(segment0, segment1))
	{
		// 両方のXベクトルが0、つまり平行である 
		if (IsZeroAllSegmentVectorX(segment0, segment1)) return false;


		// どちらが0か
		if (segment0->vector_.x == 0)
		{
			return CrossPointCalculation_OneSideZeroSegment2D_Segment2D(hit_position, segment0, segment1);
		}
		else
		{
			return CrossPointCalculation_OneSideZeroSegment2D_Segment2D(hit_position, segment1, segment0);
		}

	}
	else
	{
		return CrossPointCalculation_Segment2D_Segment2D(hit_position, segment0, segment1);
	}

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(3D線分：球) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Sphere(Vector3D* hit_position, const Segment* segment, const Sphere* sphere)
{
	// 二次方程式の計算
	QuadraticEquation equation;
	

	// 二次方程式に解があるか
	bool is_calculable = QuadraticEquation_Calculation_Segment3D_Sphere(&equation, segment, sphere);

	if(!is_calculable) return false;


	// 線分内の1番手前のtを求める
	float t = AskForTheFrontT_Segment3D_Sphere(equation.t0_, equation.t1_);

	if(!IsInSegment(t)) return false;


	// 交点を算出
	CrossPointCalculation_Segment3D_Sphere(hit_position, segment, t);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(3D線分：無限平面) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Plane(Vector3D* hit_position, const Segment* segment, const Plane* plane)
{
	// 表裏チェック
	float temp_dot = segment->vector_.CreateVectorDot(plane->normal_vector_);
	if (temp_dot >= 0.0f) return false;

	// 線分始点と平面との距離を算出
	float length = plane -> Length_Point(segment->position_);


	// 距離と線分の比較( 2乗 )
	if (IsHitSquare_Segment3D_Plane(segment, length)) return false;


	// 線分が平面に届く距離を算出
	float temp_length = CalculateCollidingLength_Segment3D_Plane(segment->vector_, plane, length);

	if (IsHit_Segment3D_Plane(segment, temp_length)) return false;


	// 平面との交点を算出
	CrossPointCalculation_Segment3D_Plane(hit_position, *segment, temp_length);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(3D線分：三角平面) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Triangle(Vector3D* hit_position, const Segment* segment, const Triangle* triangle)
{
	// 無限平面との当たり判定
	Vector3D temp_position;

	if (!HitCheck_Segment3D_Plane( &temp_position, segment, &triangle->plane_)) return false;


	// 交点が3角形内かの判定
	if(!triangle->CheckInnerPoint(temp_position)) return false;


	// 平面との交点を算出
	CrossPointCalculation_Segment3D_Triangle(hit_position, temp_position);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(3D線分：円柱) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Cylinder(Vector3D* hit_position, const Segment* segment, const Cylinder* cylinder)
{
	// 二次方程式の計算
	QuadraticEquation equation;
	
	// 二次方程式に解があるか
	bool is_calculable = QuadraticEquation_Calculation_Segment3D_Cylinder(&equation, segment, cylinder);

	if(!is_calculable) return false;


	// 線分内の1番手前のtを求める
	float t = AskForTheFrontT_Segment3D_Cylinder(equation.t0_, equation.t1_);

	if(!IsInSegment(t)) return false;


	// 交点を算出
	CrossPointCalculation_Segment3D_Cylinder(hit_position, segment, t);
	
	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(3D線分：カプセル) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Capsule(Vector3D* hit_position, const Segment* segment, const Capsule* capsule)
{
	Vector3D temp_hit_position;

	// 前半球と衝突しているか？
	if(HitCheck_Segment3D_Sphere(&temp_hit_position, segment, &capsule->sphere0_))
	{
		// 鈍角かどうか
		if (IsObtuseAngle_Segment3D_Capsule(&capsule->sphere1_, &capsule->sphere0_, &temp_hit_position))
		{
			CrossPointCalculation_Segment3D_Capsule(hit_position, &temp_hit_position);

			return true;
		}
	}


	// 後半球と衝突しているか？
	if( HitCheck_Segment3D_Sphere(&temp_hit_position, segment, &capsule->sphere1_))
	{
		// 鈍角かどうか
		if (IsObtuseAngle_Segment3D_Capsule(&capsule->sphere0_, &capsule->sphere1_, &temp_hit_position))
		{
			CrossPointCalculation_Segment3D_Capsule(hit_position, &temp_hit_position);

			return true;
		}
	}


	// 円柱と衝突しているか？
	if(HitCheck_Segment3D_Cylinder(&temp_hit_position, segment, &capsule->cylinder_))
	{
		// 全て鋭角かどうか
		if (IsAcuteAngle_Segment3D_Capsule(&capsule->sphere1_, &capsule->sphere0_, &temp_hit_position))
		{
			CrossPointCalculation_Segment3D_Capsule(hit_position, &temp_hit_position);

			return true;
		}
	}

	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(球：球) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_Sphere(Vector3D* hit_vector, const Sphere* sphere0, const Sphere* sphere1)
{
	// 中心間距離と半径の合計による衝突判定( 2乗 )
	Vector3D center_to_center_vector;
	float    two_radius;

	NecessaryLengthCalculation_Sphere_Sphere(&center_to_center_vector, &two_radius, sphere0, sphere1);

	if (!IsHitSquare_Sphere_Sphere(&center_to_center_vector, two_radius)) return false;


	// めり込み具合を算出
	AmountOfSqueezingVectorCalculation_Sphere_Sphere(hit_vector, &center_to_center_vector, two_radius);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(球：無限平面) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_Plane(Vector3D* hit_vector, const Sphere* sphere, const Plane* plane)
{
	// 平面と球の中心距離と半径との判定
	if ( !IsHit_Sphere_Plane(sphere, plane)) return false;

	// めり込み具合を算出
	AmountOfSqueezingVectorCalculation_Sphere_Plane(hit_vector, sphere, plane);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(球：三角平面) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_Triangle(Vector3D* hit_vector, const Sphere* sphere, const Triangle* triangle)
{
	// 無限平面との衝突判定
	Vector3D temp_hit_vector;

	if (!HitCheck_Sphere_Plane(&temp_hit_vector, sphere, &triangle->plane_)) return false;

	// 三角形の各辺が衝突しているか
	if (IsHit_Sphere_TriangleSide(sphere, triangle))
	{
		AmountOfSqueezingVectorCalculation_Sphere_Triangle(hit_vector, &temp_hit_vector);

		return true;
	}

	// 球が三角形の内側にめり込んでいるか
	if (IsHit_Sphere_Triangle(sphere, triangle)) 
	{
		AmountOfSqueezingVectorCalculation_Sphere_Triangle(hit_vector, &temp_hit_vector);

		return true;
	}


	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(球：カプセル) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_Capsule(Vector3D* hit_vector, const Sphere* sphere, const Capsule* capsule)
{
	// 球の中心とカプセルとの距離を算出
	Vec3  cross_point;
	float temp_t;
	float length = ShortestDistance_Segment_Point(&cross_point, &temp_t, &capsule->segment_, 
		                                              &sphere->position_ );

	// 距離と2つの半径との合計の比較
	float two_radius = sphere->radius_ + capsule->radius_;
	if (length > two_radius) return false;

	// めり込み具合を算出
	length = two_radius - length;
	AmountOfSqueezingVectorCalculation_Sphere_Capsule(hit_vector, 
	                                                  &sphere->position_,
	                                                  &cross_point,
                                                      &length);
	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(球：OBB) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_OBB(Vector3D* hit_vector, Sphere* sphere, OBB* obb)
{
	// 球とOBBの最短距離のベクトルを算出
	Vector3D temp_vector = ShortestDistance_OBB_Point(obb, &sphere->position_);

	// 距離と半径の比較
	if (FroatTruncation(temp_vector.GetLength()) > sphere->radius_) return false;

	// めり込み具合を算出
	
	AmountOfSqueezingVectorCalculation_Sphere_OBB(hit_vector, 
												  &sphere->radius_,
												  &temp_vector );
	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(無限平面：無限平面) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Plane_Plane(Segment* cross_segment, const Plane* plane0, const Plane* plane1)
{
	// 平面の法線を用いて、両者が平行であるかの確認をする(衝突するかの確認)
	if (!IsHit_Plane_Plane(plane0, plane1)) return false;
	
	// 交差線分を求める
	if (cross_segment != nullptr)
	{
		CalculationOfIntersectionSegments_Plane_Plane(cross_segment, plane0, plane1);
	}

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(無限平面：三角平面) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Plane_Triangle(const Plane* plane, const Triangle* triangle)
{
	int side0 = (int)plane->Length_Point(triangle->point_[0]);
	int side1 = (int)plane->Length_Point(triangle->point_[1]);

	// この2点が両方同じ側か
	if ((side0 && !side1) || (!side0 && side1)) return true;

	int side2 = (int)plane->Length_Point(triangle->point_[2]);

	// この2点が両方同じ側か
	if ((side1 && !side2) || (!side1 && side2)) return true;

	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(三角平面：三角平面) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Triangle_Triangle(const Triangle* triangle0, const Triangle* triangle1)
{
	bool is_hit_segment_one = false;

	// 片方の三角形がもう片方を貫いているか
	if (IsHit_Triangle_Triangle(triangle0, triangle1, &is_hit_segment_one)) return true;

	// もう片方をチェック
	if (IsHit_Triangle_Triangle(triangle1, triangle0, &is_hit_segment_one)) return true;

	// お互いに1辺が貫通しているか
	if (is_hit_segment_one) return true;

	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(カプセル：カプセル) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Capsule_Capsule(Vector3D* hit_vector, const Capsule* capsule0, const Capsule* capsule1, Vector3D active_vector)
{
	Vector3D cross_point0;
	Vector3D cross_point1;
	float t0;
	float t1;

	// 線分間の最短距離と半径の合計を算出
	float length = ShortestDistance_Segment_Segment(&cross_point0, &cross_point1, &t0, &t1, &capsule0 -> segment_, &capsule1 -> segment_);
	float center_to_center_length = capsule0->radius_ + capsule1->radius_;

	// 長さの比較
	bool is_hit = length <= center_to_center_length;

	if (!is_hit) return false;
	
	// めり込みベクトルの作成
	if (hit_vector)
	{
		Vector3D temp_vector = cross_point0 - cross_point1;

		length = center_to_center_length - length;

		if (temp_vector.GetLengthSquare() > 0.0f)
		{
			*hit_vector = temp_vector.AnyLengthVector(length);
		}
		else
		{
			*hit_vector = active_vector.AnyLengthVector(length);
		}
	}
	
	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定関数(OBB：OBB) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_OBB_OBB(Vector3D* hit_vector, OBB* obb0, OBB* obb1)
{
	hit_vector = hit_vector;

	// 軸ベクトルの確保
	Vector3D n_a_e1 = *obb0->axis_.GetForawrd();
	Vector3D n_a_e2 = *obb0->axis_.GetRight();
	Vector3D n_a_e3 = *obb0->axis_.GetUp();
				
	Vector3D n_b_e1 = *obb1->axis_.GetForawrd();
	Vector3D n_b_e2 = *obb1->axis_.GetRight();
	Vector3D n_b_e3 = *obb1->axis_.GetUp();

	// 軸方向の半分の長さを確保
	Vector3D a_e1 = *obb0->GetVectorForwardHalf();
	Vector3D a_e2 = *obb0->GetVectorRightHalf();
	Vector3D a_e3 = *obb0->GetVectorUpHalf();

	Vector3D b_e1 = *obb1->GetVectorForwardHalf();
	Vector3D b_e2 = *obb1->GetVectorRightHalf();
	Vector3D b_e3 = *obb1->GetVectorUpHalf();

	// 両者の中心間の距離
	Vector3D interval_vector = obb0->position_ - obb1->position_;

	// 分離軸：a_e1, a_e2, a_e3
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&a_e1, &n_a_e1, &b_e1, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&a_e2, &n_a_e2, &b_e1, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&a_e3, &n_a_e3, &b_e1, &b_e2, &b_e3, &interval_vector)) return false;

	// 分離軸：b_e1, b_e2, b_e3
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&b_e1, &n_b_e1, &a_e1, &a_e2, &a_e3, &interval_vector)) return false;
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&b_e2, &n_b_e2, &a_e1, &a_e2, &a_e3, &interval_vector)) return false;
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&b_e3, &n_b_e3, &a_e1, &a_e2, &a_e3, &interval_vector)) return false;

	// 分離軸：C11, C12, C13
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e1, &n_b_e1, &a_e2, &a_e3, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e1, &n_b_e2, &a_e2, &a_e3, &b_e1, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e1, &n_b_e3, &a_e2, &a_e3, &b_e1, &b_e2, &interval_vector)) return false;

	// 分離軸：C21, C22, C23
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e2, &n_b_e1, &a_e1, &a_e3, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e2, &n_b_e2, &a_e1, &a_e3, &b_e1, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e2, &n_b_e3, &a_e1, &a_e3, &b_e1, &b_e2, &interval_vector)) return false;

	// 分離軸：C31, C32, C33
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e3, &n_b_e1, &a_e1, &a_e2, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e3, &n_b_e2, &a_e1, &a_e2, &b_e1, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e3, &n_b_e3, &a_e1, &a_e2, &b_e1, &b_e2, &interval_vector)) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ どちらか1っぽうの線分のXベクトルが0かの判定関数 ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsZeroOneSideSegmentVectorX(const Segment* segment0, const Segment* segment1)
{
	if (segment0->position_.x == 0) return true;
	if (segment1->position_.x == 0) return true;

	return false;
}



//--------------------------------------------------------------------------------
//
// [ 両方の線分のXベクトルが0かの判定関数 ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsZeroAllSegmentVectorX(const Segment* segment0, const Segment* segment1)
{
	if (!segment0->position_.x == 0) return false;
	if (!segment1->position_.x == 0) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ tが線分内かの判定関数 ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsInSegment(float t)
{
	if (t < 0.0f) return false;
	if (t > 1.0f) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ 2つのtが線分内かの判定関数 ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsAllInSegment(float t0, float t1)
{
	if (!IsInSegment(t0)) return false;
	if (!IsInSegment(t1)) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ 2つのtが線分内かの判定関数 ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsParallelSegment(float a0, float a1)
{
	if (a0 ==  a1) return true;
	if (a0 == -a1) return true;

	return false;
}



//--------------------------------------------------------------------------------
//
// [ 2乗の距離で衝突するかの判定関数(3D線分：無限平面) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHitSquare_Segment3D_Plane(const Segment* segment, float length)
{
	return segment->vector_.GetLengthSquare() < (length * length);
}



//--------------------------------------------------------------------------------
//
// [ 衝突するかの判定関数(3D線分：無限平面) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_Segment3D_Plane(const Segment* segment, float length)
{
	return length > segment->vector_.GetLength();
}



//--------------------------------------------------------------------------------
//
// [ 鈍角かの判定関数(3D線分：カプセル) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsObtuseAngle_Segment3D_Capsule(const Sphere* sphere0, const Sphere* sphere1, 
														const Vec3* hit_position)
{
	return IsObtuseAngle(sphere0->position_, sphere1->position_, *hit_position);
}



//--------------------------------------------------------------------------------
//
// [ 全て鋭角かの判定関数(3D線分：カプセル) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsAcuteAngle_Segment3D_Capsule(const Sphere* sphere0, const Sphere* sphere1, 
													   const Vec3* hit_position)
{
	if (!IsObtuseAngle(sphere0->position_, sphere1->position_, *hit_position)) return false;
	if (!IsObtuseAngle(sphere1->position_, sphere0->position_, *hit_position)) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ 2乗の距離で衝突するかの判定関数(球：球) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHitSquare_Sphere_Sphere(const Vector3D* center_to_center_vector, 
												  float two_radius)
{
	return center_to_center_vector->GetLengthSquare() <= (two_radius * two_radius);
}



//--------------------------------------------------------------------------------
//
// [ 衝突するかの判定関数(球：無限平面) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_Sphere_Plane(const Sphere* sphere, const Plane* plane)
{
	return sphere->radius_ > plane->Length_Point(sphere->position_);
}



//--------------------------------------------------------------------------------
//
// [ 衝突するか判定関数(球：三角平面の辺) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_Sphere_TriangleSide(const Sphere* sphere, const Triangle* triangle)
{
	Vec3 temp_vector = triangle->point_[1] - triangle->point_[0];
	Segment temp_segment(triangle->point_[0], temp_vector);

	if (HitCheck_Segment3D_Sphere(nullptr, &temp_segment, sphere)) return true;

	temp_vector  = triangle->point_[2] - triangle->point_[1];
	temp_segment = Segment(triangle->point_[1], temp_vector);

	if (HitCheck_Segment3D_Sphere(nullptr, &temp_segment, sphere)) return true;

	temp_vector  = triangle->point_[0] - triangle->point_[2];
	temp_segment = Segment(triangle->point_[2], temp_vector);

	if (HitCheck_Segment3D_Sphere(nullptr, &temp_segment, sphere)) return true;

	return false;
}



//--------------------------------------------------------------------------------
//
// [ 衝突するか判定関数(球：三角平面) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_Sphere_Triangle(const Sphere* sphere, const Triangle* triangle)
{
	Vec3    temp_vector  = triangle->plane_.normal_vector_ * -1;
	Segment temp_segment(sphere->position_, temp_vector);

	if (HitCheck_Segment3D_Triangle(nullptr, &temp_segment, triangle)) return true;

	return false;
}



//--------------------------------------------------------------------------------
//
// [ 衝突するか判定関数(無限平面：平面) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_Plane_Plane(const Plane* plane0, const Plane* plane1)
{
	float temp_dot = plane0->normal_vector_.CreateVectorDot(plane1->normal_vector_);

	if ((temp_dot >= 1.0f) || (temp_dot <= -1.0f)) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ 衝突するか判定関数(三角平面：三角平面) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_Triangle_Triangle(const Triangle* triangle0, const Triangle* triangle1, 
												bool* is_hit_segment_one)
{
	Segment temp_segment0(triangle0->point_[0], (triangle0->point_[1] - triangle1->point_[0]));
	Segment temp_segment1(triangle0->point_[1], (triangle0->point_[2] - triangle1->point_[1]));
	Segment temp_segment2(triangle0->point_[2], (triangle0->point_[0] - triangle1->point_[2]));

	bool is_hit0 = HitCheck_Segment3D_Triangle(nullptr, &temp_segment0, triangle1);
	bool is_hit1 = HitCheck_Segment3D_Triangle(nullptr, &temp_segment1, triangle1);
	bool is_hit2 = HitCheck_Segment3D_Triangle(nullptr, &temp_segment2, triangle1);

	if (is_hit0 || is_hit1 || is_hit2)
	{
		*is_hit_segment_one = true;
	}
	else
	{
		*is_hit_segment_one = false;
	}
	
	
	if ((is_hit0 && is_hit1)) return true;
	if ((is_hit1 && is_hit2)) return true;
	if ((is_hit2 && is_hit0)) return true;

	return false;
}



//--------------------------------------------------------------------------------
//
// [ floatの切り捨て関数 ]
//
//--------------------------------------------------------------------------------

float CollisionJudgment::FroatTruncation(float num)
{
	const float SHIFT_NUM = 10000.0f;
	// 左にシフト
	num *= SHIFT_NUM;
	// 小数点切り捨て
	num = floorf(num);
	// 右にシフト
	num /= SHIFT_NUM;

	return num;
}



//--------------------------------------------------------------------------------
//
// [ 交点が線分内かの計算関数(2D線分：2D線分) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::CrossPointCalculation_InAllSegment_Segment2D_Segment2D(Vector3D cross_point, Vector3D* hit_position, 
																			   const Segment* segment0, 
																			   const Segment* segment1)
{
	// tを求める
	float t0 = (cross_point.y - segment0->position_.y) / segment0->position_.y;
	float t1 = (cross_point.x - segment1->position_.x) / segment1->position_.x;

	// 交点が線分内かどうか
	if (!IsAllInSegment(t0, t1)) return false;

	// 交点の座標を引数に代入
	*hit_position = cross_point;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ 片方がベクトルX0の時の交点計算関数(2D線分：2D線分) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::CrossPointCalculation_OneSideZeroSegment2D_Segment2D(Vector3D* hit_position, const Segment* segment0, 
																			 const Segment* segment1)
{
	// 交点を求める
	Vector3D cross_point;

	cross_point.x = segment0->position_.x;
	
	float a1      = segment1->GetSlopeSegment2D();
	float temp_x1 = cross_point.x - segment1->position_.x;

	cross_point.y = (a1 * temp_x1) + segment1->position_.x;

	return CrossPointCalculation_InAllSegment_Segment2D_Segment2D(cross_point, hit_position, segment0, segment1);

}



//--------------------------------------------------------------------------------
//
// [ 交点計算関数(2D線分：2D線分 ) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::CrossPointCalculation_Segment2D_Segment2D(Vector3D* hit_position, const Segment* segment0, 
																  const Segment* segment1)
{
	// 傾きを求める
	float a0 = segment0->GetSlopeSegment2D();
	float a1 = segment1->GetSlopeSegment2D();


	// 平行かの判定
	if (IsParallelSegment(a0, a1)) return false;


	// 交点を求める
	Vector3D cross_point;
	cross_point.x = (a0 * segment0->position_.x - a1 * segment1->position_.x + segment1->position_.y - segment1->position_.y) 
		             / (a0 - a1);

	cross_point.y = a0 * (cross_point.x - segment0->position_.x) + segment0->position_.y;

	return CrossPointCalculation_InAllSegment_Segment2D_Segment2D(cross_point, hit_position, segment0, segment1);
}



//--------------------------------------------------------------------------------
//
// [ 2次方程式計算関数(3D線分：球) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::QuadraticEquation_Calculation_Segment3D_Sphere(QuadraticEquation* equation, const Segment* segment, 
																	   const Sphere* sphere)
{
	// 解の公式を使用する為のa,b,cを求める
	// at^2 + bt + c = 0
	float temp_x = segment->position_.x - sphere->position_.x;
	float temp_y = segment->position_.y - sphere->position_.y;
	float temp_z = segment->position_.z - sphere->position_.z;

	 

	equation->a_ = segment->vector_.GetSquareX() + segment->vector_.GetSquareY() + segment->vector_.GetSquareZ();
	equation->b_ = 2.0f * (segment->vector_.x * temp_x + segment->vector_.y * temp_y + segment->vector_.z * temp_z);
	equation->c_ = (temp_x * temp_x) + (temp_y * temp_y) + (temp_z * temp_z) - (sphere->radius_ * sphere->radius_);

	// 解の公式を解く
	if(equation->CalculateTheSolutionFormula()) return true;

	return false;
}



//--------------------------------------------------------------------------------
//
// [ 線分内の1番手前のtを求める関数(3D線分：球) ]
//
//--------------------------------------------------------------------------------

float CollisionJudgment::AskForTheFrontT_Segment3D_Sphere(float t0, float t1)
{
	// 線分内の1番手前のtを求める
	float t = 2.0f;

	if( IsInSegment(t0))
	{
		if (t0 < t)
		{
			t = t0;
		}
	}

	if( IsInSegment(t1))
	{
		if (t1 < t)
		{
			t = t1;
		}
	}

	return t;
}



//--------------------------------------------------------------------------------
//
// [ 交点計算関数(3D線分：球) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::CrossPointCalculation_Segment3D_Sphere(Vector3D* hit_position, const Segment* segment, float t)
{
	if(hit_position)
	{
		*hit_position = segment->position_ + (segment -> vector_ * t);	
	}
}



//--------------------------------------------------------------------------------
//
// [ 線分が平面に届く距離の計算関数(3D線分：無限平面) ]
//
//--------------------------------------------------------------------------------

float CollisionJudgment::CalculateCollidingLength_Segment3D_Plane(Vector3D segment_vector, const Plane* plane, float length)
{
	// 線分ベクトル(正規化済み)と平面法線の反対からcosΘを求める
	segment_vector.CreateNormalize();

	float cos_theta = segment_vector.CreateVectorDot((plane->normal_vector_ * -1));


	// 線分が平面に届く距離を算出
	return length / cos_theta;
}



//--------------------------------------------------------------------------------
//
// [ 交点計算関数(3D線分：無限平面) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::CrossPointCalculation_Segment3D_Plane(Vector3D* hit_position, Segment segment, float length)
{
	if(hit_position)
	{
		segment.vector_.AnyLengthVector(length);

		*hit_position = segment.position_ + segment.vector_;
	}
}



//--------------------------------------------------------------------------------
//
// [ 交点計算関数(3D線分：三角平面) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::CrossPointCalculation_Segment3D_Triangle(Vector3D* hit_position, Vec3 position)
{
	if(hit_position)
	{
		*hit_position = position;
	}
}



//--------------------------------------------------------------------------------
//
// [ 2次方程式計算関数(3D線分：円柱) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::QuadraticEquation_Calculation_Segment3D_Cylinder(QuadraticEquation* equation, const Segment* segment, 
																		 const Cylinder* cylinder)
{
	// 解の公式を使用する為のa,b,cを求める
	// at^2 + bt + c = 0
	Vector3D tempS = cylinder->position1_ - cylinder->position0_;

	// 各種内積値の算出
	float dot_vector_vector	      = segment->vector_.CreateVectorDot(segment->vector_);
	float dot_tempS_vector	      = tempS.CreateVectorDot(segment->vector_);
	float dot_position0_vector	  = cylinder->position0_.CreateVectorDot(segment->vector_);
	float dot_tempS_tempS	      = tempS.CreateVectorDot(tempS);
	float dot_position0_tempS	  = cylinder->position0_.CreateVectorDot(tempS);
	float dot_position0_position0 = cylinder->position0_.CreateVectorDot(cylinder->position0_);

	// 円柱が成立しない
	if (dot_tempS_tempS == 0.0f) return false;


	equation->a_ = dot_vector_vector       - (dot_tempS_vector * dot_tempS_vector      ) / dot_tempS_tempS;
	equation->b_ = dot_position0_vector    - (dot_position0_tempS * dot_tempS_vector   ) / dot_tempS_tempS;
	equation->c_ = dot_position0_position0 - (dot_position0_tempS * dot_position0_tempS) / dot_tempS_tempS;


	// 解の公式を解く
	if(equation->CalculateTheSolutionFormula()) return true;

	return false;
}



//--------------------------------------------------------------------------------
//
// [ 線分内の1番手前のtを求める関数(3D線分：円柱) ]
//
//--------------------------------------------------------------------------------

float CollisionJudgment::AskForTheFrontT_Segment3D_Cylinder(float t0, float t1)
{
	// 線分内の1番手前のtを求める
	float t = 2.0f;

	if( IsInSegment(t0))
	{
		if (t0 < t)
		{
			t = t0;
		}
	}

	if( IsInSegment(t1))
	{
		if (t1 < t)
		{
			t = t1;
		}
	}

	return t;
}



//--------------------------------------------------------------------------------
//
// [ 交点計算関数(3D線分：円柱) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::CrossPointCalculation_Segment3D_Cylinder(Vector3D* hit_position, const Segment* segment, float t)
{
	if(hit_position)
	{
		*hit_position = segment->position_ + (segment -> vector_ * t);	
	}
}



//--------------------------------------------------------------------------------
//
// [ 交点計算関数(3D線分：カプセル) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::CrossPointCalculation_Segment3D_Capsule(Vec3* hit_position, const Vec3* temp_position)
{
	if(hit_position)
	{
		*hit_position = *temp_position;	
	}
}



//--------------------------------------------------------------------------------
//
// [ 必要な長さを算出関数(球：球) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::NecessaryLengthCalculation_Sphere_Sphere(Vector3D* center_to_center_vector, float* two_radius, 
																 const Sphere* sphere0, const Sphere* sphere1)
{
	*center_to_center_vector = sphere0->position_ - sphere1->position_;
	*two_radius              = sphere0->radius_   + sphere1->radius_;
}



//--------------------------------------------------------------------------------
//
// [ めり込みベクトル算出関数(球：球) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::AmountOfSqueezingVectorCalculation_Sphere_Sphere(Vector3D* hit_vector, 
																		 Vector3D* center_to_center_vector, float two_radius)
{
	if (hit_vector)
	{
		float length = two_radius - center_to_center_vector->GetLength();

		*hit_vector = center_to_center_vector->AnyLengthVector(length);
	}
}



//--------------------------------------------------------------------------------
//
// [ めり込みベクトル算出関数(球：無限平面) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::AmountOfSqueezingVectorCalculation_Sphere_Plane(Vector3D* hit_vector, const Sphere* sphere, 
																		const Plane* plane)
{
	if (hit_vector)
	{
		float temp_length = sphere->radius_ - plane->Length_Point(sphere -> position_);

		Vector3D temp_vector = plane->normal_vector_;

		*hit_vector = temp_vector.AnyLengthVector(temp_length);
	}
}



//--------------------------------------------------------------------------------
//
// [ めり込みベクトル算出関数(球：三角平面) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::AmountOfSqueezingVectorCalculation_Sphere_Triangle(Vector3D* hit_vector, Vector3D* vector)
{
	if (hit_vector)
	{
		*hit_vector = *vector;
	}
}



//--------------------------------------------------------------------------------
//
// [ めり込みベクトル算出関数(球：カプセル) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::AmountOfSqueezingVectorCalculation_Sphere_Capsule(Vector3D* hit_vector, const Vec3*  sphere_position,
																		  const Vec3*  cross_point, const float* length)
{
	if (hit_vector)
	{
		*hit_vector = *sphere_position - *cross_point;
		hit_vector->AnyLengthVector(*length);
	}
}



//--------------------------------------------------------------------------------
//
// [ めり込みベクトル算出関数(球：OBB) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::AmountOfSqueezingVectorCalculation_Sphere_OBB(Vector3D* hit_vector, const float* radius,
																	  const Vector3D* vector)
{
	if (hit_vector)
	{
		float length = *radius - vector->GetLength();
		*hit_vector = *vector;

		hit_vector->AnyLengthVector(length);
	}
}



//--------------------------------------------------------------------------------
//
// [ 交差線分の算出関数(無限平面：無限平面) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::CalculationOfIntersectionSegments_Plane_Plane(Segment* cross_segment, const Plane* plane0, 
																	  const Plane* plane1)
{
	// 外積により交差するベクトルを作成
	cross_segment->vector_ = plane0->normal_vector_.CreateVectorCross(plane1 -> normal_vector_);

	// 交差線分の始点を算出
	if (cross_segment -> vector_.z != 0.0f)
	{
		cross_segment->position_.x = (plane0->normal_vector_.y * plane1->adjustmet_d_ - plane1->normal_vector_.y * plane0->adjustmet_d_) / cross_segment->vector_.z;
		cross_segment->position_.y = (plane1->normal_vector_.x * plane0->adjustmet_d_ - plane0->normal_vector_.x * plane1->adjustmet_d_) / cross_segment->vector_.z;
		cross_segment->position_.z = 0.0f;
	}
	else if (cross_segment -> vector_.y != 0.0f)
	{
		cross_segment->position_.x = (plane1->normal_vector_.z * plane0->adjustmet_d_ - plane0->normal_vector_.z * plane1->adjustmet_d_) / cross_segment->vector_.y;
		cross_segment->position_.y = 0.0f;
		cross_segment->position_.z = (plane0->normal_vector_.x * plane1->adjustmet_d_ - plane1->normal_vector_.x * plane0->adjustmet_d_) / cross_segment->vector_.y;
	}
	else
	{
		cross_segment->position_.x = (plane0->normal_vector_.z * plane1->adjustmet_d_ - plane1->normal_vector_.z * plane0->adjustmet_d_) / cross_segment->vector_.x;
		cross_segment->position_.y = 0.0f;
		cross_segment->position_.z = (plane1->normal_vector_.y * plane0->adjustmet_d_ - plane0->normal_vector_.y * plane1->adjustmet_d_) / cross_segment->vector_.x;
	}
}



//--------------------------------------------------------------------------------
//
// [ 分離軸に投影された軸成分より投影線分の長さを求める関数(OBB：OBB) ]
//
//--------------------------------------------------------------------------------

float CollisionJudgment::LenSegOnSeparationAxis_OBB_OBB(Vector3D* separation_axis, Vector3D* e1, Vector3D* e2, Vector3D* e3)
{
	float r1 = fabsf(separation_axis->CreateVectorDot(*e1));
	float r2 = fabsf(separation_axis->CreateVectorDot(*e2));
	float r3 = (e3 != nullptr) ? fabsf(separation_axis->CreateVectorDot(*e3)) : 0;

	return r1 + r2 + r3;
}



//--------------------------------------------------------------------------------
//
// [ 通常分離軸に対しての衝突を求める関数(OBB：OBB) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_NormalSeparationAxis_OBB_OBB(Vector3D* separation_axis, Vector3D* separation_axis_normal, 
														   Vector3D* e1, Vector3D* e2, Vector3D* e3, 
														   Vector3D* interval_vector)
{
	float r_a    = separation_axis->GetLength();
	float r_b    = LenSegOnSeparationAxis_OBB_OBB(separation_axis_normal, e1, e2, e3);
	float length = fabsf(interval_vector->CreateVectorDot(*separation_axis_normal));

	if (length > (r_a + r_b)) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ 外積分離軸に対しての衝突を求める関数(OBB：OBB) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_CrossSeparationAxis_OBB_OBB(Vector3D* separation_axis_normal0, 
														  Vector3D* separation_axis_normal1, 
													      Vector3D* a_e1, Vector3D* a_e2, Vector3D* b_e1, Vector3D* b_e2,
													      Vector3D* interval_vector)
{
	Vector3D temp_cross = separation_axis_normal0->CreateVectorCross(*separation_axis_normal1);
	float r_a    = LenSegOnSeparationAxis_OBB_OBB(&temp_cross, a_e1, a_e2);
	float r_b    = LenSegOnSeparationAxis_OBB_OBB(&temp_cross, b_e1, b_e2);
	float length = fabsf(interval_vector->CreateVectorDot(temp_cross));

	if (length > (r_a + r_b)) return false;

	return true;
}