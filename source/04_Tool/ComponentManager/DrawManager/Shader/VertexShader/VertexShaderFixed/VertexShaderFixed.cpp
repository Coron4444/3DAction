//================================================================================
//!	@file	 VertexShaderFixed.cpp
//!	@brief	 固定機能頂点シェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "VertexShaderFixed.h"
#include "../../../Camera/Camera.h"

#include <Component/Draw/DrawBase/DrawBase.h>
#include <Renderer/Renderer.h>
#include <GameObjectManager/GameObjectManager.h>



//****************************************
// 関数定義
//****************************************
void VertexShaderFixed::Init()
{
	// デバイス初期化
	ShaderBase::InitDevice();

	// レンダーステートの設定( 最適化の場合はあまり呼ばないように設計する )
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->UseAlphaBlending(true);
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->SetAlphaBlending_Linear();

	// テクスチャーステージステートの設定
	// 第一引数テクスチャステージ番号
	// 第二引数α値の演算今回は乗算(RG1*RG2つまり、TEXTURE＊DIFFUSE)
	getpDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	getpDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	getpDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// サンプラーステートの設定
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->SetDefaultSamplerState();
}



void VertexShaderFixed::Uninit()
{
}



void VertexShaderFixed::ObjectSetting(DrawBase* draw, Camera* camera, unsigned object_index)
{
	// 法線を常に1に正規化
	getpDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// 行列のセット
	getpDevice()->SetTransform(D3DTS_VIEW, camera->getpViewMatrix());
	getpDevice()->SetTransform(D3DTS_PROJECTION, camera->getpProjectionMatrix());
	getpDevice()->SetTransform(D3DTS_WORLD, draw->getpMatrix(object_index));

	// ライトセット
	getpDevice()->SetRenderState(D3DRS_LIGHTING, draw->getpDrawOrderList()->getIsLighting());

	// ライトの更新
	UpdateDirectionalLignt();
}



void VertexShaderFixed::MeshSetting(DrawBase* draw, Camera* camera,
									unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	SetTexture(draw, object_index, mesh_index);
	SetMaterial(draw, object_index, mesh_index);
}



void VertexShaderFixed::SetTexture(DrawBase* draw, unsigned object_index,
								   unsigned mesh_index)
{
	LPDIRECT3DTEXTURE9 diffuse_texture = draw->getpDiffuseTexture(object_index,
																  mesh_index);
	getpDevice()->SetTexture(0, diffuse_texture);
}



void VertexShaderFixed::SetMaterial(DrawBase* draw, unsigned object_index,
									unsigned mesh_index)
{
	D3DMATERIAL9* material = draw->getpMaterial(object_index, mesh_index);
	if (material == nullptr) return;
	getpDevice()->SetMaterial(material);
}



void VertexShaderFixed::UpdateDirectionalLignt()
{
	// ライトの設定
	ZeroMemory(&directional_light_, sizeof(directional_light_));

	directional_light_.Type = D3DLIGHT_DIRECTIONAL;

	// ライト方向を単位ベクトルで代入
	Vec3 directional_light_vector = *GameObjectManager::GetDrawManager()->GetDirectionalLightVector();
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
	getpDevice()->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));

	// ライトをデバイスにセット(第一引数は0～4のライト番号)
	getpDevice()->SetLight(0, &directional_light_);

	// 0番ライトを使えるようにする
	getpDevice()->LightEnable(0, TRUE);
}