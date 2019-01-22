//================================================================================
//!	@file	 ShaderBase.cpp
//!	@brief	 シェーダーBaseClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "ShaderBase.h"

#include <Component/Draw/DrawBase/DrawBase.h>
#include <ComponentManager/DrawManager/Camera/Camera.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
LPD3DXCONSTANTTABLE ShaderBase::getpConstantTable()
{
	return constant_table_; 
}

LPDIRECT3DDEVICE9 ShaderBase::getpDevice()
{
	return device_; 
}



//****************************************
// 関数定義
//****************************************
ShaderBase::~ShaderBase()
{

}



bool ShaderBase::ShaderCompile(const char* file_name, const char* entry_function,
							   const char* version, LPD3DXBUFFER* compiled_code)
{
	LPD3DXBUFFER compil_error = nullptr;
	HRESULT hr = D3DXCompileShaderFromFile(file_name,			// ファイル名
										   nullptr,				// プリプロセッサ定義へのポインタ
										   nullptr,				// ID3DXInclude(#include疑似命令)
										   entry_function,		// エントリ関数名
										   version,				// シェーダーバージョン
										   0,					// コンパイルオプション
										   compiled_code,		// コンパイル済みコード
										   &compil_error,		// エラー情報
										   &constant_table_);	// コンスタントテーブル
	// 成功したか
	if (SUCCEEDED(hr)) return true;

	// エラーメッセージ
	if (compil_error)
	{
		// コンパイルエラーあり
		MessageBox(NULL, (LPSTR)compil_error->GetBufferPointer(), "Error", MB_OK);
	}
	else
	{
		// その他のエラー
		MessageBox(NULL, "シェーダーファイルが読み込めません", "Error", MB_OK);
	}
	return false;
}



void ShaderBase::InitDevice()
{
	// デバイスの取得
	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(VertexShaderBase.cpp)", "Error", MB_OK);
		return;
	}
}