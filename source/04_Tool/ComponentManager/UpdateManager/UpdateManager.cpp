//================================================================================
//
//    �X�V�}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "UpdateManager.h"
#include <Component/UpdateBase/UpdateBase.h>
#include <GameObjectBase/GameObjectBase.h>

#include <SafeRelease/SafeRelease.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void UpdateManager::Init()
{

}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void UpdateManager::Uninit()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�X�V�z��̃��Z�b�g
	all_update_.ResetArray();
}



//--------------------------------------------------
// +�V�[���ύX���̏I���֐�
//--------------------------------------------------
void UpdateManager::UninitWhenChangeScene()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�X�V�z��̃��Z�b�g
	all_update_.ResetArray();
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void UpdateManager::Update()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �X�V
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i) == nullptr) continue;
		all_update_.GetArrayObject(i)->Update();
	}

	// ��X�V
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i) == nullptr) continue;
		all_update_.GetArrayObject(i)->LateUpdate();
	}

	// �����X�V
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i)->GetGameObject()->GetPhysics() == nullptr) continue;
		all_update_.GetArrayObject(i)->GetGameObject()->GetPhysics()->Update();
	}


	// �f�o�b�O
#ifdef _DEBUG
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i) == nullptr) continue;
		all_update_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



//--------------------------------------------------
// +�X�V���N���X�̒ǉ��֐�
//--------------------------------------------------
void UpdateManager::AddUpdateBaseToArray(UpdateBase* update)
{
	// �ǉ��҂��z��ɒǉ�
	await_add_.AddToArray(update);
}



//--------------------------------------------------
// +�X�V���N���X�̏㏑���֐�
//--------------------------------------------------
void UpdateManager::OverwriteArrayUpdateBase(GameObjectBase* game_object,
											 UpdateBase* new_update)
{
	// �V�K��nullptr�̏ꍇ
	if (new_update == nullptr)
	{
		// �Â��X�V���N���X�̉��
		ReleaseUpdateBaseFromArray(game_object->GetUpdate());

		// �Â��X�V���N���X�̏���
		UpdateBase* temp = game_object->GetUpdate();
		SafeRelease::Normal(&temp);

		// nullptr�̑��
		game_object->SetUpdate(new_update);
	}
	else
	{
		// �z��̏㏑��
		all_update_.OverwriteArray(game_object->GetUpdate(), new_update);

		// �Â��X�V���N���X�̏���
		UpdateBase* temp = game_object->GetUpdate();
		SafeRelease::Normal(&temp);

		// �V�K�X�V���N���X�̏�����
		game_object->SetUpdate(new_update);
		new_update->SetGameObject(game_object);
		new_update->Init();
	}
}




//--------------------------------------------------
// +�X�V���N���X�̉���֐�
//--------------------------------------------------
void UpdateManager::ReleaseUpdateBaseFromArray(UpdateBase* update)
{
	// ����҂��z��ɒǉ�
	await_release_.AddToArray(update);
}



//--------------------------------------------------
// -�ǉ��҂��z��̒��g��ǉ��֐�
//--------------------------------------------------
void UpdateManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if(await_add_.GetEndPointer() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_update_.AddToArray(await_add_.GetArrayObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.ResetArray();
}



//--------------------------------------------------
// -����҂��z��̒��g������֐�
//--------------------------------------------------
void UpdateManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if(await_release_.GetEndPointer() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		all_update_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.ResetArray();
}