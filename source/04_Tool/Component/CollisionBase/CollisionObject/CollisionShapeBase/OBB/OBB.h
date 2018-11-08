//================================================================================
//
//    OBB�N���X
//    Author : Araki Kai                                �쐬�� : 2017/11/27
//
//================================================================================

#ifndef	_OBB_H_
#define _OBB_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../CollisionShapeBase.h"

#include <Vector3D.h>
#include <Transform\AxisVector\AxisVector.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class OBB : public CollisionShapeBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	OBB(float lenght_right   = 1.0f, 
		float lenght_up      = 1.0f, 
		float lenght_forward = 1.0f, 
		Vec3 position		 = Vec3(0.0f, 0.0f, 0.0f));


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~OBB();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �Q�b�^
	Vector3D* GetVectorForward();
	Vector3D* GetVectorUp     ();
	Vector3D* GetVectorRight  ();

	Vector3D* GetVectorForwardHalf();
	Vector3D* GetVectorUpHalf     ();
	Vector3D* GetVectorRightHalf  ();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�ϐ�
	Vector3D   position_;
	AxisVector axis_;
	float      lenght_right_;
	float      lenght_up_;
	float      lenght_forward_;




//------------------------------------------------------------
private	:
	// ����J�����o�ϐ�
	Vector3D   math_vector_;
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

inline OBB::OBB(float lenght_right, float lenght_up, float lenght_forward, Vec3 position )
	: CollisionShapeOrigin(CollisionShapeOrigin::Type::TYPE_OBB),
	  lenght_right_  ( lenght_right ),
	  lenght_up_     ( lenght_up ),
	  lenght_forward_( lenght_forward ),
	  position_      ( position )
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline OBB::~OBB() 
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �O�x�N�g�����擾 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorForward() 
{
	math_vector_ = *axis_.GetForawrd();

	math_vector_.AnyLengthVector(lenght_forward_);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��x�N�g�����擾 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorUp() 
{
	math_vector_ = *axis_.GetUp();

	math_vector_.AnyLengthVector(lenght_up_);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �E�x�N�g�����擾 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorRight() 
{
	math_vector_ = *axis_.GetRight();

	math_vector_.AnyLengthVector(lenght_right_);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �O�x�N�g�����擾( ���� ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorForwardHalf() 
{
	math_vector_ = *axis_.GetForawrd();

	math_vector_.AnyLengthVector(lenght_forward_ / 2);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��x�N�g�����擾( ���� ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorUpHalf() 
{
	math_vector_ = *axis_.GetUp();

	math_vector_.AnyLengthVector(lenght_up_ / 2);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �E�x�N�g�����擾( ���� ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorRightHalf() 
{
	math_vector_ = *axis_.GetRight();

	math_vector_.AnyLengthVector(lenght_right_ / 2);

	return &math_vector_;
}




//======================================================================
//
// �񃁃��o�֐��錾
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 1���������Ɠ_�̂͂ݏo�������̃x�N�g�������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void OverhangingPartOBB_Segment1D_Point( Vector3D* shortest_distance_vector, 
	                                            const Vector3D* obb_position, 
	                                            const Vector3D* obb_vector_half,
											    const Vector3D* obb_axis_vector,
	                                            const Vector3D* point )
{
	// ������0�ȏォ
	float temp_length = obb_vector_half -> GetLength();
	if ( temp_length <= 0.0f ) return;
	
	// �_���璼���ɐ������~�낵���Ƃ��̌�_�̈ʒu��\���l(t�Ƃ���)���Z�o
	Vector3D temp_vector = *point - *obb_position;
	float t = temp_vector.CreateVectorDot( *obb_axis_vector ) / temp_length;

	// �͂ݏo���������̃x�N�g�����Z�o
	if ( t < -1.0f )
	{
		*shortest_distance_vector += ( t + 1.0f ) * ( *obb_vector_half );
	}
	else if ( t > 1.0f )
	{
		*shortest_distance_vector += ( t - 1.0f ) * ( *obb_vector_half );
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ OBB�Ɠ_�̍ŒZ�����̃x�N�g�������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D ShortestDistance_OBB_Point( OBB* obb, const Vector3D* point )
{
	// OBB�܂ł̍ŒZ���������߂�x�N�g��
	Vector3D temp_vector;
	
	// �e���ɑ΂��Ă͂ݏo���������Z�o
	OverhangingPartOBB_Segment1D_Point( &temp_vector, 
	                                    &obb -> position_,
									    obb -> GetVectorForwardHalf(),
								        obb ->axis_.GetForawrd(),
	                                    point );

	OverhangingPartOBB_Segment1D_Point( &temp_vector, 
	                                    &obb -> position_,
									    obb -> GetVectorRightHalf(),
								        obb ->axis_.GetRight(),
	                                    point );

	OverhangingPartOBB_Segment1D_Point( &temp_vector, 
	                                    &obb -> position_,
									    obb -> GetVectorUpHalf(),
								        obb ->axis_.GetUp(),
	                                    point );
	return temp_vector;
}



#endif