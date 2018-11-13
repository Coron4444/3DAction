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
#include "../Shader/VertexShader/FixedVertexShader/FixedVertexShader.h"
#include "../Shader/PixelShader/FixedPixelShader/FixedPixelShader.h"
#include <Component/DrawBase/DrawBase.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>

#include <Renderer/Renderer.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void ShaderManager::Init()
{
	fixed_vertex_shader_ = new FixedVertexShader();
	fixed_vertex_shader_->Init();
	fixed_pixel_shader_ = new FixedPixelShader();
	fixed_pixel_shader_->Init();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void ShaderManager::Uninit()
{
	SafeRelease::PlusUninit(&fixed_vertex_shader_);
	SafeRelease::PlusUninit(&fixed_pixel_shader_);
}



//--------------------------------------------------
// +シェーダー設定関数
//--------------------------------------------------
void ShaderManager::SetShader(DrawBase* draw, VertexShaderType forced_vertex_type,
							  PixelShaderType forced_pixel_type)
{
	forced_vertex_type = forced_vertex_type;
	forced_pixel_type = forced_pixel_type;

	// 頂点シェーダー
	switch (draw->GetDrawOrderList()->GetVertexShaderType())
	{
		case VertexShaderType::VERTEX_FIXED:
		{
			fixed_vertex_shader_->SetShader();
			break;
		}
	}

	// ピクセルシェーダー
	switch (draw->GetDrawOrderList()->GetPixelShaderType())
	{
		case PixelShaderType::PIXEL_FIXED:
		{
			fixed_pixel_shader_->SetShader();
			break;
		}
	}
}



//--------------------------------------------------
// +共通設定関数
//--------------------------------------------------
void ShaderManager::CommonSetting(DrawBase* draw, Camera* camera, 
								  VertexShaderType forced_vertex_type,
								  PixelShaderType forced_pixel_type, unsigned object_index)
{
	forced_vertex_type = forced_vertex_type;
	forced_pixel_type = forced_pixel_type;

	// 頂点シェーダー
	switch (draw->GetDrawOrderList()->GetVertexShaderType())
	{
		case VertexShaderType::VERTEX_FIXED:
		{
			fixed_vertex_shader_->CommonSetting(draw, camera, object_index);
			break;
		}
	}

	// ピクセルシェーダー
	switch (draw->GetDrawOrderList()->GetPixelShaderType())
	{
		case PixelShaderType::PIXEL_FIXED:
		{
			fixed_pixel_shader_->CommonSetting(draw, camera, object_index);
			break;
		}
	}
}



//--------------------------------------------------
// +共通設定関数
//--------------------------------------------------
void ShaderManager::SpecificSetting(DrawBase* draw, Camera* camera, 
									VertexShaderType forced_vertex_type,
									PixelShaderType forced_pixel_type,
									unsigned object_index, unsigned mesh_index)
{
	forced_vertex_type = forced_vertex_type;
	forced_pixel_type = forced_pixel_type;

	// 頂点シェーダー
	switch (draw->GetDrawOrderList()->GetVertexShaderType())
	{
		case VertexShaderType::VERTEX_FIXED:
		{
			fixed_vertex_shader_->SpecificSetting(draw, camera, object_index, mesh_index);
				break;
		}
	}

	// ピクセルシェーダー
	switch (draw->GetDrawOrderList()->GetPixelShaderType())
	{
		case PixelShaderType::PIXEL_FIXED:
		{
			fixed_pixel_shader_->SpecificSetting(draw, camera, object_index, mesh_index);
			break;
		}
	}
}