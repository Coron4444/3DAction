//================================================================================
//
//    AABB�N���X
//    Author : Araki Kai                                �쐬�� : 2017/11/27
//
//================================================================================

#ifndef	_AABB_H_
#define _AABB_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"



/*********************************************************//**
* @brief
* AABB�N���X
*
* AABB�̊��N���X
*************************************************************/
class AABB : public CollisionShapeBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	Vector3D length_;	//!< ����
	Vector3D min_;		//!< �ŏ��l
	Vector3D max_;		//!< �ő�l


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �R���X�g���N�^
	*/
	AABB() : CollisionShapeBase(CollisionShapeBase::Type::AABB) {}

	/**
	* @brief
	* �������֐�
	* @param
	* position : ���W
	* length : �e�ӂ̒���
	*/
	void Init(Vector3D position, Vector3D length)
	{
		// ���W��ݒ�
		CollisionShapeBase::setPosition(position);

		// ������ݒ�
		length_ = length;

		// �ŏ��l�ƍő�l
		UpdateMinAndMax();
	}

	/**
	* @brief
	* �X�V�֐�
	*/
	void Update()
	{
		// �ŏ��l�ƍő�l
		UpdateMinAndMax();
	}

	// �v���p�e�B
	const Vector3D* getLength() const { return &length_; }
	void setLength(Vector3D value) { length_ = value; };
	const Vector3D* getMin() const { return &min_; }
	const Vector3D* getMax() const { return &max_; }


private:
	/**
	* @brief
	* �ŏ��l�ƍő�l�X�V�֐�
	*/
	void UpdateMinAndMax()
	{
		min_ = *CollisionShapeBase::getPositon() - length_;
		max_ = *CollisionShapeBase::getPositon() + length_;
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
inline float ShortestDistance_AABB_Point(const AABB* aabb, const Vector3D* point)
{
	// �����ׂ̂���Ōv�Z���Ă���
	float length = 0.0f;

	// �e���ɑ΂��Ăׂ�����v�Z����
	length = ShortestDistanceSquareAABB_Segment1D_Point(aabb->getMin()->x,
														aabb->getMax()->x,
														point->x);
	length = ShortestDistanceSquareAABB_Segment1D_Point(aabb->getMin()->y,
														aabb->getMax()->y,
														point->y);
	length = ShortestDistanceSquareAABB_Segment1D_Point(aabb->getMin()->z,
														aabb->getMax()->z,
														point->z);

	return (float)sqrt(length);
}



#endif