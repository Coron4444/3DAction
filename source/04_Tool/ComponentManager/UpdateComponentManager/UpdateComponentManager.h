//================================================================================
//
//    �X�V�R���|�[�l���g�}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_UPDATE_COMPONENT_MANAGER_H_
#define _UPDATE_COMPONENT_MANAGER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <LimitedPointerArray\LimitedPointerArray.h>



//======================================================================
//
// �N���X�錾
//
//======================================================================

class UpdateComponent;
class GameObjectOrigin;



//======================================================================
//
// �N���X��`
//
//======================================================================

class UpdateComponentManager
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	static const unsigned ARRAY_NUM = 1000;


//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	UpdateComponentManager() = delete;

	// �R�s�[�R���X�g���N�^
	UpdateComponentManager(const UpdateComponentManager& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	UpdateComponentManager& operator = (const UpdateComponentManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �ÓI���J�����o�֐�
	static void Init();
	static void Uninit();
	static void Uninit_ChangeScene();
	static void Update();

	static void RegistrationComponent(UpdateComponent* update_component);
	static void OverwriteComponent	 (GameObjectOrigin* game_object, UpdateComponent* new_update_component);
	static void ReleaseComponent	 (UpdateComponent* update_component);

	
//------------------------------------------------------------
private :
	// �ÓI����J�����o�֐�
	static void RegistrationUpdateComponentALL();
	static void ReleaseUpdateComponentALL();


//------------------------------------------------------------
private :
	// �ÓI�����o�ϐ�
	static LimitedPointerArray<UpdateComponent*, ARRAY_NUM> all_update_component_;
	static LimitedPointerArray<UpdateComponent*, ARRAY_NUM> registration_;
	static LimitedPointerArray<UpdateComponent*, ARRAY_NUM> release_;
};



#endif
