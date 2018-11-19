//================================================================================
//
//    頂点シェーダー基底クラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_VERTEX_SHADER_BASE_H_
#define _VERTEX_SHADER_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "ShaderBase.h"



/*********************************************************//**
* @brief
* 頂点シェーダー基底クラス
*
* 頂点シェーダー基底クラス
*************************************************************/
class VertexShaderBase : public ShaderBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	LPDIRECT3DVERTEXSHADER9 vertex_shader_ = nullptr;	//!< 頂点シェーダー


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
		GetDevice()->SetVertexShader(vertex_shader_);
	}

	/**
	* @brief
	* 頂点シェーダーコンパイル関数
	* @param
	* file_name : ファイル名
	* entry_function : エントリ関数名
	* version : シェーダーバージョン
	* @return コンパイル成功ならtrue
	*/
	bool VertexShaderCompile(const char* file_name, const char* entry_function,
							 const char* version)
	{
		LPD3DXBUFFER compiled_code;
		bool is_compile = ShaderBase::ShaderCompile(file_name, entry_function,
													version, &compiled_code);
		if (!is_compile) return false;

		HRESULT hr = ShaderBase::GetDevice()
			->CreateVertexShader((DWORD*)compiled_code->GetBufferPointer(),
								 &vertex_shader_);

		// 成功したか
		if (SUCCEEDED(hr)) return true;

		// エラーメッセージ
		MessageBox(nullptr, "頂点シェーダー作成失敗", "Error", MB_OK);
		return false;
	}

	/**
	* @brief
	* 頂点シェーダー解放関数
	*/
	void ReleaseVertexShader()
	{
		SafeRelease::PlusRelease(&vertex_shader_);
	}

	// プロパティ
	LPDIRECT3DVERTEXSHADER9 GetVertexShader() { return vertex_shader_; }
};

#endif
