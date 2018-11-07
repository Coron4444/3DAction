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

class Segment;
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
private :
	// デフォルトコンストラクタ
	CollisionJudgment() = delete;

	// コピーコンストラクタ
	CollisionJudgment(const CollisionJudgment& class_name) = delete;

	// 代入演算子のオーバーロード
	CollisionJudgment& operator = (const CollisionJudgment& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 静的公開メンバ関数
	static bool HitCheck_Segment2D_Segment2D(Vector3D* hit_position, const Segment* segment0, const Segment* segment1);
	static bool HitCheck_Segment3D_Sphere	(Vector3D* hit_position, const Segment* segment, const Sphere* sphere);
	static bool HitCheck_Segment3D_Plane	(Vector3D* hit_position, const Segment* segment, const Plane* plane);
	static bool HitCheck_Segment3D_Triangle	(Vector3D* hit_position, const Segment* segment, const Triangle* triangle);
	static bool HitCheck_Segment3D_Cylinder	(Vector3D* hit_position, const Segment* segment, const Cylinder* cylinder);
	static bool HitCheck_Segment3D_Capsule	(Vector3D* hit_position, const Segment* segment, const Capsule* capsule);
	static bool HitCheck_Sphere_Sphere		(Vector3D* hit_vector, const Sphere* sphere0, const Sphere* sphere1);
	static bool HitCheck_Sphere_Plane		(Vector3D* hit_vector, const Sphere* sphere, const Plane* plane);
	static bool HitCheck_Sphere_Triangle	(Vector3D* hit_vector, const Sphere* sphere, const Triangle* triangle);
	static bool HitCheck_Sphere_Capsule		(Vector3D* hit_vector, const Sphere* sphere, const Capsule* capsule);
	static bool HitCheck_Sphere_OBB			(Vector3D* hit_vector, Sphere* sphere, OBB* obb);
	static bool HitCheck_Plane_Plane		(Segment* cross_segment, const Plane* plane0, const Plane* plane1);
	static bool HitCheck_Plane_Triangle		(const Plane* plane, const Triangle* triangle);
	static bool HitCheck_Triangle_Triangle	(const Triangle* triangle0, const Triangle* triangle1);
	static bool HitCheck_Capsule_Capsule	(Vector3D* hit_vector, const Capsule* capsule0, const Capsule* capsule1, Vector3D active_vector = Vec3(0.0f, 0.0f, 0.0f));
	static bool HitCheck_OBB_OBB			(Vector3D* hit_vector, OBB* obb0, OBB* obb1);


//------------------------------------------------------------
private :
	// 条件
	static bool IsZeroOneSideSegmentVectorX	   (const Segment* segment0, const Segment* segment1);
	static bool IsZeroAllSegmentVectorX		   (const Segment* segment0, const Segment* segment1);
	static bool IsInSegment					   (float t);
	static bool IsAllInSegment				   (float t0, float t1);
	static bool IsParallelSegment			   (float a0, float a1);
	static bool IsHitSquare_Segment3D_Plane	   (const Segment* segment, float length);
	static bool IsHit_Segment3D_Plane		   (const Segment* segment, float length);
	static bool IsObtuseAngle_Segment3D_Capsule(const Sphere* sphere0, const Sphere* sphere1, const Vec3* hit_position);
	static bool IsAcuteAngle_Segment3D_Capsule (const Sphere* sphere0, const Sphere* sphere1, const Vec3* hit_position);
	static bool IsHitSquare_Sphere_Sphere	   (const Vector3D* center_to_center_vector, float two_radius);
	static bool IsHit_Sphere_Plane			   (const Sphere* sphere, const Plane* plane);
	static bool IsHit_Sphere_TriangleSide	   (const Sphere* sphere, const Triangle* triangle);
	static bool IsHit_Sphere_Triangle		   (const Sphere* sphere, const Triangle* triangle);
	static bool IsHit_Plane_Plane			   (const Plane* plane0, const Plane* plane1);
	static bool IsHit_Triangle_Triangle		   (const Triangle* triangle0, const Triangle* triangle1, bool* is_hit_segment_one);

	// 計算
	static float FroatTruncation									   (float num);
	static bool  CrossPointCalculation_InAllSegment_Segment2D_Segment2D(Vector3D cross_point, Vector3D* hit_position, const Segment* segment0, const Segment* segment1);
	static bool  CrossPointCalculation_OneSideZeroSegment2D_Segment2D  (Vector3D* hit_position, const Segment* segment0, const Segment* segment1);
	static bool  CrossPointCalculation_Segment2D_Segment2D			   (Vector3D* hit_position, const Segment* segment0, const Segment* segment1);
	static bool  QuadraticEquation_Calculation_Segment3D_Sphere		   (QuadraticEquation* equation, const Segment* segment, const Sphere* sphere);
	static float AskForTheFrontT_Segment3D_Sphere					   (float t0, float t1);
	static void  CrossPointCalculation_Segment3D_Sphere				   (Vector3D* hit_position, const Segment* segment, float t);
	static float CalculateCollidingLength_Segment3D_Plane			   (Vector3D segment_vector, const Plane* plane, float length);
	static void  CrossPointCalculation_Segment3D_Plane				   (Vector3D* hit_position, Segment segment, float length);
	static void  CrossPointCalculation_Segment3D_Triangle			   (Vector3D* hit_position, Vec3 position);
	static bool  QuadraticEquation_Calculation_Segment3D_Cylinder	   (QuadraticEquation* equation, const Segment* segment, const Cylinder* cylinder);
	static float AskForTheFrontT_Segment3D_Cylinder					   (float t0, float t1);
	static void  CrossPointCalculation_Segment3D_Cylinder			   (Vector3D* hit_position, const Segment* segment, float t);
	static void  CrossPointCalculation_Segment3D_Capsule			   (Vec3* hit_position, const Vec3* temp_position);
	static void  NecessaryLengthCalculation_Sphere_Sphere			   (Vector3D* center_to_center_vector, float* two_radius, const Sphere* sphere0, const Sphere* sphere1);
	static void  AmountOfSqueezingVectorCalculation_Sphere_Sphere	   (Vector3D* hit_vector, Vector3D* center_to_center_vector, float two_radius);
	static void  AmountOfSqueezingVectorCalculation_Sphere_Plane	   (Vector3D* hit_vector, const Sphere* sphere, const Plane* plane);
	static void  AmountOfSqueezingVectorCalculation_Sphere_Triangle	   (Vector3D* hit_vector, Vector3D* vector);
	static void  AmountOfSqueezingVectorCalculation_Sphere_Capsule	   (Vector3D* hit_vector, const Vec3*  sphere_position, const Vec3*  cross_point, const float* length);
	static void  AmountOfSqueezingVectorCalculation_Sphere_OBB		   (Vector3D* hit_vector, const float* radius, const Vector3D* vector);
	static void  CalculationOfIntersectionSegments_Plane_Plane		   (Segment* cross_segment, const Plane* plane0, const Plane* plane1);
	static float LenSegOnSeparationAxis_OBB_OBB						   (Vector3D* separation_axis, Vector3D* e1, Vector3D* e2, Vector3D* e3 = nullptr);
	static bool  IsHit_NormalSeparationAxis_OBB_OBB					   (Vector3D* separation_axis, Vector3D* separation_axis_normal, Vector3D* e1, Vector3D* e2, Vector3D* e3, Vector3D* interval_vector);
	static bool  IsHit_CrossSeparationAxis_OBB_OBB					   (Vector3D* separation_axis_normal0, Vector3D* separation_axis_normal1, Vector3D* a_e1, Vector3D* a_e2, Vector3D* b_e1, Vector3D* b_e2, Vector3D* interval_vector);

};



#endif