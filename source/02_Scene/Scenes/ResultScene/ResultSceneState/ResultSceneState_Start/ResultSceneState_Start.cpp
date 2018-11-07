//================================================================================
//
//    ���U���g�V�[���X�e�[�g�N���X(�X�^�[�g)
//    Author : Araki Kai                                �쐬�� : 2018/11/06
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "ResultSceneState_Start.h"
#include "../../ResultScene.h"

#include <SceneManager/SceneManager.h>
#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState/TitleSceneState_Start/TitleSceneState_Start.h>

#include <ResourceManager\ResourceManager.h>
#include <SafeRelease/SafeRelease.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <Keyboard\Keyboard.h>

#include <2D/UI/ClearLogo/ClearLogoFactory/ClearLogoFactory.h>
#include <2D/UI/FailureLogo/FailureLogoFactory/FailureLogoFactory.h>
#include <2D\UI\PushSpaceLogo\PushSpaceLogoFactory\PushSpaceLogoFactory.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void ResultSceneState_Start::Init()
{
	// ���U���g�V�[���̎擾
	result_scene_ = (ResultScene*)scene_;

	// �f�t�H���g�J�����̍쐬
	DrawComponentManager::CreateDefaultCamera(nullptr);

	if (result_scene_->GetSceneManager()->GetCommonData()->GetIsClear())
	{
		// �N���A���S
		ClearLogoFactory clear_logo_factory;
		clear_logo_factory.Create();
	}
	else
	{
		// ���s���S
		FailureLogoFactory failure_logo_factory;
		failure_logo_factory.Create();
	}

	// �v�b�V���X�y�[�X���S
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void ResultSceneState_Start::Uninit()
{
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void ResultSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		result_scene_->GetSceneManager()->SetNextScene(new TitleScene(new TitleSceneState_Start()));
	}
}



//--------------------------------------------------
// +���Z�b�g�֐�
//--------------------------------------------------
void ResultSceneState_Start::Reset()
{

}