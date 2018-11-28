//================================================================================
//
//    �Փˊ��N���X
//    Author : Araki Kai                                �쐬�� : 2018/04/17
//
//================================================================================

#ifndef	_COLLISION_BASE_H_
#define _COLLISION_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../ComponentBase/ComponentBase.h"
#include "CollisionObjects/CollisionObjects.h"

#include <LimitedPointerArray\LimitedPointerArray.h>
#include <Transform\Transform.h>

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



/*********************************************************//**
* @brief
* �Փˊ��N���X
*
* �Փ˂̊��N���X
*************************************************************/
class CollisionBase : public ComponentBase
{
//==============================
// �萔
//==============================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< �z��


//==============================
// �񋓌^��`
//==============================
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


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LimitedPointerArray<CollisionObjects*, ARRAY_NUM> collision_objects_;	//!< �����Փ˃I�u�W�F�N�g�z��
	State state_ = State::NONE;			//!< �X�e�[�g
	bool is_judgment_ground_ = true;	//!< �n�ʂƂ̔���t���O


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~CollisionBase() {}

	/**
	* @brief
	* �X�V�֐�
	*/
	virtual void Update() = 0;

	/**
	* @brief
	* �f�o�b�O�\���֐�
	*/
	virtual void DebugDisplay() = 0;

	/**
	* @brief
	* �Փˎ��֐�
	* @param
	* hit_collision : ����̏Փˊ��N���X
	* hit_object :����̏Փ˃I�u�W�F�N�g
	* hit_my_object : �����̏Փ˃I�u�W�F�N�g
	*/
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject* hit_object,
							  CollisionObject* hit_my_object) = 0;

	/**
	* @brief
	* ��Փˎ��֐�
	* @param
	* hit_collision : ����̏Փˊ��N���X
	* hit_object :����̏Փ˃I�u�W�F�N�g
	* hit_my_object : �����̏Փ˃I�u�W�F�N�g
	*/
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject* hit_object,
								 CollisionObject* hit_my_object) = 0;

	/**
	* @brief
	* �t�B�[���h�Ƃ̏Փˎ��֐�
	*/
	virtual void HitGround(float position_y) = 0;

	/**
	* @brief
	* �t�B�[���h�Ƃ̔�Փˎ��֐�
	*/
	virtual void NotHitGround(float position_y) = 0;

	/**
	* @brief
	* �����Փ˃I�u�W�F�N�g�ǉ��֐�
	*/
	void AddCollisionObjectsToArray(CollisionObjects* object)
	{
		collision_objects_.AddToArray(object);
	}

	/**
	* @brief
	* �����Փ˃I�u�W�F�N�g�㏑���֐�
	*/
	void OverwriteArrayCollisionsObject(CollisionObjects* old_object,
										CollisionObjects* new_object)
	{
		old_object->ReleaseAllCollisionObjectFromArray();
		collision_objects_.OverwriteArray(old_object, new_object);
	}

	/**
	* @brief
	* �����Փ˃I�u�W�F�N�g����֐�
	*/
	void ReleaseCollisionObjectsFromArray(CollisionObjects* object)
	{
		object->ReleaseAllCollisionObjectFromArray();
		collision_objects_.DeleteFromArrayAndSortArray(object);
	}

	/**
	* @brief
	* �����Փ˃I�u�W�F�N�g�S����֐�
	*/
	void ReleaseAllCollisionObjectsFromArray()
	{
		for (unsigned i = 0; i < collision_objects_.GetEndPointer(); i++)
		{
			collision_objects_.GetArrayObject(i)
				->ReleaseAllCollisionObjectFromArray();
		}
		collision_objects_.ReleaseObjectAndResetArray();
	}

	/**
	* @brief
	* �߂荞�݉����֐�
	*/
	void EliminationOfNesting(Transform* transform, const Vec3* hit_vector)
	{
		*transform->GetPosition() += *hit_vector;
		transform->UpdateWorldMatrixISRT();
	}

	// �v���p�e�B
	unsigned getEndIndexOfArray() { return collision_objects_.GetEndPointer(); }
	CollisionObjects* getCollisionObjects(unsigned index) { return collision_objects_.GetArrayObject(index); }
	State getState() { return state_; }
	void setState(State value) { state_ = value; }
	bool getIsJudgmentGround() { return is_judgment_ground_; }
	void setIsJudgmentGround(bool value) { is_judgment_ground_ = value; }
};



#endif