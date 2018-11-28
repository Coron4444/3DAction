//================================================================================
//
//    �󔒏Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================

#ifndef	_COLLISION_NULL_H_
#define _COLLISION_NULL_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <assert.h>
#include "../../Base/CollisionBase/CollisionBase.h"



/*********************************************************//**
* @brief
* �󔒏Փ˃N���X
*
* �Փ˂̋󔒃N���X
*************************************************************/
class CollisionNull : public CollisionBase
{
//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~CollisionNull() 
	{
		ReleaseAllCollisionObjectsFromArray();
	}

	/**
	* @brief
	* �I���֐�
	*/
	virtual void Uninit() override
	{
		// �����Փ˃I�u�W�F�N�g�̔���OFF
		for (unsigned i = 0; i < getEndIndexOfArray(); i++)
		{
			getCollisionObjects(i)->setIsJudgment(false);
		}
	}

	/**
	* @brief
	* �X�V�֐�
	*/
	virtual void Update() {}

	/**
	* @brief
	* �f�o�b�O�\���֐�
	*/
	virtual void DebugDisplay() {}

	/**
	* @brief
	* �Փˎ��֐�
	* @param
	* hit_collision : ����̏Փˊ��N���X
	* hit_object :����̏Փ˃I�u�W�F�N�g
	* hit_my_object : �����̏Փ˃I�u�W�F�N�g
	*/
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject*  hit_object,
							  CollisionObject*  hit_my_object)
	{
		// �g���Ă��Ȃ������̏���
		hit_collision = hit_collision;
		hit_object = hit_object;
		hit_my_object = hit_my_object;
	}

	/**
	* @brief
	* ��Փˎ��֐�
	* @param
	* hit_collision : ����̏Փˊ��N���X
	* hit_object :����̏Փ˃I�u�W�F�N�g
	* hit_my_object : �����̏Փ˃I�u�W�F�N�g
	*/
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject*  hit_object,
								 CollisionObject*  hit_my_object)
	{
		// �g���Ă��Ȃ������̏���
		hit_collision = hit_collision;
		hit_object = hit_object;
		hit_my_object = hit_my_object;
	}

	/**
	* @brief
	* �t�B�[���h�Ƃ̏Փˎ��֐�
	*/
	virtual void HitGround(float position_y) { position_y = position_y; }

	/**
	* @brief
	* �t�B�[���h�Ƃ̔�Փˎ��֐�
	*/
	virtual void NotHitGround(float position_y) { position_y = position_y; }
};



#endif