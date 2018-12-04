//================================================================================
//!	@file	 CollisionBase.h
//!	@brief	 �Փ�BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COLLISION_BASE_H_
#define _COLLISION_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../ComponentBase/ComponentBase.h"
#include "CollisionObjects/CollisionObjects.h"

#include <LimitedPointerArray/LimitedPointerArray.h>
#include <Transform/Transform.h>
#include <Vector3D.h>



//************************************************************														   
//! @brief   �Փ�BaseClass
//!
//! @details �Փ˂�BaseClass
//************************************************************
class CollisionBase : public ComponentBase
{
//====================
// �񋓌^��`
//====================
public:
	// �X�e�[�g
	enum State
	{
		NONE = -1,
		PLAYER,
		COIN,
		ENEMY,
		GOAL,
		MAX
	};


//====================
// �萔
//====================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< �z��


//====================
// �ϐ�
//====================
private:
	LimitedPointerArray<CollisionObjects*, ARRAY_NUM> collision_objects_;	//!< �����Փ˃I�u�W�F�N�g�z��
	State state_ = State::NONE;			//!< �X�e�[�g
	bool is_judgment_ground_ = true;	//!< �n�ʂƂ̔���t���O


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~CollisionBase() {}

	//----------------------------------------
	//! @brief �Փˎ��֐�
	//! @param[in, out] hit_collision ����̏Փˊ��N���X
	//! @param[in, out] hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param[in, out] hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject* hit_object,
							  CollisionObject* hit_my_object) = 0;

	//----------------------------------------
	//! @brief ��Փˎ��֐�
	//! @param[in, out] hit_collision ����̏Փˊ��N���X
	//! @param[in, out] hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param[in, out] hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject* hit_object,
								 CollisionObject* hit_my_object) = 0;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̏Փˎ��֐�
	//! @param[in] position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̔�Փˎ��֐�
	//! @param[in] position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void NotHitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief �����Փ˃I�u�W�F�N�g�ǉ��֐�
	//! @param[in] object �ǉ������������Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddCollisionObjectsToArray(CollisionObjects* object)
	{
		collision_objects_.AddToArray(object);
	}

	//----------------------------------------
	//! @brief �����Փ˃I�u�W�F�N�g�㏑���֐�
	//! @param[in] object �Â������Փ˃I�u�W�F�N�g
	//! @param[in] object �V���������Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void OverwriteArrayCollisionsObject(CollisionObjects* old_object,
										CollisionObjects* new_object)
	{
		old_object->ReleaseAllCollisionObjectFromArray();
		collision_objects_.OverwriteArray(old_object, new_object);
	}

	//----------------------------------------
	//! @brief �����Փ˃I�u�W�F�N�g����֐�
	//! @param[in] object ���������������Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseCollisionObjectsFromArray(CollisionObjects* object)
	{
		object->ReleaseAllCollisionObjectFromArray();
		collision_objects_.DeleteFromArrayAndSortArray(object);
	}

	//----------------------------------------
	//! @brief �����Փ˃I�u�W�F�N�g�S����֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseAllCollisionObjectsFromArray()
	{
		for (unsigned i = 0; i < collision_objects_.GetEndPointer(); i++)
		{
			collision_objects_.GetArrayObject(i)
				->ReleaseAllCollisionObjectFromArray();
		}
		collision_objects_.ReleaseObjectAndResetArray();
	}

	//----------------------------------------
	//! @brief �߂荞�݉����֐�
	//! @param[in, out] transform  �߂荞�݂��������������
	//! @param[in]      hit_vector �߂荞�݃x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void EliminationOfNesting(Transform* transform, const Vec3* hit_vector)
	{
		*transform->GetPosition() += *hit_vector;
		transform->UpdateWorldMatrixISRT();
	}

	// �v���p�e�B
	unsigned getEndIndexOfArray() { return collision_objects_.GetEndPointer(); }
	CollisionObjects* getpCollisionObjects(unsigned index) { return collision_objects_.GetArrayObject(index); }
	State getState() { return state_; }
	void setState(State value) { state_ = value; }
	bool getIsJudgmentGround() { return is_judgment_ground_; }
	void setIsJudgmentGround(bool value) { is_judgment_ground_ = value; }
};



#endif