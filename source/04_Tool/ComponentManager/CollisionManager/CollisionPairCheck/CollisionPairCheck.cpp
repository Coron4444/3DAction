//================================================================================
//
//    �Փ˃y�A����N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/04/20
//
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionPairCheck.h"



//****************************************
// �ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�Փˊ��N���X�y�A����֐�
//--------------------------------------------------
bool CollisionPairCheck::IsCheck(CollisionBase* collision0, CollisionBase* collision1)
{
	if (!IsPair(collision0, collision1)) return false;

	return true;
}



//--------------------------------------------------
// -�y�A����֐�
//--------------------------------------------------
bool CollisionPairCheck::IsPair(CollisionBase* collision0, CollisionBase* collision1)
{
	// �w�肵���R���|�[�l���g���i�[����
	CollisionBase* temp;

	// ������v���C���[�̏ꍇ
	temp = IsState(CollisionBase::State::PLAYER, collision0, collision1);
	temp = OtherSideComponent(temp, collision0, collision1);

	if (temp != nullptr) return PairList_Player(temp);

	return false;
}



//--------------------------------------------------
// -�w�肵���Փ˃X�e�[�g�̌����֐�
//--------------------------------------------------
CollisionBase* CollisionPairCheck::IsState(CollisionBase::State state,
										   CollisionBase* collision0,
										   CollisionBase* collision1)
{
	if (state == collision0->getState()) return collision0;
	if (state == collision1->getState()) return collision1;

	return nullptr;
}



//--------------------------------------------------
// -�w�肵���R���|�[�l���g�̋t��Ԃ��֐�
//--------------------------------------------------
CollisionBase* CollisionPairCheck::OtherSideComponent(CollisionBase* age_component,
													  CollisionBase* collision0,
													  CollisionBase* collision1)
{
	if (age_component == nullptr) return nullptr;
	if (age_component == collision0) return collision1;
	if (age_component == collision1) return collision0;

	return nullptr;
}



//--------------------------------------------------
// -�v���C���[�̃y�A���X�g�֐�
//--------------------------------------------------
bool CollisionPairCheck::PairList_Player(CollisionBase* collision)
{
	switch (collision->getState())
	{
		// �Փ˂������Ȃ��Փ˃R���|�[�l���g
		case CollisionBase::State::PLAYER:
		{
			return false;
		}


		default:
		{
			return true;
		}
	}
}