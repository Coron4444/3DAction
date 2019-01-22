//================================================================================
//!	@file	 VertexShaderBase.h
//!	@brief	 頂点シェーダーBaseClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_VERTEX_SHADER_BASE_H_
#define _VERTEX_SHADER_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "../../ShaderBase/ShaderBase.h"



//************************************************************														   
//! @brief   頂点シェーダーBassClass
//!
//! @details 頂点シェーダーのBassClass
//************************************************************
class VertexShaderBase : public ShaderBase
{
//====================
// 変数
//====================
private:
	LPDIRECT3DVERTEXSHADER9 vertex_shader_ = nullptr;	//!< 頂点シェーダー


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 頂点シェーダー取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3DVERTEXSHADER9 頂点シェーダー
	//----------------------------------------
	LPDIRECT3DVERTEXSHADER9 getpVertexShader();


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
	//! @brief 頂点シェーダーコンパイル関数
	//! @details
	//! @param *file_name      ファイル名
	//! @param *entry_function エントリ関数名
	//! @param *version        シェーダーバージョン
	//! @retval bool コンパイル成功ならtrue
	//----------------------------------------
	bool VertexShaderCompile(const char* file_name,
							 const char* entry_function,
							 const char* version);

	//----------------------------------------
	//! @brief 頂点シェーダー解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseVertexShader();
};

#endif
