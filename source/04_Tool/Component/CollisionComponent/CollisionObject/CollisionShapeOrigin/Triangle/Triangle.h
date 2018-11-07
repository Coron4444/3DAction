//================================================================================
//
//    �O�p�`�N���X
//    Author : Araki Kai                                �쐬�� : 2017/11/28
//
//================================================================================

#ifndef	_TRIANGLE_H_
#define _TRIANGLE_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../CollisionShapeOrigin.h"
#include "../Plane/Plane.h"

#include <Vector3D.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Triangle : public CollisionShapeOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 3�_�����R���X�g���N�^
	Triangle(Vec3 point0 = Vec3(0.0f, 0.0f, 0.0f), Vec3 point1 = Vec3(0.0f, 0.0f, 0.0f), Vec3 point2 = Vec3(0.0f, 0.0f, 0.0f));


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~Triangle();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�	
	bool CheckInnerPoint( Vec3 point ) const;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�ϐ�
	Vector3D point_[3];
	Plane    plane_;
};





//======================================================================
//
// ��ÓI�����o�֐���`( inline )
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 3�_�����R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Triangle::Triangle(Vec3 point0, Vec3 point1, Vec3 point2)
	: CollisionShapeOrigin(CollisionShapeOrigin::Type::TYPE_TRIANGLE),
	  plane_(point0, point1, point2)
{
	point_[0] = point0;
	point_[1] = point1;
	point_[2] = point2;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Triangle::~Triangle() 
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool Triangle::CheckInnerPoint( Vec3 point ) const
{
	// �C�ӂ̓_����e���_�ւ̃x�N�g�����Z�o
	Vector3D vector0 = point_[0] - point;
	Vector3D vector1 = point_[1] - point;
	Vector3D vector2 = point_[2] - point;


	// 3�p�`�̕ӂ��Ȃ���x�N�g�����Z�o
	Vector3D edge_vector0 = point_[0] - point_[1];
	Vector3D edge_vector1 = point_[1] - point_[2];
	Vector3D edge_vector2 = point_[2] - point_[0];


	// �O�ς̎Z�o
	Vector3D Cross_vector0 = vector0.CreateVectorCross(edge_vector0);
	Vector3D Cross_vector1 = vector1.CreateVectorCross(edge_vector1);
	Vector3D Cross_vector2 = vector2.CreateVectorCross(edge_vector2);

	int zero_vector = 0;

	if (Cross_vector0.GetLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (Cross_vector1.GetLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (Cross_vector2.GetLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (zero_vector >= 2)
	{
		return true;
	}
	else if (zero_vector == 1)
	{
		float dot0 = 0.0f;

		if (Cross_vector0.GetLengthSquare() == 0.0f)
		{
			// �O�ς̌�����������Ă��邩�̃`�F�b�N
			dot0 = Cross_vector1.CreateVectorDot(Cross_vector2);
		}
		if (Cross_vector1.GetLengthSquare() == 0.0f)
		{
			// �O�ς̌�����������Ă��邩�̃`�F�b�N
			dot0 = Cross_vector0.CreateVectorDot(Cross_vector2);
		}
		if (Cross_vector2.GetLengthSquare() == 0.0f)
		{
			// �O�ς̌�����������Ă��邩�̃`�F�b�N
			dot0 = Cross_vector0.CreateVectorDot(Cross_vector1);
		}

		bool is_same_direction = dot0 > 0.0f;

		if (is_same_direction) return true;
	}
	else
	{
		// �O�ς̌�����������Ă��邩�̃`�F�b�N
		float dot0 = Cross_vector0.CreateVectorDot(Cross_vector1);
		float dot1 = Cross_vector1.CreateVectorDot(Cross_vector2);
		float dot2 = Cross_vector0.CreateVectorDot(Cross_vector2);

		bool is_same_direction0 = (dot0 * dot1) > 0.0f;
		bool is_same_direction1 = (dot0 * dot2) > 0.0f;
		bool is_same_direction2 = (dot1 * dot2) > 0.0f;

		int  same_count = 0;
		if (is_same_direction0 == is_same_direction1) same_count++;
		if (is_same_direction0 == is_same_direction2) same_count++;
		if (is_same_direction1 == is_same_direction2) same_count++;

		if (same_count == 3) return true;
	}

	return false;
}



#endif