//================================================================================
//
//    固定機能頂点シェーダークラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_FIXED_VERTEX_SHADER_H_
#define _FIXED_VERTEX_SHADER_H_



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
* 固定機能頂点シェーダークラス
*
* 固定機能の頂点シェーダークラス
*************************************************************/
class FixedVertexShader
{
//==============================
// 非静的メンバ変数
//==============================
private:
	LPDIRECT3DDEVICE9 device_;			//!< デバイス
	D3DLIGHT9 directional_light_;		//!< ディレクショナルライト


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

private :
	// テクスチャ設定
	void SetTexture(DrawBase* draw, unsigned object_index, unsigned mesh_index);

	// マテリアル設定
	void SetMaterial(DrawBase* draw, unsigned object_index, unsigned mesh_index);

	// 拡散照明更新
	void UpdateDirectionalLignt();
};



#endif
