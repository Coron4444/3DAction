//================================================================================
//!	@file	 VertexShaderFixed.h
//!	@brief	 固定機能頂点シェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_VERTEX_SHADER_FIXED_H_
#define _VERTEX_SHADER_FIXED_H_



//****************************************
// インクルード文
//****************************************
#include "../VertexShaderNull/VertexShaderNull.h"



//****************************************
// クラス宣言
//****************************************
class Camera;
class DrawBase;



//************************************************************														   
//! @brief   固定機能頂点シェーダーClass
//!
//! @details 固定機能の頂点シェーダーClass
//************************************************************
class VertexShaderFixed : public VertexShaderNull
{
//====================
// 変数
//====================
private:
	D3DLIGHT9 directional_light_;	//!< ディレクショナルライト


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

private:
	//----------------------------------------
	//! @brief テクスチャ設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param object_index 描画オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void SetTexture(DrawBase* draw, unsigned object_index, unsigned mesh_index);

	//----------------------------------------
	//! @brief マテリアル設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param object_index 描画オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void SetMaterial(DrawBase* draw, unsigned object_index, unsigned mesh_index);

	//----------------------------------------
	//! @brief 拡散照明更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateDirectionalLignt();
};



#endif
