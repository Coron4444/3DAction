//================================================================================
//
//    Xモデルオブジェクトクラス
//    Author : Araki Kai                                作成日 : 2017/12/18
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "ModelXObject.h"

#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトコンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject::ModelXObject(const std::string* file_path, bool is_share_data)
{
	// マテリアルバッファ
	LPD3DXBUFFER material_buffer = nullptr;
	
	// XModelの読み込み
	InputModelX(file_path, &material_buffer);

	// マテリアル情報の読み込み
	InputMaterial(file_path, &material_buffer, is_share_data);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject::~ModelXObject()
{
	SafeRelease::PlusRelease(&mesh_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ マテリアルの色変更関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXObject::SetMaterialColor(unsigned index, XColor4 color)
{
	material_[index].Diffuse.r = color.r;
	material_[index].Diffuse.g = color.g;
	material_[index].Diffuse.b = color.b;
	material_[index].Diffuse.a = color.a;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 頂点情報変更関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXObject::UpdateMeshDeclaration(const D3DVERTEXELEMENT9* DECLARATION)
{
	LPD3DXMESH temp_mesh;

	// デバイスの取得
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(ModelXObject.cpp)", "Error", MB_OK);
		return;
	}

	mesh_->CloneMesh(mesh_->GetOptions(),
		             DECLARATION,
					 device,
		             &temp_mesh);

	SafeRelease::PlusRelease(&mesh_);

	mesh_ = temp_mesh;
}



//--------------------------------------------------------------------------------
//
// [ XModel読み込み関数 ]
//
//--------------------------------------------------------------------------------

void ModelXObject::InputModelX(const std::string* file_path, LPD3DXBUFFER* material_buffer)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(ModelXObject.cpp)", "Error", MB_OK);
		return;
	}

	HRESULT hr = D3DXLoadMeshFromX(file_path->c_str(),		// ファイル名
						           D3DXMESH_SYSTEMMEM,		// 一度CPUで最適化したものをVRAMに渡す
						           device,					// デバイス
						           nullptr,					// 隣接性情報
						           material_buffer,			// マテリアル情報
						           NULL,					// エフェクトの初期化
						           &material_num_,			// マテリアル数
						           &mesh_);					// メッシュ

#ifdef _DEBUG
	assert(!FAILED(hr) && "ModelXの読み込みに失敗(ModelXObject.cpp)");
#else
	hr = hr;
#endif
}



//--------------------------------------------------------------------------------
//
// [ XModelのMaterial情報読み込み関数 ]
//
//--------------------------------------------------------------------------------

void ModelXObject::InputMaterial(const std::string* file_path, LPD3DXBUFFER* material_buffer, bool is_share_data)
{
	// マテリアルサイズ変更
	material_.resize(material_num_);

	// マテリアルの情報をのポインタ取得
	LPD3DXMATERIAL temp_material = (LPD3DXMATERIAL)(*material_buffer)->GetBufferPointer();

	// マテリアルで分割したパーツたち
	for (DWORD i = 0; i < material_num_; i++)
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
		std::string texture_key_name  = temp_material[i].pTextureFilename;
		std::string texture_file_path = *file_path;
		MakeTextureFilePathAndKeyName(&texture_key_name, &texture_file_path);
		
		TextureObject* texture_object = nullptr;

		if (is_share_data)
		{
			texture_object = TextureManager::AddShareData(&texture_key_name, &texture_file_path);
		}
		else
		{
			texture_object = TextureManager::AddUniqueData(&texture_key_name, &texture_file_path);
		}

		texture_object_array_.push_back(texture_object);
	}

	// マテリアルバッファの解放
	SafeRelease::PlusRelease(material_buffer);
}



//--------------------------------------------------------------------------------
//
// [ テクスチャ用のファイルパス&キーネームの作成関数 ]
//
//--------------------------------------------------------------------------------

void ModelXObject::MakeTextureFilePathAndKeyName(std::string* texture_key_name, std::string* texture_file_path)
{
	// ファイルパスからフォルダ名を/付きで取得
	auto slash_index = texture_file_path->rfind("/");
	auto slash_index2 = texture_file_path->rfind("/", slash_index - 1);
	unsigned temp_num = (unsigned)(slash_index - slash_index2);
	std::string temp_strign = texture_file_path->substr(slash_index2 + 1, temp_num);

	// キーネームの作成
	*texture_key_name = temp_strign + *texture_key_name;

	// ファイルパスの作成
	*texture_file_path = texture_file_path->substr(0, slash_index2 + 1);
}