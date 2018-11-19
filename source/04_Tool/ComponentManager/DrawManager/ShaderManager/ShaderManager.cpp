//================================================================================
//
//    シェーダーマネージャークラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "ShaderManager.h"
#include "../Shader/ShaderBase/VertexShaderNull.h"
#include "../Shader/ShaderBase/PixelShaderNull.h"
#include "../Shader/VertexShader/VertexShaderFixed/VertexShaderFixed.h"
#include "../Shader/VertexShader/VertexShaderBumpMapping/VertexShaderBumpMapping.h"
#include "../Shader/PixelShader/PixelShaderBumpMapping/PixelShaderBumpMapping.h"

#include <Component/Base/DrawBase/DrawBase.h>

#include <SafeRelease/SafeRelease.h>



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void ShaderManager::Init()
{
	InitVertexShaders();
	InitPixelShaders();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void ShaderManager::Uninit()
{
	UninitVertexShaders();
	UninitPixelShaders();
}



//--------------------------------------------------
// +シェーダー設定関数
//--------------------------------------------------
void ShaderManager::SetShader(DrawBase* draw, VertexShaderType forced_vertex_type,
							  PixelShaderType forced_pixel_type)
{
	// 頂点シェーダー
	SetVertexShader(draw, forced_vertex_type);

	// ピクセルシェーダー
	SetPixelShader(draw, forced_pixel_type);
}



//--------------------------------------------------
// +共通設定関数
//--------------------------------------------------
void ShaderManager::CommonSetting(DrawBase* draw, Camera* camera,
								  VertexShaderType forced_vertex_type,
								  PixelShaderType forced_pixel_type,
								  unsigned object_index)
{
	// 頂点シェーダー
	CommonSettingVertexShader(draw, camera, forced_vertex_type, object_index);

	// ピクセルシェーダー
	CommonSettingPixelShader(draw, camera, forced_pixel_type, object_index);
}



//--------------------------------------------------
// +共通設定関数
//--------------------------------------------------
void ShaderManager::SpecificSetting(DrawBase* draw, Camera* camera,
									VertexShaderType forced_vertex_type,
									PixelShaderType forced_pixel_type,
									unsigned object_index, unsigned mesh_index)
{
	// 頂点シェーダー
	SpecificSettingVertexShader(draw, camera, forced_vertex_type, object_index,
								mesh_index);

	// ピクセルシェーダー
	SpecificSettingPixelShader(draw, camera, forced_pixel_type, object_index,
							   mesh_index);
}



//--------------------------------------------------
// -頂点シェーダー初期化関数
//--------------------------------------------------
void ShaderManager::InitVertexShaders()
{
	// 生成
	vertex_shaders_[VertexShaderType::VERTEX_FIXED] = new VertexShaderFixed();
	vertex_shaders_[VertexShaderType::VERTEX_BUMP_MAPPING] = new VertexShaderBumpMapping();

	// 初期化
	for (unsigned i = 0; i < VertexShaderType::VERTEX_MAX; i++)
	{
		vertex_shaders_[i]->Init();
	}
}



//--------------------------------------------------
// -ピクセルシェーダー初期化関数
//--------------------------------------------------
void ShaderManager::InitPixelShaders()
{
	// 生成
	pixel_shaders_[PixelShaderType::PIXEL_FIXED] = new PixelShaderNull();
	pixel_shaders_[PixelShaderType::PIXEL_BUMP_MAPPING] = new PixelShaderBumpMapping();

	// 初期化
	for (unsigned i = 0; i < PixelShaderType::PIXEL_MAX; i++)
	{
		pixel_shaders_[i]->Init();
	}
}



//--------------------------------------------------
// -頂点シェーダー終了関数
//--------------------------------------------------
void ShaderManager::UninitVertexShaders()
{
	// 解放
	for (unsigned i = 0; i < VertexShaderType::VERTEX_MAX; i++)
	{
		SafeRelease::PlusUninit(&vertex_shaders_[i]);
	}
}



//--------------------------------------------------
// -ピクセルシェーダー終了関数
//--------------------------------------------------
void ShaderManager::UninitPixelShaders()
{
	// 解放
	for (unsigned i = 0; i < PixelShaderType::PIXEL_MAX; i++)
	{
		SafeRelease::PlusUninit(&pixel_shaders_[i]);
	}
}



//--------------------------------------------------
// -頂点シェーダー設定関数
//--------------------------------------------------
void ShaderManager::SetVertexShader(DrawBase* draw,
									VertexShaderType forced_vertex_type)
{
	if (forced_vertex_type != VertexShaderType::VERTEX_NONE)
	{
		vertex_shaders_[forced_vertex_type]->SetShader();
		return;
	}

	vertex_shaders_[draw->GetDrawOrderList()->GetVertexShaderType()]->SetShader();
}



//--------------------------------------------------
// -ピクセルシェーダー設定関数
//--------------------------------------------------
void ShaderManager::SetPixelShader(DrawBase* draw, PixelShaderType forced_pixel_type)
{
	// 強制設定があるかどうか
	if (forced_pixel_type != PixelShaderType::PIXEL_NONE)
	{
		pixel_shaders_[forced_pixel_type]->SetShader();
		return;
	}

	pixel_shaders_[draw->GetDrawOrderList()->GetPixelShaderType()]->SetShader();
}



//--------------------------------------------------
// +頂点シェーダー共通設定関数
//--------------------------------------------------
void ShaderManager::CommonSettingVertexShader(DrawBase* draw, Camera* camera,
											  VertexShaderType forced_vertex_type,
											  unsigned object_index)
{
	// 強制設定があるかどうか
	if (forced_vertex_type != VertexShaderType::VERTEX_NONE)
	{
		vertex_shaders_[forced_vertex_type]->CommonSetting(draw, camera, object_index);
		return;
	}

	vertex_shaders_[draw->GetDrawOrderList()->GetVertexShaderType()]
		->CommonSetting(draw, camera, object_index);
}



//--------------------------------------------------
// +ピクセルシェーダー共通設定関数
//--------------------------------------------------
void ShaderManager::CommonSettingPixelShader(DrawBase* draw, Camera* camera,
											 PixelShaderType forced_pixel_type,
											 unsigned object_index)
{
	// 強制設定があるかどうか
	if (forced_pixel_type != PixelShaderType::PIXEL_NONE)
	{
		pixel_shaders_[forced_pixel_type]->CommonSetting(draw, camera, object_index);
		return;
	}

	pixel_shaders_[draw->GetDrawOrderList()->GetPixelShaderType()]
		->CommonSetting(draw, camera, object_index);
}



//--------------------------------------------------
// +頂点シェーダー共通設定関数
//--------------------------------------------------
void ShaderManager::SpecificSettingVertexShader(DrawBase* draw, Camera* camera,
												VertexShaderType forced_vertex_type,
												unsigned object_index,
												unsigned mesh_index)
{
	// 強制設定があるかどうか
	if (forced_vertex_type != VertexShaderType::VERTEX_NONE)
	{
		vertex_shaders_[forced_vertex_type]->SpecificSetting(draw, camera,
															 object_index, mesh_index);
		return;
	}

	vertex_shaders_[draw->GetDrawOrderList()->GetVertexShaderType()]
		->SpecificSetting(draw, camera, object_index, mesh_index);
}



//--------------------------------------------------
// +ピクセルシェーダー共通設定関数
//--------------------------------------------------
void ShaderManager::SpecificSettingPixelShader(DrawBase* draw, Camera* camera,
											   PixelShaderType forced_pixel_type,
											   unsigned object_index,
											   unsigned mesh_index)
{
	// 強制設定があるかどうか
	if (forced_pixel_type != PixelShaderType::PIXEL_NONE)
	{
		pixel_shaders_[forced_pixel_type]->SpecificSetting(draw, camera,
														   object_index, mesh_index);
		return;
	}

	pixel_shaders_[draw->GetDrawOrderList()->GetPixelShaderType()]
		->SpecificSetting(draw, camera, object_index, mesh_index);
}