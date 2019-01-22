//================================================================================
//!	@file	 PixelShaderNull.h
//!	@brief	 空白ピクセルシェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_PIXEL_SHADER_NULL_H_
#define _PIXEL_SHADER_NULL_H_



//****************************************
// インクルード文
//****************************************
#include "../PixelShaderBase/PixelShaderBase.h"



//************************************************************														   
//! @brief   空白ピクセルシェーダーClass
//!
//! @details 空白ピクセルシェーダーのClass
//************************************************************
class PixelShaderNull : public PixelShaderBase
{
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
	virtual void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit();

	//----------------------------------------
	//! @brief オブジェクト設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param *camera      カメラ
	//! @param object_index 描画オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void ObjectSetting(DrawBase* draw, Camera* camera, unsigned object_index);

	//----------------------------------------
	//! @brief メッシュ設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param *camera      カメラ
	//! @param object_index 描画オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void MeshSetting(DrawBase* draw, Camera* camera,
							 unsigned object_index, unsigned mesh_index);
};

#endif
