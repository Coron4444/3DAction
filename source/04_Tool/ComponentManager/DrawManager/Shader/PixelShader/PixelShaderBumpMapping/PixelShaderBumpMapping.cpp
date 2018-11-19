//================================================================================
//
//    バンプマッピングピクセルシェーダークラス
//    Author : Araki Kai                                作成日 : 2018/11/17
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "PixelShaderBumpMapping.h"

#include <GameObjectManager/GameObjectManager.h>



//****************************************
// 定数定義
//****************************************
const char* PixelShaderBumpMapping::PATH = "resource/HLSL/Effect/PixelShader/PixelShaderBumpMapping.psh";



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void PixelShaderBumpMapping::Init()
{
	// デバイス初期化
	InitDevice();

	// シェーダーのコンパイル
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void PixelShaderBumpMapping::Uninit()
{
	// シェーダーの解放
	ReleasePixelShader();
}



//--------------------------------------------------
// +共通設定関数
//--------------------------------------------------
void PixelShaderBumpMapping::CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index)
{
	// ライト方向をセット
	Vec4 light_position = (Vec4)*GameObjectManager::GetDrawManager()
		->GetDirectionalLightVector();
	light_position.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->GetMatrix(object_index));
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vec3*)&light_position, (Vec3*)&light_position);
	light_position.w = -0.7f;		// 環境光の比率
	GetConstantTable()->SetVector(GetDevice(),
								  "LAMBERT_DIFFUSE_LIGHT_VECTOR",
								  &light_position);
}



//--------------------------------------------------
// +固有設定関数
//--------------------------------------------------
void PixelShaderBumpMapping::SpecificSetting(DrawBase* draw, Camera* camera,
											  unsigned object_index, unsigned mesh_index)
{
	// デカールテクスチャの設定
	int sampler_index = GetConstantTable()->GetSamplerIndex("DECALE_SAMPLER");
	GetDevice()->SetTexture(sampler_index, 
							draw->GetDecaleTexture(object_index, mesh_index));

	// 法線テクスチャの設定
	sampler_index = GetConstantTable()->GetSamplerIndex("NORMAL_SAMPLER");
	GetDevice()->SetTexture(sampler_index, 
							draw->GetNormalTexture(object_index, mesh_index));
}