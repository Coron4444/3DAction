//================================================================================
//!	@file	 VertexShaderBase.cpp
//!	@brief	 頂点シェーダーBaseClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "VertexShaderBase.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
LPDIRECT3DVERTEXSHADER9 VertexShaderBase::getpVertexShader()
{
	return vertex_shader_;
}



//****************************************
// 関数定義
//****************************************
void VertexShaderBase::ShaderSetToDevice()
{
	getpDevice()->SetVertexShader(vertex_shader_);
}



bool VertexShaderBase::VertexShaderCompile(const char* file_name,
										   const char* entry_function,
										   const char* version)
{
	LPD3DXBUFFER compiled_code;
	bool is_compile = ShaderBase::ShaderCompile(file_name, entry_function,
												version, &compiled_code);
	if (!is_compile) return false;

	HRESULT hr = getpDevice()
		->CreateVertexShader((DWORD*)compiled_code->GetBufferPointer(),
							 &vertex_shader_);

	// 成功したか
	if (SUCCEEDED(hr)) return true;

	// エラーメッセージ
	MessageBox(nullptr, "頂点シェーダー作成失敗", "Error", MB_OK);
	return false;
}



void VertexShaderBase::ReleaseVertexShader()
{
	SafeRelease::PlusRelease(&vertex_shader_);
}