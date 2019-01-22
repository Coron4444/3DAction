//================================================================================
//!	@file	 PixelShaderBumpMapping.h
//!	@brief	 バンプマッピングピクセルシェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_PIXEL_SHADER_BUMP_MAPPING_H_
#define _PIXEL_SHADER_BUMP_MAPPING_H_



//****************************************
// インクルード文
//****************************************
#include "../PixelShaderNull/PixelShaderNull.h"



//************************************************************														   
//! @brief   バンプマッピングピクセルシェーダーClass
//!
//! @details バンプマッピングピクセルシェーダーのClass
//************************************************************
class PixelShaderBumpMapping : public PixelShaderNull
{
//====================
// 定数
//====================
private:
	static const char* PATH;	//!< ファイルパス


//====================
// 変数
//====================
private:
	D3DXMATRIX math_matrix_;		//!< 計算用行列


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief オブジェクト設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param *camera      カメラ
	//! @param object_index 描画オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	void ObjectSetting(DrawBase* draw, Camera* camera, unsigned object_index);

	//----------------------------------------
	//! @brief メッシュ設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param *camera      カメラ
	//! @param object_index 描画オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void MeshSetting(DrawBase* draw, Camera* camera,
					 unsigned object_index, unsigned mesh_index);
};



#endif
