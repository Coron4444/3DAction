//================================================================================
//
//    �����N���X
//    Author : Araki Kai                                �쐬�� : 2017/11/27
//
//================================================================================

#ifndef	_SEGMENT_H_
#define _SEGMENT_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../CollisionShapeBase.h"

#include <Vector3D.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Segment : public CollisionShapeBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	Segment(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), Vec3 vector = Vec3(0.0f, 0.0f, 0.0f));


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~Segment();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	float    GetSlopeSegment2D   () const;

	Vector3D GetAddVectorPosition() const {return position_ + vector_;}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�ϐ�
	Vector3D position_;
	Vector3D vector_;
};





//======================================================================
//
// ��ÓI�����o�֐���`( inline )
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�R���X�g���N�^ ]
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
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Segment::~Segment() 
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 2D�̐����̌X���쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Segment::GetSlopeSegment2D() const
{
	return vector_.y / vector_.x;
}



//======================================================================
//
// �񃁃��o�֐��錾
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �����Ɠ_�̍ŒZ���������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Line_Point(Vec3* cross_point, float* t, const Segment* segment, const Vector3D* point)
{
	// �����̍��W�Ɠ_�Ƃ̃x�N�g��
	Vector3D temp_vector = *point - segment -> position_;

	// ��_��t���Z�o
	*t = 0.0f;
	bool is_not_zero_length = segment->vector_.GetLengthSquare() > 0.0f;

	if (is_not_zero_length)
	{
		*t = segment->vector_.CreateVectorDot(temp_vector) / segment->vector_.CreateVectorDot(segment->vector_);
	}
		
	// ��_��h���Z�o
	*cross_point = segment->position_ + (segment->vector_ * (*t));

	// ������Ԃ�
	temp_vector = *cross_point - *point;

	return temp_vector.GetLength();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �����Ɠ_�̍ŒZ���������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Segment_Point(Vec3* cross_point, float* t, const Segment* segment, const Vector3D* point)
{
	// �����̖��[��ۑ�
	Vec3 segment_position1 = segment->GetAddVectorPosition();

	// �����Ɠ_�̍ŒZ�������Z�o
	float length = ShortestDistance_Line_Point(cross_point, t, segment, point);


	// �����̎n�_���_���O���̎�
	if (IsObtuseAngle(*point, segment->position_, segment_position1))
	{
		*cross_point = segment->position_;

		Vector3D temp_vector = segment->position_ - *point;

		return temp_vector.GetLength();
	}
	
	// �����̏I�_���_���O���̎�
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
// [ 2���������s���̔���֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool Is_ParallelSegment(const Segment* segment0, const Segment* segment1)
{
	// 2���������s���ǂ���( �O�ς̒�����0���ǂ��� )
	Vector3D temp_vector = segment0->vector_.CreateVectorCross(segment1->vector_);


	// �덷�͈͂��ǂ���
	const float num_error = 0.000001f;

	bool is_error_range = -num_error < temp_vector.GetLengthSquare() && temp_vector.GetLengthSquare() < num_error;

	if (is_error_range) return true;

	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �����ƒ����̍ŒZ���������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Line_Line(Vec3* cross_point0, Vec3* cross_point1, float* t0, float* t1, const Segment* segment0, const Segment* segment1)
{
	// 2���������s
	if(Is_ParallelSegment(segment0, segment1))
	{
		// ����1�ƒ���0�̍��W�Ƃ̍ŒZ�������Z�o
		float length = ShortestDistance_Line_Point(cross_point1, t1, segment1, &segment0->position_);
		*cross_point0 = segment0->position_;
		*t0 = 0.0f;

		return length;
	}

	// ���s�łȂ�
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
// [ 0�`1�̊ԂɎ��߂�֐� ]
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
// [ �����Ɛ����̍ŒZ���������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Segment_Segment(Vec3* cross_point0, Vec3* cross_point1, float* t0, float* t1, const Segment* segment0, const Segment* segment1)
{
	// segment0���k�ނ��Ă���
	if (segment0->vector_.GetLengthSquare() <= 0.0f)
	{
		if (segment1->vector_.GetLengthSquare() <= 0.0f)
		{
			// �_�Ɠ_�̋���
			Vector3D temp_vector = segment1->position_ - segment0->position_;
			*cross_point0 = segment0->position_;
			*cross_point1 = segment1->position_;
			*t0 = 0.0f;
			*t1 = 0.0f;

			return temp_vector.GetLength();
		}
		else
		{
			// segment0�̍��W��segment1�̍ŒZ����
			float length = ShortestDistance_Segment_Point(cross_point1, t1, segment1, &segment0 -> position_);
			*cross_point0 = segment0->position_;
			*t0 = 0.0f;
			Clamp0_1(t1);
			return length;
		}
	}
	

	// segment1���k�ނ��Ă�
	if (segment1->vector_.GetLengthSquare() <= 0.0f)
	{
		// segment0�̍��W��segment1�̍ŒZ����
		float length = ShortestDistance_Segment_Point(cross_point0, t0, segment0, &segment1 -> position_);
		*cross_point1 = segment1->position_;
		*t1 = 0.0f;
		Clamp0_1(t0);
		return length;
	}

	// �������m
	// ���s�̎�
	if(Is_ParallelSegment(segment0, segment1))
	{
		// �����̒[�_��1��������
		float length = ShortestDistance_Segment_Point(cross_point1, t1, segment1, &segment0 -> position_);
		*cross_point0 = segment0->position_;
		*t0 = 0.0f;

		// t1�����܂��Ă�����ΏI��
		bool within_range = *t1 >= 0.0f && *t1 <= 1.0f;
		if (within_range) return length;

	}
	else
	{
		// 2�����̍ŒZ���������߂āAt0,t1��������
		float length = ShortestDistance_Line_Line(cross_point0, cross_point1, t0, t1, segment0, segment1);

		// �������Ɏ��܂��Ă���ΏI��
		bool within_range = *t0 >= 0.0f && *t0 <= 1.0f && *t1 >= 0.0f && *t1 <= 1.0f;
		if (within_range) return length;
	}

	// segment0����t0���N�����v���A�������~�낷
	Clamp0_1(t0);
	*cross_point0 = segment0->position_ + segment0->vector_ * (*t0);
	Vector3D temp_point = *cross_point0;
	float length  = ShortestDistance_Segment_Point(cross_point1, t1, segment1, &temp_point);
	
	// �~�낵���������������ɂ��邩
	bool within_range = *t1 >= 0.0f && *t1 <= 1.0f;
	if (within_range) return length;

	// segment1���N�����v���A�������~�낷
	Clamp0_1(t1);
	*cross_point1 = segment1->position_ + segment1->vector_ * (*t1);
	temp_point = *cross_point1;
	length  = ShortestDistance_Segment_Point(cross_point0, t0, segment0, &temp_point);
	
	// �~�낵���������������ɂ��邩
	within_range = *t0 >= 0.0f && *t0 <= 1.0f;
	if (within_range) return length;

	// 2�����̒[�_�̋������ŒZ�Ɣ���
	Clamp0_1(t0);
	*cross_point0 = segment0->position_ + segment0->vector_ * (*t0);
	Vector3D temp_vector = *cross_point1 - *cross_point0;

	return temp_vector.GetLength();
}



#endif