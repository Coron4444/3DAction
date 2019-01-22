//================================================================================
//!	@file	 SceneManager.cpp
//!	@brief	 シーンマネージャClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "SceneManager.h"
#include <SceneBase/SceneBase.h>

#include <main.h>
#include <SafeRelease/SafeRelease.h>
#include <GameObjectManager\GameObjectManager.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>
#include <Texture/TextureManager/TextureManager.h>
#include <ModelX/ModelXManager/ModelXManager.h>
#include <MdBin/MdBinManager/MdBinManager.h>



//****************************************
// 定数定義
//****************************************
const Fade::Type SceneManager::DEFAULT_FADE_TYPE = Fade::Type::TYPE_NORMAL;
const float      SceneManager::DEFAULT_FADE_SPEED = 1.0f;
const XColor4    SceneManager::DEFAULT_FADE_COLOR(0.0f, 0.0f, 0.0f, 1.0f);



//****************************************
// プロパティ定義
//****************************************
bool SceneManager::CommonData::getIsUpdate()
{ 
	return is_update_; 
}



void SceneManager::CommonData::setIsUpdate(bool value)
{ 
	is_update_ = value; 
}



bool SceneManager::CommonData::getIsClear()
{ 
	return is_clear_; 
}



void SceneManager::CommonData::setIsClear(bool value)
{ 
	is_clear_ = value; 
}



void SceneManager::setNextScene(SceneBase* value)
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
	common_data_->setIsUpdate(false);

	// フェードアウト初期化
	GameObjectManager::GetDrawManager()->getpBackBuffer()
		->InitFade(fade_type_, Fade::State::STATE_FADE_OUT,
				   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
				   fade_color_, fade_speed_);
}



SceneManager::CommonData* SceneManager::getpCommonData()
{ 
	return common_data_; 
}



void SceneManager::setFadeType(Fade::Type value) 
{ 
	fade_type_ = value; 
}



void SceneManager::setFadeSpeed(float value) 
{ 
	fade_speed_ = value; 
}



void SceneManager::setFadeColor(XColor4 value) 
{ 
	fade_color_ = value; 
}



//****************************************
// 関数定義
//****************************************
void SceneManager::Init(SceneBase* scene)
{
	// 共有データーの初期化
	common_data_ = new CommonData();
	common_data_->Reset();

	// リソースの初期化
	EffekseerManager::getpInstance()->Init();
	TextureManager::getpInstance()->Init();
	ModelXManager::getpInstance()->Init();
	MdBinManager::getpInstance()->Init();

	// ゲームオブジェクトマネージャの初期化
	GameObjectManager::Init();

	// シーンの初期化
	current_scene_ = scene;
	current_scene_->setSceneManager(this);
	current_scene_->Init();
}



void SceneManager::Uninit()
{
	// シーンの終了処理
	if (current_scene_ != nullptr) current_scene_->Uninit();
	if (next_scene_ != nullptr)  next_scene_->Uninit();

	//ゲームオブジェクトマネージャの終了処理
	GameObjectManager::Uninit();

	// リソースの終了処理
	MdBinManager::getpInstance()->Uninit();
	MdBinManager::ReleaseInstance();
	ModelXManager::getpInstance()->Uninit();
	ModelXManager::ReleaseInstance();
	TextureManager::getpInstance()->Uninit();
	TextureManager::ReleaseInstance();
	EffekseerManager::getpInstance()->Uninit();
	EffekseerManager::ReleaseInstance();

	// 各種開放
	SafeRelease::Normal(&current_scene_);
	SafeRelease::Normal(&next_scene_);
	SafeRelease::Normal(&common_data_);
}



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



void SceneManager::UpdateScene()
{
	if (current_scene_ == nullptr) return;

	// 各シーン特有の更新
	current_scene_->Update();
	
	// ゲームオブジェクトマネージャの更新
	GameObjectManager::Update();
}



void SceneManager::DrawScene()
{
	if (current_scene_ == nullptr) return;

	//ゲームオブジェクトマネージャの描画
	GameObjectManager::Draw();
}



void SceneManager::ResetScene()
{
	// 既にほかの要求を受け付けている場合
	if (state_ != SceneManager::State::NONE) return;

	// ステートの変更
	state_ = SceneManager::State::RESET_SCENE;

	// フェードアウト初期化
	GameObjectManager::GetDrawManager()->getpBackBuffer()
		->InitFade(fade_type_, Fade::State::STATE_FADE_OUT,
				   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
				   fade_color_, fade_speed_);
}



void SceneManager::SceneChange()
{
	// フェード処理が終わっているかどうか
	if (!GameObjectManager::GetDrawManager()->getpBackBuffer()->IsFadeEnd()) return;

	// フェードのステートごとの処理
	if (GameObjectManager::GetDrawManager()->getpBackBuffer()
		->IsFadeStateName(Fade::State::STATE_FADE_OUT))
	{
		// 現在のメインシーンの終了処理
		SafeRelease::PlusUninit(&current_scene_);

		// ゲームオブジェクトマネージャのシーン変更時終了処理
		GameObjectManager::UninitWhenChangeScene();

		// 新しいシーンへ移行
		current_scene_ = next_scene_;
		next_scene_ = nullptr;
		current_scene_->setSceneManager(this);
		current_scene_->Init();

		// フェード終了
		GameObjectManager::GetDrawManager()->getpBackBuffer()->UninitFade();

		// フェードイン初期化
		GameObjectManager::GetDrawManager()->getpBackBuffer()
			->InitFade(fade_type_, Fade::State::STATE_FADE_IN,
					   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
					   fade_color_, fade_speed_);
	}
	else if (GameObjectManager::GetDrawManager()->getpBackBuffer()
			 ->IsFadeStateName(Fade::State::STATE_FADE_IN))
	{
		// フェード終了処理
		state_ = SceneManager::State::NONE;
		common_data_->setIsUpdate(true);
		GameObjectManager::GetDrawManager()->getpBackBuffer()->UninitFade();
	}
}



void SceneManager::SceneReset()
{
	// フェード処理が終わっているかどうか
	if (!GameObjectManager::GetDrawManager()->getpBackBuffer()->IsFadeEnd()) return;

	// フェードのステートごとの処理
	if (GameObjectManager::GetDrawManager()->getpBackBuffer()
		->IsFadeStateName(Fade::State::STATE_FADE_OUT))
	{
		// 現在のメインシーンのリセット
		GameObjectManager::AllReset();
		current_scene_->Reset();

		// フェード終了
		GameObjectManager::GetDrawManager()->getpBackBuffer()->UninitFade();

		// フェードイン初期化
		GameObjectManager::GetDrawManager()->getpBackBuffer()
			->InitFade(fade_type_, Fade::State::STATE_FADE_IN,
					   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
					   fade_color_, fade_speed_);
	}
	else if (GameObjectManager::GetDrawManager()->getpBackBuffer()
			 ->IsFadeStateName(Fade::State::STATE_FADE_IN))
	{
		// フェード終了処理
		state_ = SceneManager::State::NONE;
		common_data_->setIsUpdate(true);
		GameObjectManager::GetDrawManager()->getpBackBuffer()->UninitFade();
	}
}