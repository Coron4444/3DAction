//================================================================================
//
//    衝突判定クラス(static)
//    Author : Araki Kai                                作成日 : 2017/11/27
//
//================================================================================

#ifndef	_COLLISION_JUDGMENT_H_
#define _COLLISION_JUDGMENT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <Vector3D.h>



//======================================================================
//
// クラス宣言
//
//======================================================================

class LineSegment;
class Sphere;
class Plane;
class Triangle;
class Cylinder;
class Capsule;
class OBB;
class QuadraticEquation;



//======================================================================
//
// クラス定義
//
//======================================================================

class CollisionJudgment
{
//------------------------------------------------------------
private:
	// デフォルトコンストラクタ
	CollisionJudgment() = delete;

	// コピーコンストラクタ
	CollisionJudgment(const CollisionJudgment& class_name) = delete;

	// 代入演算子のオーバーロード
	CollisionJudgment& operator = (const CollisionJudgment& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// 静的公開メンバ関数
	static bool HitCheck_Segment2D_Segment2D(Vector3D* hit_position, LineSegment* line_segment0, LineSegment* segment1);
	static bool HitCheck_Segment3D_Sphere(Vector3D* hit_position, LineSegment* line_segment, Sphere* sphere);
	static bool HitCheck_Segment3D_Plane(Vector3D* hit_position, LineSegment* line_segment, Plane* plane);
	static bool HitCheck_Segment3D_Triangle(Vector3D* hit_position, LineSegment* line_segment, Triangle* triangle);
	static bool HitCheck_Segment3D_Cylinder(Vector3D* hit_position, LineSegment* line_segment, Cylinder* cylinder);
	static bool HitCheck_Segment3D_Capsule(Vector3D* hit_position, LineSegment* line_segment, Capsule* capsule);
	static bool HitCheck_Sphere_Sphere(Vector3D* hit_vector, Sphere* sphere0, Sphere* sphere1);
	static bool HitCheck_Sphere_Plane(Vector3D* hit_vector, Sphere* sphere, Plane* plane);
	static bool HitCheck_Sphere_Triangle(Vector3D* hit_vector, Sphere* sphere, Triangle* triangle);
	static bool HitCheck_Sphere_Capsule(Vector3D* hit_vector, Sphere* sphere, Capsule* capsule);
	static bool HitCheck_Sphere_OBB(Vector3D* hit_vector, Sphere* sphere, OBB* obb);
	static bool HitCheck_Plane_Plane(LineSegment* cross_line_segment, Plane* plane0, Plane* plane1);
	static bool HitCheck_Plane_Triangle(Plane* plane, Triangle* triangle);
	static bool HitCheck_Triangle_Triangle(Triangle* triangle0, Triangle* triangle1);
	static bool HitCheck_Capsule_Capsule(Vector3D* hit_vector, Capsule* capsule0, Capsule* capsule1, Vector3D active_vector = {0.0f, 0.0f, 0.0f});
	static bool HitCheck_OBB_OBB(Vector3D* hit_vector, OBB* obb0, OBB* obb1);

//------------------------------------------------------------
private:
	// 条件
	static bool IsZeroOneSideSegmentVectorX(LineSegment* line_segment0, LineSegment* line_segment1);
	static bool IsZeroAllSegmentVectorX(LineSegment* line_segment0, LineSegment* line_segment1);
	static bool IsInSegment(float t);
	static bool IsAllInSegment(float t0, float t1);
	static bool IsParallelSegment(float a0, float a1);
	static bool IsHitSquare_Segment3D_Plane(LineSegment* line_segment, float length);
	static bool IsHit_Segment3D_Plane(LineSegment* line_segment, float length);
	static bool IsObtuseAngle_Segment3D_Capsule(Sphere* sphere0, Sphere* sphere1, Vec3* hit_position);
	static bool IsAcuteAngle_Segment3D_Capsule(Sphere* sphere0, Sphere* sphere1, Vec3* hit_position);
	static bool IsHitSquare_Sphere_Sphere(Vector3D* center_to_center_vector, float two_radius);
	static bool IsHit_Sphere_Plane(Sphere* sphere, Plane* plane);
	static bool IsHit_Sphere_TriangleSide(Sphere* sphere, Triangle* triangle);
	static bool IsHit_Sphere_Triangle(Sphere* sphere, Triangle* triangle);
	static bool IsHit_Plane_Plane(Plane* plane0, Plane* plane1);
	static bool IsHit_Triangle_Triangle(Triangle* triangle0, Triangle* triangle1, bool* is_hit_segment_one);

	// 計算
	static float FroatTruncation(float num);
	static bool  CrossPointCalculation_InAllSegment_Segment2D_Segment2D(Vector3D cross_point, Vector3D* hit_position, LineSegment* segment0, LineSegment* segment1);
	static bool  CrossPointCalculation_OneSideZeroSegment2D_Segment2D(Vector3D* hit_position, LineSegment* line_segment0, LineSegment* line_segment1);
	static bool  CrossPointCalculation_Segment2D_Segment2D(Vector3D* hit_position, LineSegment* line_segment0, LineSegment* line_segment1);
	static bool  QuadraticEquation_Calculation_Segment3D_Sphere(QuadraticEquation* equation, LineSegment* line_segment, Sphere* sphere);
	static float AskForTheFrontT_Segment3D_Sphere(float t0, float t1);
	static void  CrossPointCalculation_Segment3D_Sphere(Vector3D* hit_position, LineSegment* segment, float t);
	static float CalculateCollidingLength_Segment3D_Plane(Vector3D segment_vector, Plane* plane, float length);
	static void  CrossPointCalculation_Segment3D_Plane(Vector3D* hit_position, LineSegment* line_segment, float length);
	static void  CrossPointCalculation_Segment3D_Triangle(Vector3D* hit_position, Vec3 position);
	static bool  QuadraticEquation_Calculation_Segment3D_Cylinder(QuadraticEquation* equation, LineSegment* line_segment, Cylinder* cylinder);
	static float AskForTheFrontT_Segment3D_Cylinder(float t0, float t1);
	static void  CrossPointCalculation_Segment3D_Cylinder(Vector3D* hit_position, LineSegment* line_segment, float t);
	static void  CrossPointCalculation_Segment3D_Capsule(Vec3* hit_position, Vec3* temp_position);
	static void  NecessaryLengthCalculation_Sphere_Sphere(Vector3D* center_to_center_vector, float* two_radius, Sphere* sphere0, Sphere* sphere1);
	static void  AmountOfSqueezingVectorCalculation_Sphere_Sphere(Vector3D* hit_vector, Vector3D* center_to_center_vector, float two_radius);
	static void  AmountOfSqueezingVectorCalculation_Sphere_Plane(Vector3D* hit_vector, Sphere* sphere, Plane* plane);
	static void  AmountOfSqueezingVectorCalculation_Sphere_Triangle(Vector3D* hit_vector, Vector3D* vector);
	static void  AmountOfSqueezingVectorCalculation_Sphere_Capsule(Vector3D* hit_vector, Vec3* sphere_position, Vec3* cross_point, float* length);
	static void  AmountOfSqueezingVectorCalculation_Sphere_OBB(Vector3D* hit_vector, float radius, Vector3D* vector);
	static void  CalculationOfIntersectionSegments_Plane_Plane(LineSegment* cross_line_segment, Plane* plane0, Plane* plane1);
	static float LenSegOnSeparationAxis_OBB_OBB(Vector3D* separation_axis, Vector3D* e1, Vector3D* e2, Vector3D* e3 = nullptr);
	static bool  IsHit_NormalSeparationAxis_OBB_OBB(Vector3D* separation_axis, Vector3D* separation_axis_normal, Vector3D* e1, Vector3D* e2, Vector3D* e3, Vector3D* interval_vector);
	static bool  IsHit_CrossSeparationAxis_OBB_OBB(Vector3D* separation_axis_normal0, Vector3D* separation_axis_normal1, Vector3D* a_e1, Vector3D* a_e2, Vector3D* b_e1, Vector3D* b_e2, Vector3D* interval_vector);

};



#endif