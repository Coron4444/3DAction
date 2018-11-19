//================================================================================
//
//    �`��}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "DrawManager.h"
#include "ShaderManager/ShaderManager.h"

#include <Component/Base/DrawBase/DrawBase.h>
#include <GameObjectBase/GameObjectBase.h>

#include <Renderer/Renderer.h>

#include <Transform/Transform.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void DrawManager::Init()
{
	// �V�F�[�_�[�}�l�[�W���[������
	shader_manager_ = new ShaderManager();
	shader_manager_->Init();

	// �o�b�N�o�b�t�@������
	back_buffer_ = new BackBuffer();
	back_buffer_->Init();
	back_buffer_->SetShaderManager(shader_manager_);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void DrawManager::Uninit()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�`��z��̃��Z�b�g
	all_draw_.ResetArray();

	// �o�b�N�o�b�t�@�I������
	SafeRelease::PlusUninit(&back_buffer_);
	SafeRelease::PlusUninit(&shader_manager_);
}



//--------------------------------------------------
// +�V�[���ύX���̏I���֐�
//--------------------------------------------------
void DrawManager::UninitWhenChangeScene()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�`��z��̃��Z�b�g
	all_draw_.ResetArray();

	// �o�b�N�o�b�t�@�I������
	back_buffer_->UninitWhenChangeScene();
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void DrawManager::Update()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �S�����_�[�^�[�Q�b�g�̃��Z�b�g
	ResetAllRenderTarget();

	// �����_�[�^�[�Q�b�g���Ƃ̐U�蕪��
	DistributeDrawBase();

	// �S�����_�[�^�[�Q�b�g�X�V�֐�
	UpdateAllRenderTarget();

	// �f�o�b�O�\��
#ifdef _DEBUG
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		if (all_draw_.GetArrayObject(i) == nullptr) continue;
		all_draw_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void DrawManager::Draw()
{
	// �o�b�N�o�b�t�@
	back_buffer_->Draw();
}



//--------------------------------------------------
// +�`����N���X�̒ǉ��֐�
//--------------------------------------------------
void DrawManager::AddDrawBaseToArray(DrawBase* draw)
{
	// �ǉ��҂��z��ɒǉ�
	await_add_.AddToArray(draw);
}



//--------------------------------------------------
// +�`����N���X�̏㏑���֐�
//--------------------------------------------------
void DrawManager::OverwriteArrayDrawBase(GameObjectBase* game_object,
										 DrawBase* new_draw)
{
	// �V�K��nullptr�̏ꍇ
	if (new_draw == nullptr)
	{
		// �Â��`����N���X�̉��
		ReleaseDrawBaseFromArray(game_object->GetDraw());

		// �Â��`����N���X�̏���
		DrawBase* temp = game_object->GetDraw();
		SafeRelease::Normal(&temp);

		// nullptr�̑��
		game_object->SetDraw(new_draw);
	}
	else
	{
		// �z��̏㏑��
		all_draw_.OverwriteArray(game_object->GetDraw(), new_draw);

		// �Â��`����N���X�̏���
		DrawBase* temp = game_object->GetDraw();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g�̏�����
		game_object->SetDraw(new_draw);
		new_draw->SetGameObject(game_object);
		new_draw->Init();
	}
}



//--------------------------------------------------
// +�`����N���X�̉���֐�
//--------------------------------------------------
void DrawManager::ReleaseDrawBaseFromArray(DrawBase* draw)
{
	// ����҂��z��ɒǉ�
	await_release_.AddToArray(draw);
}



//--------------------------------------------------
// -�ǉ��҂��z��̒��g��ǉ��֐�
//--------------------------------------------------
void DrawManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if (await_add_.GetEndPointer() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_draw_.AddToArray(await_add_.GetArrayObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.ResetArray();
}



//--------------------------------------------------
// -����҂��z��̒��g������֐�
//--------------------------------------------------
void DrawManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if (await_release_.GetEndPointer() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		all_draw_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.ResetArray();
}



//--------------------------------------------------
// -�S�����_�[�^�[�Q�b�g�X�V�֐�
//--------------------------------------------------
void DrawManager::UpdateAllRenderTarget()
{
	// �o�b�N�o�b�t�@
	back_buffer_->Update();
}



//--------------------------------------------------
// -�S�����_�[�^�[�Q�b�g���Z�b�g�֐�
//--------------------------------------------------
void DrawManager::ResetAllRenderTarget()
{
	// �o�b�N�o�b�t�@
	back_buffer_->ResetAllArray();
}



//--------------------------------------------------
// -�`����N���X�U�蕪���֐�
//--------------------------------------------------
void DrawManager::DistributeDrawBase()
{
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		// �o�b�N�o�b�t�@
		if (all_draw_.GetArrayObject(i)->GetDrawOrderList()->GetRenderTargetFlag()
			->CheckAny(DrawOrderList::RENDER_TARGET_BACK_BUFFER))
		{
			back_buffer_->AddDrawBaseToArray(all_draw_.GetArrayObject(i));
		}
	}
}