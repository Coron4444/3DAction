//================================================================================
//
//    �Փ˔���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2017/11/27
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
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
// [ �Փ˔���֐�(2D�����F2D����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment2D_Segment2D(Vector3D* hit_position, const Segment* segment0, const Segment* segment1)
{
	// X�������̃x�N�g����0���ǂ���
	if (IsZeroOneSideSegmentVectorX(segment0, segment1))
	{
		// ������X�x�N�g����0�A�܂蕽�s�ł��� 
		if (IsZeroAllSegmentVectorX(segment0, segment1)) return false;


		// �ǂ��炪0��
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
// [ �Փ˔���֐�(3D�����F��) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Sphere(Vector3D* hit_position, const Segment* segment, const Sphere* sphere)
{
	// �񎟕������̌v�Z
	QuadraticEquation equation;
	

	// �񎟕������ɉ������邩
	bool is_calculable = QuadraticEquation_Calculation_Segment3D_Sphere(&equation, segment, sphere);

	if(!is_calculable) return false;


	// ��������1�Ԏ�O��t�����߂�
	float t = AskForTheFrontT_Segment3D_Sphere(equation.t0_, equation.t1_);

	if(!IsInSegment(t)) return false;


	// ��_���Z�o
	CrossPointCalculation_Segment3D_Sphere(hit_position, segment, t);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(3D�����F��������) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Plane(Vector3D* hit_position, const Segment* segment, const Plane* plane)
{
	// �\���`�F�b�N
	float temp_dot = segment->vector_.CreateVectorDot(plane->normal_vector_);
	if (temp_dot >= 0.0f) return false;

	// �����n�_�ƕ��ʂƂ̋������Z�o
	float length = plane -> Length_Point(segment->position_);


	// �����Ɛ����̔�r( 2�� )
	if (IsHitSquare_Segment3D_Plane(segment, length)) return false;


	// ���������ʂɓ͂��������Z�o
	float temp_length = CalculateCollidingLength_Segment3D_Plane(segment->vector_, plane, length);

	if (IsHit_Segment3D_Plane(segment, temp_length)) return false;


	// ���ʂƂ̌�_���Z�o
	CrossPointCalculation_Segment3D_Plane(hit_position, *segment, temp_length);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(3D�����F�O�p����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Triangle(Vector3D* hit_position, const Segment* segment, const Triangle* triangle)
{
	// �������ʂƂ̓����蔻��
	Vector3D temp_position;

	if (!HitCheck_Segment3D_Plane( &temp_position, segment, &triangle->plane_)) return false;


	// ��_��3�p�`�����̔���
	if(!triangle->CheckInnerPoint(temp_position)) return false;


	// ���ʂƂ̌�_���Z�o
	CrossPointCalculation_Segment3D_Triangle(hit_position, temp_position);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(3D�����F�~��) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Cylinder(Vector3D* hit_position, const Segment* segment, const Cylinder* cylinder)
{
	// �񎟕������̌v�Z
	QuadraticEquation equation;
	
	// �񎟕������ɉ������邩
	bool is_calculable = QuadraticEquation_Calculation_Segment3D_Cylinder(&equation, segment, cylinder);

	if(!is_calculable) return false;


	// ��������1�Ԏ�O��t�����߂�
	float t = AskForTheFrontT_Segment3D_Cylinder(equation.t0_, equation.t1_);

	if(!IsInSegment(t)) return false;


	// ��_���Z�o
	CrossPointCalculation_Segment3D_Cylinder(hit_position, segment, t);
	
	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(3D�����F�J�v�Z��) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Segment3D_Capsule(Vector3D* hit_position, const Segment* segment, const Capsule* capsule)
{
	Vector3D temp_hit_position;

	// �O�����ƏՓ˂��Ă��邩�H
	if(HitCheck_Segment3D_Sphere(&temp_hit_position, segment, &capsule->sphere0_))
	{
		// �݊p���ǂ���
		if (IsObtuseAngle_Segment3D_Capsule(&capsule->sphere1_, &capsule->sphere0_, &temp_hit_position))
		{
			CrossPointCalculation_Segment3D_Capsule(hit_position, &temp_hit_position);

			return true;
		}
	}


	// �㔼���ƏՓ˂��Ă��邩�H
	if( HitCheck_Segment3D_Sphere(&temp_hit_position, segment, &capsule->sphere1_))
	{
		// �݊p���ǂ���
		if (IsObtuseAngle_Segment3D_Capsule(&capsule->sphere0_, &capsule->sphere1_, &temp_hit_position))
		{
			CrossPointCalculation_Segment3D_Capsule(hit_position, &temp_hit_position);

			return true;
		}
	}


	// �~���ƏՓ˂��Ă��邩�H
	if(HitCheck_Segment3D_Cylinder(&temp_hit_position, segment, &capsule->cylinder_))
	{
		// �S�ĉs�p���ǂ���
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
// [ �Փ˔���֐�(���F��) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_Sphere(Vector3D* hit_vector, const Sphere* sphere0, const Sphere* sphere1)
{
	// ���S�ԋ����Ɣ��a�̍��v�ɂ��Փ˔���( 2�� )
	Vector3D center_to_center_vector;
	float    two_radius;

	NecessaryLengthCalculation_Sphere_Sphere(&center_to_center_vector, &two_radius, sphere0, sphere1);

	if (!IsHitSquare_Sphere_Sphere(&center_to_center_vector, two_radius)) return false;


	// �߂荞�݋���Z�o
	AmountOfSqueezingVectorCalculation_Sphere_Sphere(hit_vector, &center_to_center_vector, two_radius);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(���F��������) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_Plane(Vector3D* hit_vector, const Sphere* sphere, const Plane* plane)
{
	// ���ʂƋ��̒��S�����Ɣ��a�Ƃ̔���
	if ( !IsHit_Sphere_Plane(sphere, plane)) return false;

	// �߂荞�݋���Z�o
	AmountOfSqueezingVectorCalculation_Sphere_Plane(hit_vector, sphere, plane);

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(���F�O�p����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_Triangle(Vector3D* hit_vector, const Sphere* sphere, const Triangle* triangle)
{
	// �������ʂƂ̏Փ˔���
	Vector3D temp_hit_vector;

	if (!HitCheck_Sphere_Plane(&temp_hit_vector, sphere, &triangle->plane_)) return false;

	// �O�p�`�̊e�ӂ��Փ˂��Ă��邩
	if (IsHit_Sphere_TriangleSide(sphere, triangle))
	{
		AmountOfSqueezingVectorCalculation_Sphere_Triangle(hit_vector, &temp_hit_vector);

		return true;
	}

	// �����O�p�`�̓����ɂ߂荞��ł��邩
	if (IsHit_Sphere_Triangle(sphere, triangle)) 
	{
		AmountOfSqueezingVectorCalculation_Sphere_Triangle(hit_vector, &temp_hit_vector);

		return true;
	}


	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(���F�J�v�Z��) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_Capsule(Vector3D* hit_vector, const Sphere* sphere, const Capsule* capsule)
{
	// ���̒��S�ƃJ�v�Z���Ƃ̋������Z�o
	Vec3  cross_point;
	float temp_t;
	float length = ShortestDistance_Segment_Point(&cross_point, &temp_t, &capsule->segment_, 
		                                              &sphere->position_ );

	// ������2�̔��a�Ƃ̍��v�̔�r
	float two_radius = sphere->radius_ + capsule->radius_;
	if (length > two_radius) return false;

	// �߂荞�݋���Z�o
	length = two_radius - length;
	AmountOfSqueezingVectorCalculation_Sphere_Capsule(hit_vector, 
	                                                  &sphere->position_,
	                                                  &cross_point,
                                                      &length);
	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(���FOBB) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Sphere_OBB(Vector3D* hit_vector, Sphere* sphere, OBB* obb)
{
	// ����OBB�̍ŒZ�����̃x�N�g�����Z�o
	Vector3D temp_vector = ShortestDistance_OBB_Point(obb, &sphere->position_);

	// �����Ɣ��a�̔�r
	if (FroatTruncation(temp_vector.GetLength()) > sphere->radius_) return false;

	// �߂荞�݋���Z�o
	
	AmountOfSqueezingVectorCalculation_Sphere_OBB(hit_vector, 
												  &sphere->radius_,
												  &temp_vector );
	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(�������ʁF��������) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Plane_Plane(Segment* cross_segment, const Plane* plane0, const Plane* plane1)
{
	// ���ʂ̖@����p���āA���҂����s�ł��邩�̊m�F������(�Փ˂��邩�̊m�F)
	if (!IsHit_Plane_Plane(plane0, plane1)) return false;
	
	// �������������߂�
	if (cross_segment != nullptr)
	{
		CalculationOfIntersectionSegments_Plane_Plane(cross_segment, plane0, plane1);
	}

	return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(�������ʁF�O�p����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Plane_Triangle(const Plane* plane, const Triangle* triangle)
{
	int side0 = (int)plane->Length_Point(triangle->point_[0]);
	int side1 = (int)plane->Length_Point(triangle->point_[1]);

	// ����2�_��������������
	if ((side0 && !side1) || (!side0 && side1)) return true;

	int side2 = (int)plane->Length_Point(triangle->point_[2]);

	// ����2�_��������������
	if ((side1 && !side2) || (!side1 && side2)) return true;

	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(�O�p���ʁF�O�p����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Triangle_Triangle(const Triangle* triangle0, const Triangle* triangle1)
{
	bool is_hit_segment_one = false;

	// �Е��̎O�p�`�������Е����т��Ă��邩
	if (IsHit_Triangle_Triangle(triangle0, triangle1, &is_hit_segment_one)) return true;

	// �����Е����`�F�b�N
	if (IsHit_Triangle_Triangle(triangle1, triangle0, &is_hit_segment_one)) return true;

	// ���݂���1�ӂ��ђʂ��Ă��邩
	if (is_hit_segment_one) return true;

	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���֐�(�J�v�Z���F�J�v�Z��) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_Capsule_Capsule(Vector3D* hit_vector, const Capsule* capsule0, const Capsule* capsule1, Vector3D active_vector)
{
	Vector3D cross_point0;
	Vector3D cross_point1;
	float t0;
	float t1;

	// �����Ԃ̍ŒZ�����Ɣ��a�̍��v���Z�o
	float length = ShortestDistance_Segment_Segment(&cross_point0, &cross_point1, &t0, &t1, &capsule0 -> segment_, &capsule1 -> segment_);
	float center_to_center_length = capsule0->radius_ + capsule1->radius_;

	// �����̔�r
	bool is_hit = length <= center_to_center_length;

	if (!is_hit) return false;
	
	// �߂荞�݃x�N�g���̍쐬
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
// [ �Փ˔���֐�(OBB�FOBB) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionJudgment::HitCheck_OBB_OBB(Vector3D* hit_vector, OBB* obb0, OBB* obb1)
{
	hit_vector = hit_vector;

	// ���x�N�g���̊m��
	Vector3D n_a_e1 = *obb0->axis_.GetForawrd();
	Vector3D n_a_e2 = *obb0->axis_.GetRight();
	Vector3D n_a_e3 = *obb0->axis_.GetUp();
				
	Vector3D n_b_e1 = *obb1->axis_.GetForawrd();
	Vector3D n_b_e2 = *obb1->axis_.GetRight();
	Vector3D n_b_e3 = *obb1->axis_.GetUp();

	// �������̔����̒������m��
	Vector3D a_e1 = *obb0->GetVectorForwardHalf();
	Vector3D a_e2 = *obb0->GetVectorRightHalf();
	Vector3D a_e3 = *obb0->GetVectorUpHalf();

	Vector3D b_e1 = *obb1->GetVectorForwardHalf();
	Vector3D b_e2 = *obb1->GetVectorRightHalf();
	Vector3D b_e3 = *obb1->GetVectorUpHalf();

	// ���҂̒��S�Ԃ̋���
	Vector3D interval_vector = obb0->position_ - obb1->position_;

	// �������Fa_e1, a_e2, a_e3
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&a_e1, &n_a_e1, &b_e1, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&a_e2, &n_a_e2, &b_e1, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&a_e3, &n_a_e3, &b_e1, &b_e2, &b_e3, &interval_vector)) return false;

	// �������Fb_e1, b_e2, b_e3
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&b_e1, &n_b_e1, &a_e1, &a_e2, &a_e3, &interval_vector)) return false;
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&b_e2, &n_b_e2, &a_e1, &a_e2, &a_e3, &interval_vector)) return false;
	if (!IsHit_NormalSeparationAxis_OBB_OBB(&b_e3, &n_b_e3, &a_e1, &a_e2, &a_e3, &interval_vector)) return false;

	// �������FC11, C12, C13
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e1, &n_b_e1, &a_e2, &a_e3, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e1, &n_b_e2, &a_e2, &a_e3, &b_e1, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e1, &n_b_e3, &a_e2, &a_e3, &b_e1, &b_e2, &interval_vector)) return false;

	// �������FC21, C22, C23
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e2, &n_b_e1, &a_e1, &a_e3, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e2, &n_b_e2, &a_e1, &a_e3, &b_e1, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e2, &n_b_e3, &a_e1, &a_e3, &b_e1, &b_e2, &interval_vector)) return false;

	// �������FC31, C32, C33
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e3, &n_b_e1, &a_e1, &a_e2, &b_e2, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e3, &n_b_e2, &a_e1, &a_e2, &b_e1, &b_e3, &interval_vector)) return false;
	if (!IsHit_CrossSeparationAxis_OBB_OBB(&n_a_e3, &n_b_e3, &a_e1, &a_e2, &b_e1, &b_e2, &interval_vector)) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ �ǂ��炩1���ۂ��̐�����X�x�N�g����0���̔���֐� ]
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
// [ �����̐�����X�x�N�g����0���̔���֐� ]
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
// [ t�����������̔���֐� ]
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
// [ 2��t�����������̔���֐� ]
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
// [ 2��t�����������̔���֐� ]
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
// [ 2��̋����ŏՓ˂��邩�̔���֐�(3D�����F��������) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHitSquare_Segment3D_Plane(const Segment* segment, float length)
{
	return segment->vector_.GetLengthSquare() < (length * length);
}



//--------------------------------------------------------------------------------
//
// [ �Փ˂��邩�̔���֐�(3D�����F��������) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_Segment3D_Plane(const Segment* segment, float length)
{
	return length > segment->vector_.GetLength();
}



//--------------------------------------------------------------------------------
//
// [ �݊p���̔���֐�(3D�����F�J�v�Z��) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsObtuseAngle_Segment3D_Capsule(const Sphere* sphere0, const Sphere* sphere1, 
														const Vec3* hit_position)
{
	return IsObtuseAngle(sphere0->position_, sphere1->position_, *hit_position);
}



//--------------------------------------------------------------------------------
//
// [ �S�ĉs�p���̔���֐�(3D�����F�J�v�Z��) ]
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
// [ 2��̋����ŏՓ˂��邩�̔���֐�(���F��) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHitSquare_Sphere_Sphere(const Vector3D* center_to_center_vector, 
												  float two_radius)
{
	return center_to_center_vector->GetLengthSquare() <= (two_radius * two_radius);
}



//--------------------------------------------------------------------------------
//
// [ �Փ˂��邩�̔���֐�(���F��������) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::IsHit_Sphere_Plane(const Sphere* sphere, const Plane* plane)
{
	return sphere->radius_ > plane->Length_Point(sphere->position_);
}



//--------------------------------------------------------------------------------
//
// [ �Փ˂��邩����֐�(���F�O�p���ʂ̕�) ]
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
// [ �Փ˂��邩����֐�(���F�O�p����) ]
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
// [ �Փ˂��邩����֐�(�������ʁF����) ]
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
// [ �Փ˂��邩����֐�(�O�p���ʁF�O�p����) ]
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
// [ float�̐؂�̂Ċ֐� ]
//
//--------------------------------------------------------------------------------

float CollisionJudgment::FroatTruncation(float num)
{
	const float SHIFT_NUM = 10000.0f;
	// ���ɃV�t�g
	num *= SHIFT_NUM;
	// �����_�؂�̂�
	num = floorf(num);
	// �E�ɃV�t�g
	num /= SHIFT_NUM;

	return num;
}



//--------------------------------------------------------------------------------
//
// [ ��_�����������̌v�Z�֐�(2D�����F2D����) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::CrossPointCalculation_InAllSegment_Segment2D_Segment2D(Vector3D cross_point, Vector3D* hit_position, 
																			   const Segment* segment0, 
																			   const Segment* segment1)
{
	// t�����߂�
	float t0 = (cross_point.y - segment0->position_.y) / segment0->position_.y;
	float t1 = (cross_point.x - segment1->position_.x) / segment1->position_.x;

	// ��_�����������ǂ���
	if (!IsAllInSegment(t0, t1)) return false;

	// ��_�̍��W�������ɑ��
	*hit_position = cross_point;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ �Е����x�N�g��X0�̎��̌�_�v�Z�֐�(2D�����F2D����) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::CrossPointCalculation_OneSideZeroSegment2D_Segment2D(Vector3D* hit_position, const Segment* segment0, 
																			 const Segment* segment1)
{
	// ��_�����߂�
	Vector3D cross_point;

	cross_point.x = segment0->position_.x;
	
	float a1      = segment1->GetSlopeSegment2D();
	float temp_x1 = cross_point.x - segment1->position_.x;

	cross_point.y = (a1 * temp_x1) + segment1->position_.x;

	return CrossPointCalculation_InAllSegment_Segment2D_Segment2D(cross_point, hit_position, segment0, segment1);

}



//--------------------------------------------------------------------------------
//
// [ ��_�v�Z�֐�(2D�����F2D���� ) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::CrossPointCalculation_Segment2D_Segment2D(Vector3D* hit_position, const Segment* segment0, 
																  const Segment* segment1)
{
	// �X�������߂�
	float a0 = segment0->GetSlopeSegment2D();
	float a1 = segment1->GetSlopeSegment2D();


	// ���s���̔���
	if (IsParallelSegment(a0, a1)) return false;


	// ��_�����߂�
	Vector3D cross_point;
	cross_point.x = (a0 * segment0->position_.x - a1 * segment1->position_.x + segment1->position_.y - segment1->position_.y) 
		             / (a0 - a1);

	cross_point.y = a0 * (cross_point.x - segment0->position_.x) + segment0->position_.y;

	return CrossPointCalculation_InAllSegment_Segment2D_Segment2D(cross_point, hit_position, segment0, segment1);
}



//--------------------------------------------------------------------------------
//
// [ 2���������v�Z�֐�(3D�����F��) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::QuadraticEquation_Calculation_Segment3D_Sphere(QuadraticEquation* equation, const Segment* segment, 
																	   const Sphere* sphere)
{
	// ���̌������g�p����ׂ�a,b,c�����߂�
	// at^2 + bt + c = 0
	float temp_x = segment->position_.x - sphere->position_.x;
	float temp_y = segment->position_.y - sphere->position_.y;
	float temp_z = segment->position_.z - sphere->position_.z;

	 

	equation->a_ = segment->vector_.GetSquareX() + segment->vector_.GetSquareY() + segment->vector_.GetSquareZ();
	equation->b_ = 2.0f * (segment->vector_.x * temp_x + segment->vector_.y * temp_y + segment->vector_.z * temp_z);
	equation->c_ = (temp_x * temp_x) + (temp_y * temp_y) + (temp_z * temp_z) - (sphere->radius_ * sphere->radius_);

	// ���̌���������
	if(equation->CalculateTheSolutionFormula()) return true;

	return false;
}



//--------------------------------------------------------------------------------
//
// [ ��������1�Ԏ�O��t�����߂�֐�(3D�����F��) ]
//
//--------------------------------------------------------------------------------

float CollisionJudgment::AskForTheFrontT_Segment3D_Sphere(float t0, float t1)
{
	// ��������1�Ԏ�O��t�����߂�
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
// [ ��_�v�Z�֐�(3D�����F��) ]
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
// [ ���������ʂɓ͂������̌v�Z�֐�(3D�����F��������) ]
//
//--------------------------------------------------------------------------------

float CollisionJudgment::CalculateCollidingLength_Segment3D_Plane(Vector3D segment_vector, const Plane* plane, float length)
{
	// �����x�N�g��(���K���ς�)�ƕ��ʖ@���̔��΂���cos�������߂�
	segment_vector.CreateNormalize();

	float cos_theta = segment_vector.CreateVectorDot((plane->normal_vector_ * -1));


	// ���������ʂɓ͂��������Z�o
	return length / cos_theta;
}



//--------------------------------------------------------------------------------
//
// [ ��_�v�Z�֐�(3D�����F��������) ]
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
// [ ��_�v�Z�֐�(3D�����F�O�p����) ]
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
// [ 2���������v�Z�֐�(3D�����F�~��) ]
//
//--------------------------------------------------------------------------------

bool CollisionJudgment::QuadraticEquation_Calculation_Segment3D_Cylinder(QuadraticEquation* equation, const Segment* segment, 
																		 const Cylinder* cylinder)
{
	// ���̌������g�p����ׂ�a,b,c�����߂�
	// at^2 + bt + c = 0
	Vector3D tempS = cylinder->position1_ - cylinder->position0_;

	// �e����ϒl�̎Z�o
	float dot_vector_vector	      = segment->vector_.CreateVectorDot(segment->vector_);
	float dot_tempS_vector	      = tempS.CreateVectorDot(segment->vector_);
	float dot_position0_vector	  = cylinder->position0_.CreateVectorDot(segment->vector_);
	float dot_tempS_tempS	      = tempS.CreateVectorDot(tempS);
	float dot_position0_tempS	  = cylinder->position0_.CreateVectorDot(tempS);
	float dot_position0_position0 = cylinder->position0_.CreateVectorDot(cylinder->position0_);

	// �~�����������Ȃ�
	if (dot_tempS_tempS == 0.0f) return false;


	equation->a_ = dot_vector_vector       - (dot_tempS_vector * dot_tempS_vector      ) / dot_tempS_tempS;
	equation->b_ = dot_position0_vector    - (dot_position0_tempS * dot_tempS_vector   ) / dot_tempS_tempS;
	equation->c_ = dot_position0_position0 - (dot_position0_tempS * dot_position0_tempS) / dot_tempS_tempS;


	// ���̌���������
	if(equation->CalculateTheSolutionFormula()) return true;

	return false;
}



//--------------------------------------------------------------------------------
//
// [ ��������1�Ԏ�O��t�����߂�֐�(3D�����F�~��) ]
//
//--------------------------------------------------------------------------------

float CollisionJudgment::AskForTheFrontT_Segment3D_Cylinder(float t0, float t1)
{
	// ��������1�Ԏ�O��t�����߂�
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
// [ ��_�v�Z�֐�(3D�����F�~��) ]
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
// [ ��_�v�Z�֐�(3D�����F�J�v�Z��) ]
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
// [ �K�v�Ȓ������Z�o�֐�(���F��) ]
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
// [ �߂荞�݃x�N�g���Z�o�֐�(���F��) ]
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
// [ �߂荞�݃x�N�g���Z�o�֐�(���F��������) ]
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
// [ �߂荞�݃x�N�g���Z�o�֐�(���F�O�p����) ]
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
// [ �߂荞�݃x�N�g���Z�o�֐�(���F�J�v�Z��) ]
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
// [ �߂荞�݃x�N�g���Z�o�֐�(���FOBB) ]
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
// [ ���������̎Z�o�֐�(�������ʁF��������) ]
//
//--------------------------------------------------------------------------------

void CollisionJudgment::CalculationOfIntersectionSegments_Plane_Plane(Segment* cross_segment, const Plane* plane0, 
																	  const Plane* plane1)
{
	// �O�ςɂ���������x�N�g�����쐬
	cross_segment->vector_ = plane0->normal_vector_.CreateVectorCross(plane1 -> normal_vector_);

	// ���������̎n�_���Z�o
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
// [ �������ɓ��e���ꂽ��������蓊�e�����̒��������߂�֐�(OBB�FOBB) ]
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
// [ �ʏ핪�����ɑ΂��Ă̏Փ˂����߂�֐�(OBB�FOBB) ]
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
// [ �O�ϕ������ɑ΂��Ă̏Փ˂����߂�֐�(OBB�FOBB) ]
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