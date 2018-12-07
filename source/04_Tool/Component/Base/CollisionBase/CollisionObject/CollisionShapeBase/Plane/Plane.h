//================================================================================
//!	@file	 Plane.h
//!	@brief	 ����Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_PLANE_H_
#define _PLANE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   ����Class
//!
//! @details ���ʂ�Class
//************************************************************
class Plane : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	Vector3D normal_;		//!< �@��
	float    adjustmet_d_;	//!< D����


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	Plane() : CollisionShapeBase(CollisionShapeBase::Type::PLANE) {}

	//----------------------------------------
	//! @brief �������֐�(�@����1�_)
	//! @param[in] normal �@��
	//! @param[in] point  �_
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D normal, Vector3D point)
	{
		// �@��
		normal_ = normal;
		normal_.CreateNormalize();

		// D����
		adjustmet_d_ = -((normal_.x * point.x) + (normal_.y * point.y) + (normal_.z * point.z));
	}

	//----------------------------------------
	//! @brief �������֐�(3�_)
	//! @param[in] point0 �_
	//! @param[in] point1 �_
	//! @param[in] point2 �_
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vec3 point0, Vec3 point1, Vec3 point2)
	{
		// �@���̍쐬
		Vec3 temp_normal_vector = Point3_Cross(point0, point1, point2);

		// ������
		Init(temp_normal_vector, point0);
	}



	// �v���p�e�B
	Vector3D* getpNormal() { return &normal_; }
	float getAdjustmetD() { return adjustmet_d_; }

};



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���ʂƍ��W�Ƃ̒����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Length_Point(Plane* plane, Vec3* point)
{
	return (plane->getpNormal()->x * point->x) 
		+ (plane->getpNormal()->y * point->y) 
		+ (plane->getpNormal()->z * point->z) + plane->getAdjustmetD();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���W�����ʂ̕\���ɂ��邩����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool IsFrontSide_Point(Plane* plane, Vec3* point)
{
	if (Length_Point(plane, point) < 0.0f) return false;

	return true;
}



#endif