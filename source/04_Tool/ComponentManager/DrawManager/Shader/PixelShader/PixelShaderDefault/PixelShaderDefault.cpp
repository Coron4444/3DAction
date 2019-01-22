//================================================================================
//!	@file	 PixelShaderDefault.cpp
//!	@brief	 デフォルトピクセルシェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/21
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "PixelShaderDefault.h"

#include <GameObjectManager/GameObjectManager.h>



//****************************************
// 定数定義
//****************************************
const char* PixelShaderDefault::PATH = "resource/HLSL/Effect/PixelShader/Default.psh";



//****************************************
// 関数定義
//****************************************
void PixelShaderDefault::Init()
{
	// デバイス初期化
	InitDevice();

	// シェーダーのコンパイル
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderDefault::Uninit()
{
	// シェーダーの解放
	ReleasePixelShader();
}



void PixelShaderDefault::ObjectSetting(DrawBase* draw, Camera* camera,
									   unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



void PixelShaderDefault::MeshSetting(DrawBase* draw, Camera* camera,
									 unsigned object_index,
									 unsigned mesh_index)
{
	camera = camera;
	draw = draw;
	object_index = object_index;
	mesh_index = mesh_index;
	// ディヒューズテクスチャの設定
	int diffuse_sampler_ = getpConstantTable()->GetSamplerIndex("DIFFUSE_SAMPLER");
	LPDIRECT3DTEXTURE9 diffuse_texture = draw->getpDiffuseTexture(object_index, mesh_index);
	bool is_texture = diffuse_texture != nullptr;
	getpConstantTable()->SetBool(getpDevice(), "IS_TEXTURE", is_texture);
	getpDevice()->SetTexture(diffuse_sampler_, diffuse_texture);
}