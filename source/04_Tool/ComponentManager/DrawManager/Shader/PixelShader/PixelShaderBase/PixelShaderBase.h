//================================================================================
//!	@file	 PixelShaderBase.h
//!	@brief	 ピクセルシェーダーBassClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_PIXEL_SHADER_BASE_H_
#define _PIXEL_SHADER_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "../../ShaderBase/ShaderBase.h"



//************************************************************														   
//! @brief   ピクセルシェーダーBassClass
//!
//! @details ピクセルシェーダーのBassClass
//************************************************************
class PixelShaderBase : public ShaderBase
{
//====================
// 変数
//====================
private:
	LPDIRECT3DPIXELSHADER9 pixel_shader_ = nullptr;		//!< ピクセルシェーダー


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ピクセルシェーダー取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3DPIXELSHADER9 ピクセルシェーダー
	//----------------------------------------
	LPDIRECT3DPIXELSHADER9 getpPixelShader();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デバイスにシェーダー設定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ShaderSetToDevice() override;

	//----------------------------------------
	//! @brief ピクセルシェーダーコンパイル関数
	//! @details
	//! @param *file_name      ファイル名
	//! @param *entry_function エントリ関数名
	//! @param *version        シェーダーバージョン
	//! @retval bool コンパイル成功ならtrue
	//----------------------------------------
	bool PixelShaderCompile(const char* file_name,
							const char* entry_function,
							const char* version);

	//----------------------------------------
	//! @brief ピクセルシェーダー解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleasePixelShader();
};

#endif
