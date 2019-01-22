//================================================================================
//!	@file	 VertexShaderBumpMapping.h
//!	@brief	 バンプマッピング頂点シェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_VERTEX_SHADER_BUMP_MAPPING_H_
#define _VERTEX_SHADER_BUMP_MAPPING_H_



//****************************************
// インクルード文
//****************************************
#include "../VertexShaderNull/VertexShaderNull.h"

#include <Vector3D.h>



//****************************************
// クラス宣言
//****************************************
class ModelXObject;



//************************************************************														   
//! @brief   バンプマッピング頂点シェーダーClass
//!
//! @details バンプマッピングの頂点シェーダーClass
//************************************************************
class VertexShaderBumpMapping : public VertexShaderNull
{
//====================
// 定数
//====================
private:
	static const D3DVERTEXELEMENT9 DECLARATION[];	//!< 頂点宣言
	static const char* PATH;						//!< ファイルパス


//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief 頂点宣言用メッシュ更新関数
	//! @details
	//! @param model_x Xモデルオブジェクト
	//! @retval void なし
	//----------------------------------------
	static void UpdateMeshDeclaration(ModelXObject* model_x);


//====================
// 変数
//====================
private:
	MATRIX math_matrix_;										//!< 計算用行列
	IDirect3DVertexDeclaration9* declaration_object_ = nullptr;	//!< 頂点宣言


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
