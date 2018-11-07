//================================================================================
//
//    �V�[���}�l�[�W���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2018/11/02
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "SceneManager.h"
#include <SceneBace/SceneBace.h>

#include <main.h>
#include <SafeRelease/SafeRelease.h>

#include <GameObjectManager\GameObjectManager.h>
#include <ResourceManager\ResourceManager.h>



//****************************************
// �萔��`
//****************************************
const Fade::Type SceneManager::DEFAULT_FADE_TYPE = Fade::Type::TYPE_NORMAL;
const float      SceneManager::DEFAULT_FADE_SPEED = 1.0f;
const XColor4    SceneManager::DEFAULT_FADE_COLOR(0.0f, 0.0f, 0.0f, 1.0f);



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�R���X�g���N�^
//--------------------------------------------------
SceneManager::SceneManager(SceneBace* scene)
	: state_(SceneManager::State::NONE),
	common_data_(nullptr),
	current_scene_(nullptr),
	next_scene_(nullptr),
	fade_type_(DEFAULT_FADE_TYPE),
	fade_speed_(DEFAULT_FADE_SPEED),
	fade_color_(DEFAULT_FADE_COLOR)
{
	// ���L�f�[�^�[�̏�����
	common_data_ = new CommonData();
	common_data_->Reset();

	// ���\�[�X�̏�����
	ResourceManager::InitAllData();

	// �R���|�[�l���g�}�l�[�W���[�̏�����
	UpdateComponentManager::Init();
	DrawComponentManager::Init();
	CollisionComponentManager::Init();

	// �V�[���̏�����
	current_scene_ = scene;
	current_scene_->SetSceneManager(this);
	current_scene_->Init();
}



//--------------------------------------------------
// +�f�X�g���N�^
//--------------------------------------------------
SceneManager::~SceneManager()
{
	// �V�[���̏I������
	if (current_scene_ != nullptr) current_scene_->Uninit();
	if (next_scene_ != nullptr)  next_scene_->Uninit();

	// �R���|�[�l���g�}�l�[�W���[�̏I������
	UpdateComponentManager::Uninit();
	DrawComponentManager::Uninit();
	CollisionComponentManager::Uninit();

	// �Q�[���I�u�W�F�N�g�̑S�J��
	GameObjectManager::ReleaseAll();

	// ���\�[�X�̏I������
	ResourceManager::UninitAllData();

	// �e��J��
	SafeRelease::Normal(&current_scene_);
	SafeRelease::Normal(&next_scene_);
	SafeRelease::Normal(&common_data_);
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void SceneManager::Update()
{
	switch (state_)
	{
		case SceneManager::State::CHANGE_SCENE:
		{
			// �V�[���ύX
			SceneChange();
			break;
		}
		case SceneManager::State::RESET_SCENE:
		{
			// �V�[�����Z�b�g
			SceneReset();
			break;
		}
	}
}



//--------------------------------------------------
// +�V�[���̍X�V�֐�
//--------------------------------------------------
void SceneManager::UpdateScene()
{
	if (current_scene_ == nullptr) return;

	// ����҂��I�u�W�F�N�g�̉��
	GameObjectManager::ReleaseAllWaitingObjects();

	// �R���|�[�l���g�P�ʂ̍X�V
	UpdateComponentManager::Update();
	CollisionComponentManager::Update();

	// �e�V�[�����L�̍X�V
	current_scene_->Update();
}



//--------------------------------------------------
// +�V�[���̕`��֐�
//--------------------------------------------------
void SceneManager::DrawScene()
{
	if (current_scene_ == nullptr) return;

	// �R���|�[�l���g�P�ʂ̕`��
	DrawComponentManager::Draw();
}



//--------------------------------------------------
// +���̃V�[���ݒ�֐�
//--------------------------------------------------
void SceneManager::SetNextScene(SceneBace* value)
{
	// ���ɂق��̗v�����󂯕t���Ă���ꍇ
	if (state_ != SceneManager::State::NONE)
	{
		SafeRelease::PlusUninit(&value);
		return;
	}

	// �ύX�V�[���̓o�^
	next_scene_ = value;

	// �X�e�[�g�̕ύX
	state_ = SceneManager::State::CHANGE_SCENE;

	// Update�t���OOFF
	common_data_->SetIsUpdate(false);

	// �t�F�[�h�A�E�g������
	DrawComponentManager::InitFade(fade_type_, Fade::State::STATE_FADE_OUT,
								   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
								   fade_color_, fade_speed_);
}



//--------------------------------------------------
// +�V�[�����Z�b�g�֐�
//--------------------------------------------------
void SceneManager::ResetScene()
{
	// ���ɂق��̗v�����󂯕t���Ă���ꍇ
	if (state_ != SceneManager::State::NONE) return;

	// �X�e�[�g�̕ύX
	state_ = SceneManager::State::RESET_SCENE;

	// �t�F�[�h�A�E�g������
	DrawComponentManager::InitFade(fade_type_, Fade::State::STATE_FADE_OUT,
								   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
								   fade_color_, fade_speed_);
}



//--------------------------------------------------
// -�V�[���ύX�֐�
//--------------------------------------------------
void SceneManager::SceneChange()
{
	// �t�F�[�h�������I����Ă��邩�ǂ���
	if (!DrawComponentManager::IsFadeEnd()) return;

	// �t�F�[�h�̃X�e�[�g���Ƃ̏���
	if (DrawComponentManager::IsFadeStateName(Fade::State::STATE_FADE_OUT))
	{
		// ���݂̃��C���V�[���̏I������
		SafeRelease::PlusUninit(&current_scene_);
		GameObjectManager::ReleaseAll();

		// �R���|�[�l���g�̃V�[���ύX�I������
		UpdateComponentManager::Uninit_ChangeScene();
		DrawComponentManager::Uninit_ChangeScene();
		CollisionComponentManager::Uninit_ChangeScene();

		// �ŗL���\�[�X�̉��
		ResourceManager::UninitUniqueData();

		// �V�����V�[���ֈڍs
		current_scene_ = next_scene_;
		next_scene_ = nullptr;
		current_scene_->SetSceneManager(this);
		current_scene_->Init();

		// �t�F�[�h�I��
		DrawComponentManager::UninitFade();

		// �t�F�[�h�C��������
		DrawComponentManager::InitFade(fade_type_, Fade::State::STATE_FADE_IN,
									   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
									   fade_color_, fade_speed_);
	}
	else if (DrawComponentManager::IsFadeStateName(Fade::State::STATE_FADE_IN))
	{
		// �t�F�[�h�I������
		state_ = SceneManager::State::NONE;
		common_data_->SetIsUpdate(true);
		DrawComponentManager::UninitFade();
	}
}



//--------------------------------------------------
// -�V�[�����Z�b�g�֐�
//--------------------------------------------------
void SceneManager::SceneReset()
{
	// �t�F�[�h�������I����Ă��邩�ǂ���
	if (!DrawComponentManager::IsFadeEnd()) return;

	// �t�F�[�h�̃X�e�[�g���Ƃ̏���
	if (DrawComponentManager::IsFadeStateName(Fade::State::STATE_FADE_OUT))
	{
		// ���݂̃��C���V�[���̃��Z�b�g
		GameObjectManager::ResetAll();
		current_scene_->Reset();

		// �t�F�[�h�I��
		DrawComponentManager::UninitFade();

		// �t�F�[�h�C��������
		DrawComponentManager::InitFade(fade_type_, Fade::State::STATE_FADE_IN,
									   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
									   fade_color_, fade_speed_);
	}
	else if (DrawComponentManager::IsFadeStateName(Fade::State::STATE_FADE_IN))
	{
		// �t�F�[�h�I������
		state_ = SceneManager::State::NONE;
		common_data_->SetIsUpdate(true);
		DrawComponentManager::UninitFade();
	}
}