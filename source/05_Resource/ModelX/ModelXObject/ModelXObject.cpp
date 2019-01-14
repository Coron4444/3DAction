//================================================================================
//!	@file	 ModelXObject.cpp
//!	@brief	 XモデルオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "ModelXObject.h"
#include "../ModelXManager/ModelXManager.h"

#include <SafeRelease/SafeRelease.h>
#include <Texture/TextureManager/TextureManager.h>




//****************************************
// プロパティ定義
//****************************************
LPD3DXMESH ModelXObject::getpMesh()
{
	return mesh_;
}



unsigned ModelXObject::getMeshNum()
{
	return mesh_num_;
}



D3DMATERIAL9* ModelXObject::getpMaterial(unsigned index)
{
	return &material_[index];
}



void ModelXObject::setMaterialColor(unsigned index, XColor4 color)
{
	material_[index].Diffuse.r = color.r;
	material_[index].Diffuse.g = color.g;
	material_[index].Diffuse.b = color.b;
	material_[index].Diffuse.a = color.a;
}



TextureObject* ModelXObject::getpDiffuseTextureObject(unsigned index)
{
	return diffuse_texture_object_[index];
}



//****************************************
// 関数定義
//****************************************
void ModelXObject::Init(std::string* file_path, const std::string* map_key_name)
{
	// マテリアルバッファ
	LPD3DXBUFFER material_buffer = nullptr;

	// メッシュ生成
	CreateMesh(file_path, &material_buffer);

	// マテリアル生成
	CreateMaterial(file_path, &material_buffer);

	// キー名保存
	map_key_name_ = *map_key_name;
}



void ModelXObject::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	SafeRelease::PlusRelease(&mesh_);

	for (auto& contents : diffuse_texture_object_)
	{
		SafeRelease::PlusRelease(&contents);
	}

	ModelXManager::getpInstance()->ReleaseFromTheMap(&map_key_name_);
	delete this;
}



void ModelXObject::ForcedRelease()
{
	reference_counter_ = 0;
	Release();
}



void ModelXObject::AddReferenceCounter()
{
	reference_counter_++;
}



void ModelXObject::UpdateMeshDeclaration(const D3DVERTEXELEMENT9* declaration)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(ModelXObject.cpp)", "Error", MB_OK);
		return;
	}

	// 頂点情報の変更
	LPD3DXMESH temp_mesh;
	mesh_->CloneMesh(mesh_->GetOptions(),
					 declaration,
					 device,
					 &temp_mesh);

	SafeRelease::PlusRelease(&mesh_);

	mesh_ = temp_mesh;
}



void ModelXObject::CreateMesh(std::string* file_path, LPD3DXBUFFER* material_buffer)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(ModelXObject.cpp)", "Error", MB_OK);
		return;
	}

	HRESULT hr = D3DXLoadMeshFromX(file_path->c_str(),	// ファイル名
								   D3DXMESH_SYSTEMMEM,	// 一度CPUで最適化したものをVRAMに渡す
								   device,				// デバイス
								   nullptr,				// 隣接性情報
								   material_buffer,		// マテリアル情報
								   NULL,				// エフェクトの初期化
								   &mesh_num_,			// メッシュ数
								   &mesh_);				// メッシュ
	if (FAILED(hr))
	{
		MessageBox(nullptr, "メッシュの生成に失敗(TextureObject.cpp)", "Error", MB_OK);
		return;
	}
}



void ModelXObject::CreateMaterial(std::string* file_path, LPD3DXBUFFER* material_buffer)
{
	// マテリアルサイズ変更
	material_.resize(mesh_num_);

	// マテリアルの情報をのポインタ取得
	LPD3DXMATERIAL temp_material = (LPD3DXMATERIAL)(*material_buffer)->GetBufferPointer();

	// マテリアルで分割したパーツたち
	for (DWORD i = 0; i < mesh_num_; i++)
	{
		ZeroMemory(&material_[i], sizeof(D3DMATERIAL9));

		// デヒューズカラーの設定
		material_[i].Diffuse.r = temp_material[i].MatD3D.Diffuse.r;
		material_[i].Diffuse.g = temp_material[i].MatD3D.Diffuse.g;
		material_[i].Diffuse.b = temp_material[i].MatD3D.Diffuse.b;
		material_[i].Diffuse.a = temp_material[i].MatD3D.Diffuse.a;

		// アンビエントカラーの設定
		material_[i].Ambient.r = temp_material[i].MatD3D.Ambient.r;
		material_[i].Ambient.g = temp_material[i].MatD3D.Ambient.g;
		material_[i].Ambient.b = temp_material[i].MatD3D.Ambient.b;
		material_[i].Ambient.a = temp_material[i].MatD3D.Ambient.a;

		// テクスチャの読み込み
		if (temp_material[i].pTextureFilename == NULL) continue;
		std::string key_name = temp_material[i].pTextureFilename;
		std::string path = *file_path;
		CreateFilePathAndKeyName(&path, &key_name);

		TextureObject* texture_object = TextureManager::getpInstance()->getpObject(&key_name, &path);
		diffuse_texture_object_.push_back(texture_object);
	}

	// マテリアルバッファの解放
	SafeRelease::PlusRelease(material_buffer);
}



void ModelXObject::CreateFilePathAndKeyName(std::string* file_path,
											std::string* key_name)
{
	// ファイルパスからフォルダ名を/付きで取得
	auto slash_index = file_path->rfind("/");
	auto slash_index2 = file_path->rfind("/", slash_index - 1);
	unsigned temp_num = (unsigned)(slash_index - slash_index2);
	std::string temp_strign = file_path->substr(slash_index2 + 1, temp_num);

	// キーネームの作成
	*key_name = temp_strign + *key_name;

	// ファイルパスの作成
	*file_path = file_path->substr(0, slash_index2 + 1);
}