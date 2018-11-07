//================================================================================
//
//    �Փ˃R���|�[�l���g�y�A����N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/04/20
//
//================================================================================

#ifndef	_COLLISION_COMPONENT_PAIR_CHECK_H_
#define _COLLISION_COMPONENT_PAIR_CHECK_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <vector>
#include <Component\CollisionComponent\CollisionComponent.h>

#include <Vector3D.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class CollisionComponentPairCheck
{
//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	CollisionComponentPairCheck() = delete;

	// �R�s�[�R���X�g���N�^
	CollisionComponentPairCheck(const CollisionComponentPairCheck& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	CollisionComponentPairCheck& operator = (const CollisionComponentPairCheck& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �Փ˃R���|�[�l���g�y�A����
	static bool IsCheck(CollisionComponent* component_0, CollisionComponent* component_1);



//------------------------------------------------------------
private :
	// �y�A����
	static bool IsPair(CollisionComponent* component_0, CollisionComponent* component_1);
	
	// �y�A���X�g
	static bool PairList_Player(CollisionComponent* component);

	// ��������
	static CollisionComponent* IsState(CollisionComponent::State state, 
									   CollisionComponent* component_0, 
									   CollisionComponent* component_1);

	static CollisionComponent* OtherSideComponent(CollisionComponent* age_component, 
												  CollisionComponent* component_0, 
												  CollisionComponent* component_1);
};



#endif