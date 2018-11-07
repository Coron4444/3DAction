//================================================================================
//
//    �Փ˃R���|�[�l���g�y�A����N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/04/20
//
//================================================================================


//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "CollisionComponentPairCheck.h"



//======================================================================
//
// �ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˔���X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionComponentPairCheck::IsCheck(CollisionComponent* component_0, CollisionComponent* component_1)
{
	if (!IsPair(component_0, component_1)) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ �Փˑ���m�F�֐� ]
//
//--------------------------------------------------------------------------------

bool CollisionComponentPairCheck::IsPair(CollisionComponent* component_0, CollisionComponent* component_1)
{
	// �w�肵���R���|�[�l���g���i�[����
	CollisionComponent* temp_component;
	
	// ������v���C���[�̏ꍇ
	temp_component = IsState(CollisionComponent::State::PLAYER, component_0, component_1);
	temp_component = OtherSideComponent(temp_component, component_0, component_1);
	
	if (temp_component != nullptr) return PairList_Player(temp_component);

	return false;
}



//--------------------------------------------------------------------------------
//
// [ �w�肵���I�u�W�F�N�g�^�C�v�̌����֐� ]
//
//--------------------------------------------------------------------------------

CollisionComponent* CollisionComponentPairCheck::IsState(CollisionComponent::State state, 
														 CollisionComponent* component_0, 
														 CollisionComponent* component_1)
{
	if (state == component_0->GetState()) return component_0;
	if (state == component_1->GetState()) return component_1;

	return nullptr;
}



//--------------------------------------------------------------------------------
//
// [ �w�肵���R���|�[�l���g�̋t��Ԃ��֐� ]
//
//--------------------------------------------------------------------------------

CollisionComponent* CollisionComponentPairCheck::OtherSideComponent(CollisionComponent* age_component, 
																	CollisionComponent* component_0, 
																	CollisionComponent* component_1)
{
	if (age_component == nullptr) return nullptr;
	if (age_component == component_0) return component_1;
	if (age_component == component_1) return component_0;

	return nullptr;
}



//--------------------------------------------------------------------------------
//
// [ �v���C���[�̃y�A���X�g�֐� ]
//
//--------------------------------------------------------------------------------

bool CollisionComponentPairCheck::PairList_Player(CollisionComponent* component)
{
	switch(component->GetState())
	{
		// �Փ˂������Ȃ��Փ˃R���|�[�l���g
		case CollisionComponent::State::PLAYER :
		{
			return false;
		}
			

		default :
		{
			return true;
		}
	}
}