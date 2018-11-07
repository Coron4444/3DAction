//================================================================================
//
//    �Q�[���I�u�W�F�N�g�̎Q�ƃ}�l�[�W���N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/15
//
//================================================================================

#ifndef	_GAME_OBJECT_REFERENCE_MANAGER_H_
#define _GAME_OBJECT_REFERENCE_MANAGER_H_



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include <LimitedPointerArray\LimitedPointerArray.h>
#include <unordered_map>



//**********************************************************************
//
// �N���X�錾
//
//**********************************************************************

class GameObjectOrigin;



//**********************************************************************
//
// �N���X��`
//
//**********************************************************************

class GameObjectReferenceManager
{
// ============================================================
public : 
	// �萔
	static const unsigned ARRAY_NUM = 1000;

// ============================================================
public : 
	struct ReferenceData
	{
		// �R���X�g���N�^
		ReferenceData(GameObjectOrigin* source, void* pointer, GameObjectOrigin* destination)
		{
			reference_source_	   = source;
			reference_destination_ = destination;
			reference_pointer_	   = pointer;
		}

		// �����o�ϐ�
		GameObjectOrigin* reference_source_;
		GameObjectOrigin* reference_destination_;
		void*			  reference_pointer_;
		int				  registration_index_;
	};

	struct ReferenceMap
	{
		// �L�[�̃I�u�W�F�N�g���Q�ƌ��̃}�b�v
		std::unordered_map<GameObjectOrigin*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> source_map_;
		
		// �L�[�̃I�u�W�F�N�g���Q�Ɛ�̃}�b�v
		std::unordered_map<GameObjectOrigin*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> destination_map_;
	};


// ============================================================
public :
	// �f�t�H���g�R���X�g���N�^
	GameObjectReferenceManager();


// ============================================================
public :
	// �f�X�g���N�^
	~GameObjectReferenceManager();


// ============================================================
public :
	// �����o�֐�
	void RegistrationReference(GameObjectOrigin* source, void* pointer, GameObjectOrigin* destination);
	void ReleaseReference(GameObjectOrigin* object);
	void AllReleaseReference();



// ============================================================
private :
	// �����o�֐�
	void RegistrationReference_Source(GameObjectOrigin* source, void* pointer, GameObjectOrigin* destination);
	void RegistrationReference_Destination(GameObjectOrigin* source, void* pointer, GameObjectOrigin* destination);

	void ReleaseReference_Source(GameObjectOrigin* object);
	void ReleaseReference_Destination(GameObjectOrigin* object);

	
// ============================================================
private :
	// �����o�ϐ�
	ReferenceMap reference_map_;
};



#endif
