//================================================================================
//
//    空白頂点シェーダークラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_VERTEX_SHADER_NULL_H_
#define _VERTEX_SHADER_NULL_H_



//****************************************
// インクルード文
//****************************************
#include "VertexShaderBase.h"



/*********************************************************//**
* @brief
* 空白頂点シェーダークラス
*
* 空白頂点シェーダークラス
*************************************************************/
class VertexShaderNull : public VertexShaderBase
{
//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	virtual void Init()	
	{
		ShaderBase::InitDevice();
	}

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit() {}

	/**
	* @brief
	* 共通設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* object_index : 描画オブジェクトインデックス
	*/
	virtual void CommonSetting(DrawBase* draw, Camera* camera,
							   unsigned object_index) {}

	/**
	* @brief
	* 固有設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* object_index : 描画オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	virtual void SpecificSetting(DrawBase* draw, Camera* camera,
								 unsigned object_index, unsigned mesh_index) {}
};

#endif
