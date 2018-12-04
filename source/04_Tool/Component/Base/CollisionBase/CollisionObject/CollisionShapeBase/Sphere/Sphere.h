//================================================================================
//!	@file	 Sphere.h
//!	@brief	 ��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_SPHERE_H_
#define _SPHERE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   ��Class
//!
//! @details ����Class
//************************************************************
class Sphere : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	Vector3D position_;		//!< ���W
	float radius_;			//!< ���a


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	Sphere() : CollisionShapeBase(CollisionShapeBase::Type::SPHERE) {}

	//----------------------------------------
	//! @brief �������֐�
	//! @param[in] position �n�_���W
	//! @param[in] radius   ���a
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D position, float radius)
	{
		// ���W
		position_ = position;

		// ���a
		radius_ = radius;
	}

	// �v���p�e�B
	Vector3D* getpPosition() { return &position_; }
	float getRadius() { return radius_; }
	void setRadius(float value) { radius_ = value; }
};



#endif