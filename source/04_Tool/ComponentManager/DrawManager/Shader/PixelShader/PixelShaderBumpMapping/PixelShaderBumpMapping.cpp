//================================================================================
//!	@file	 PixelShaderBumpMapping.cpp
//!	@brief	 バンプマッピングピクセルシェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "PixelShaderBumpMapping.h"

#include <GameObjectManager/GameObjectManager.h>



//****************************************
// 定数定義
//****************************************
const char* PixelShaderBumpMapping::PATH = "resource/HLSL/Effect/PixelShader/BumpMapping.psh";



//****************************************
// 関数定義
//****************************************
void PixelShaderBumpMapping::Init()
{
	// デバイス初期化
	InitDevice();

	// シェーダーのコンパイル
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderBumpMapping::Uninit()
{
	// シェーダーの解放
	ReleasePixelShader();
}



void PixelShaderBumpMapping::ObjectSetting(DrawBase* draw, Camera* camera,
										   unsigned object_index)
{
	camera = camera;

	// ライト方向をセット
	Vec4 light_position = (Vec4)*GameObjectManager::GetDrawManager()
		->GetDirectionalLightVector();
	light_position.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->getpMatrix(object_index));
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vec3*)&light_position, (Vec3*)&light_position);
	light_position.w = -0.7f;		// 環境光の比率
	getpConstantTable()->SetVector(getpDevice(), "LAMBERT_DIFFUSE_LIGHT_VECTOR",
								   &light_position);
}



void PixelShaderBumpMapping::MeshSetting(DrawBase* draw, Camera* camera,
										 unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	// ディヒューズテクスチャの設定
	int sampler_index = getpConstantTable()->GetSamplerIndex("DIFFUSE_SAMPLER");
	getpDevice()->SetTexture(sampler_index,
							 draw->getpDiffuseTexture(object_index, mesh_index));

	// 法線テクスチャの設定
	sampler_index = getpConstantTable()->GetSamplerIndex("NORMAL_SAMPLER");
	getpDevice()->SetTexture(sampler_index,
							 draw->getpNormalTexture(object_index, mesh_index));
}