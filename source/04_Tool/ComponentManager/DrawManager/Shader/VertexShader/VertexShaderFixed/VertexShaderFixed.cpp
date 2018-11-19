//================================================================================
//
//    固定機能頂点シェーダークラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "VertexShaderFixed.h"
#include "../../../Camera/Camera.h"

#include <Component/DrawBase/DrawBase.h>
#include <Renderer/Renderer.h>
#include <GameObjectManager/GameObjectManager.h>


//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void VertexShaderFixed::Init()
{
	// デバイス初期化
	ShaderBase::InitDevice();

	// レンダーステートの設定( 最適化の場合はあまり呼ばないように設計する )
	((RendererDirectX9*)Renderer::GetInstance()->GetRenderer())->UseAlphaBlending(true);
	((RendererDirectX9*)Renderer::GetInstance()->GetRenderer())->SetAlphaBlending_Linear();

	// テクスチャーステージステートの設定
	// 第一引数テクスチャステージ番号
	// 第二引数α値の演算今回は乗算(RG1*RG2つまり、TEXTURE＊DIFFUSE)
	ShaderBase::GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	ShaderBase::GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	ShaderBase::GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// サンプラーステートの設定
	((RendererDirectX9*)Renderer::GetInstance()->GetRenderer())->SetDefaultSamplerState();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void VertexShaderFixed::Uninit()
{

}



//--------------------------------------------------
// +共通設定関数
//--------------------------------------------------
void VertexShaderFixed::CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index)
{
	// 法線を常に1に正規化
	ShaderBase::GetDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// 行列のセット
	ShaderBase::GetDevice()->SetTransform(D3DTS_VIEW, camera->GetViewMatrix());
	ShaderBase::GetDevice()->SetTransform(D3DTS_PROJECTION, camera->GetProjectionMatrix());
	ShaderBase::GetDevice()->SetTransform(D3DTS_WORLD, draw->GetMatrix(object_index));
	
	// ライトセット
	ShaderBase::GetDevice()->SetRenderState(D3DRS_LIGHTING, draw->GetDrawOrderList()->GetIsLighting());

	// ライトの更新
	UpdateDirectionalLignt();
}



//--------------------------------------------------
// +固有設定関数
//--------------------------------------------------
void VertexShaderFixed::SpecificSetting(DrawBase* draw, Camera* camera,
										unsigned object_index, unsigned mesh_index)
{
	SetTexture(draw, object_index, mesh_index);
	SetMaterial(draw, object_index, mesh_index);
}



//--------------------------------------------------
// -テクスチャ設定関数
//--------------------------------------------------
void VertexShaderFixed::SetTexture(DrawBase* draw, unsigned object_index,
								   unsigned mesh_index)
{
	LPDIRECT3DTEXTURE9 temp = draw->GetDecaleTexture(object_index, mesh_index);

	ShaderBase::GetDevice()->SetTexture(0, temp);
}



//--------------------------------------------------
// -マテリアル設定関数 
//--------------------------------------------------
void VertexShaderFixed::SetMaterial(DrawBase* draw, unsigned object_index,
									unsigned mesh_index)
{
	D3DMATERIAL9* temp = draw->GetMaterial(object_index, mesh_index);

	if (temp == nullptr) return;

	ShaderBase::GetDevice()->SetMaterial(temp);
}



//--------------------------------------------------
// -マテリアル設定関数 
//--------------------------------------------------
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
	ShaderBase::GetDevice()->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));

	// ライトをデバイスにセット(第一引数は0～4のライト番号)
	ShaderBase::GetDevice()->SetLight(0, &directional_light_);

	// 0番ライトを使えるようにする
	ShaderBase::GetDevice()->LightEnable(0, TRUE);
}