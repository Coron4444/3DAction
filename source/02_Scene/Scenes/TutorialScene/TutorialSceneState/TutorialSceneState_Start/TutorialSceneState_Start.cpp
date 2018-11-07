//================================================================================
//
//    �`���[�g���A���V�[���X�e�[�g�N���X(�X�^�[�g)
//    Author : Araki Kai                                �쐬�� : 2018/11/06
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TutorialSceneState_Start.h"
#include "../../TutorialScene.h"
#include "../TutorialSceneState_End/TutorialSceneState_End.h"

#include <SceneManager\SceneManager.h>

#include <ResourceManager\ResourceManager.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <Keyboard\Keyboard.h>

#include <GameObjectManager/GameObjectManager.h>

#include <2D\UI\TutorialLogo01\TutorialLogo01Factory\TutorialLogo01Factory.h>
#include <2D\UI\TutorialLogo02\TutorialLogo02Factory\TutorialLogo02Factory.h>
#include <2D\UI\PushSpaceLogo\PushSpaceLogoFactory\PushSpaceLogoFactory.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void TutorialSceneState_Start::Init()
{
	// �`���[�g���A���V�[���̎擾
	tutorial_scene_ = (TutorialScene*)scene_;

	// �f�t�H���g�J�����̍쐬
	DrawComponentManager::CreateDefaultCamera(nullptr);

	// �`���[�g���A�����S02
	TutorialLogo02Factory tutorial_logo_02_factory;
	tutorial_logo_02_factory.Create();

	// �`���[�g���A�����S01
	TutorialLogo01Factory tutorial_logo_01_factory;
	tutorial_scene_->SetLogo(tutorial_logo_01_factory.Create());

	// �v�b�V���X�y�[�X���S
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void TutorialSceneState_Start::Uninit()
{
	GameObjectManager::Release(tutorial_scene_->GetLogo());
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void TutorialSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		tutorial_scene_->SetState(new TutorialSceneState_End());
	}
}



//--------------------------------------------------
// +���Z�b�g�֐�
//--------------------------------------------------
void TutorialSceneState_Start::Reset()
{

}