//================================================================================
//
//    シェーダー基底クラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_SHADER_BASE_H_
#define _SHADER_BASE_H_



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
* シェーダー基底クラス
*
* シェーダー基底クラス
*************************************************************/
class ShaderBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	LPDIRECT3DDEVICE9 device_ = nullptr;			//!< デバイス
	LPD3DXCONSTANTTABLE	constant_table_ = nullptr;	//!< 定数テーブル


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	virtual void Init() = 0;

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit() = 0;

	/**
	* @brief
	* シェーダー設定関数
	*/
	virtual void SetShader() = 0;

	/**
	* @brief
	* 共通設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* object_index : 描画オブジェクトインデックス
	*/
	virtual void CommonSetting(DrawBase* draw, Camera* camera,
							   unsigned object_index) = 0;

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
								 unsigned object_index, unsigned mesh_index) = 0;

	// プロパティ
	LPDIRECT3DDEVICE9* GetDevicePointer() { return &device_; }
	LPDIRECT3DDEVICE9 GetDevice() { return device_; }
	LPD3DXCONSTANTTABLE GetConstantTable() { return constant_table_; }
};

#endif
