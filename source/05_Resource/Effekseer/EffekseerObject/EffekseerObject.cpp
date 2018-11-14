//================================================================================
//
//    エフェクシアオブジェクトクラス
//    Author : Araki Kai                                作成日 : 2017/12/18
//
//================================================================================




//======================================================================
//
// インクルード文
//
//======================================================================

#include <codecvt>

#include "EffekseerObject.h"

#include <Renderer\Renderer.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const int EffekseerObject::MAX_SPRITE_NUM = 2000;



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトコンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerObject::EffekseerObject(const std::string* file_path)
	: effekseer_handle_(0),
	  effekseer_effect_(nullptr),
	  is_playing_      (false),
	  is_repeat_       (false),
	  is_pause_        (false)
{
	// 初期化と読み込み
	InitRenderer_Manager();
	InputEffect(file_path);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerObject::~EffekseerObject()
{
	//エフェクトの停止
	Stop();

	//エフェクトを解放
	ES_SAFE_RELEASE(effekseer_effect_);

	//エフェクト管理用インスタンスを破棄
	effekseer_manager_->Destroy();

	//描画用インスタンスを破棄
	effekseer_renderer_->Destroy();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::Update()
{
	// ワールド行列の設定
	SetWorldMatrix(transform_.GetWorldMatrix());

	// 再生中かどうか
	is_playing_ = effekseer_manager_->Exists(effekseer_handle_);

	if (!is_playing_)
	{
		// リピートするかどうか
		if (is_repeat_)
		{
			Play();
		}
		else
		{
			Stop();
		}
	}

	effekseer_manager_->Flip();
	
	//すべてのエフェクトの更新
	effekseer_manager_->Update();

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::Draw()
{
	effekseer_renderer_->BeginRendering();
	effekseer_manager_->Draw();
	effekseer_renderer_->EndRendering();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 再生関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::Play()
{
	//エフェクトの再生
	effekseer_handle_ = effekseer_manager_->Play(effekseer_effect_, 0.0f, 0.0f, 0.0f);
	effekseer_manager_->Flip();
	is_playing_ = true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 停止関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::Stop()
{
	//エフェクトの停止
	effekseer_manager_->StopEffect(effekseer_handle_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 一時停止設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetPause(bool is_pause)
{
	//エフェクトの一時停止
	is_pause_ = is_pause;
	effekseer_manager_->SetPaused(effekseer_handle_, is_pause_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 速度設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetVelocity(float velocity)
{
	//エフェクトの速度指定
	effekseer_manager_->SetSpeed(effekseer_handle_, velocity);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ カラー設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	effekseer_manager_->SetAllColor(effekseer_handle_, Effekseer::Color(r, g, b, a));
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ プロジェクション行列設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetProjectionMatrix(Effekseer::Matrix44* projection_matrix)
{
	effekseer_renderer_->SetProjectionMatrix(*projection_matrix);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ビュー行列設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetViewMatrix(Effekseer::Matrix44* view_matrix)
{
	effekseer_renderer_->SetCameraMatrix(*view_matrix);
}



//--------------------------------------------------------------------------------
//
// [ レンダラー&マネージャ初期化関数 ]
//
//--------------------------------------------------------------------------------

void EffekseerObject::InitRenderer_Manager()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
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
	effekseer_manager_->SetRingRenderer  (effekseer_renderer_->CreateRingRenderer());
	effekseer_manager_->SetTrackRenderer (effekseer_renderer_->CreateTrackRenderer());
	effekseer_manager_->SetModelRenderer (effekseer_renderer_->CreateModelRenderer());

	// テクスチャの読み込みを設定(今回はファイルから読み込み)
	effekseer_manager_->SetTextureLoader(effekseer_renderer_->CreateTextureLoader());
	effekseer_manager_->SetModelLoader  (effekseer_renderer_->CreateModelLoader());

	// 左手座標系に設定
	effekseer_manager_->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);
}



//--------------------------------------------------------------------------------
//
// [ エフェクトの読み込み関数 ]
//
//--------------------------------------------------------------------------------

void EffekseerObject::InputEffect(const std::string* file_path)
{
	// wchar_tにコンバート
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
	std::wstring temp_file_path = convert.from_bytes(*file_path);


	// エフェクトの読み込み
	effekseer_effect_ = Effekseer::Effect::Create(effekseer_manager_, 
												  (const EFK_CHAR*)temp_file_path.c_str());	
}



//--------------------------------------------------------------------------------
//
// [ ワールド行列設定関数 ]
//
//--------------------------------------------------------------------------------

void EffekseerObject::SetWorldMatrix(const MATRIX* world_matrix)
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