//================================================================================
//
//    固定機能ピクセルシェーダークラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_FIXED_PIXEL_SHADER_H_
#define _FIXED_PIXEL_SHADER_H_



//****************************************
// インクルード文
//****************************************
#include <Renderer/Renderer.h>



//****************************************
// クラス宣言
//****************************************
class Camera;
class DrawBase;



/*********************************************************//**
* @brief
* 固定機能ピクセルシェーダークラス
*
* 固定機能のピクセルシェーダークラス
*************************************************************/
class FixedPixelShader
{
//==============================
// 非静的メンバ変数
//==============================
private:
	LPDIRECT3DDEVICE9 device_;			//!< デバイス


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
	* シェーダー設定関数
	*/
	void SetShader();

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
