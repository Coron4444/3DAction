//================================================================================
//!	@file	 Capsule.h
//!	@brief	 �J�v�Z��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_CAPSULE_H_
#define _CAPSULE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"
#include "../Cylinder/Cylinder.h"
#include "../Sphere/Sphere.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   �J�v�Z��Class
//!
//! @details �J�v�Z����Class
//************************************************************
class Capsule : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	Cylinder cylinder_;		//!< �~��
	Sphere sphere0_;		//!< ��
	Sphere sphere1_;		//!< ��


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	Capsule() : CollisionShapeBase(CollisionShapeBase::Type::CAPSULE) {}

	//----------------------------------------
	//! @brief �������֐�
	//! @param[in] position �n�_���W
	//! @param[in] vector   ����
	//! @param[in] radius   ���a
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector, float radius)
	{
		// �~��
		cylinder_.Init(position, vector, radius);

		// ��
		sphere0_.Init(*cylinder_.getpPosition(), radius);
		sphere1_.Init(cylinder_.getAddVectorToPosition(), radius);
	}

	//----------------------------------------
	//! @brief �������֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update()
	{
		// ��
		*sphere0_.getpPosition() = *cylinder_.getpPosition();
		sphere0_.setRadius(cylinder_.getRadius());
		*sphere1_.getpPosition() = cylinder_.getAddVectorToPosition();
		sphere1_.setRadius(cylinder_.getRadius());
	}

	// �v���p�e�B
	Sphere* getpSphere0() { return &sphere0_; }
	Sphere* getpSphere1() { return &sphere1_; }
	Cylinder* getpCylinder() { return &cylinder_; }
	LineSegment* getpLineSegment() { return cylinder_.getpLineSegment(); }
	Vector3D* getpPosition() { return cylinder_.getpPosition(); }
	Vector3D* getpVector() { return cylinder_.getpVector(); }
	Vector3D getAddVectorToPosition() { return cylinder_.getAddVectorToPosition(); }
	float getRadius() { return cylinder_.getRadius(); }
	void setRadius(float value) { cylinder_.setRadius(value); }
};



#endif