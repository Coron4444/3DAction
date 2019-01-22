//================================================================================
//!	@file	 MdBinObject.cpp
//!	@brief	 バイナリーモデルオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "MdBinObject.h"
#include "../MdbinManager/MdBinManager.h"

#include <Vector3D.h>
#include <Renderer\Renderer.h>
#include <SafeRelease/SafeRelease.h>
#include <Texture\TextureManager\TextureManager.h>



//****************************************
// プロパティ定義
//****************************************
std::string* MdBinObject::Bone::getpName()
{
	return &name_;
}



MATRIX* MdBinObject::Bone::getpOffsetMatrix()
{
	return &offset_matrix_;
}



int MdBinObject::Bone::getAnimationMatrixArraySize()
{
	return animation_matrix_.size();
}



void MdBinObject::Bone::setAnimationMatrixArraySize(int value)
{
	animation_matrix_.resize(value);
}



MATRIX* MdBinObject::Bone::getpAnimationMatrix(int index)
{
	return &animation_matrix_[index];
}



int MdBinObject::Mesh::getVertexArraySize()
{
	return vertex_.size();
}



void MdBinObject::Mesh::setVertexArraySize(int value)
{
	vertex_.resize(value);
}



MdBinObject::Vertex* MdBinObject::Mesh::getpVertex(int index)
{
	return &vertex_[index];
}



int MdBinObject::Mesh::getIndexArraySize()
{
	return index_.size();
}



void MdBinObject::Mesh::setIndexArraySize(int value)
{
	index_.resize(value);
}



WORD* MdBinObject::Mesh::getpIndex(int index)
{
	return &index_[index];
}



int MdBinObject::Mesh::getBoneArraySize()
{
	return bone_.size();
}



void MdBinObject::Mesh::setBoneArraySize(int value)
{
	bone_.resize(value);
}



MdBinObject::Bone* MdBinObject::Mesh::getpBone(int index)
{
	return &bone_[index];
}



int MdBinObject::Mesh::getMaterialIndex()
{
	return material_index_;
}



void MdBinObject::Mesh::setMaterialIndex(int value)
{
	material_index_ = value;
}



int MdBinObject::Mesh::getPrimitiveNum()
{
	return primitive_num_;
}



void MdBinObject::Mesh::setPrimitiveNum(int value)
{
	primitive_num_ = value;
}



TextureObject* MdBinObject::Mesh::getpDiffuseTextureObject()
{
	return diffuse_texture_object_;
}



void MdBinObject::Mesh::setDiffuseTextureObject(TextureObject* value)
{
	diffuse_texture_object_ = value;
}



LPDIRECT3DVERTEXBUFFER9 MdBinObject::Mesh::getpVertexBuffer()
{
	return vertex_buffer_;
}



LPDIRECT3DVERTEXBUFFER9* MdBinObject::Mesh::getp2VertexBuffer()
{
	return &vertex_buffer_;
}



LPDIRECT3DINDEXBUFFER9 MdBinObject::Mesh::getpIndexBuffer()
{
	return index_buffer_;
}



LPDIRECT3DINDEXBUFFER9* MdBinObject::Mesh::getp2IndexBuffer()
{
	return &index_buffer_;
}



unsigned MdBinObject::getMeshNum()
{
	return mesh_.size();
}



MdBinObject::Mesh* MdBinObject::getpMesh(int index)
{
	return &mesh_[index];
}



D3DMATERIAL9* MdBinObject::getpMaterial(unsigned mesh_index)
{
	return &material_[mesh_[mesh_index].getMaterialIndex()];
}



TextureObject* MdBinObject::getpDiffuseTextureObject(unsigned mesh_index)
{
	return mesh_[mesh_index].getpDiffuseTextureObject();
}



LPDIRECT3DTEXTURE9 MdBinObject::getpDiffuseTextureHandler(unsigned mesh_index)
{
	if (mesh_[mesh_index].getpDiffuseTextureObject() == nullptr) return nullptr;
	return mesh_[mesh_index].getpDiffuseTextureObject()->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void MdBinObject::Mesh::Uninit()
{
	SafeRelease::PlusRelease(&vertex_buffer_);
	SafeRelease::PlusRelease(&index_buffer_);
	SafeRelease::PlusRelease(&diffuse_texture_object_);
}



void MdBinObject::Init(std::string* file_path, const std::string* map_key_name)
{
	// バイナリーモデルデータの読み込み
	MdBinData md_bin_data;
	if (!MdBinData::InportData(&md_bin_data, *file_path))
	{
		MessageBox(NULL, "バイナリーモデルをインポート出来ませんでした。", "Error", MB_OK);
		return;
	}

	// マテリアル生成
	CreateMaterial(&md_bin_data);

	// メッシュ生成
	CreateMesh(file_path, &md_bin_data);

	// アニメーション数保存
	animation_frame_num_ = md_bin_data.getAnimationFramNum();

	// キー名保存
	map_key_name_ = *map_key_name;
}



void MdBinObject::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	for (auto& contents : mesh_)
	{
		contents.Uninit();
	}

	MdBinManager::getpInstance()->ReleaseFromTheMap(&map_key_name_);
	delete this;
}



void MdBinObject::ForcedRelease()
{
	reference_counter_ = 0;
	Release();
}



void MdBinObject::AddReferenceCounter()
{
	reference_counter_++;
}



void MdBinObject::Draw(unsigned mesh_index)
{
	// 頂点バッファセット
	device_->SetStreamSource(0,										// パイプライン番号
							 mesh_[mesh_index].getpVertexBuffer(),	// バーテックスバッファ変数名
							 0,										// どこから流し込むか
							 sizeof(MdBinObject::Vertex));			// ストライド値(隣の頂点までの長さ＝1頂点の大きさ)

	// 描画
	device_->DrawPrimitive(D3DPT_TRIANGLELIST,
						   0,
						   mesh_[mesh_index].getPrimitiveNum());

	/*
	// インデックス版の表示(FBXの最適化等で実装するか決める)
	device_->SetIndices(mesh_[mesh_index].getpIndexBuffer());
	device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
								  0,											// セットストリームからどれくらいずれているか
								  0,											// インデックスで一番小さい値
								  (UINT)mesh_[mesh_index].getVertexArraySize(),	// 頂点数
								  0,											// スタートインデックス番号
								  mesh_[mesh_index].getPrimitiveNum());			// プリミティブ数

	*/
}



void MdBinObject::CreateMaterial(MdBinData* md_bin_data)
{
	// マテリアル数取得
	int material_num = md_bin_data->getMaterialArraySize();
	material_.resize(material_num);

	// マテリアルごとの処理
	for (int i = 0; i < material_num; i++)
	{
		// 透明度
		float alpha = *md_bin_data->getpMaterial(i)->getpTransparent();

		// アンビエント
		material_[i].Ambient.r = *md_bin_data->getpMaterial(i)->getpAmbient()->getpR();
		material_[i].Ambient.g = *md_bin_data->getpMaterial(i)->getpAmbient()->getpG();
		material_[i].Ambient.b = *md_bin_data->getpMaterial(i)->getpAmbient()->getpB();
		material_[i].Ambient.a = alpha;

		// ディヒューズ
		material_[i].Diffuse.r = *md_bin_data->getpMaterial(i)->getpDiffuse()->getpR();
		material_[i].Diffuse.g = *md_bin_data->getpMaterial(i)->getpDiffuse()->getpG();
		material_[i].Diffuse.b = *md_bin_data->getpMaterial(i)->getpDiffuse()->getpB();
		material_[i].Diffuse.a = alpha;

		// エミッシブ
		material_[i].Emissive.r = *md_bin_data->getpMaterial(i)->getpEmissive()->getpR();
		material_[i].Emissive.g = *md_bin_data->getpMaterial(i)->getpEmissive()->getpG();
		material_[i].Emissive.b = *md_bin_data->getpMaterial(i)->getpEmissive()->getpB();
		material_[i].Emissive.a = alpha;

		// スペキュラ&スペキュラパワー
		material_[i].Specular.r = *md_bin_data->getpMaterial(i)->getpSpecular()->getpR();
		material_[i].Specular.g = *md_bin_data->getpMaterial(i)->getpSpecular()->getpG();
		material_[i].Specular.b = *md_bin_data->getpMaterial(i)->getpSpecular()->getpB();
		material_[i].Specular.a = alpha;
		material_[i].Power = *md_bin_data->getpMaterial(i)->getpPower();
	}
}



void MdBinObject::CreateMesh(std::string* file_path, MdBinData* md_bin_data)
{
	// メッシュ数取得
	int mesh_num = md_bin_data->getMeshArraySize();
	mesh_.resize(mesh_num);

	// メッシュごとの処理
	for (int i = 0; i < mesh_num; i++)
	{
		// マテリアルインデックス生成
		CreateMaterialIndex(i, md_bin_data);

		// インデックス生成
		CreateIndex(i, md_bin_data);

		// 頂点生成
		CreateVertex(i, md_bin_data);

		// ディヒューズテクスチャ生成
		CreateDiffuseTexture(i, file_path, md_bin_data);

		// ボーン生成
		CreateBone(i, md_bin_data);

		// バッファ生成
		CreateBuffer(i);
	}
}



void MdBinObject::CreateMaterialIndex(int mesh_index, MdBinData* md_bin_data)
{
	int material_index = *md_bin_data->getpMesh(mesh_index)->getpMaterialIndex();
	mesh_[mesh_index].setMaterialIndex(material_index);
}



void MdBinObject::CreateIndex(int mesh_index, MdBinData* md_bin_data)
{
	// インデックス数取得
	mesh_[mesh_index].setIndexArraySize(md_bin_data->getpMesh(mesh_index)
										->getIndexArraySize());

   // データ取得
	for (int i = 0; i < mesh_[mesh_index].getIndexArraySize(); i++)
	{
		WORD index = (WORD)*md_bin_data->getpMesh(mesh_index)->getpIndex(i);
		*mesh_[mesh_index].getpIndex(i) = index;
	}

	// プリミティブ数生成
	int primitive_num = mesh_[mesh_index].getIndexArraySize() / 3;
	mesh_[mesh_index].setPrimitiveNum(primitive_num);
}



void MdBinObject::CreateVertex(int mesh_index, MdBinData* md_bin_data)
{
	// 頂点数取得
	mesh_[mesh_index].setVertexArraySize(md_bin_data->getpMesh(mesh_index)
										 ->getVertexArraySize());

	// 各種データ取得
	for (int i = 0; i < mesh_[mesh_index].getVertexArraySize(); i++)
	{
		CreateVertexPosition(mesh_index, i, md_bin_data);
		CreateNormal(mesh_index, i, md_bin_data);
		CreateColor(mesh_index, i);
		CreateUV(mesh_index, i, md_bin_data);
		CreateBoneWeight(mesh_index, i, md_bin_data);
	}
}



void MdBinObject::CreateVertexPosition(int mesh_index, int vertex_index,
									   MdBinData* md_bin_data)
{
	MdBinData::Vector3* md_position = md_bin_data->getpMesh(mesh_index)
		->getpPosition(vertex_index);
	MdBinObject::Vertex* vertex = mesh_[mesh_index].getpVertex(vertex_index);
	vertex->posisiont_.x = *md_position->getpX();
	vertex->posisiont_.y = *md_position->getpY();
	vertex->posisiont_.z = *md_position->getpZ();
}



void MdBinObject::CreateNormal(int mesh_index, int vertex_index,
							   MdBinData* md_bin_data)
{
	MdBinData::Vector3* md_normal = md_bin_data->getpMesh(mesh_index)
		->getpNormal(vertex_index);
	MdBinObject::Vertex* vertex = mesh_[mesh_index].getpVertex(vertex_index);
	vertex->normal_.x = *md_normal->getpX();
	vertex->normal_.y = *md_normal->getpY();
	vertex->normal_.z = *md_normal->getpZ();
}



void MdBinObject::CreateColor(int mesh_index, int vertex_index)
{
	int material_index = mesh_[mesh_index].getMaterialIndex();
	D3DMATERIAL9 diffuse = material_[material_index];
	Color4 color = (Color4)XColor4(diffuse.Diffuse.r, diffuse.Diffuse.g,
								   diffuse.Diffuse.b, diffuse.Diffuse.a);
	MdBinObject::Vertex* vertex = mesh_[mesh_index].getpVertex(vertex_index);
	vertex->color_ = color;
}



void MdBinObject::CreateUV(int mesh_index, int vertex_index,
						   MdBinData* md_bin_data)
{
	float u = *md_bin_data->getpMesh(mesh_index)->getpUVSet(0)->getpU(vertex_index);
	float v = *md_bin_data->getpMesh(mesh_index)->getpUVSet(0)->getpV(vertex_index);
	MdBinObject::Vertex* vertex = mesh_[mesh_index].getpVertex(vertex_index);
	vertex->uv_.x = u;
	vertex->uv_.y = v;
}



void MdBinObject::CreateBoneWeight(int mesh_index, int vertex_index,
								   MdBinData* md_bin_data)
{
	if (md_bin_data->getpMesh(mesh_index)->getBoneArraySize() > 0)
	{
		for (int i = 0; i < MdBinData::Mesh::BoneWeight::MAX_BONE_NUM; i++)
		{
			mesh_[mesh_index].getpVertex(vertex_index)->bone_index_[i] = 
				(unsigned char)(md_bin_data->getpMesh(mesh_index)->getpBoneWeight(vertex_index)->getBoneIndex(i));
			mesh_[mesh_index].getpVertex(vertex_index)->bone_weight_[i] = 
				md_bin_data->getpMesh(mesh_index)->getpBoneWeight(vertex_index)->getBoneWeight(i);
		}
	}
	else
	{
		for (int i = 0; i < MdBinData::Mesh::BoneWeight::MAX_BONE_NUM; i++)
		{
			mesh_[mesh_index].getpVertex(vertex_index)->bone_index_[i] = (unsigned char)0;
			mesh_[mesh_index].getpVertex(vertex_index)->bone_weight_[i] = 0.0f;
		}
	}
}



void MdBinObject::CreateDiffuseTexture(int mesh_index, std::string* file_path,
									   MdBinData* md_bin_data)
{
	if (md_bin_data->getpMesh(mesh_index)->getpUVSet(0)->getTextureArraySize() <= 0) return;

	std::string key_name = *md_bin_data->getpMesh(mesh_index)->getpUVSet(0)
		->getpTexture(0)->getpFilePath();
	std::string path = *file_path;
	CreateFilePathAndKeyName(&path, &key_name);
	TextureObject* texture_object = TextureManager::getpInstance()->getpObject(&key_name, &path);
	mesh_[mesh_index].setDiffuseTextureObject(texture_object);
}



void MdBinObject::CreateBone(int mesh_index,
							 MdBinData* md_bin_data)
{
	int bone_num = md_bin_data->getpMesh(mesh_index)->getBoneArraySize();
	if (bone_num > 0)
	{
		mesh_[mesh_index].setBoneArraySize(bone_num);
		for (int i = 0; i < bone_num; i++)
		{
			// ボーン名
			*mesh_[mesh_index].getpBone(i)->getpName() = *md_bin_data->getpMesh(mesh_index)->getpBone(i)->getpName();

			// オフセット行列
			ChangeMatrix(mesh_[mesh_index].getpBone(i)->getpOffsetMatrix(),
						 md_bin_data->getpMesh(mesh_index)->getpBone(i)->getpOffsetMatrix());

			MATRIX offset_matrix;
			D3DXMatrixInverse(&offset_matrix, NULL, mesh_[mesh_index].getpBone(i)->getpOffsetMatrix());

			// アニメーション行列
			int animation_fram_num = md_bin_data->getAnimationFramNum();
			mesh_[mesh_index].getpBone(i)->setAnimationMatrixArraySize(animation_fram_num);
			for (int j = 0; j < animation_fram_num; j++)
			{
				MATRIX frame_matrix;
				ChangeMatrix(&frame_matrix,
							 md_bin_data->getpMesh(mesh_index)->getpBone(i)->getpAnimationMatrix(j));

				// オフセット行列とフレーム行列を乗算しアニメーション行列とする
				*mesh_[mesh_index].getpBone(i)->getpAnimationMatrix(j) = offset_matrix * frame_matrix;
			}
		}
	}
	else
	{
		// ボーンがない場合はデフォルトボーンを1本持たせる
		bone_num = 1;
		mesh_[mesh_index].setBoneArraySize(bone_num);

		// ボーン名
		*mesh_[mesh_index].getpBone(0)->getpName() = "DefaultBone";

		// オフセット行列
		MATRIX default_matrix;
		D3DXMatrixIdentity(&default_matrix);
		*mesh_[mesh_index].getpBone(0)->getpOffsetMatrix() = default_matrix;

		// アニメーション行列
		int animation_fram_num = md_bin_data->getAnimationFramNum();
		mesh_[mesh_index].getpBone(0)->setAnimationMatrixArraySize(animation_fram_num);
		for (int j = 0; j < animation_fram_num; j++)
		{
			*mesh_[mesh_index].getpBone(0)->getpAnimationMatrix(j) = default_matrix;
		}
	}
}



void MdBinObject::ChangeMatrix(MATRIX* directx_matrix,
							   MdBinData::Matrix* md_bin_matrix)
{
	for (int i = 0; i < MdBinData::Matrix::ARRAY_HEIGHT; i++)
	{
		for (int j = 0; j < MdBinData::Matrix::ARRAY_WIDTH; j++)
		{
			(*directx_matrix)(i, j) = md_bin_matrix->getMatrixElement(i, j);
		}
	}
}



void MdBinObject::CreateFilePathAndKeyName(std::string* file_path,
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



void MdBinObject::CreateBuffer(int mesh_index)
{
	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(MdBinObject.cpp)", "Error", MB_OK);
		return;
	}

	CreateVertexBuffer(mesh_index);
	CreateIndexBuffer(mesh_index);
}



void MdBinObject::CreateVertexBuffer(int mesh_index)
{
	// VRAMのメモリを確保(GPUに依頼)(頂点バッファの作成)
	unsigned buffer_num = sizeof(MdBinObject::Vertex) * mesh_[mesh_index].getVertexArraySize();
	HRESULT  hr = device_->CreateVertexBuffer(buffer_num,								// 借りたいbafの量(バイト)、つまり1頂点の容量×必要頂点数
											  D3DUSAGE_WRITEONLY,						// 使用用途(今回は書き込みのみ、GPUが早く動くが書き込んだデータを読んではダメ(値が不定))
											  RendererDirectX9::FVF_VERTEX_3D,			// 頂点属性
											  D3DPOOL_MANAGED,							// 頂点バッファの管理方法( MANAGEDは管理はDirect3Dにお任せという意味 )
											  mesh_[mesh_index].getp2VertexBuffer(),	// 管理者の居場所のメモ帳(ポインタのポインタ)(全てはこれの値を知るための作業)
											  NULL);									// なぞ？
	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファの生成に失敗(MdBinObject.cpp)", "Error", MB_OK);
	}

	// 頂点の登録
	MdBinObject::Vertex* temp_vertex;	// 仮想アドレスをもらう頂点ポインタ

	// ロックする
	mesh_[mesh_index].getpVertexBuffer()->Lock(0,						// どこからロックしたいか
											   0,						// どのくらい借りたいか(0はVertexBuffer全部)
											   (void**)&temp_vertex,	// ロックするとVRAMの仮想アドレスがもらえる(実際に書き込んでいるわけではない)
											   D3DLOCK_DISCARD);		// 0でもよい

	for (auto i = 0; i < mesh_[mesh_index].getVertexArraySize(); i++)
	{
		temp_vertex[i] = *mesh_[mesh_index].getpVertex(i);
	}

	// アンロック
	mesh_[mesh_index].getpVertexBuffer()->Unlock();
}



void MdBinObject::CreateIndexBuffer(int mesh_index)
{
	// VRAMのメモリを確保(GPUに依頼)(インデックスバッファの作成)
	unsigned buffer_num = sizeof(WORD) * mesh_[mesh_index].getIndexArraySize();
	HRESULT	hr = device_->CreateIndexBuffer(buffer_num,								// 借りたいbafの量(バイト)、つまり1頂点の容量×必要頂点数
											D3DUSAGE_WRITEONLY,						// 使用用途(今回は書き込みのみ、GPUが早く動くが書き込んだデータを読んではダメ(値が不定))
											D3DFMT_INDEX16,							// 頂点フォーマット(WORD型だから16、DWORD型なら32)
											D3DPOOL_MANAGED,						// 頂点バッファの管理方法( MANAGEDは管理はDirect3Dにお任せという意味 )
											mesh_[mesh_index].getp2IndexBuffer(),	// 管理者の居場所のメモ帳(ポインタのポインタ)(全てはこれの値を知るための作業)
											NULL);									// なぞ？									// なぞ？
	if (FAILED(hr))
	{
		MessageBox(NULL, "インデックスバッファの生成に失敗(MdBinObject.cpp)", "Error", MB_OK);
	}

	// インデックスの登録
	LPWORD temp_index;		// 仮想アドレスをもらう頂点ポインタ 

	// ロックする
	mesh_[mesh_index].getpIndexBuffer()->Lock(0,					// どこからロックしたいか
											  0,					// どのくらい借りたいか(0はVertexBuffer全部)
											  (void**)&temp_index,	// ロックするとVRAMの仮想アドレスがもらえる(実際に書き込んでいるわけではない)
											  D3DLOCK_DISCARD);		// 0でもよい

	for (auto i = 0; i < mesh_[mesh_index].getIndexArraySize(); i++)
	{
		temp_index[i] = *mesh_[mesh_index].getpIndex(i);
	}


	// アンロック
	mesh_[mesh_index].getpIndexBuffer()->Unlock();
}