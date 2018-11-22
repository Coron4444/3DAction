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

#include <2D/UI/TutorialLogo/TutorialLogoFactory/TutorialLogoFactory.h>
#include <2D/UI/PushSpaceLogo/PushSpaceLogoFactory/PushSpaceLogoFactory.h>



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
	GameObjectManager::GetDrawManager()->GetBackBuffer()
		->GetCamera()->ChangeState(nullptr);

	// チュートリアルロゴ
	TutorialLogoFactory tutorial_logo_factory;
	tutorial_scene_->SetTutorialLogo(tutorial_logo_factory.Create());

	// プッシュスペースロゴ
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void TutorialSceneState_Start::Uninit()
{
	
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