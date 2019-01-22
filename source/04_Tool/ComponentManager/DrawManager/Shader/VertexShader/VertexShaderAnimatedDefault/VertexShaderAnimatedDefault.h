//================================================================================
//!	@file	 VertexShaderAnimatedDefault.h
//!	@brief	 アニメーション付きデフォルト頂点シェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_VERTEX_SHADER_ANIMATED_DEFAULT_H_
#define _VERTEX_SHADER_ANIMATED_DEFAULT_H_



//****************************************
// インクルード文
//****************************************
#include "../VertexShaderNull/VertexShaderNull.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   アニメーション付きデフォルト頂点シェーダーClass
//!
//! @details アニメーション付きデフォルトの頂点シェーダーClass
//************************************************************
class VertexShaderAnimatedDefault : public VertexShaderNull
{
//====================
// 定数
//====================
private:
	static const D3DVERTEXELEMENT9 VERTEX_DECLARATION[];	//!< 頂点宣言配列
	static const char* PATH;			//!< ファイルパス
	static const int MAX_BONE_NUM = 55;	//!< 最大ボーン数


//====================
// 変数
//====================
private:
	IDirect3DVertexDeclaration9* vertex_declaration_ = nullptr;		//!< 頂点宣言
	MATRIX bone_matrix_[MAX_BONE_NUM];								//!< ボーン行列


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
