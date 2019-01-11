//================================================================================
//!	@file	 CollisionCalculation.h
//!	@brief	 衝突計算Class
//! @details static
//!	@author  Kai Araki									@date 2018/11/06
//================================================================================
#ifndef	_COLLISION_CALCULATION_H_
#define _COLLISION_CALCULATION_H_



//****************************************
// インクルード文
//****************************************
#include <Vector3D.h>



//****************************************
// クラス宣言
//****************************************
class AABB;
class Capsule;
class Cylinder;
class LineSegment;
class OBB;
class Plane;
class Sphere;
class Triangle;
class QuadraticEquation;



//************************************************************														   
//! @brief   衝突計算Class
//!
//! @details 衝突計算のClass(static)
//************************************************************
class CollisionCalculation
{
//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief 2D線分と2D線分の衝突判定関数
	//! @details
	//! @param *hit_point     衝突点
	//! @param *line_segment0 線分
	//! @param *line_segment1 線分
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOf2DLineSegmentAnd2DLineSegment(Vector3D* hit_point,
																 LineSegment* line_segment0,
																 LineSegment* line_segment1);

	//----------------------------------------
	//! @brief 線分と球の衝突判定関数
	//! @details
	//! @param *hit_point    衝突点
	//! @param *line_segment 線分
	//! @param *sphere       球
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndSphere(Vector3D* hit_point,
														LineSegment* line_segment,
														Sphere* sphere);

	//----------------------------------------
	//! @brief 線分と平面の衝突判定関数
	//! @details
	//! @param *hit_point    衝突点
	//! @param *line_segment 線分
	//! @param *plane        平面
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndPlane(Vector3D* hit_point,
													   LineSegment* line_segment,
													   Plane* plane);

	//----------------------------------------
	//! @brief 線分と三角形平面の衝突判定関数
	//! @details
	//! @param *hit_point    衝突点
	//! @param *line_segment 線分
	//! @param *triangle     三角形平面
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndTriangle(Vector3D* hit_point,
														  LineSegment* line_segment,
														  Triangle* triangle);

	//----------------------------------------
	//! @brief 線分と円柱の衝突判定関数
	//! @details
	//! @param *hit_point    衝突点
	//! @param *line_segment 線分
	//! @param *cylinder     円柱
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndCylinder(Vector3D* hit_point,
														  LineSegment* line_segment,
														  Cylinder* cylinder);

	//----------------------------------------
	//! @brief 線分とカプセルの衝突判定関数
	//! @details
	//! @param *hit_point    衝突点
	//! @param *line_segment 線分
	//! @param *capsule      カプセル
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndCapsule(Vector3D* hit_point,
														 LineSegment* line_segment,
														 Capsule* capsule);

	//----------------------------------------
	//! @brief 球と球の衝突判定関数
	//! @details
	//! @param *hit_vector 衝突ベクトル
	//! @param *sphere0    球
	//! @param *sphere1    球
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndSphere(Vector3D* hit_vector,
												   Sphere* sphere0,
												   Sphere* sphere1);

	//----------------------------------------
	//! @brief 球と平面の衝突判定関数
	//! @details
	//! @param *hit_vector 衝突ベクトル
	//! @param *sphere     球
	//! @param *plane      球
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndPlane(Vector3D* hit_vector,
												  Sphere* sphere,
												  Plane* plane);

	//----------------------------------------
	//! @brief 球と三角形平面の衝突判定関数
	//! @details
	//! @param *hit_vector 衝突ベクトル
	//! @param *sphere     球
	//! @param *triangle   三角形平面
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndTriangle(Vector3D* hit_vector,
													 Sphere* sphere,
													 Triangle* triangle);

	//----------------------------------------
	//! @brief 球とカプセルの衝突判定関数
	//! @details
	//! @param *hit_vector 衝突ベクトル
	//! @param *sphere     球
	//! @param *capsule    カプセル
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndCapsule(Vector3D* hit_vector,
													Sphere* sphere,
													Capsule* capsule);

	//----------------------------------------
	//! @brief 球とOBBの衝突判定関数
	//! @details
	//! @param *hit_vector 衝突ベクトル
	//! @param *sphere     球
	//! @param *obb        OBB
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndOBB(Vector3D* hit_vector,
												Sphere* sphere,
												OBB* obb);

	//----------------------------------------
	//! @brief 平面と平面の衝突判定関数
	//! @details
	//! @param *hit_line_segment 衝突線分
	//! @param *plane0           平面
	//! @param *plane1           平面
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfPlaneAndPlane(LineSegment* hit_line_segment,
												 Plane* plane0,
												 Plane* plane1);

	//----------------------------------------
	//! @brief 平面と三角形平面の衝突判定関数
	//! @details
	//! @param *plane    平面
	//! @param *triangle 三角形平面
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfPlaneAndTriangle(Plane* plane,
													Triangle* triangle);

	//----------------------------------------
	//! @brief 三角形平面と三角形平面の衝突判定関数
	//! @details
	//! @param *triangle0 三角形平面
	//! @param *triangle0 三角形平面
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfTriangleAndTriangle(Triangle* triangle0,
													   Triangle* triangle1);

	//----------------------------------------
	//! @brief カプセルとカプセルの衝突判定関数
	//! @details
	//! @param *hit_vector    衝突ベクトル
	//! @param *capsule0      カプセル
	//! @param *capsule1      カプセル
	//! @param active_vector  補正用ベクトル
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfCapsuleAndCapsule(Vector3D* hit_vector,
													 Capsule* capsule0,
													 Capsule* capsule1,
													 Vector3D active_vector = {0.0f, 0.0f, 0.0f});

	//----------------------------------------
	//! @brief OBBとOBBの衝突判定関数
	//! @details
	//! @param *hit_vector 衝突ベクトル
	//! @param *obb0       OBB
	//! @param *obb1       OBB
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool CollisionJudgmentOfOBBAndOBB(Vector3D* hit_vector,
											 OBB* obb0,
											 OBB* obb1);

private:
	//----------------------------------------
	//! @brief floatの切り捨て関数
	//! @details
	//! @param num 切り捨てたい数値
	//! @retval float 切り捨てたfloat値
	//----------------------------------------
	static float FroatTruncation(float num);

	//----------------------------------------
	//! @brief 比率が0~1の間にあるか判定関数
	//! @details
	//! @param ratio 比率
	//! @retval bool 比率が0~1の間ならtrue
	//----------------------------------------
	static bool DetermineWhetherTheRatioIsBetweenZeroAndOne(float ratio);

	//----------------------------------------
	//! @brief 両方の比率が0~1の間にあるか判定関数
	//! @details
	//! @param ratio0 比率
	//! @param ratio1 比率
	//! @retval bool 比率が0~1の間ならtrue
	//----------------------------------------
	static bool DetermineWhetherBothRatiosAreBetweenZeroAndOne(float ratio0,
															   float ratio1);

	//----------------------------------------
	//! @brief どちらかの線分のXが0か判定関数
	//! @details
	//! @param *line_segment0 線分
	//! @param *line_segment1 線分
	//! @retval bool どちらかのXが0ならtrue
	//----------------------------------------
	static bool DetermineWhetherXOfEitherLineSegmentIsZero(LineSegment* line_segment0,
														   LineSegment* line_segment1);

	//----------------------------------------
	//! @brief 両方の線分のXが0か判定関数
	//! @details
	//! @param *line_segment0 線分
	//! @param *line_segment1 線分
	//! @retval bool 両方のXが0ならtrue
	//----------------------------------------
	static bool DetermineWhetherXOfBothLineSegmentsIsZero(LineSegment* line_segment0,
														  LineSegment* line_segment1);

	//----------------------------------------
	//! @brief 傾きから平行か判定関数
	//! @details
	//! @param slope0 傾き
	//! @param slope1 傾き
	//! @retval bool 平行ならtrue
	//----------------------------------------
	static bool DetermineWhetherItIsParallelFromSlope(float slope0, float slope1);

	//----------------------------------------
	//! @brief ベクトルより長いか判定関数
	//! @details
	//! @param *vector ベクトル
	//! @param length  長さ
	//! @retval bool ベクトルより長い場合true
	//----------------------------------------
	static bool DetermineIfItIsLongerThanVector(Vector3D* vector, float length);

	//----------------------------------------
	//! @brief 球が各辺に衝突しているか判定関数
	//! @details
	//! @param *sphere   球
	//! @param *triangle 三角形平面
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool DetermineWhetherASphereCollidesAgainstEachSide(Sphere* sphere,
															   Triangle* triangle);

	//----------------------------------------
	//! @brief 球が内部にめり込んでいるか判定関数
	//! @details
	//! @param *sphere   球
	//! @param *triangle 三角形平面
	//! @retval bool めり込んでいる場合true
	//----------------------------------------
	static bool DetermineWhetherTheSphereIsSinkingInside(Sphere* sphere,
														 Triangle* triangle);

	//----------------------------------------
	//! @brief 平面が平行か判定関数
	//! @details
	//! @param *plane0 平面
	//! @param *plane1 平面
	//! @retval bool 平行ならtrue
	//----------------------------------------
	static bool DetermineWhetherThePlaneIsParallel(Plane* plane0, Plane* plane1);

	//----------------------------------------
	//! @brief 三角形平面が貫いているか判定関数
	//! @details
	//! @param *is_hit_segment_one 1辺が貫通しているかフラグ
	//! @param *triangle0          三角形平面
	//! @param *triangle1          三角形平面
	//! @retval bool 貫いていればtrue
	//----------------------------------------
	static bool DetermineIfATrianglePenetrates(bool* is_hit_segment_one,
											   Triangle* triangle0,
											   Triangle* triangle1);

	//----------------------------------------
	//! @brief 交点が線分内か判定関数
	//! @details
	//! @param *hit_point         衝突点
	//! @param *line_segment0     線分
	//! @param *line_segment1     線分
	//! @param intersection_point 交点
	//! @retval bool 線分内の場合true
	//----------------------------------------
	static bool DetermineWhetherTheIntersectionPointIsWithinALineSegment(Vector3D* hit_point,
																		 LineSegment* line_segment0,
																		 LineSegment* line_segment1,
																		 Vector3D intersection_point);

	//----------------------------------------
	//! @brief Xが0の時の2D線分と2D線分の交点計算関数
	//! @details
	//! @param *hit_point     衝突点
	//! @param *line_segment0 線分
	//! @param *line_segment1 線分
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(Vector3D* hit_point,
																				  LineSegment* line_segment0,
																				  LineSegment* line_segment1);

	//----------------------------------------
	//! @brief 2D線分と2D線分の交点計算関数
	//! @details
	//! @param *hit_point     衝突点
	//! @param *line_segment0 線分
	//! @param *line_segment1 線分
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool IntersectionCalculationOf2DLineSegmentAnd2DLineSegment(Vector3D* hit_point,
																	   LineSegment* line_segment0,
																	   LineSegment* line_segment1);

	//----------------------------------------
	//! @brief 線分と球の2次方程式計算
	//! @details
	//! @param *equation     2次方程式
	//! @param *line_segment 線分
	//! @param *sphere       球
	//! @retval bool 2次方程式の解がある場合true
	//----------------------------------------
	static bool QuadraticEquationCalculationForLineSegmentsAndSpheres(QuadraticEquation* equation,
																	  LineSegment* line_segment,
																	  Sphere* sphere);

	//----------------------------------------
	//! @brief 線分と円柱の2次方程式計算
	//! @details
	//! @param *equation     2次方程式
	//! @param *line_segment 線分
	//! @param *cylinder     円柱
	//! @retval bool 2次方程式の解がある場合true
	//----------------------------------------
	static bool QuadraticEquationCalculationForLineSegmentsAndCylinders(QuadraticEquation* equation,
																		LineSegment* line_segment,
																		Cylinder* cylinder);

	//----------------------------------------
	//! @brief 線分内の1番手前の比率の算出関数
	//! @details
	//! @param ratio0 比率
	//! @param ratio1 比率
	//! @retval float 1番手前の比率
	//----------------------------------------
	static float CalculateTheRatioOfTheFrontInTheLineSegment(float ratio0, float ratio1);

	//----------------------------------------
	//! @brief 線分が平面に届く距離の算出関数
	//! @details
	//! @param segment_vector 線分ベクトル
	//! @param *plane         平面
	//! @param length         長さ
	//! @retval float 線分が平面に届く距離
	//----------------------------------------
	static float CalculateTheDistanceTheLineSegmentReachesThePlane(Vector3D segment_vector,
																   Plane* plane,
																   float length);

	//----------------------------------------
	//! @brief 衝突線分の算出関数
	//! @details
	//! @param *hit_line_segment 衝突線分
	//! @param *plane0           平面
	//! @param *plane1           平面
	//! @retval void なし
	//----------------------------------------
	static void CalculationOfCollisionLineSegment(LineSegment* hit_line_segment,
												  Plane* plane0,
												  Plane* plane1);

	//----------------------------------------
	//! @brief 投影線分の長さの算出関数
	//! @details
	//! @param *my_separation_axis     自分の分離軸
	//! @param *other_separation_axis0 相手の分離軸
	//! @param *other_separation_axis1 相手の分離軸
	//! @param *other_separation_axis2 相手の分離軸
	//! @retval float 投影線分の長さ
	//----------------------------------------
	static float CalculateTheLengthOfTheProjectionLineSegment(Vector3D* my_separation_axis,
															  Vector3D* other_separation_axis0,
															  Vector3D* other_separation_axis1,
															  Vector3D* other_separation_axis2 = nullptr);

	//----------------------------------------
	//! @brief 通常の分離軸との衝突判定関数
	//! @details
	//! @param *my_separation_axis        自分の分離軸
	//! @param *my_separation_axis_normal 自分の分離軸の単位ベクトル
	//! @param *other_separation_axis0    相手の分離軸
	//! @param *other_separation_axis1    相手の分離軸
	//! @param *other_separation_axis2    相手の分離軸
	//! @param *interval_vector           両方のOBB間のベクトル
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool DeterminationOfCollisionWithOrdinarySeparationAxis(Vector3D* my_separation_axis,
																   Vector3D* my_separation_axis_normal,
																   Vector3D* other_separation_axis0,
																   Vector3D* other_separation_axis1,
																   Vector3D* other_separation_axis2,
																   Vector3D* interval_vector);

	//----------------------------------------
	//! @brief 外積の分離軸との衝突判定関数
	//! @details
	//! @param *my_separation_axis_normal 自分の分離軸の単位ベクトル
	//! @param *my_separation_axis_normal 相手の分離軸の単位ベクトル
	//! @param *my_separation_axis0       自分の分離軸
	//! @param *my_separation_axis1       自分の分離軸
	//! @param *other_separation_axis0    相手の分離軸
	//! @param *other_separation_axis1    相手の分離軸
	//! @param *interval_vector           両方のOBB間のベクトル
	//! @retval bool 衝突している場合true
	//----------------------------------------
	static bool DeterminationOfCollisionWithOuterAxisSeparationAxis(Vector3D* my_separation_axis_normal,
																	Vector3D* other_separation_axis_normal,
																	Vector3D* my_separation_axis0,
																	Vector3D* my_separation_axis1,
																	Vector3D* other_separation_axis0,
																	Vector3D* other_separation_axis1,
																	Vector3D* interval_vector);

	//----------------------------------------
	//! @brief 1D線分と点の最短距離のべき乗算出関数
	//! @details
	//! @param line_segment_min         線分の始点
	//! @param line_segment_max         線分の終点
	//! @param any_component_of_a_point 点の任意の成分
	//! @retval float 1D線分と点の最短距離のべき乗
	//----------------------------------------
	static float CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(float line_segment_min,
																				 float line_segment_max,
																				 float any_component_of_a_point);

	//----------------------------------------
	//! @brief AABBと点の最短距離の算出関数
	//! @details
	//! @param *aabb  AABB
	//! @param *point 点
	//! @retval float AABBと点の最短距離
	//----------------------------------------
	float CalculateTheShortestDistanceBetweenAABBAndAPoint(AABB* aabb, Vector3D* point);


//====================
// 消去済み関数
//====================
private:
	CollisionCalculation() = delete;
	CollisionCalculation(const CollisionCalculation& class_name) = delete;
	CollisionCalculation& operator = (const CollisionCalculation& class_name) = delete;
};



#endif