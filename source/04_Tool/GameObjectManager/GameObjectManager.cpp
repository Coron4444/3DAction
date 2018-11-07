//================================================================================
//
//    �Q�[���I�u�W�F�N�g�̃}�l�[�W���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/07/13
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "GameObjectManager.h"
#include "../GameObjectOrigin/GameObjectOrigin.h"
#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

LimitedPointerArray<GameObjectOrigin*, GameObjectManager::ARRAY_NUM> GameObjectManager::all_game_object_;
LimitedPointerArray<GameObjectOrigin*, GameObjectManager::ARRAY_NUM> GameObjectManager::all_release_game_object_;

GameObjectReferenceManager GameObjectManager::reference_manager_;




//======================================================================
//
// �ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �z��ɓo�^�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::Registration(GameObjectOrigin* game_object)
{
	all_game_object_.AddToArray(game_object);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ����҂�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::ReleaseAllWaitingObjects()
{
	// �o�^����Ă���I�u�W�F�N�g��S�ĉ��
	all_release_game_object_.ReleaseObjectAndResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::Release(GameObjectOrigin* game_object)
{
	// �Q�ƃf�[�^���
	reference_manager_.ReleaseReference(game_object);

	// �S�̔z�񂩂�̏���
	all_game_object_.DeleteFromArrayAndSortArray(game_object);

	// �����[�X�z��ɓo�^
	all_release_game_object_.AddToArray(game_object);

	// �Q�[���I�u�W�F�N�g�̉��
	game_object->ReleaseObject();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �S�ĉ���֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::ReleaseAll()
{
	// �Q�ƃf�[�^��S�ď���
	reference_manager_.AllReleaseReference();

	// �o�^����Ă���I�u�W�F�N�g��S�ĉ��
	for (unsigned i = 0; i < all_game_object_.GetEndPointer(); i++)
	{
		all_game_object_.GetArrayObject(i)->ReleaseObject();
		GameObjectOrigin* temp = all_game_object_.GetArrayObject(i);
		SafeRelease::Normal(&temp);
	}

	// �I�u�W�F�N�g�z������Z�b�g
	all_game_object_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �S�ă��Z�b�g�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::ResetAll()
{
	// �o�^����Ă���I�u�W�F�N�g��S�ă��Z�b�g
	for (unsigned i = 0; i < all_game_object_.GetEndPointer(); i++)
	{
		all_game_object_.GetArrayObject(i)->Reset();
	}
}