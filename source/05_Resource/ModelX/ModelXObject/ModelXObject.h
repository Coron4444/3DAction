//================================================================================
//!	@file	 ModelXObject.h
//!	@brief	 XモデルオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_MODEL_X_OBJECT_H_
#define _MODEL_X_OBJECT_H_



//****************************************
// インクルード文
//****************************************
#include <string>
#include <vector>

#include <Renderer\Renderer.h>
#include <Vector3D.h>



//****************************************
// クラス宣言
//****************************************
class TextureObject;



//************************************************************														   
//! @brief   XモデルオブジェクトClass
//!
//! @details XモデルのオブジェクトClass
//************************************************************
class ModelXObject
{
//====================
// 変数
//====================
private:
	LPD3DXMESH mesh_;										//!< メッシュ
	DWORD mesh_num_;										//!< メッシュ数
	std::vector<D3DMATERIAL9> material_;					//!< マテリアル
	std::vector<TextureObject*> diffuse_texture_object_;	//!< ディヒューズテクスチャオブジェクト
	int reference_counter_ = 0;								//!< 参照カウンタ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief メッシュ取得関数
	//! @details
	//! @param void なし 
	//! @retval LPD3DXMESH メッシュ
	//----------------------------------------
	LPD3DXMESH getpMesh() { return mesh_; }

	//----------------------------------------
	//! @brief メッシュ数取得関数
	//! @details
	//! @param void なし 
	//! @retval unsigned メッシュ数
	//----------------------------------------
	unsigned getMeshNum() { return material_num_; }

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param index インデックス 
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned index) { return &material_[index]; }
	
	//----------------------------------------
	//! @brief マテリアル色設定関数
	//! @details
	//! @param index インデックス
	//! @param color 色
	//! @retval void なし
	//----------------------------------------
	void setMaterialColor(unsigned index, XColor4 color);

	//----------------------------------------
	//! @brief ディヒューズテクスチャオブジェクト取得関数
	//! @details
	//! @param index インデックス
	//! @retval void なし
	//----------------------------------------
	TextureObject* getpDiffuseTextureObject(unsigned index) { return texture_object_array_.at(index); }

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *file_path ファイルパス
	//! @retval void なし
	//----------------------------------------
	void Init(std::string* file_path);

	//----------------------------------------
	//! @brief 解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Release();

	//----------------------------------------
	//! @brief 参照カウンタ追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddReferenceCounter();

	//----------------------------------------
	//! @brief 参照カウンタリセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetReferenceCounter();

	//----------------------------------------
	//! @brief 頂点情報変更関数
	//! @details
	//! @param declaration 頂点宣言
	//! @retval void なし
	//----------------------------------------
	void UpdateMeshDeclaration(D3DVERTEXELEMENT9* declaration);


private:
	//----------------------------------------
	//! @brief メッシュ生成関数
	//! @details
	//! @param *file_path       ファイルパス
	//! @param *material_buffer マテリアルバッファ
	//! @retval void なし
	//----------------------------------------
	void CreateMesh(std::string* file_path, LPD3DXBUFFER* material_buffer);

	//----------------------------------------
	//! @brief マテリアル生成関数
	//! @details
	//! @param *file_path       ファイルパス
	//! @param *material_buffer マテリアルバッファ
	//! @retval void なし
	//----------------------------------------
	void CreateMaterial(std::string* file_path, LPD3DXBUFFER* material_buffer);

	//----------------------------------------
	//! @brief ファイルパス&キー名生成関数
	//! @details
	//! @param *file_path ファイルパス
	//! @param *key_name  キー名
	//! @retval void なし
	//----------------------------------------
	void CreateFilePathAndKeyName(std::string* file_path,
								  std::string* key_name);
};



#endif