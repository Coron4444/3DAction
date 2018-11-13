//================================================================================
//
//    シーンマネージャクラスヘッダ
//    Author : Araki Kai                                作成日 : 2018/11/02
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "SceneManager.h"
#include <SceneBase/SceneBase.h>

#include <main.h>
#include <SafeRelease/SafeRelease.h>
#include <ResourceManager\ResourceManager.h>



//****************************************
// 定数定義
//****************************************
const Fade::Type SceneManager::DEFAULT_FADE_TYPE = Fade::Type::TYPE_NORMAL;
const float      SceneManager::DEFAULT_FADE_SPEED = 1.0f;
const XColor4    SceneManager::DEFAULT_FADE_COLOR(0.0f, 0.0f, 0.0f, 1.0f);



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +コンストラクタ
//--------------------------------------------------
SceneManager::SceneManager(SceneBase* scene)
	: state_(SceneManager::State::NONE),
	common_data_(nullptr),
	current_scene_(nullptr),
	next_scene_(nullptr),
	fade_type_(DEFAULT_FADE_TYPE),
	fade_speed_(DEFAULT_FADE_SPEED),
	fade_color_(DEFAULT_FADE_COLOR)
{
	// 共有データーの初期化
	common_data_ = new CommonData();
	common_data_->Reset();

	// リソースの初期化
	ResourceManager::InitAllData();

	// ゲームオブジェクトマネージャの初期化
	GameObjectManager::Init();

	// シーンの初期化
	current_scene_ = scene;
	current_scene_->SetSceneManager(this);
	current_scene_->Init();
}



//--------------------------------------------------
// +デストラクタ
//--------------------------------------------------
SceneManager::~SceneManager()
{
	// シーンの終了処理
	if (current_scene_ != nullptr) current_scene_->Uninit();
	if (next_scene_ != nullptr)  next_scene_->Uninit();

	//ゲームオブジェクトマネージャの終了処理
	GameObjectManager::Uninit();

	// リソースの終了処理
	ResourceManager::UninitAllData();

	// 各種開放
	SafeRelease::Normal(&current_scene_);
	SafeRelease::Normal(&next_scene_);
	SafeRelease::Normal(&common_data_);
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void SceneManager::Update()
{
	switch (state_)
	{
		case SceneManager::State::CHANGE_SCENE:
		{
			// シーン変更
			SceneChange();
			break;
		}
		case SceneManager::State::RESET_SCENE:
		{
			// シーンリセット
			SceneReset();
			break;
		}
	}
}



//--------------------------------------------------
// +シーンの更新関数
//--------------------------------------------------
void SceneManager::UpdateScene()
{
	if (current_scene_ == nullptr) return;

	// 各シーン特有の更新
	current_scene_->Update();
	
	// ゲームオブジェクトマネージャの更新
	GameObjectManager::Update();
}



//--------------------------------------------------
// +シーンの描画関数
//--------------------------------------------------
void SceneManager::DrawScene()
{
	if (current_scene_ == nullptr) return;

	//ゲームオブジェクトマネージャの描画
	GameObjectManager::Draw();
}



//--------------------------------------------------
// +次のシーン設定関数
//--------------------------------------------------
void SceneManager::SetNextScene(SceneBase* value)
{
	// 既にほかの要求を受け付けている場合
	if (state_ != SceneManager::State::NONE)
	{
		value->ReleaseState();
		SafeRelease::Normal(&value);
		return;
	}

	// 変更シーンの登録
	next_scene_ = value;

	// ステートの変更
	state_ = SceneManager::State::CHANGE_SCENE;

	// UpdateフラグOFF
	common_data_->SetIsUpdate(false);

	// フェードアウト初期化
	GameObjectManager::GetDrawManager()->GetBackBuffer()
		->InitFade(fade_type_, Fade::State::STATE_FADE_OUT,
				   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
				   fade_color_, fade_speed_);
}



//--------------------------------------------------
// +シーンリセット関数
//--------------------------------------------------
void SceneManager::ResetScene()
{
	// 既にほかの要求を受け付けている場合
	if (state_ != SceneManager::State::NONE) return;

	// ステートの変更
	state_ = SceneManager::State::RESET_SCENE;

	// フェードアウト初期化
	GameObjectManager::GetDrawManager()->GetBackBuffer()
		->InitFade(fade_type_, Fade::State::STATE_FADE_OUT,
				   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
				   fade_color_, fade_speed_);
}



//--------------------------------------------------
// -シーン変更関数
//--------------------------------------------------
void SceneManager::SceneChange()
{
	// フェード処理が終わっているかどうか
	if (!GameObjectManager::GetDrawManager()->GetBackBuffer()->IsFadeEnd()) return;

	// フェードのステートごとの処理
	if (GameObjectManager::GetDrawManager()->GetBackBuffer()
		->IsFadeStateName(Fade::State::STATE_FADE_OUT))
	{
		// 現在のメインシーンの終了処理
		SafeRelease::PlusUninit(&current_scene_);

		// ゲームオブジェクトマネージャのシーン変更時終了処理
		GameObjectManager::UninitWhenChangeScene();

		// 固有リソースの解放
		ResourceManager::UninitUniqueData();

		// 新しいシーンへ移行
		current_scene_ = next_scene_;
		next_scene_ = nullptr;
		current_scene_->SetSceneManager(this);
		current_scene_->Init();

		// フェード終了
		GameObjectManager::GetDrawManager()->GetBackBuffer()->UninitFade();

		// フェードイン初期化
		GameObjectManager::GetDrawManager()->GetBackBuffer()
			->InitFade(fade_type_, Fade::State::STATE_FADE_IN,
					   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
					   fade_color_, fade_speed_);
	}
	else if (GameObjectManager::GetDrawManager()->GetBackBuffer()
			 ->IsFadeStateName(Fade::State::STATE_FADE_IN))
	{
		// フェード終了処理
		state_ = SceneManager::State::NONE;
		common_data_->SetIsUpdate(true);
		GameObjectManager::GetDrawManager()->GetBackBuffer()->UninitFade();
	}
}



//--------------------------------------------------
// -シーンリセット関数
//--------------------------------------------------
void SceneManager::SceneReset()
{
	// フェード処理が終わっているかどうか
	if (!GameObjectManager::GetDrawManager()->GetBackBuffer()->IsFadeEnd()) return;

	// フェードのステートごとの処理
	if (GameObjectManager::GetDrawManager()->GetBackBuffer()
		->IsFadeStateName(Fade::State::STATE_FADE_OUT))
	{
		// 現在のメインシーンのリセット
		GameObjectManager::AllReset();
		current_scene_->Reset();

		// フェード終了
		GameObjectManager::GetDrawManager()->GetBackBuffer()->UninitFade();

		// フェードイン初期化
		GameObjectManager::GetDrawManager()->GetBackBuffer()
			->InitFade(fade_type_, Fade::State::STATE_FADE_IN,
					   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
					   fade_color_, fade_speed_);
	}
	else if (GameObjectManager::GetDrawManager()->GetBackBuffer()
			 ->IsFadeStateName(Fade::State::STATE_FADE_IN))
	{
		// フェード終了処理
		state_ = SceneManager::State::NONE;
		common_data_->SetIsUpdate(true);
		GameObjectManager::GetDrawManager()->GetBackBuffer()->UninitFade();
	}
}