//================================================================================
//
//    �J�v�Z���N���X
//    Author : Araki Kai                                �쐬�� : 2017/12/21
//
//================================================================================

#ifndef	_CAPSULE_H_
#define _CAPSULE_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../CollisionShapeBase.h"
#include "../Cylinder/Cylinder.h"
#include "../Segment/Segment.h"
#include "../Sphere/Sphere.h"

#include <Vector3D.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Capsule : public CollisionShapeBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	Capsule(Segment segment = Segment(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)), 
		    float   radius  = 1.0f);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~Capsule();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�ϐ�
	Segment  segment_;
	float    radius_;
	Sphere   sphere0_;
	Sphere   sphere1_;
	Cylinder cylinder_;
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

inline Capsule::Capsule(Segment segment, float radius)
	: CollisionShapeBase(CollisionShapeBase::Type::CAPSULE),
	  segment_ (segment), 
	  radius_  (radius),
	  sphere0_ (segment_.position_, radius_),
	  sphere1_ (segment_.GetAddVectorPosition(), radius_),
	  cylinder_(sphere0_.position_, sphere1_.position_, radius)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Capsule::~Capsule() 
{
}



#endif