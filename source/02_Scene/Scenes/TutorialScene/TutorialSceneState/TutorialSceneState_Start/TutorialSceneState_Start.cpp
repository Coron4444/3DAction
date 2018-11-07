//================================================================================
//
//    チュートリアルシーンステートクラス(スタート)
//    Author : Araki Kai                                作成日 : 2018/11/06
//
//================================================================================



//****************************************
// インクルード文
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
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void TutorialSceneState_Start::Init()
{
	// チュートリアルシーンの取得
	tutorial_scene_ = (TutorialScene*)scene_;

	// デフォルトカメラの作成
	DrawComponentManager::CreateDefaultCamera(nullptr);

	// チュートリアルロゴ02
	TutorialLogo02Factory tutorial_logo_02_factory;
	tutorial_logo_02_factory.Create();

	// チュートリアルロゴ01
	TutorialLogo01Factory tutorial_logo_01_factory;
	tutorial_scene_->SetLogo(tutorial_logo_01_factory.Create());

	// プッシュスペースロゴ
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void TutorialSceneState_Start::Uninit()
{
	GameObjectManager::Release(tutorial_scene_->GetLogo());
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void TutorialSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		tutorial_scene_->SetState(new TutorialSceneState_End());
	}
}



//--------------------------------------------------
// +リセット関数
//--------------------------------------------------
void TutorialSceneState_Start::Reset()
{

}