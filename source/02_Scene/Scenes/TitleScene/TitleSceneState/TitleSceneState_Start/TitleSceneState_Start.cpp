//================================================================================
//
//    �^�C�g���V�[���X�e�[�g�N���X(�X�^�[�g)
//    Author : Araki Kai                                �쐬�� : 2018/11/06
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TitleSceneState_Start.h"
#include "../../TitleScene.h"

#include <SceneManager/SceneManager.h>
#include <Scenes/TutorialScene/TutorialScene.h>
#include <Scenes/TutorialScene/TutorialSceneState/TutorialSceneState_Start/TutorialSceneState_Start.h>

#include <ResourceManager/ResourceManager.h>
#include <SafeRelease/SafeRelease.h>
#include <ConvertToFrame/MeterToFrame/MeterToFrame.h>
#include <Keyboard/Keyboard.h>

#include <2D/UI/TitleLogo/TitleLogoFactory/TitleLogoFactory.h>
#include <2D/UI/PushSpaceLogo/PushSpaceLogoFactory/PushSpaceLogoFactory.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void TitleSceneState_Start::Init()
{
	// �^�C�g���V�[���̎擾
	title_scene_ = (TitleScene*)scene_;

	// �f�t�H���g�J�����̍쐬
	GameObjectManager::GetDrawManager()->GetBackBuffer()
		->GetCamera()->ChangeState(nullptr);

	// �^�C�g�����S
	TitleLogoFactory title_logo_factory;
	title_logo_factory.Create();

	// �v�b�V���X�y�[�X���S
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void TitleSceneState_Start::Uninit()
{
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void TitleSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		title_scene_->GetSceneManager()
			->SetNextScene(new TutorialScene(new TutorialSceneState_Start()));
	}
}



//--------------------------------------------------
// +���Z�b�g�֐�
//--------------------------------------------------
void TitleSceneState_Start::Reset()
{

}