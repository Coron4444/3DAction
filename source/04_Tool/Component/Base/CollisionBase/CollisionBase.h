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
#include "CollisionObject\CollisionObject.h"

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
	static const unsigned ARRAY_NUM = 100;		//!< �z��


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
		MAX
	};


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> all_collision_object_;	//!< �S�Փ˃I�u�W�F�N�g�z��

	State state_;	//!< �X�e�[�g

	bool is_judgment_;			//!< ����t���O
	bool is_judgment_ground_;	//!< �n�ʂƂ̔���t���O


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �R���X�g���N�^
	*/
	CollisionBase(State state)
		: state_(state),
		is_judgment_(true),
		is_judgment_ground_(true)
	{
	}

	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~CollisionBase() {}

	/**
	* @brief
	* �I���֐�
	*/
	virtual void Uninit() = 0;

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
							  CollisionObject*  hit_object,
							  CollisionObject*  hit_my_object) = 0;

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
								 CollisionObject*  hit_my_object) = 0;

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
	* �Փ˃I�u�W�F�N�g�ǉ��֐�
	*/
	void AddCollisionObjectToArray(CollisionObject* object)
	{
		all_collision_object_.AddToArray(object);
	}

	/**
	* @brief
	* �Փ˃I�u�W�F�N�g�㏑���֐�
	*/
	void OverwriteArrayCollisionObject(CollisionObject* old_object,
									   CollisionObject* new_object)
	{
		all_collision_object_.OverwriteArray(old_object, new_object);
	}

	/**
	* @brief
	* �Փ˃I�u�W�F�N�g����֐�
	*/
	void ReleaseCollisionObjectFromArray(CollisionObject* object)
	{
		all_collision_object_.DeleteFromArrayAndSortArray(object);
	}

	/**
	* @brief
	* �Փ˃I�u�W�F�N�g�S����֐�
	*/
	void ReleaseAllCollisionObjectFromArray()
	{
		all_collision_object_.ReleaseObjectAndResetArray();
	}

	/**
	* @brief
	* �S�Ă̏Փ˗p�f�[�^�̃��Z�b�g�֐�
	*/
	void ResetHitDataAllCollisionObject()
	{
		for (unsigned i = 0; i < all_collision_object_.GetEndPointer(); i++)
		{
			all_collision_object_.GetArrayObject(i)->ResetHitData();
		}
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
	unsigned GetEndIndexOfArray() { return all_collision_object_.GetEndPointer(); }
	CollisionObject* GetCollisionObject(unsigned index) { return all_collision_object_.GetArrayObject(index); }
	State GetState() { return state_; }
	bool GetIsJudgment() { return is_judgment_; }
	void SetIsJudgment(bool value) { is_judgment_ = value; }
	bool GetIsJudgmentGround() { return is_judgment_; }
	void SetIsJudgmentGround(bool value) { is_judgment_ = value; }
};



#endif