//================================================================================
//!	@file	 EffekseerObject.cpp
//!	@brief	 エフェクシアオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================




//****************************************
// インクルード文
//****************************************
#include <codecvt>

#include "EffekseerObject.h"
#include "../EffekseerManager/EffekseerManager.h"

#include <Renderer\Renderer.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const int EffekseerObject::MAX_SPRITE_NUM = 2000;


//****************************************
// プロパティ定義
//****************************************
void EffekseerObject::setDisposable(bool value)
{
	is_disposable_ = value;
}



bool EffekseerObject::getpIsPlaying()
{
	return is_playing_;
}



void EffekseerObject::setIsRepeat(bool value)
{
	is_repeat_ = value;
}



Transform* EffekseerObject::getpTransform()
{
	return &transform_;
}



//****************************************
// 関数定義
//****************************************
void EffekseerObject::Init(std::string* file_path, const std::string* map_key_name)
{
	// レンダラー&マネージャ生成
	CreateRendererAndManager();

	// エフェクト生成
	CreateEffect(file_path);

	// キー名保存
	map_key_name_ = *map_key_name;
}



void EffekseerObject::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	//エフェクトの停止
	Stop();

	//各種開放
	ES_SAFE_RELEASE(effekseer_effect_);
	effekseer_manager_->Destroy();
	effekseer_renderer_->Destroy();

	// マップから解放
	if (!is_disposable_)
	{
		EffekseerManager::getpInstance()->ReleaseFromTheMap(&map_key_name_);
	}
	delete this;
}



void EffekseerObject::ForcedRelease()
{
	reference_counter_ = 0;
	Release();
}



void EffekseerObject::AddReferenceCounter()
{
	reference_counter_++;
}



void EffekseerObject::CreateRendererAndManager()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(EffekseerObject.cpp)", "Error", MB_OK);
		return;
	}

	// エフェクシアの初期化
	effekseer_renderer_ = EffekseerRendererDX9::Renderer::Create(device, MAX_SPRITE_NUM);
	effekseer_manager_ = Effekseer::Manager::Create(MAX_SPRITE_NUM);

	// 描画機能の設定
	effekseer_manager_->SetSpriteRenderer(effekseer_renderer_->CreateSpriteRenderer());
	effekseer_manager_->SetRibbonRenderer(effekseer_renderer_->CreateRibbonRenderer());
	effekseer_manager_->SetRingRenderer(effekseer_renderer_->CreateRingRenderer());
	effekseer_manager_->SetTrackRenderer(effekseer_renderer_->CreateTrackRenderer());
	effekseer_manager_->SetModelRenderer(effekseer_renderer_->CreateModelRenderer());

	// テクスチャ&モデルの読み込み設定(今回はファイルから読み込み)
	effekseer_manager_->SetTextureLoader(effekseer_renderer_->CreateTextureLoader());
	effekseer_manager_->SetModelLoader(effekseer_renderer_->CreateModelLoader());

	// 左手座標系に設定
	effekseer_manager_->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);
}



void EffekseerObject::CreateEffect(std::string* file_path)
{
	// wchar_tにコンバート
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
	std::wstring converted_file_path = convert.from_bytes(*file_path);

	// エフェクトの読み込み
	effekseer_effect_ = Effekseer::Effect::Create(effekseer_manager_,
		(const EFK_CHAR*)converted_file_path.c_str());
}



void EffekseerObject::Update()
{
	// 再生中かどうか
	is_playing_ = effekseer_manager_->Exists(effekseer_handle_);
	if (!is_playing_)
	{
		// 使い捨てかどうか
		if (is_disposable_) return;

		// リピートするかどうか
		is_repeat_ ? Play() : Stop();
	}

	// ワールド行列変更
	ChangeWorldMatrix(transform_.getpWorldMatrix());
	
	//すべてのエフェクトの更新
	effekseer_manager_->Update();
}



void EffekseerObject::Draw()
{
	effekseer_renderer_->BeginRendering();
	effekseer_manager_->Draw();
	effekseer_renderer_->EndRendering();
}



void EffekseerObject::Play()
{
	//エフェクトの再生
	is_playing_ = true;
	effekseer_handle_ = effekseer_manager_->Play(effekseer_effect_, 0.0f, 0.0f, 0.0f);
	effekseer_manager_->Flip();
}



void EffekseerObject::Stop()
{
	is_playing_ = false;
	effekseer_manager_->StopEffect(effekseer_handle_);
	effekseer_manager_->Flip();
}



void EffekseerObject::Pause(bool is_pause)
{
	is_pause_ = is_pause;
	effekseer_manager_->SetPaused(effekseer_handle_, is_pause_);
	effekseer_manager_->Flip();
}



void EffekseerObject::ChangeVelocity(float velocity)
{
	effekseer_manager_->SetSpeed(effekseer_handle_, velocity);
}



void EffekseerObject::ChangeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	effekseer_manager_->SetAllColor(effekseer_handle_, Effekseer::Color(r, g, b, a));
}



void EffekseerObject::ChangeViewMatrix(Effekseer::Matrix44* view_matrix)
{
	effekseer_renderer_->SetCameraMatrix(*view_matrix);
}



void EffekseerObject::ChangeProjectionMatrix(Effekseer::Matrix44* projection_matrix)
{
	effekseer_renderer_->SetProjectionMatrix(*projection_matrix);
}



void EffekseerObject::ChangeWorldMatrix(MATRIX* world_matrix)
{
	// エフェクシア用ワールド行列
	world_matrix_.Value[0][0] = world_matrix->_11;
	world_matrix_.Value[0][1] = world_matrix->_12;
	world_matrix_.Value[0][2] = world_matrix->_13;
	world_matrix_.Value[1][0] = world_matrix->_21;
	world_matrix_.Value[1][1] = world_matrix->_22;
	world_matrix_.Value[1][2] = world_matrix->_23;
	world_matrix_.Value[2][0] = world_matrix->_31;
	world_matrix_.Value[2][1] = world_matrix->_32;
	world_matrix_.Value[2][2] = world_matrix->_33;
	world_matrix_.Value[3][0] = world_matrix->_41;
	world_matrix_.Value[3][1] = world_matrix->_42;
	world_matrix_.Value[3][2] = world_matrix->_43;

	// ワールド行列をセット
	effekseer_manager_->SetMatrix(effekseer_handle_, world_matrix_);
}