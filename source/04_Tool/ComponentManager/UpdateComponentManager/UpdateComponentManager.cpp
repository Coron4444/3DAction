//================================================================================
//
//    �X�V�R���|�[�l���g�}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "UpdateComponentManager.h"
#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Component\UpdateComponent\UpdateComponent.h>
#include <SafeRelease/SafeRelease.h>


//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

LimitedPointerArray<UpdateComponent*, UpdateComponentManager::ARRAY_NUM> UpdateComponentManager::all_update_component_;
LimitedPointerArray<UpdateComponent*, UpdateComponentManager::ARRAY_NUM> UpdateComponentManager::registration_;
LimitedPointerArray<UpdateComponent*, UpdateComponentManager::ARRAY_NUM> UpdateComponentManager::release_;



//======================================================================
//
// �ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::Init()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::Uninit()
{
	// ����p�z��̃��Z�b�g
	release_.ResetArray();

	// �o�^�p�z��̃��Z�b�g
	registration_.ResetArray();

	// �R���|�[�l���g�z��̃��Z�b�g
	all_update_component_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �V�[���ύX���̏I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::Uninit_ChangeScene()
{
	// ����p�z��̃��Z�b�g
	release_.ResetArray();

	// �o�^�p�z��̃��Z�b�g
	registration_.ResetArray();

	// �R���|�[�l���g�z��̃��Z�b�g
	all_update_component_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::Update()
{
	// ����҂��̉��
	ReleaseUpdateComponentALL();

	// �o�^�҂��̓o�^
	RegistrationUpdateComponentALL();

	// �X�V
	for (unsigned i = 0; i < all_update_component_.GetEndPointer(); i++)
	{
		if (all_update_component_.GetArrayObject(i) == nullptr) continue;
		all_update_component_.GetArrayObject(i)->Update();
	}

	// ��X�V
	for (unsigned i = 0; i < all_update_component_.GetEndPointer(); i++)
	{
		if (all_update_component_.GetArrayObject(i) == nullptr) continue;
		all_update_component_.GetArrayObject(i)->LateUpdate();
	}

	// �����X�V
	for (unsigned i = 0; i < all_update_component_.GetEndPointer(); i++)
	{
		if (all_update_component_.GetArrayObject(i)->GetGameObjectOrigin()->GetPhysics() == nullptr) continue;

		// �����X�V
		all_update_component_.GetArrayObject(i)->GetGameObjectOrigin()->GetPhysics()->Update();
	}


#ifdef _DEBUG
	// �f�o�b�O
	for (unsigned i = 0; i < all_update_component_.GetEndPointer(); i++)
	{
		if (all_update_component_.GetArrayObject(i) == nullptr) continue;
		all_update_component_.GetArrayObject(i)->Debug();
	}
#endif

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�R���|�[�l���g�o�^�\��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::RegistrationComponent(UpdateComponent* update_component)
{
	// �o�^
	registration_.AddToArray(update_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�R���|�[�l���g�㏑���֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::OverwriteComponent(GameObjectOrigin* game_object, UpdateComponent* new_update_component)
{
	// �V�K�R���|�[�l���g��nullptr���ǂ���
	if (new_update_component == nullptr)
	{
		// �Â��I�u�W�F�N�g�̉���\��
		ReleaseComponent(game_object->GetUpdateComponent());

		// �Â��R���|�[�l���g�̏���
		UpdateComponent* temp = game_object->GetUpdateComponent();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g(nullptr)�̑��
		game_object->SetUpdateComponent(new_update_component);
	}
	else
	{
		// �z��̏㏑��
		all_update_component_.OverwriteArray(game_object->GetUpdateComponent(), new_update_component);

		// �Â��R���|�[�l���g�̏���
		UpdateComponent* temp = game_object->GetUpdateComponent();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g�̏�����
		game_object->SetUpdateComponent(new_update_component);
		new_update_component->SetGameObjectOrigin(game_object);
		new_update_component->Init();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�R���|�[�l���g����\��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::ReleaseComponent(UpdateComponent* update_component)
{
	// ����z��o�^
	release_.AddToArray(update_component);
}



//--------------------------------------------------------------------------------
//
// [ �S�Ă̓o�^�҂��X�V�R���|�[�l���g�̓o�^�֐� ]
//
//--------------------------------------------------------------------------------

void UpdateComponentManager::RegistrationUpdateComponentALL()
{
	// �o�^�҂������邩�ǂ���
	if(registration_.GetEndPointer() <= 0) return;

	// �o�^
	for (unsigned i = 0; i < registration_.GetEndPointer(); i++)
	{
		all_update_component_.AddToArray(registration_.GetArrayObject(i));
	}

	// �o�^�҂��z������Z�b�g
	registration_.ResetArray();
}



//--------------------------------------------------------------------------------
//
// [ �S�Ẳ���҂��X�V�R���|�[�l���g�̉���֐� ]
//
//--------------------------------------------------------------------------------

void UpdateComponentManager::ReleaseUpdateComponentALL()
{
	// ����҂������邩�ǂ���
	if(release_.GetEndPointer() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < release_.GetEndPointer(); i++)
	{
		all_update_component_.DeleteFromArrayAndSortArray(release_.GetArrayObject(i));
	}

	// ����҂��z������Z�b�g
	release_.ResetArray();
}