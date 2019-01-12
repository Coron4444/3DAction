//================================================================================
//!	@file	 TutorialSceneState_End.cpp
//!	@brief	 チュートリアルシーンステート(エンド)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "TutorialSceneState_End.h"
#include "../../TutorialScene.h"

#include <SceneManager\SceneManager.h>
#include <Scenes\GameScene\GameScene.h>
#include <Scenes/GameScene/GameSceneState/GameSceneState_Start/GameSceneState_Start.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <Keyboard\Keyboard.h>

#include <2D/UI/TutorialLogo/TutorialLogoFactory/TutorialLogoFactory.h>



//****************************************
// 関数定義
//****************************************
void TutorialSceneState_End::Init()
{
	// チュートリアルシーンの取得
	tutorial_scene_ = (TutorialScene*)getpScene();

	tutorial_scene_->getpTutorialLogo()->SetLogoNum(1);
}



void TutorialSceneState_End::Uninit()
{
}



void TutorialSceneState_End::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		tutorial_scene_->getpSceneManager()
			->setNextScene(new GameScene(new GameSceneState_Start()));
	}
}



void TutorialSceneState_End::Reset()
{

}