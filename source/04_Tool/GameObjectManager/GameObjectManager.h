//================================================================================
//
//    �Q�[���I�u�W�F�N�g�̃}�l�[�W���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/07/13
//
//================================================================================

#ifndef	_GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <LimitedPointerArray\LimitedPointerArray.h>
#include "GameObjectReferenceManager\GameObjectReferenceManager.h"



//======================================================================
//
// �N���X�錾
//
//======================================================================

class GameObjectOrigin;



//======================================================================
//
// �N���X��`
//
//======================================================================

class GameObjectManager
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �萔
	static const unsigned ARRAY_NUM = 1000;

//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	GameObjectManager() = delete;

	// �R�s�[�R���X�g���N�^
	GameObjectManager(const GameObjectManager& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	GameObjectManager& operator = (const GameObjectManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �ÓI�����o�֐�
	static void Registration(GameObjectOrigin* game_object);
	static void Release		(GameObjectOrigin* game_object);
	static void ReleaseAllWaitingObjects();
	static void ReleaseAll	();
	static void ResetAll	();

	// �Q�Ƃ̓o�^
	template<class Type>
	static void GetPointer_RegistrationReference(GameObjectOrigin* reference_source,
												 Type* reference_destination,
												 Type* reference_pointer)
	{
		// �Q�Ɛ�̑��
		*reference_pointer = reference_destination;

		// �Q�Ƃ̓o�^
		reference_manager_.RegistrationReference(reference_source, 
												 (void*)reference_pointer, 
												 (GameObjectOrigin*)reference_destination);
	}



//------------------------------------------------------------
private :
	// �ÓI�����o�ϐ�
	static LimitedPointerArray<GameObjectOrigin*, ARRAY_NUM> all_game_object_;
	static LimitedPointerArray<GameObjectOrigin*, ARRAY_NUM> all_release_game_object_;

	static GameObjectReferenceManager reference_manager_;
};



#endif
