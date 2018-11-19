//================================================================================
//
//    ピクセルシェーダー基底クラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_PIXEL_SHADER_BASE_H_
#define _PIXEL_SHADER_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "ShaderBase.h"



/*********************************************************//**
* @brief
* ピクセルシェーダー基底クラス
*
* ピクセルシェーダー基底クラス
*************************************************************/
class PixelShaderBase : public ShaderBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	LPDIRECT3DPIXELSHADER9 pixel_shader_ = nullptr;		//!< ピクセルシェーダー


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* シェーダー設定関数
	*/
	void SetShader() override
	{
		GetDevice()->SetPixelShader(pixel_shader_);
	}

	/**
	* @brief
	* ピクセルシェーダーコンパイル関数
	* @param
	* file_name : ファイル名
	* entry_function : エントリ関数名
	* version : シェーダーバージョン
	* @return コンパイル成功ならtrue
	*/
	bool PixelShaderCompile(const char* file_name, const char* entry_function,
							 const char* version)
	{
		LPD3DXBUFFER compiled_code;
		bool is_compile = ShaderBase::ShaderCompile(file_name, entry_function,
													version, &compiled_code);
		if (!is_compile) return false;

		HRESULT hr = ShaderBase::GetDevice()
			->CreatePixelShader((DWORD*)compiled_code->GetBufferPointer(),
								 &pixel_shader_);

		// 成功したか
		if (SUCCEEDED(hr)) return true;

		// エラーメッセージ
		MessageBox(nullptr, "ピクセルシェーダー作成失敗", "Error", MB_OK);
		return false;
	}

	/**
	* @brief
	* ピクセルシェーダー解放関数
	*/
	void ReleasePixelShader()
	{
		SafeRelease::PlusRelease(&pixel_shader_);
	}

	// プロパティ
	LPDIRECT3DPIXELSHADER9 GetPixelShader() { return pixel_shader_; }
};

#endif
