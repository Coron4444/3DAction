//================================================================================
//
//    リザルトシーンステートクラス(スタート)
//    Author : Araki Kai                                作成日 : 2018/11/06
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "ResultSceneState_Start.h"
#include "../../ResultScene.h"

#include <SceneManager/SceneManager.h>
#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState/TitleSceneState_Start/TitleSceneState_Start.h>

#include <ResourceManager\ResourceManager.h>
#include <SafeRelease/SafeRelease.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <Keyboard\Keyboard.h>

#include <2D/UI/ClearLogo/ClearLogoFactory/ClearLogoFactory.h>
#include <2D/UI/FailureLogo/FailureLogoFactory/FailureLogoFactory.h>
#include <2D\UI\PushSpaceLogo\PushSpaceLogoFactory\PushSpaceLogoFactory.h>



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void ResultSceneState_Start::Init()
{
	// リザルトシーンの取得
	result_scene_ = (ResultScene*)scene_;

	// デフォルトカメラの作成
	DrawComponentManager::CreateDefaultCamera(nullptr);

	if (result_scene_->GetSceneManager()->GetCommonData()->GetIsClear())
	{
		// クリアロゴ
		ClearLogoFactory clear_logo_factory;
		clear_logo_factory.Create();
	}
	else
	{
		// 失敗ロゴ
		FailureLogoFactory failure_logo_factory;
		failure_logo_factory.Create();
	}

	// プッシュスペースロゴ
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void ResultSceneState_Start::Uninit()
{
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void ResultSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		result_scene_->GetSceneManager()->SetNextScene(new TitleScene(new TitleSceneState_Start()));
	}
}



//--------------------------------------------------
// +リセット関数
//--------------------------------------------------
void ResultSceneState_Start::Reset()
{

}