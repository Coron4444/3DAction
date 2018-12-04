//================================================================================
//!	@file	 AABB.h
//!	@brief	 AABBClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_AABB_H_
#define _AABB_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>


//************************************************************														   
//! @brief   AABBClass
//!
//! @details AABB��Class
//************************************************************
class AABB : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	Vector3D position_;	//!< ���W
	Vector3D length_;	//!< �e�ӂ̒���
	Vector3D min_;		//!< �ŏ��l
	Vector3D max_;		//!< �ő�l


//====================
// �֐�
//====================
public:
	/**
	* @brief
	* �R���X�g���N�^
	*/
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	AABB() : CollisionShapeBase(CollisionShapeBase::Type::AABB) {}

	//----------------------------------------
	//! @brief �������֐�
	//! @param[in] position ���W
	//! @param[in] length   �e�ӂ̒���
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D position, Vector3D length)
	{
		// ���W��ݒ�
		position_ = position;

		// ������ݒ�
		length_ = length;

		// �ŏ��l�ƍő�l
		UpdateMinAndMax();
	}

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update()
	{
		// �ŏ��l�ƍő�l
		UpdateMinAndMax();
	}

	// �v���p�e�B
	Vector3D* getpPositon() { return &position_; }
	Vector3D* getpLength() { return &length_; }
	void setLength(Vector3D value) { length_ = value; };
	Vector3D* getpMin() { return &min_; }
	Vector3D* getpMax() { return &max_; }


private:
	//----------------------------------------
	//! @brief �ŏ��l�ƍő�l�X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateMinAndMax()
	{
		min_ = position_ - length_;
		max_ = position_ + length_;
	}
};



//****************************************
// �񃁃��o�֐���`
//****************************************
//--------------------------------------------------
// +1���������Ɠ_�̍ŒZ�����ׂ̂�������߂�֐�
//--------------------------------------------------
inline float ShortestDistanceSquareAABB_Segment1D_Point(float position_min,
												 float position_max,
												 float point_any)
{
	float length = 0.0f;

	// ������菬�����Ƃ�
	if (point_any < position_min)
	{
		length += (position_min - point_any) * (position_min - point_any);
	}

	// �������傫���Ƃ�
	if (point_any > position_max)
	{
		length += (position_max - point_any) * (position_max - point_any);
	}

	return length;
}



//--------------------------------------------------
// +AABB�Ɠ_�̍ŒZ���������߂�֐�
//--------------------------------------------------
inline float ShortestDistance_AABB_Point(AABB* aabb, Vector3D* point)
{
	// �����ׂ̂���Ōv�Z���Ă���
	float length = 0.0f;

	// �e���ɑ΂��Ăׂ�����v�Z����
	length = ShortestDistanceSquareAABB_Segment1D_Point(aabb->getpMin()->x,
														aabb->getpMax()->x,
														point->x);
	length = ShortestDistanceSquareAABB_Segment1D_Point(aabb->getpMin()->y,
														aabb->getpMax()->y,
														point->y);
	length = ShortestDistanceSquareAABB_Segment1D_Point(aabb->getpMin()->z,
														aabb->getpMax()->z,
														point->z);

	return (float)sqrt(length);
}



#endif