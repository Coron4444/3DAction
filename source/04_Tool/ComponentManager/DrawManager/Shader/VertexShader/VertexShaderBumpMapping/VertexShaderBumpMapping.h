//================================================================================
//
//    バンプマッピング頂点シェーダークラス
//    Author : Araki Kai                                作成日 : 2018/11/17
//
//================================================================================

#ifndef	_VERTEX_SHADER_BUMP_MAPPING_H_
#define _VERTEX_SHADER_BUMP_MAPPING_H_



//****************************************
// インクルード文
//****************************************
#include "../../ShaderBase/VertexShaderNull.h"



//****************************************
// クラス宣言
//****************************************
class ModelXObject;



/*********************************************************//**
* @brief
* バンプマッピング頂点シェーダークラス
*
* バンプマッピングの頂点シェーダークラス
*************************************************************/
class VertexShaderBumpMapping : public VertexShaderNull
{
//==============================
// 定数
//==============================
private:
	static const char* PATH;
	static const D3DVERTEXELEMENT9 DECLARATION[];


//==============================
// 非静的メンバ変数
//==============================
private:
	// 計算用
	D3DXMATRIX math_matrix_;

	// 頂点宣言オブジェクト
	IDirect3DVertexDeclaration9* declaration_object_;

//==============================
// 静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 頂点宣言用メッシュ更新関数
	* @param
	* model_x : Xモデルオブジェクト
	*/
	static void UpdateMeshDeclaration(ModelXObject* model_x);


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
