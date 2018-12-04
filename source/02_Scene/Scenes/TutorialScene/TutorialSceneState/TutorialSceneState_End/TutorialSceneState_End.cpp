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

#include <ResourceManager\ResourceManager.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <Keyboard\Keyboard.h>

#include <GameObjectManager/GameObjectManager.h>



//****************************************
// 関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void TutorialSceneState_End::Init()
{
	// チュートリアルシーンの取得
	tutorial_scene_ = (TutorialScene*)scene_;

	tutorial_scene_->getpTutorialLogo()->SetLogoNum(1);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void TutorialSceneState_End::Uninit()
{
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void TutorialSceneState_End::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		tutorial_scene_->getpSceneManager()
			->setNextScene(new GameScene(new GameSceneState_Start()));
	}
}



//--------------------------------------------------
// +リセット関数
//--------------------------------------------------
void TutorialSceneState_End::Reset()
{

}