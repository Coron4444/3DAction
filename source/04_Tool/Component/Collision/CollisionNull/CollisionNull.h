//================================================================================
//!	@file	 Collision.h
//!	@brief	 �󔒏Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COLLISION_NULL_H_
#define _COLLISION_NULL_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../Base/CollisionBase/CollisionBase.h"



//************************************************************														   
//! @brief   �󔒏Փ�Class
//!
//! @details �Փ˂̋�Class
//************************************************************
class CollisionNull : public CollisionBase
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~CollisionNull() 
	{
		ReleaseAllCollisionObjectsFromArray();
	}

	//----------------------------------------
	//! @brief �������֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Init() override {}

	//----------------------------------------
	//! @brief �I���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() override
	{
		// �����Փ˃I�u�W�F�N�g�̔���OFF
		for (unsigned i = 0; i < getEndIndexOfArray(); i++)
		{
			getpCollisionObjects(i)->setIsJudgment(false);
		}
	}

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Update() {}

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DebugDisplay() {}

	//----------------------------------------
	//! @brief �Փˎ��֐�
	//! @param[in, out] hit_collision ����̏Փˊ��N���X
	//! @param[in, out] hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param[in, out] hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject*  hit_object,
							  CollisionObject*  hit_my_object)
	{
		// �g���Ă��Ȃ������̏���
		hit_collision = hit_collision;
		hit_object = hit_object;
		hit_my_object = hit_my_object;
	}

	//----------------------------------------
	//! @brief ��Փˎ��֐�
	//! @param[in, out] hit_collision ����̏Փˊ��N���X
	//! @param[in, out] hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param[in, out] hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject*  hit_object,
								 CollisionObject*  hit_my_object)
	{
		// �g���Ă��Ȃ������̏���
		hit_collision = hit_collision;
		hit_object = hit_object;
		hit_my_object = hit_my_object;
	}

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̏Փˎ��֐�
	//! @param[in] position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitGround(float position_y) { position_y = position_y; }

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̔�Փˎ��֐�
	//! @param[in] position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void NotHitGround(float position_y) { position_y = position_y; }
};



#endif