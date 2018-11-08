//================================================================================
//
//    固定パイプラインオブジェクトクラス(static)
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include <assert.h>

#include "FixedPipelineObject.h"
#include <ComponentManager\DrawComponentManager\Camera\Camera.h>
#include <Component/DrawComponent/DrawComponent.h>
#include <GameObjectOrigin/GameObjectOrigin.h>


#include <main.h>
#include <Transform\Transform.h>




//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

D3DLIGHT9		  FixedPipelineObject::directional_light_;
LPDIRECT3DDEVICE9 FixedPipelineObject::device_ = nullptr;



//======================================================================
//
// 静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::Init()
{
	// デバイスの取得
	Renderer::GetInstance()->GetDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(FixedPipeline.cpp)", "Error", MB_OK);
		return;
	}

	// ディレクショナルライト初期化
	Init_DirectionalLignt();

	// レンダーステートの設定( 最適化の場合はあまり呼ばないように設計する )
	UseAlphaBlending(true);
	SetAlphaBlending_Linear();

	// テクスチャーステージステートの設定
	// 第一引数テクスチャステージ番号
	// 第二引数α値の演算今回は乗算(RG1*RG2つまり、TEXTURE＊DIFFUSE)
	device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// サンプラーステートの設定
	SetDefaultSamplerState();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::Uninit()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 3D描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::Draw3D(DrawComponent* draw_component, Camera* camera)
{
	// 統一設定
	UnifiedSetting();
	
	// 3D描画設定
	SetDraw3D(camera);

	// ワールド行列セット
	SetWorldMatrix(draw_component);
	
	for (unsigned i = 0; i < draw_component->GetMeshNum(); i++)
	{
		// テクスチャのセット
		SetTexture(draw_component, i);

		// マテリアルのセット
		SetMaterial(draw_component, i);

		// 描画
		draw_component->Draw(i);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 2D描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::Draw2D(DrawComponent* draw_component, Camera* camera)
{
	camera = camera;

	// 統一設定
	UnifiedSetting();

	// 2D描画設定
	SetDraw2D();

	// ワールド行列セット
	SetWorldMatrix(draw_component);
	
	for (unsigned i = 0; i < draw_component->GetMeshNum(); i++)
	{
		// テクスチャのセット
		SetTexture(draw_component, i);

		// マテリアルのセット
		SetMaterial(draw_component, i);

		// 描画
		draw_component->Draw(i);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 3D描画設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::SetDraw3D(Camera* camera)
{
	device_->SetTransform( D3DTS_VIEW,		camera->GetViewMatrix());
	device_->SetTransform( D3DTS_PROJECTION, camera->GetProjectionMatrix());
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 2D描画設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::SetDraw2D()
{
	// ビュー行列の作成
	MatrixExtend matrix_view;

	// プロジェクション行列の作成
	MATRIX matrix_projection 
			= {2.0f/SCREEN_WIDTH,				0.0f, 0.0f, 0.0f,
						    0.0f, 2.0f/SCREEN_HEIGHT, 0.0f, 0.0f,
						    0.0f,               0.0f, 1.0f, 0.0f,
						    0.0f,               0.0f, 0.0f, 1.0f
			  };

	device_->SetTransform(D3DTS_VIEW,	   matrix_view.GetWorldMatrix());
	device_->SetTransform(D3DTS_PROJECTION, &matrix_projection);
}



//--------------------------------------------------------------------------------
//
// [ 固定パイプライン統一設定関数 ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::UnifiedSetting()
{
	// 法線を常に1に正規化
	device_->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
}



//--------------------------------------------------------------------------------
//
// [ ワールド行列設定関数 ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::SetWorldMatrix(DrawComponent* draw_component)
{
	device_->SetTransform(D3DTS_WORLD, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix());
}



//--------------------------------------------------------------------------------
//
// [ テクスチャ設定関数 ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::SetTexture(DrawComponent* draw_component, unsigned mesh_index)
{
	LPDIRECT3DTEXTURE9 temp = draw_component->GetDecaleTexture(mesh_index);

	device_->SetTexture(0, temp);
}



//--------------------------------------------------------------------------------
//
// [ マテリアル設定関数 ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::SetMaterial(DrawComponent* draw_component, unsigned mesh_index)
{
	D3DMATERIAL9* temp = draw_component->GetMaterial(mesh_index);

	if (temp == nullptr) return;

	device_->SetMaterial(temp);
}



//--------------------------------------------------------------------------------
//
// [ ディレクショナルライト初期化関数 ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::Init_DirectionalLignt()
{
	// ライトの設定
	ZeroMemory(&directional_light_, sizeof(directional_light_));

	directional_light_.Type = D3DLIGHT_DIRECTIONAL;
	
	// ライト方向を単位ベクトルで代入
	Vec3 directional_light_vector = Vec3(0.5f, -1.0f, 0.8f);
	D3DXVec3Normalize((D3DXVECTOR3*)&directional_light_.Direction, &directional_light_vector);
	
	// ライトカラー
	directional_light_.Diffuse.r = 1.0f;
	directional_light_.Diffuse.g = 1.0f;
	directional_light_.Diffuse.b = 1.0f;
	directional_light_.Diffuse.a = 1.0f;
	
	// アンビエントライト
	directional_light_.Ambient.r = 0.1f;
	directional_light_.Ambient.g = 0.1f;
	directional_light_.Ambient.b = 0.1f;
	directional_light_.Ambient.a = 1.0f;
	
	// グローバルアンビエントの設定
	device_->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));

	// ライトをデバイスにセット(第一引数は0～4のライト番号)
	device_->SetLight(0, &directional_light_);

	// 0番ライトを使えるようにする
	device_->LightEnable(0, TRUE);
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ アルファ合成フラグ関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::UseAlphaBlending(bool flag)
{
	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, flag);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ アルファ合成関数(線形合成) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Linear()
{
	// SRC --- 今から描くもの。
	// DEST--- すでに描画されている画面のこと。
	// 1は100%(255)のこと
	// 今回はSRC_αが0だから背景色が100%で出ている。

	// {(1 - SRC_α) * DEST_RGB} + (SRC_RGB * SRC_α) 
	device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ アルファ合成関数(加算合成) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Add()
{
	// (DST_RGB * 1) - (SRC_RGB * SRC_α) 
	device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ アルファ合成関数(減算合成) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Sub()
{
	// (DST_RGB * 1) - (SRC_RGB * SRC_α) 
	device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ アルファ合成関数(乗算合成) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Mul()
{
	//device_-> SetRenderState( D3DRS_BLENDOP, 任意の値)
	// 下記2行で成立するため上記の設定に依存しない

	// (DST_RGB * SRC_RGB) + (SRC_RGB * 0)
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ アルファ合成関数(焼きこみ合成) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Baking()
{
	//device_-> SetRenderState(D3DRS_BLENDOP, 任意の値)
	// 下記2行で成立するため上記の設定に依存しない

	// (DST_RGB * DST_RGB) + ( SRC_RGB * 0 )
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ アルファ合成関数(ネガポジ反転合成) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Nega()
{
	//device_->SetRenderState(D3DRS_BLENDOP, 任意の値)
	// 下記2行で成立するため上記の設定に依存しない

	// (DST_RGB * 0) + (1 - DST_RGB) * SRC_RGB
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ アルファ合成関数(不透明合成) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Opacity()
{
	//device_->SetRenderState(D3DRS_BLENDOP, 任意の値)
	// 下記2行で成立するため上記の設定に依存しない

	// (DST_RGB * 0) + (SRC_RGB * 1)
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトサンプラーステート設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::SetDefaultSamplerState()
{
	// 第二引数(UVの設定)
	// 第三引数テクスチャー座標外の処理
	// WRAP ( 複製 )
	// CLAMP( 一番最後のピクセルを引き延ばして参照する )
	// MIRROR( 鏡 )
	device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// フィルタリング
	// MIPマップ(あらかじめ小さい画像データを自動で用意しておく)
	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// デフォルトはPOINT(代表点1個を拾ってくる)
																				// LINEAR(周りの点を集約して、つまり色をブレンドして1点にする)よって色がぼけるが滑らか
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// デフォルトはPOINT
	device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);	// デフォルトはNONE(MIPマップを使わない)
																				// LINEAR（MIPマップ間を線形補完する）
}