//================================================================================
//!	@file	 CollisionCalculation.cpp
//!	@brief	 衝突計算Class
//! @details static
//!	@author  Kai Araki									@date 2018/11/06
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "CollisionCalculation.h"

#include "../../../Component/Collision/CollisionBase/CollisionObject/CollisionShapeBase/AABB/AABB.h"
#include "../../../Component/Collision/CollisionBase/CollisionObject/CollisionShapeBase/Capsule/Capsule.h"
#include "../../../Component/Collision/CollisionBase/CollisionObject/CollisionShapeBase/Cylinder/Cylinder.h"
#include "../../../Component/Collision/CollisionBase/CollisionObject/CollisionShapeBase/OBB/OBB.h"
#include "../../../Component/Collision/CollisionBase/CollisionObject/CollisionShapeBase/Plane/Plane.h"
#include "../../../Component/Collision/CollisionBase/CollisionObject/CollisionShapeBase/LineSegment/LineSegment.h"
#include "../../../Component/Collision/CollisionBase/CollisionObject/CollisionShapeBase/Sphere/Sphere.h"
#include "../../../Component/Collision/CollisionBase/CollisionObject/CollisionShapeBase/Triangle/Triangle.h"

#include <QuadraticEquation\QuadraticEquation.h>



//****************************************
// static関数定義
//****************************************
bool CollisionCalculation::CollisionJudgmentOf2DLineSegmentAnd2DLineSegment(Vector3D* hit_point,
																			LineSegment* line_segment0,
																			LineSegment* line_segment1)
{
	// X軸方向のベクトルが0かどうか
	if (DetermineWhetherXOfEitherLineSegmentIsZero(line_segment0, line_segment1))
	{
		// 両方のXベクトルが0、つまり平行である 
		if (DetermineWhetherXOfBothLineSegmentsIsZero(line_segment0,
													  line_segment1)) return false;

		// どちらかのXが0の場合
		if (line_segment0->getpVector()->x == 0)
		{
			return IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(hit_point,
																					 line_segment0,
																					 line_segment1);
		}
		else
		{
			return IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(hit_point,
																					 line_segment1,
																					 line_segment0);
		}

	}
	else
	{
		return IntersectionCalculationOf2DLineSegmentAnd2DLineSegment(hit_point,
																	  line_segment0,
																	  line_segment1);
	}

}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndSphere(Vector3D* hit_point,
																   LineSegment* line_segment,
																   Sphere* sphere)
{
	// 二次方程式の計算
	QuadraticEquation equation;

	// 二次方程式に解があるか
	bool is_calculable = QuadraticEquationCalculationForLineSegmentsAndSpheres(&equation,
																			   line_segment,
																			   sphere);
	if (!is_calculable) return false;

	// 線分内の1番手前の比率を求める
	float ratio = CalculateTheRatioOfTheFrontInTheLineSegment(equation.t0_,
															  equation.t1_);
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio)) return false;

	// 衝突点の算出
	if (hit_point)
	{
		*line_segment->getpVector() *= ratio;
		*hit_point = line_segment->getAddVectorToPosition();
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndPlane(Vector3D* hit_point,
																  LineSegment* line_segment,
																  Plane* plane)
{
	// 表裏チェック
	float temp_dot = line_segment->getpVector()->CreateVectorDot(*plane->getpNormal());
	if (temp_dot >= 0.0f) return false;

	// 線分始点と平面との距離を算出
	float length = Length_Point(plane, line_segment->getpPosition());

	// 距離と線分の比較
	if (DetermineIfItIsLongerThanVector(line_segment->getpVector(),
										length)) return false;

	// 線分が平面に届く距離を算出
	float temp_length = CalculateTheDistanceTheLineSegmentReachesThePlane(*line_segment->getpVector(),
																		  plane,
																		  length);
	if (DetermineIfItIsLongerThanVector(line_segment->getpVector(),
										temp_length)) return false;

	// 衝突点の算出
	if (hit_point)
	{
		line_segment->getpVector()->AnyLengthVector(length);
		*hit_point = line_segment->getAddVectorToPosition();
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndTriangle(Vector3D* hit_point,
																	 LineSegment* line_segment,
																	 Triangle* triangle)
{
	// 無限平面との当たり判定
	Vector3D temp_position;
	if (!CollisionJudgmentOfLineSegmentAndPlane(&temp_position, line_segment, triangle->getpPlane())) return false;

	// 交点が3角形内かの判定
	if (!CheckInnerPoint(triangle, &temp_position)) return false;

	// 衝突点の算出
	if (hit_point)
	{
		*hit_point = temp_position;
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndCylinder(Vector3D* hit_point,
																	 LineSegment* line_segment,
																	 Cylinder* cylinder)
{
	// 二次方程式の計算
	QuadraticEquation equation;

	// 二次方程式に解があるか
	bool is_calculable = QuadraticEquationCalculationForLineSegmentsAndCylinders(&equation,
																				 line_segment,
																				 cylinder);
	if (!is_calculable) return false;

	// 線分内の1番手前の比率を求める
	float ratio = CalculateTheRatioOfTheFrontInTheLineSegment(equation.t0_,
															  equation.t1_);
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio)) return false;

	// 衝突点の算出
	if (hit_point)
	{
		*line_segment->getpVector() *= ratio;
		*hit_point = line_segment->getAddVectorToPosition();
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndCapsule(Vector3D* hit_point,
																	LineSegment* line_segment,
																	Capsule* capsule)
{
	Vector3D temp_hit_position;

	// 前半球と衝突しているか？
	if (CollisionJudgmentOfLineSegmentAndSphere(&temp_hit_position, line_segment,
												capsule->getpSphere0()))
	{
		// 鈍角かどうか
		if (IsObtuseAngle(*capsule->getpSphere1()->getpPosition(),
						  *capsule->getpSphere0()->getpPosition(),
						  temp_hit_position))
		{
			// 衝突点の算出
			if (hit_point)
			{
				*hit_point = temp_hit_position;
			}
			return true;
		}
	}

	// 後半球と衝突しているか？
	if (CollisionJudgmentOfLineSegmentAndSphere(&temp_hit_position, line_segment, capsule->getpSphere1()))
	{
		// 鈍角かどうか
		if (IsObtuseAngle(*capsule->getpSphere0()->getpPosition(),
						  *capsule->getpSphere1()->getpPosition(),
						  temp_hit_position))
		{
			// 衝突点の算出
			if (hit_point)
			{
				*hit_point = temp_hit_position;
			}
			return true;
		}
	}

	// 円柱と衝突しているか？
	if (CollisionJudgmentOfLineSegmentAndCylinder(&temp_hit_position, line_segment,
												  capsule->getpCylinder()))
	{
		// 全て鋭角かどうか
		if (!IsObtuseAngle(*capsule->getpSphere0()->getpPosition(),
						   *capsule->getpSphere1()->getpPosition(),
						   temp_hit_position)) return false;
		if (!IsObtuseAngle(*capsule->getpSphere1()->getpPosition(),
						   *capsule->getpSphere0()->getpPosition(),
						   temp_hit_position)) return false;

		// 衝突点の算出
		if (hit_point)
		{
			*hit_point = temp_hit_position;
		}
		return true;
	}

	return false;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndSphere(Vector3D* hit_vector,
															  Sphere* sphere0,
															  Sphere* sphere1)
{
	// 中心間距離と半径の合計による衝突判定
	Vector3D center_to_center_vector = *sphere0->getpPosition() - *sphere1->getpPosition();
	float two_radius = sphere0->getRadius() + sphere1->getRadius();

	if (!DetermineIfItIsLongerThanVector(&center_to_center_vector,
										 two_radius)) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		float length = two_radius - center_to_center_vector.GetLength();
		*hit_vector = center_to_center_vector.AnyLengthVector(length);
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndPlane(Vector3D* hit_vector,
															 Sphere* sphere,
															 Plane* plane)
{
	// 平面と球の中心距離と半径との判定
	float temp_length = Length_Point(plane, sphere->getpPosition());
	if (!(sphere->getRadius() > temp_length)) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		temp_length = sphere->getRadius() - Length_Point(plane, sphere->getpPosition());
		Vector3D temp_vector = *plane->getpNormal();
		*hit_vector = temp_vector.AnyLengthVector(temp_length);
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndTriangle(Vector3D* hit_vector,
																Sphere* sphere,
																Triangle* triangle)
{
	// 無限平面との衝突判定
	Vector3D temp_hit_vector;
	if (!CollisionJudgmentOfSphereAndPlane(&temp_hit_vector, sphere, triangle->getpPlane())) return false;

	// 三角形の各辺が衝突しているか
	if (DetermineWhetherASphereCollidesAgainstEachSide(sphere, triangle))
	{
		// 衝突ベクトルの算出
		if (hit_vector)
		{
			*hit_vector = temp_hit_vector;
		}
		return true;
	}

	// 球が三角形の内側にめり込んでいるか
	if (DetermineWhetherTheSphereIsSinkingInside(sphere, triangle))
	{
		// 衝突ベクトルの算出
		if (hit_vector)
		{
			*hit_vector = temp_hit_vector;
		}
		return true;
	}
	return false;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndCapsule(Vector3D* hit_vector,
															   Sphere* sphere,
															   Capsule* capsule)
{
	// 球の中心とカプセルとの距離を算出
	Vec3  intersection_point;
	float temp_t;
	float length = ShortestDistancePointAndLineSegment(&intersection_point, &temp_t,
													   sphere->getpPosition(),
													   capsule->getpLineSegment());

	// 距離と2つの半径との合計の比較
	float two_radius = sphere->getRadius() + capsule->getRadius();
	if (length > two_radius) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		length = two_radius - length;
		*hit_vector = *sphere->getpPosition() - intersection_point;
		hit_vector->AnyLengthVector(length);
	}

	return true;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndOBB(Vector3D* hit_vector,
														   Sphere* sphere,
														   OBB* obb)
{
	// 球とOBBの最短距離のベクトルを算出
	Vector3D temp_vector = ShortestDistance_OBB_Point(obb, sphere->getpPosition());

	// 距離と半径の比較
	if (FroatTruncation(temp_vector.GetLength()) > sphere->getRadius()) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		float length = sphere->getRadius() - temp_vector.GetLength();
		*hit_vector = temp_vector;
		hit_vector->AnyLengthVector(length);
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfPlaneAndPlane(LineSegment* hit_line_segment,
															Plane* plane0,
															Plane* plane1)
{
	// 平面の法線を用いて、両者が平行であるかの確認をする(衝突するかの確認)
	if (!DetermineWhetherThePlaneIsParallel(plane0, plane1)) return false;

	// 交差線分を求める
	if (hit_line_segment != nullptr)
	{
		CalculationOfCollisionLineSegment(hit_line_segment, plane0, plane1);
	}

	return true;
}



bool CollisionCalculation::CollisionJudgmentOfPlaneAndTriangle(Plane* plane,
															   Triangle* triangle)
{
	int side0 = (int)Length_Point(plane, triangle->getpPoint0());
	int side1 = (int)Length_Point(plane, triangle->getpPoint1());

	// この2点が両方同じ側か
	if ((side0 && !side1) || (!side0 && side1)) return true;

	int side2 = (int)Length_Point(plane, triangle->getpPoint2());

	// この2点が両方同じ側か
	if ((side1 && !side2) || (!side1 && side2)) return true;

	return false;
}



bool CollisionCalculation::CollisionJudgmentOfTriangleAndTriangle(Triangle* triangle0,
																  Triangle* triangle1)
{
	bool is_hit_segment_one = false;

	// 片方の三角形がもう片方を貫いているか
	if (DetermineIfATrianglePenetrates(&is_hit_segment_one, 
									   triangle0, triangle1)) return true;

	// もう片方をチェック
	if (DetermineIfATrianglePenetrates(&is_hit_segment_one,
									   triangle1, triangle0)) return true;

	// お互いに1辺が貫通しているか
	if (is_hit_segment_one) return true;

	return false;
}



bool CollisionCalculation::CollisionJudgmentOfCapsuleAndCapsule(Vector3D* hit_vector,
																Capsule* capsule0,
																Capsule* capsule1,
																Vector3D active_vector)
{
	Vector3D intersection_point0;
	Vector3D intersection_point1;
	float t0;
	float t1;

	// 線分間の最短距離と半径の合計を算出
	float length = ShortestDistance_Segment_Segment(&intersection_point0, &intersection_point1, &t0,
													&t1, capsule0->getpLineSegment(),
													capsule1->getpLineSegment());
	float center_to_center_length = capsule0->getRadius() + capsule1->getRadius();

	// 長さの比較
	bool is_hit = length <= center_to_center_length;

	if (!is_hit) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		Vector3D temp_vector = intersection_point0 - intersection_point1;

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



bool CollisionCalculation::CollisionJudgmentOfOBBAndOBB(Vector3D* hit_vector,
														OBB* obb0,
														OBB* obb1)
{
	hit_vector = hit_vector;

	// 分離軸の確保(軸方向の半分の長さ)
	Vector3D obb0_separation_axis0 = obb0->getForwardVectorHalf();
	Vector3D obb0_separation_axis1 = obb0->getRightVectorHalf();
	Vector3D obb0_separation_axis2 = obb0->getUpVectorHalf();

	Vector3D obb1_separation_axis0 = obb1->getForwardVectorHalf();
	Vector3D obb1_separation_axis1 = obb1->getRightVectorHalf();
	Vector3D obb1_separation_axis2 = obb1->getUpVectorHalf();

	// 分離軸単位ベクトルの確保(軸ベクトル)
	Vector3D obb0_normal_separation_axis0 = *obb0->getpAxisVector()->GetForawrd();
	Vector3D obb0_normal_separation_axis1 = *obb0->getpAxisVector()->GetRight();
	Vector3D obb0_normal_separation_axis2 = *obb0->getpAxisVector()->GetUp();

	Vector3D obb1_normal_separation_axis0 = *obb1->getpAxisVector()->GetForawrd();
	Vector3D obb1_normal_separation_axis1 = *obb1->getpAxisVector()->GetRight();
	Vector3D obb1_normal_separation_axis2 = *obb1->getpAxisVector()->GetUp();

	// 両者の中心間の距離
	Vector3D interval_vector = *obb0->getpPosition() - *obb1->getpPosition();

	// 通常の分離軸との衝突判定
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb0_separation_axis0,
															&obb0_normal_separation_axis0,
															&obb1_separation_axis0,
															&obb1_separation_axis1,
															&obb1_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb0_separation_axis1,
															&obb0_normal_separation_axis1,
															&obb1_separation_axis0,
															&obb1_separation_axis1,
															&obb1_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb0_separation_axis2,
															&obb0_normal_separation_axis2,
															&obb1_separation_axis0,
															&obb1_separation_axis1,
															&obb1_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb1_separation_axis0,
															&obb1_normal_separation_axis0,
															&obb0_separation_axis0,
															&obb0_separation_axis1,
															&obb0_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb1_separation_axis1,
															&obb1_normal_separation_axis1,
															&obb0_separation_axis0,
															&obb0_separation_axis1,
															&obb0_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb1_separation_axis2,
															&obb1_normal_separation_axis2,
															&obb0_separation_axis0,
															&obb0_separation_axis1,
															&obb0_separation_axis2,
															&interval_vector)) return false;

	// 外積の分離軸との衝突判定
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis0,
															 &obb1_normal_separation_axis0,
															 &obb0_separation_axis1,
															 &obb0_separation_axis2,
															 &obb1_separation_axis1,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis0,
															 &obb1_normal_separation_axis1,
															 &obb0_separation_axis1,
															 &obb0_separation_axis2,
															 &obb1_separation_axis0,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis0,
															 &obb1_normal_separation_axis2,
															 &obb0_separation_axis1,
															 &obb0_separation_axis2,
															 &obb1_separation_axis0,
															 &obb1_separation_axis1,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis1,
															 &obb1_normal_separation_axis0,
															 &obb0_separation_axis0,
															 &obb0_separation_axis2,
															 &obb1_separation_axis1,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis1,
															 &obb1_normal_separation_axis1,
															 &obb0_separation_axis0,
															 &obb0_separation_axis2,
															 &obb1_separation_axis0,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis1,
															 &obb1_normal_separation_axis2,
															 &obb0_separation_axis0,
															 &obb0_separation_axis2,
															 &obb1_separation_axis0,
															 &obb1_separation_axis1,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis2,
															 &obb1_normal_separation_axis0,
															 &obb0_separation_axis0,
															 &obb0_separation_axis1,
															 &obb1_separation_axis1,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis2,
															 &obb1_normal_separation_axis1,
															 &obb0_separation_axis0,
															 &obb0_separation_axis1,
															 &obb1_separation_axis0,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis2,
															 &obb1_normal_separation_axis2,
															 &obb0_separation_axis0,
															 &obb0_separation_axis1,
															 &obb1_separation_axis0,
															 &obb1_separation_axis1,
															 &interval_vector)) return false;

	return true;
}



float CollisionCalculation::FroatTruncation(float num)
{
	float SHIFT_NUM = 10000.0f;
	// 左にシフト
	num *= SHIFT_NUM;
	// 小数点切り捨て
	num = floorf(num);
	// 右にシフト
	num /= SHIFT_NUM;

	return num;
}



bool CollisionCalculation::DetermineWhetherTheRatioIsBetweenZeroAndOne(float ratio)
{
	if (ratio < 0.0f) return false;
	if (ratio > 1.0f) return false;

	return true;
}



bool CollisionCalculation::DetermineWhetherBothRatiosAreBetweenZeroAndOne(float ratio0,
																		  float ratio1)
{
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio0)) return false;
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio1)) return false;

	return true;
}



bool CollisionCalculation::DetermineWhetherXOfEitherLineSegmentIsZero(LineSegment* line_segment0,
																	  LineSegment* line_segment1)
{
	if (line_segment0->getpPosition()->x == 0) return true;
	if (line_segment1->getpPosition()->x == 0) return true;
	return false;
}



bool CollisionCalculation::DetermineWhetherXOfBothLineSegmentsIsZero(LineSegment* line_segment0,
																	 LineSegment* line_segment1)
{
	if (!line_segment0->getpPosition()->x == 0) return false;
	if (!line_segment1->getpPosition()->x == 0) return false;
	return true;
}



bool CollisionCalculation::DetermineWhetherItIsParallelFromSlope(float slope0,
																 float slope1)
{
	if (slope0 == slope1) return true;
	if (slope0 == -slope1) return true;
	return false;
}



bool CollisionCalculation::DetermineIfItIsLongerThanVector(Vector3D* vector,
														   float length)
{
	return vector->GetLengthSquare() <= (length * length);
}



bool CollisionCalculation::DetermineWhetherASphereCollidesAgainstEachSide(Sphere* sphere,
																		  Triangle* triangle)
{
	// 1つめの辺
	Vec3 temp_vector = *triangle->getpPoint1() - *triangle->getpPoint0();
	LineSegment temp_line_segment;
	temp_line_segment.Init(*triangle->getpPoint0(), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndSphere(nullptr, &temp_line_segment,
												sphere)) return true;

	// 2つめの辺
	temp_vector = *triangle->getpPoint2() - *triangle->getpPoint1();
	temp_line_segment.Init(*triangle->getpPoint1(), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndSphere(nullptr, &temp_line_segment,
												sphere)) return true;

	// 3つめの辺
	temp_vector = *triangle->getpPoint0() - *triangle->getpPoint2();
	temp_line_segment.Init(*triangle->getpPoint2(), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndSphere(nullptr, &temp_line_segment,
												sphere)) return true;

	return false;
}



bool CollisionCalculation::DetermineWhetherTheSphereIsSinkingInside(Sphere* sphere,
																	Triangle* triangle)
{
	Vec3 temp_vector = *triangle->getpPlane()->getpNormal() * -1;
	LineSegment temp_line_segment;
	temp_line_segment.Init(*sphere->getpPosition(), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndTriangle(nullptr, &temp_line_segment,
												  triangle)) return true;
	return false;
}



bool CollisionCalculation::DetermineWhetherThePlaneIsParallel(Plane* plane0,
															  Plane* plane1)
{
	float temp_dot = plane0->getpNormal()->CreateVectorDot(*plane1->getpNormal());
	if ((temp_dot >= 1.0f) || (temp_dot <= -1.0f)) return false;
	return true;
}



bool CollisionCalculation::DetermineIfATrianglePenetrates(bool* is_hit_segment_one,
														  Triangle* triangle0,
														  Triangle* triangle1)
{
	LineSegment temp_line_segment0;
	temp_line_segment0.Init(*triangle0->getpPoint0(), *triangle0->getpPoint1() - *triangle1->getpPoint0());
	LineSegment temp_line_segment1;
	temp_line_segment1.Init(*triangle0->getpPoint1(), *triangle0->getpPoint2() - *triangle1->getpPoint1());
	LineSegment temp_line_segment2;
	temp_line_segment2.Init(*triangle0->getpPoint2(), *triangle0->getpPoint0() - *triangle1->getpPoint2());

	bool is_hit0 = CollisionJudgmentOfLineSegmentAndTriangle(nullptr, &temp_line_segment0, triangle1);
	bool is_hit1 = CollisionJudgmentOfLineSegmentAndTriangle(nullptr, &temp_line_segment1, triangle1);
	bool is_hit2 = CollisionJudgmentOfLineSegmentAndTriangle(nullptr, &temp_line_segment2, triangle1);

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



bool CollisionCalculation::DetermineWhetherTheIntersectionPointIsWithinALineSegment(Vector3D* hit_point,
																					LineSegment* line_segment0,
																					LineSegment* line_segment1,
																					Vector3D intersection_point)
{
	// 比率を求める
	float ratio0 = (intersection_point.y - line_segment0->getpPosition()->y) / line_segment0->getpPosition()->y;
	float ratio1 = (intersection_point.x - line_segment1->getpPosition()->x) / line_segment1->getpPosition()->x;

	// 交点が線分内かどうか
	if (!DetermineWhetherBothRatiosAreBetweenZeroAndOne(ratio0, ratio1)) return false;

	// 交点の座標を引数に代入
	*hit_point = intersection_point;

	return true;
}



bool CollisionCalculation::IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(Vector3D* hit_point,
																							 LineSegment* line_segment0,
																							 LineSegment* line_segment1)
{
	// 衝突点の算出
	Vector3D intersection_point;
	intersection_point.x = line_segment0->getpPosition()->x;
	float slope1 = line_segment1->getSlopeOf2DLineSegment();
	float temp_x1 = intersection_point.x - line_segment1->getpPosition()->x;
	intersection_point.y = (slope1 * temp_x1) + line_segment1->getpPosition()->x;

	return DetermineWhetherTheIntersectionPointIsWithinALineSegment(hit_point,
																	line_segment0,
																	line_segment1,
																	intersection_point);

}



bool CollisionCalculation::IntersectionCalculationOf2DLineSegmentAnd2DLineSegment(Vector3D* hit_point,
																				  LineSegment* line_segment0,
																				  LineSegment* line_segment1)
{
	// 傾きを求める
	float slope0 = line_segment0->getSlopeOf2DLineSegment();
	float slope1 = line_segment1->getSlopeOf2DLineSegment();


	// 平行かの判定
	if (DetermineWhetherItIsParallelFromSlope(slope0, slope1)) return false;

	// 衝突点の算出
	Vector3D intersection_point;
	intersection_point.x = (slope0 * line_segment0->getpPosition()->x - slope1
							* line_segment1->getpPosition()->x
							+ line_segment1->getpPosition()->y
							- line_segment1->getpPosition()->y) / (slope0 - slope1);

	intersection_point.y = slope0 * (intersection_point.x - line_segment0->getpPosition()->x) + line_segment0->getpPosition()->y;

	return DetermineWhetherTheIntersectionPointIsWithinALineSegment(hit_point,
																	line_segment0,
																	line_segment1,
																	intersection_point);
}



bool CollisionCalculation::QuadraticEquationCalculationForLineSegmentsAndSpheres(QuadraticEquation* equation,
																				 LineSegment* line_segment,
																				 Sphere* sphere)
{
	// 解の公式を使用する為のa,b,cを求める
	// at^2 + bt + c = 0
	float temp_x = line_segment->getpPosition()->x - sphere->getpPosition()->x;
	float temp_y = line_segment->getpPosition()->y - sphere->getpPosition()->y;
	float temp_z = line_segment->getpPosition()->z - sphere->getpPosition()->z;



	equation->a_ = line_segment->getpVector()->GetSquareX()
		+ line_segment->getpVector()->GetSquareY()
		+ line_segment->getpVector()->GetSquareZ();
	equation->b_ = 2.0f * (line_segment->getpVector()->x
						   * temp_x + line_segment->getpVector()->y
						   * temp_y + line_segment->getpVector()->z * temp_z);
	equation->c_ = (temp_x * temp_x) + (temp_y * temp_y) + (temp_z * temp_z)
		- (sphere->getRadius() * sphere->getRadius());

	// 解の公式を解く
	if (equation->CalculateTheSolutionFormula()) return true;

	return false;
}



bool CollisionCalculation::QuadraticEquationCalculationForLineSegmentsAndCylinders(QuadraticEquation* equation,
																				   LineSegment* line_segment,
																				   Cylinder* cylinder)
{
	// 解の公式を使用する為のa,b,cを求める
	// at^2 + bt + c = 0
	Vector3D tempS = *cylinder->getpVector();

	// 各種内積値の算出
	float dot_vector_vector = line_segment->getpVector()->CreateVectorDot(*line_segment->getpVector());
	float dot_tempS_vector = tempS.CreateVectorDot(*line_segment->getpVector());
	float dot_position0_vector = cylinder->getpPosition()->CreateVectorDot(*line_segment->getpVector());
	float dot_tempS_tempS = tempS.CreateVectorDot(tempS);
	float dot_position0_tempS = cylinder->getpPosition()->CreateVectorDot(tempS);
	float dot_position0_position0 = cylinder->getpPosition()->CreateVectorDot(*cylinder->getpPosition());

	// 円柱が成立しない
	if (dot_tempS_tempS == 0.0f) return false;


	equation->a_ = dot_vector_vector - (dot_tempS_vector * dot_tempS_vector) / dot_tempS_tempS;
	equation->b_ = dot_position0_vector - (dot_position0_tempS * dot_tempS_vector) / dot_tempS_tempS;
	equation->c_ = dot_position0_position0 - (dot_position0_tempS * dot_position0_tempS) / dot_tempS_tempS;


	// 解の公式を解く
	if (equation->CalculateTheSolutionFormula()) return true;

	return false;
}



float CollisionCalculation::CalculateTheRatioOfTheFrontInTheLineSegment(float ratio0,
																		float ratio1)
{
	// 線分内の1番手前の比率を求める
	float ratio = 2.0f;

	if (DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio0))
	{
		if (ratio0 < ratio)
		{
			ratio = ratio0;
		}
	}
	if (DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio1))
	{
		if (ratio1 < ratio)
		{
			ratio = ratio1;
		}
	}

	return ratio;
}



float CollisionCalculation::CalculateTheDistanceTheLineSegmentReachesThePlane(Vector3D segment_vector,
																			  Plane* plane,
																			  float length)
{
	// 線分ベクトル(正規化済み)と平面法線の反対からcosΘを求める
	segment_vector.CreateNormalize();
	float cos_theta = segment_vector.CreateVectorDot((*plane->getpNormal() * -1));

	// 線分が平面に届く距離を算出
	return length / cos_theta;
}



void CollisionCalculation::CalculationOfCollisionLineSegment(LineSegment* hit_line_segment,
															 Plane* plane0,
															 Plane* plane1)
{
	// 外積により交差するベクトルを作成
	*hit_line_segment->getpVector() = plane0->getpNormal()->CreateVectorCross(*plane1->getpNormal());

	// 交差線分の始点を算出
	if (hit_line_segment->getpVector()->z != 0.0f)
	{
		hit_line_segment->getpPosition()->x = (plane0->getpNormal()->y
											   * plane1->getAdjustmetD()
											   - plane1->getpNormal()->y
											   * plane0->getAdjustmetD())
			/ hit_line_segment->getpVector()->z;
		hit_line_segment->getpPosition()->y = (plane1->getpNormal()->x
											   * plane0->getAdjustmetD()
											   - plane0->getpNormal()->x
											   * plane1->getAdjustmetD())
			/ hit_line_segment->getpVector()->z;
		hit_line_segment->getpPosition()->z = 0.0f;
	}
	else if (hit_line_segment->getpVector()->y != 0.0f)
	{
		hit_line_segment->getpPosition()->x = (plane1->getpNormal()->z
											   * plane0->getAdjustmetD()
											   - plane0->getpNormal()->z
											   * plane1->getAdjustmetD())
			/ hit_line_segment->getpVector()->y;
		hit_line_segment->getpPosition()->y = 0.0f;
		hit_line_segment->getpPosition()->z = (plane0->getpNormal()->x
											   * plane1->getAdjustmetD()
											   - plane1->getpNormal()->x
											   * plane0->getAdjustmetD())
			/ hit_line_segment->getpVector()->y;
	}
	else
	{
		hit_line_segment->getpPosition()->x = (plane0->getpNormal()->z
											   * plane1->getAdjustmetD()
											   - plane1->getpNormal()->z
											   * plane0->getAdjustmetD())
			/ hit_line_segment->getpVector()->x;
		hit_line_segment->getpPosition()->y = 0.0f;
		hit_line_segment->getpPosition()->z = (plane1->getpNormal()->y
											   * plane0->getAdjustmetD()
											   - plane0->getpNormal()->y
											   * plane1->getAdjustmetD())
			/ hit_line_segment->getpVector()->x;
	}
}



float CollisionCalculation::CalculateTheLengthOfTheProjectionLineSegment(Vector3D* my_separation_axis,
																		 Vector3D* other_separation_axis0,
																		 Vector3D* other_separation_axis1,
																		 Vector3D* other_separation_axis2)
{
	float r1 = fabsf(my_separation_axis->CreateVectorDot(*other_separation_axis0));
	float r2 = fabsf(my_separation_axis->CreateVectorDot(*other_separation_axis1));
	float r3 = (other_separation_axis2 != nullptr)
		? fabsf(my_separation_axis->CreateVectorDot(*other_separation_axis2)) : 0;

	return r1 + r2 + r3;
}



bool CollisionCalculation::DeterminationOfCollisionWithOrdinarySeparationAxis(Vector3D* my_separation_axis,
																			  Vector3D* my_separation_axis_normal,
																			  Vector3D* other_separation_axis0,
																			  Vector3D* other_separation_axis1,
																			  Vector3D* other_separation_axis2,
																			  Vector3D* interval_vector)
{
	float r_a = my_separation_axis->GetLength();
	float r_b = CalculateTheLengthOfTheProjectionLineSegment(my_separation_axis_normal,
															 other_separation_axis0,
															 other_separation_axis1,
															 other_separation_axis2);
	float length = fabsf(interval_vector->CreateVectorDot(*my_separation_axis_normal));
	if (length > (r_a + r_b)) return false;
	return true;
}



bool CollisionCalculation::DeterminationOfCollisionWithOuterAxisSeparationAxis(Vector3D* my_separation_axis_normal,
																			   Vector3D* other_separation_axis_normal,
																			   Vector3D* my_separation_axis0,
																			   Vector3D* my_separation_axis1,
																			   Vector3D* other_separation_axis0,
																			   Vector3D* other_separation_axis1,
																			   Vector3D* interval_vector)
{
	Vector3D temp_cross = my_separation_axis_normal
		->CreateVectorCross(*other_separation_axis_normal);
	float r_a = CalculateTheLengthOfTheProjectionLineSegment(&temp_cross,
															 my_separation_axis0,
															 my_separation_axis1);
	float r_b = CalculateTheLengthOfTheProjectionLineSegment(&temp_cross,
															 other_separation_axis0,
															 other_separation_axis1);
	float length = fabsf(interval_vector->CreateVectorDot(temp_cross));
	if (length > (r_a + r_b)) return false;
	return true;
}



float CollisionCalculation::CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(float line_segment_min,
																							float line_segment_max,
																							float any_component_of_a_point)
{
	float length = 0.0f;

	// 線分より小さいとき
	if (any_component_of_a_point < line_segment_min)
	{
		length += (line_segment_min - any_component_of_a_point)
			* (line_segment_min - any_component_of_a_point);
	}

	// 線分より大きいとき
	if (any_component_of_a_point > line_segment_max)
	{
		length += (line_segment_max - any_component_of_a_point)
			* (line_segment_max - any_component_of_a_point);
	}

	return length;
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenAABBAndAPoint(AABB* aabb, Vector3D* point)
{
	// 長さのべき乗で計算していく
	float length = 0.0f;

	// 各軸に対してべき乗を計算する
	length += CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(aabb->getpMin()->x,
																			  aabb->getpMax()->x,
																			  point->x);
	length += CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(aabb->getpMin()->y,
																			  aabb->getpMax()->y,
																			  point->y);
	length += CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(aabb->getpMin()->z,
																			  aabb->getpMax()->z,
																			  point->z);

	return (float)sqrt(length);
}