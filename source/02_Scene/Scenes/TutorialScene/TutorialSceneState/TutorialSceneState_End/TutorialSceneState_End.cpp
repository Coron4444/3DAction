//================================================================================
//
//    �`���[�g���A���V�[���X�e�[�g�N���X(�X�^�[�g)
//    Author : Araki Kai                                �쐬�� : 2018/11/06
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TutorialSceneState_End.h"
#include "../../TutorialScene.h"

#include <SceneManager\SceneManager.h>
#include <Scenes\GameScene\GameScene.h>
#include <Scenes/GameScene/GameSceneState/GameSceneState_Start/GameSceneState_Start.h>

#include <ResourceManager\ResourceManager.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <Keyboard\Keyboard.h>

#include <GameObjectManager/GameObjectManager.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void TutorialSceneState_End::Init()
{
	// �`���[�g���A���V�[���̎擾
	tutorial_scene_ = (TutorialScene*)scene_;

	tutorial_scene_->GetTutorialLogo()->SetLogoNum(1);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void TutorialSceneState_End::Uninit()
{
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void TutorialSceneState_End::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		tutorial_scene_->GetSceneManager()
			->SetNextScene(new GameScene(new GameSceneState_Start()));
	}
}



//--------------------------------------------------
// +���Z�b�g�֐�
//--------------------------------------------------
void TutorialSceneState_End::Reset()
{

}