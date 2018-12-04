//================================================================================
//
//    Xモデルクラス
//    Author : Araki Kai                                作成日 : 2017/12/18
//
//================================================================================

#ifndef	_MODEL_X_OBJECT_H_
#define _MODEL_X_OBJECT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>
#include <vector>

#include <Vector3D.h>
#include <Texture\TextureManager\TextureManager.h>
#include <Renderer\Renderer.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class ModelXObject
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	ModelXObject(const std::string* file_path, bool is_share_data);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	virtual ~ModelXObject();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メッシュ
	LPD3DXMESH GetMesh(){return mesh_;}
	unsigned getMeshNum(){return material_num_;}	// Xモデルはマテリアル数がメッシュ数の代わり
	void UpdateMeshDeclaration(const D3DVERTEXELEMENT9* DECLARATION);
	
	// マテリアル
	D3DMATERIAL9* GetMaterial(unsigned index){return &material_[index];}
	void SetMaterialColor(unsigned index, XColor4 color);

	// テクスチャ
	const TextureObject* GetDecaleTextureName(unsigned index){return texture_object_array_.at(index);}


//------------------------------------------------------------
private :
	// 非公開メンバ関数
	void InputModelX   (const std::string* file_path, LPD3DXBUFFER* material_buffer);
	void InputMaterial (const std::string* file_path, LPD3DXBUFFER* material_buffer, bool is_share_data);
	void MakeTextureFilePathAndKeyName(std::string* texture_key_name, std::string* texture_file_path);
	

//------------------------------------------------------------
private :
	// メッシュ
	LPD3DXMESH	 mesh_;
	DWORD		 material_num_;
	
	// マテリアル
	std::vector<D3DMATERIAL9> material_;

	// テクスチャ
	std::vector<TextureObject*> texture_object_array_;
};



#endif