//================================================================================
//
//    �Փ˃R���|�[�l���g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/04/17
//
//================================================================================

#ifndef	_COLLISION_COMPONENT_H_
#define _COLLISION_COMPONENT_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../ComponentOrigin/ComponentOrigin.h"
#include "CollisionObject\CollisionObject.h"
#include <LimitedPointerArray\LimitedPointerArray.h>
#include <Transform\Transform.h>

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



//======================================================================
//
// �N���X��`
//
//======================================================================

class CollisionComponent : public ComponentOrigin
{
//------------------------------------------------------------
private :
	// �萔
	static const unsigned ARRAY_NUM = 100;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �X�e�[�g
	enum State
	{
		NONE = -1,
		PLAYER,
		COIN,
		ENEMY,
		MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �R���X�g���N�^
	CollisionComponent(CollisionComponent::State state)
		: state_(state),
		  is_judgment_(true),
		  is_judgment_ground_(true)
	{
	}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���z�f�X�g���N�^
	virtual ~CollisionComponent(){}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	virtual void Uninit() override
	{
		// ����t���OOFF
		SetIsJudgment(false);

		// �z��̒��g�����
		all_collision_object_.ReleaseObjectAndResetArray();
	}

	// �X�V
	virtual void Update(){}

	// �f�o�b�O
	virtual void Debug(){}

	// �Փˎ�����
	virtual void HitCollision(CollisionComponent* hit_component, 
							  CollisionObject*    hit_opponent_object,
							  CollisionObject*    hit_myself_object)
	{
		// �g���Ă��Ȃ������̏���
		hit_component		= hit_component;
		hit_opponent_object = hit_opponent_object;
		hit_myself_object   = hit_myself_object;
	}

	// ��Փˎ�����
	virtual void NotHitCollision(CollisionComponent* hit_component, 
							     CollisionObject*    hit_opponent_object,
							     CollisionObject*    hit_myself_object)
	{
		// �g���Ă��Ȃ������̏���
		hit_component		= hit_component;
		hit_opponent_object = hit_opponent_object;
		hit_myself_object   = hit_myself_object;
	}

	// �Փ˃I�u�W�F�N�g�z��̖��[index�̎擾
	unsigned GetEndIndexCollisionObjectArray(){return all_collision_object_.GetEndPointer();}

	// �Փ˃I�u�W�F�N�g�̎擾
	CollisionObject* GetCollisionObject(unsigned index){return all_collision_object_.GetArrayObject(index);}

	// �S�Ă̏Փ˗p�f�[�^�����Z�b�g
	void ResetHitData_AllCollisionObject()
	{
		for(unsigned i = 0; i < all_collision_object_.GetEndPointer(); i++)
		{
			all_collision_object_.GetArrayObject(i)->ResetHitData();
		}
	}

	// �Փ˃I�u�W�F�N�g�z��ɒǉ�
	void AddCollisionObject(CollisionObject* object)
	{
		all_collision_object_.AddToArray(object);
	}

	// �Փ˃I�u�W�F�N�g�z��̏㏑��
	void OverwriteCollisionObject(CollisionObject* old_object, 
								  CollisionObject* new_object)
	{
		all_collision_object_.OverwriteArray(old_object, new_object);
	}

	// �Փ˃I�u�W�F�N�g�z�񂩂����
	void ReleaseCollisionObject(CollisionObject* object)
	{
		all_collision_object_.DeleteFromArrayAndSortArray(object);
	}
	
	// ���
	CollisionComponent::State GetState(){return state_;}

	// ����t���O
	void SetIsJudgment(bool is_judgment){is_judgment_ = is_judgment;}
	bool GetIsJudgment(){return is_judgment_;}

	// �߂荞�݉���
	void EliminationOfNesting(Transform* transform, const Vec3* hit_vector)
	{
		*transform->GetPosition() += *hit_vector;
		transform->UpdateWorldMatrixISRT();
	}

	// �t�B�[���h
	void SetIsJudgmentGround(bool is_judgment){is_judgment_ = is_judgment;}
	bool GetIsJudgmentGround(){return is_judgment_;}
	virtual void HitGround(float position_y){position_y = position_y;}
	virtual void NotHitGround(float position_y){position_y = position_y;}


//------------------------------------------------------------
private :
	// �Փ˃I�u�W�F�N�g�z��
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> all_collision_object_;
	
	// ���
	CollisionComponent::State state_;
	
	// ����t���O
	bool is_judgment_;
	bool is_judgment_ground_;


};



#endif