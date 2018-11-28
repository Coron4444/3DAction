//================================================================================
//
//    ゲームシーンステートクラス(スタート)
//    Author : Araki Kai                                作成日 : 2018/11/06
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "GameSceneState_Start.h"
#include "../../GameScene.h"

#include <SceneManager/SceneManager.h>
#include <Scenes/ResultScene/ResultScene.h>
#include <Scenes/ResultScene/ResultSceneState/ResultSceneState_Start/ResultSceneState_Start.h>

#include <ResourceManager/ResourceManager.h>
#include <SafeRelease/SafeRelease.h>
#include <ConvertToFrame/MeterToFrame/MeterToFrame.h>
#include <Keyboard/Keyboard.h>

#include <3D/Coin/CoinFactory/CoinFactory.h>
#include <3D/Enemy/EnemyFactory/EnemyFactory.h>
#include <3D/Field/FieldFactory/FieldFactory.h>
#include <3D/Goal/GoalFactory/GoalFactory.h>
#include <3D/SkyDome/SkyDomeFactory/SkyDomeFactory.h>
#include <3D/Player/PlayerFactory/PlayerFactory.h>
#include <3D/StencilShadowTest/StencilShadowTestFactory/StencilShadowTestFactory.h>
#include <2D/UI/Score/ScoreFactory/ScoreFactory.h>



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void GameSceneState_Start::Init()
{
	// ゲームシーンの取得
	game_scene_ = (GameScene*)scene_;

	// ゲームシーン共通データーの初期化
	game_scene_->SetIsClear(false);
	game_scene_->SetScore(0);

	// デフォルトカメラの作成
	//GameObjectManager::GetDrawManager()->GetBackBuffer()
	//	->GetCamera()->ChangeState(new CameraState_CrawlUp());
	GameObjectManager::GetDrawManager()->GetBackBuffer()
		->GetCamera()->ChangeState(new CameraState_HomingTarget());

	// コインの作成
	CoinFactory coin_factory;
	Coin* temp = coin_factory.Create();
	*temp->GetTransform()->GetPosition() = Vec3(5.0f, 0.0f, 0.0f);
	temp->GetTransform()->UpdateWorldMatrixSRT();
	
	temp = coin_factory.Create();
	*temp->GetTransform()->GetPosition() = Vec3(5.0f, 0.0f, 5.0f);
	temp->GetTransform()->UpdateWorldMatrixSRT();
	
	temp = coin_factory.Create();
	*temp->GetTransform()->GetPosition() = Vec3(-5.0f, 0.0f, -5.0f);
	temp->GetTransform()->UpdateWorldMatrixSRT();

	for (unsigned i = 0; i < 20; i++)
	{
		for (unsigned j = 0; j < 3; j++)
		{
			for (unsigned k = 0; k < 10; k++)
			{
				Coin* temp = coin_factory.Create();
				*temp->GetTransform()->GetPosition() = Vec3(-40.0f + i * 5.0f, 
															  0.0f + j * 3.0f, 
															-40.0f + k * 5.0f);
				temp->GetTransform()->UpdateWorldMatrixSRT();
			}
		}
	}

	// スカイドーム
	SkyDomeFactory sky_dome_factory;
	sky_dome_factory.Create();


	// フィールド
	FieldFactory field_factory;
	field_factory.Create();

	//StencilShadowTestFactory stencil_factory;
	//stencil_factory.Create();


	// プレイヤー
	PlayerFactory player_factory;
	Player* player = player_factory.Create(game_scene_);

	((CameraState_HomingTarget*)GameObjectManager::GetDrawManager()->GetBackBuffer()
		->GetCamera()->GetCameraState())->SetTarget(player);

	// 敵
	EnemyFactory enemy_factory;
	Enemy* temp2 = enemy_factory.Create();
	*temp2->GetTransform()->GetPosition() = Vec3(-5.0f, 0.0f, 5.0f);
	temp2->GetTransform()->UpdateWorldMatrixSRT();

	// ゴール
	GoalFactory goal_factory;
	Goal* temp3 = goal_factory.Create();
	*temp3->GetTransform()->GetPosition() = Vec3(10.0f, 0.0f, 20.0f);
	temp3->GetTransform()->UpdateWorldMatrixSRT();

	// スコア
	ScoreFactory score_factory;
	score_factory.Create(game_scene_);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void GameSceneState_Start::Uninit()
{
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void GameSceneState_Start::Update()
{
	// クリア
	if (game_scene_->getGameOver() == 0)
	{
		game_scene_->GetSceneManager()->GetCommonData()->SetIsClear(true);
		game_scene_->GetSceneManager()->SetNextScene(new ResultScene(new ResultSceneState_Start()));
	}

	// 失敗
	if (game_scene_->getGameOver() == 1)
	{
		game_scene_->GetSceneManager()->GetCommonData()->SetIsClear(false);
		game_scene_->GetSceneManager()->SetNextScene(new ResultScene(new ResultSceneState_Start()));
	}
}



//--------------------------------------------------
// +リセット関数
//--------------------------------------------------
void GameSceneState_Start::Reset()
{

}