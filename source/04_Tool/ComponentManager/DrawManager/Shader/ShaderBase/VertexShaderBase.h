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

	// プロパティ
	LPDIRECT3DVERTEXSHADER9 GetVertexShader() { return vertex_shader_; }
};

#endif
