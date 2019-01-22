//================================================================================
//!	@file	 TitleSceneState_Start.cpp
//!	@brief	 タイトルシーンステート(スタート)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "TitleSceneState_Start.h"
#include "../../TitleScene.h"

#include <SceneManager/SceneManager.h>
#include <Scenes/TutorialScene/TutorialScene.h>
#include <Scenes/TutorialScene/TutorialSceneState/TutorialSceneState_Start/TutorialSceneState_Start.h>

#include <GameObjectManager/GameObjectManager.h>
#include <SafeRelease/SafeRelease.h>
#include <ConvertToFrame/MeterToFrame/MeterToFrame.h>
#include <Keyboard/Keyboard.h>

#include <2D/UI/TitleLogo/TitleLogoFactory/TitleLogoFactory.h>
#include <2D/UI/PushSpaceLogo/PushSpaceLogoFactory/PushSpaceLogoFactory.h>



//****************************************
// 関数定義
//****************************************
void TitleSceneState_Start::Init()
{
	// タイトルシーンの取得
	title_scene_ = (TitleScene*)getpScene();

	// デフォルトカメラの作成
	GameObjectManager::GetDrawManager()->getpBackBuffer()
		->getpCamera()->setState(nullptr);

	// タイトルロゴ
	TitleLogoFactory title_logo_factory;
	title_logo_factory.Create();

	// プッシュスペースロゴ
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



void TitleSceneState_Start::Uninit()
{
}



void TitleSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		title_scene_->getpSceneManager()
			->setNextScene(new TutorialScene(new TutorialSceneState_Start()));
	}
}



void TitleSceneState_Start::Reset()
{

}