//================================================================================
//
//    タイトルシーンステートクラス(スタート)
//    Author : Araki Kai                                作成日 : 2018/11/06
//
//================================================================================



//****************************************
// インクルード文
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
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void TitleSceneState_Start::Init()
{
	// タイトルシーンの取得
	title_scene_ = (TitleScene*)scene_;

	// デフォルトカメラの作成
	GameObjectManager::GetDrawManager()->GetBackBuffer()
		->GetCamera()->ChangeState(nullptr);

	// タイトルロゴ
	TitleLogoFactory title_logo_factory;
	title_logo_factory.Create();

	// プッシュスペースロゴ
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void TitleSceneState_Start::Uninit()
{
}



//--------------------------------------------------
// +更新関数
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
// +リセット関数
//--------------------------------------------------
void TitleSceneState_Start::Reset()
{

}