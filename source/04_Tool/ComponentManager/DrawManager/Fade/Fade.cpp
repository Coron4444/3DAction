//================================================================================
//
//    フェードクラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "Fade.h"

#include <assert.h>
#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <SafeRelease/SafeRelease.h>
#include <Vector\ConvertToFrame\TimeToFrame\TimeToFrame.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// 定数定義
//****************************************
const std::string Fade::TEXTURE_NAME_TRANSITION_01 = "Fade/Transition_01.png";



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +コンストラクタ
//--------------------------------------------------
Fade::Fade()
	: plane_polygon_(nullptr)
{
	plane_polygon_ = new PlanePolygon();

	// テクスチャの登録
	transition01_texture_ = TextureManager::AddShareData(&TEXTURE_NAME_TRANSITION_01);

	// オーダーリスト設定
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
}



//--------------------------------------------------
// +デストラクタ
//--------------------------------------------------
Fade::~Fade()
{
	// 各種開放
	SafeRelease::Normal(&plane_polygon_);
}



//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void Fade::Init(Type type, State state, Vec2 size, XColor4 color, float speed)
{
	// アサート群
	assert(state != State::STATE_NONE && state != State::STATE_MAX && "不正なステートの入力を確認(fade.cpp)");

	// 各種代入
	type_ = type;
	state_ = state;

	// フェードを指定サイズに変更
	transform_.GetScale()->x = size.x;
	transform_.GetScale()->y = size.y;
	transform_.UpdateWorldMatrixSRT();

	// エンドフラグOFF
	end_flag_ = false;

	// ステートごとの処理
	if (state_ == State::STATE_FADE_IN)
	{
		// カラー
		color.a = 1.0f;
		color_ = color;
		plane_polygon_->SetColor(color_);

		// フェード速度(単位：秒)
		speed_ = -(1.0f / (float)Second_To_Frame(speed));
	}
	else if (state_ == State::STATE_FADE_OUT)
	{
		// カラー
		color.a = 0.0f;
		color_ = color;
		plane_polygon_->SetColor(color_);

		// フェード速度(単位：秒)
		speed_ = 1.0f / (float)Second_To_Frame(speed);
	}
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void Fade::Uninit()
{
	// ステートごとの処理
	if (state_ == State::STATE_FADE_IN)
	{
		
	}
	else if (state_ == State::STATE_FADE_OUT)
	{
		
	}

	end_flag_ = false;
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void Fade::Update()
{
	// α値を変更
	color_.a += speed_;
	plane_polygon_->SetColor(color_);

	// フェードオブジェクトの更新
	if (state_ == State::STATE_FADE_IN)
	{
		// α値が1を上回ったら
		if (color_.a <= 0.0f)
		{
			end_flag_ = true;
		}
	}
	else if (state_ == State::STATE_FADE_OUT)
	{
		// α値が1を上回ったら
		if (color_.a >= 1.0f)
		{
			end_flag_ = true;
		}
	}
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void Fade::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// ポリゴン描画
	plane_polygon_->Draw();
}