//================================================================================
//
//    バンプマッピングピクセルシェーダークラス
//    Author : Araki Kai                                作成日 : 2018/11/17
//
//================================================================================

#ifndef	_PIXEL_SHADER_BUMP_MAPPING_H_
#define _PIXEL_SHADER_BUMP_MAPPING_H_



//****************************************
// インクルード文
//****************************************
#include "../../ShaderBase/PixelShaderNull.h"



/*********************************************************//**
* @brief
* バンプマッピングピクセルシェーダークラス
*
* バンプマッピングのピクセルシェーダークラス
*************************************************************/
class PixelShaderBumpMapping : public PixelShaderNull
{
//==============================
// 定数
//==============================
private:
	static const char* PATH;


//==============================
// 非静的メンバ変数
//==============================
private:
	// 計算用
	D3DXMATRIX math_matrix_;



//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init();

	/**
	* @brief
	* 終了関数
	*/
	void Uninit();

	/**
	* @brief
	* 共通設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* object_index : 描画オブジェクトインデックス
	*/
	void CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index);

	/**
	* @brief
	* 固有設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* object_index : 描画オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	void SpecificSetting(DrawBase* draw, Camera* camera, 
						 unsigned object_index, unsigned mesh_index);
};



#endif
