//================================================================================
//!	@file	 Cylinder.h
//!	@brief	 �~��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_CYLINDER_H_
#define _CYLINDER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"
#include "../LineSegment/LineSegment.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   �~��Class
//!
//! @details �~����Class
//************************************************************
class Cylinder : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	LineSegment line_segment_;	//!< ����
	float radius_;				//!< ���a


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	Cylinder() : CollisionShapeBase(CollisionShapeBase::Type::CYLINDER) {}

	//----------------------------------------
	//! @brief �������֐�
	//! @param[in] position �n�_���W
	//! @param[in] vector   ����
	//! @param[in] radius   ���a
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector, float radius)
	{
		// ����
		line_segment_.Init(position, vector);

		// ���a
		radius_ = radius;
	}

	// �v���p�e�B
	LineSegment* getpLineSegment() { return &line_segment_; }
	Vector3D* getpPosition() { return line_segment_.getpPosition(); }
	Vector3D* getpVector() { return line_segment_.getpVector(); }
	Vector3D getAddVectorToPosition() { return line_segment_.getAddVectorToPosition(); }
	float getRadius() { return radius_; }
	void setRadius(float value) { radius_ = value; }
};



#endif