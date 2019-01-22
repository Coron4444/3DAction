//================================================================================
//!	@file	 TutorialSceneState_Start.cpp
//!	@brief	 チュートリアルシーンステート(スタート)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "TutorialSceneState_Start.h"
#include "../../TutorialScene.h"
#include "../TutorialSceneState_End/TutorialSceneState_End.h"

#include <SceneManager\SceneManager.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <Keyboard\Keyboard.h>

#include <GameObjectManager/GameObjectManager.h>

#include <2D/UI/TutorialLogo/TutorialLogoFactory/TutorialLogoFactory.h>
#include <2D/UI/PushSpaceLogo/PushSpaceLogoFactory/PushSpaceLogoFactory.h>



//****************************************
// 関数定義
//****************************************
void TutorialSceneState_Start::Init()
{
	// チュートリアルシーンの取得
	tutorial_scene_ = (TutorialScene*)getpScene();

	// デフォルトカメラの作成
	GameObjectManager::GetDrawManager()->getpBackBuffer()
		->getpCamera()->setState(nullptr);

	// チュートリアルロゴ
	TutorialLogoFactory tutorial_logo_factory;
	tutorial_scene_->setTutorialLogo(tutorial_logo_factory.Create());

	// プッシュスペースロゴ
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



void TutorialSceneState_Start::Uninit()
{
}



void TutorialSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		tutorial_scene_->setState(new TutorialSceneState_End());
	}
}



void TutorialSceneState_Start::Reset()
{
}