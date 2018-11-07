//================================================================================
//
//    FBXモデルクラスヘッダ
//    Author : Araki Kai                                作成日 : 2018/01/19
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "ModelFBXObject.h"
#include <ModelFBX\LoadMFM\LoadMFM.h>

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Vector3D.h>
#include <Texture\TextureManager\TextureManager.h>
#include <EffectFile\EffectFile.h>


//**********************************************************************
//
// 定数定義
//
//**********************************************************************

namespace
{
	const DWORD	FVF_VERTEX_3D = ( D3DFVF_XYZ | D3DFVF_NORMAL |D3DFVF_DIFFUSE | D3DFVF_TEX1 );

	// 頂点宣言構造体配列
	D3DVERTEXELEMENT9 MFM_VERTEX_DECLARATION[] = {
		{ 0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,     0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,       0 },
		{ 0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,        0 },
		{ 0, 28, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     0 },
		{ 0, 36, D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT,  0 },
		{ 0, 52, D3DDECLTYPE_UBYTE4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
	D3DDECL_END()
	};
}



//**********************************************************************
//
// 非静的メンバ関数定義
//
//**********************************************************************

//================================================================================
//
// [ デフォルトコンストラクタ ]
//
//================================================================================

ModelFBXObject::ModelFBXObject(TextureManager* texture_manager, const std::string* key_name, const std::string* file_path)
	: texture_manager_   (texture_manager),
	  vertex_declaration_(nullptr)
{
	// ファイルの読み込み
	std::string full_path = "";

	if (file_path == nullptr)
	{
		full_path = *key_name;	
	}
	else
	{
		full_path = *file_path + *key_name;
	}

	// モデル及びメッシュを生成
	mfmlib::Model temp_model;

	// モデルの読み込み
	temp_model.FileLoadFullData((TCHAR*)full_path.c_str());

	// 頂点の作成
	CreateVertex(&temp_model, &mesh_, file_path);

	CreateMaterial(&temp_model);

	// デバイスの取得
	LPDIRECT3DDEVICE9 device = RendererDirectX9::GetDevice();
	assert(device != nullptr && "Deviceの取得に失敗(ModelFBXObject.cpp)");

	AccessVRAM(device, &mesh_);
}



//================================================================================
//
// [ デストラクタ ]
//
//================================================================================

ModelFBXObject::~ModelFBXObject()
{
	for (auto& contents : mfm_model_data_.VertexBuffer)
	{
		// 頂点バッファの解放
		SafeReleaseDirectX9(&contents);
	}
}



//================================================================================
//
// [ 頂点作成関数 ]
//
//================================================================================

void ModelFBXObject::CreateVertex(mfmlib::Model* temp_model, std::vector<Shaderbuff>* temp_mesh, const std::string* file_path)
{
	// バッファを総メッシュ分増やす
	temp_mesh->resize(temp_model->MeshNum);
	mfm_model_data_.MeshData.resize(temp_model->MeshNum);

	// メッシュ数分回す
	for( unsigned i = 0; i < temp_mesh->size(); i++ )
	{
		// インデックス数分回す
		temp_mesh->at(i).Vertex.resize(temp_model->MeshData[i].Index.Num);
		
		// インデックス番号の取得
		mfm_model_data_.MeshData[i].MaterialIndex = temp_model->MeshData[i].MaterialIndex;
	
		// ？
		temp_model->BoneData[i].BoneNum;

		// 頂点情報取得
		for (unsigned j = 0; j < temp_mesh->at(i).Vertex.size(); j++)
		{
			// 頂点
			int temp_index_num = temp_model->MeshData[i].Index.Data[j];
			temp_mesh->at(i).Vertex[j].Pos.x = temp_model->MeshData[i].Vertex.Data[temp_index_num].x;
			temp_mesh->at(i).Vertex[j].Pos.y = temp_model->MeshData[i].Vertex.Data[temp_index_num].y;
			temp_mesh->at(i).Vertex[j].Pos.z = temp_model->MeshData[i].Vertex.Data[temp_index_num].z;

			// 法線
			temp_mesh->at(i).Vertex[j].Normal.x = temp_model->MeshData[i].Normals.Data[j].x;
			temp_mesh->at(i).Vertex[j].Normal.y = temp_model->MeshData[i].Normals.Data[j].y;
			temp_mesh->at(i).Vertex[j].Normal.z = temp_model->MeshData[i].Normals.Data[j].z;

			// UV
			if ( temp_model->MeshData[ i ].TexUV.Num != 0 )
			{
				temp_mesh->at(i).Vertex[j].texcoord.x = temp_model->MeshData[i].TexUV.Data[j].U;
				temp_mesh->at(i).Vertex[j].texcoord.y = temp_model->MeshData[i].TexUV.Data[j].V;
			}
			else
			{
				temp_mesh->at(i).Vertex[j].texcoord.x = 0.0f;
				temp_mesh->at(i).Vertex[j].texcoord.y = 0.0f;
			}
			
			// カラー
			XColor4 temp_color;
			temp_color.r = temp_model->MaterialData[mfm_model_data_.MeshData[i].MaterialIndex].Color.Diffuse.x;
			temp_color.g = temp_model->MaterialData[mfm_model_data_.MeshData[i].MaterialIndex].Color.Diffuse.y;
			temp_color.b = temp_model->MaterialData[mfm_model_data_.MeshData[i].MaterialIndex].Color.Diffuse.z;
			
			if (temp_model->MaterialData[mfm_model_data_.MeshData[i].MaterialIndex].Color.Transparency == 0.0f)
			{
				temp_color.a = 1.0f;
			}
			else
			{
				temp_color.a = temp_model->MaterialData[mfm_model_data_.MeshData[i].MaterialIndex].Color.Transparency;
			}

			temp_mesh->at(i).Vertex[j].color = (Color4)temp_color;


			// ボーンの重み
			if (temp_model->BoneData[i].BoneNum > 0)
			{
				for (int k = 0; k < MAX_MFM_BONE; k++)
				{
					// 頂点へのボーンの重みとボーン番号取得
					temp_mesh->at(i).Vertex[j].ImpactMap.weight[k]      = temp_model->BoneData[i].VertexData.Data[temp_index_num].weight[k];
					temp_mesh->at(i).Vertex[j].ImpactMap.matrixIndex[k] = (unsigned char)temp_model->BoneData[i].VertexData.Data[temp_index_num].index[k];
				}
			}
		}

	
		// テクスチャ名の読み込み
		std::string temp_name = temp_model->MaterialData[mfm_model_data_.MeshData[i].MaterialIndex].pTexName;
		if(temp_name != "")
		{
			mfm_model_data_.MeshData[i].TexName = temp_name;
			texture_manager_->RegistrationTextureObject(&mfm_model_data_.MeshData[i].TexName, file_path);
		}

		// プリミティブ数の取得
		mfm_model_data_.MeshData[i].PrimitiveNum = temp_model->MeshData[i].PrimitiveIndex;

		// アニメーションフレーム数の取得
		mfm_model_data_.nAnimFrame = temp_model->FrameNum;

		// メッシュに含まれるボーンの取得
		mfm_model_data_.bone.resize(temp_mesh->size());						// メッシュ数分ボーン領域確保
		mfm_model_data_.bone[i].resize(temp_model->BoneData[i].BoneNum);		// このメッシュのボーン数の領域確保

		for (unsigned j = 0; j < mfm_model_data_.bone[i].size(); j++)
		{
			// アニメーションフレーム数分領域確保
			mfm_model_data_.bone[i][j].MatAry.resize(mfm_model_data_.nAnimFrame);

			Mtx init_matrix;												// 初期姿勢行列
			Mtx init_matrix_inverse;										// ボーンオフセット行列

			// 初期姿勢行列の取得
			const int MATRIX_WIDTH  = 4;
			const int MATRIX_HEIGHT = 4;
			for (int r = 0; r < MATRIX_HEIGHT; r++)
			{
				for (int c = 0; c < MATRIX_WIDTH; c++)
				{
					init_matrix(r, c) = temp_model->BoneData[i].Data[j].init.Get(r, c);
				}
			}

			// ボーンオフセット行列(初期姿勢行列の逆行列)を作成
			D3DXMatrixInverse(&init_matrix_inverse, NULL, &init_matrix);

			// 各アニメーションフレームのローカル姿勢変換行列の取得
			for (int k = 0; k < mfm_model_data_.nAnimFrame; k++)
			{
				Mtx local_posture_conversion_matrix;

				for (int r = 0; r < MATRIX_HEIGHT; r++)
				{
					for (int c = 0; c < MATRIX_WIDTH; c++)
					{
						local_posture_conversion_matrix(r, c) = temp_model->BoneData[i].Data[j].perFrame.Data[k].Get(r, c);
					}
				}

				// ローカル変換行列にボーンオフセット行列を乗算
				mfm_model_data_.bone[i][j].MatAry[k] = init_matrix_inverse * local_posture_conversion_matrix;
			}
		}
	}
}



//================================================================================
//
// [ マテリアル作成関数 ]
//
//================================================================================

void ModelFBXObject::CreateMaterial(mfmlib::Model* temp_model)
{
	// マテリアル数の確定
	mfm_model_data_.Material.resize(temp_model->materialNum);

	// メッシュ数分回す
	for(unsigned i = 0; i < mfm_model_data_.Material.size(); i++)
	{
		// アンビエント
		mfm_model_data_.Material[i].Ambient.r = temp_model->MaterialData[i].Color.Ambient.x;
		mfm_model_data_.Material[i].Ambient.g = temp_model->MaterialData[i].Color.Ambient.y;
		mfm_model_data_.Material[i].Ambient.b = temp_model->MaterialData[i].Color.Ambient.z;
		mfm_model_data_.Material[i].Ambient.a = temp_model->MaterialData[i].Color.Transparency;
														 
		// ディフューズ								   
		mfm_model_data_.Material[i].Diffuse.r = temp_model->MaterialData[i].Color.Diffuse.x;
		mfm_model_data_.Material[i].Diffuse.g = temp_model->MaterialData[i].Color.Diffuse.y;
		mfm_model_data_.Material[i].Diffuse.b = temp_model->MaterialData[i].Color.Diffuse.z;
		mfm_model_data_.Material[i].Diffuse.a = temp_model->MaterialData[i].Color.Transparency;

		// エミッシブ
		mfm_model_data_.Material[i].Emissive.r = temp_model->MaterialData[i].Color.Emissive.x;
		mfm_model_data_.Material[i].Emissive.g = temp_model->MaterialData[i].Color.Emissive.y;
		mfm_model_data_.Material[i].Emissive.b = temp_model->MaterialData[i].Color.Emissive.z;
		mfm_model_data_.Material[i].Emissive.a = temp_model->MaterialData[i].Color.Transparency;

		// スペキュラ
		mfm_model_data_.Material[i].Power = temp_model->MaterialData[i].Color.Shininess;

		// スペキュラ色
		mfm_model_data_.Material[i].Specular.r = temp_model->MaterialData[i].Color.Specular.x;
		mfm_model_data_.Material[i].Specular.g = temp_model->MaterialData[i].Color.Specular.y;
		mfm_model_data_.Material[i].Specular.b = temp_model->MaterialData[i].Color.Specular.z;
		mfm_model_data_.Material[i].Specular.a = temp_model->MaterialData[i].Color.Transparency;
	}
}



//================================================================================
//
// [ VRAMへのアクセス操作関数 ]
//
//================================================================================

void ModelFBXObject::AccessVRAM(LPDIRECT3DDEVICE9 pDevice, std::vector<Shaderbuff>* temp_mesh)
{
	// 頂点バッファの領域確保
	mfm_model_data_.VertexBuffer.resize(temp_mesh->size());

	for (unsigned i = 0;  i < temp_mesh->size(); i++)
	{
		// VRAMのメモリを確保(GPUに依頼)(頂点バッファの作成)
		HRESULT  hr = pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D) * temp_mesh->at(i).Vertex.size(),
													D3DUSAGE_WRITEONLY,
													FVF_VERTEX_3D,				
													D3DPOOL_MANAGED,			
													&mfm_model_data_.VertexBuffer[i],	
													NULL);				

		if (FAILED(hr))
		{
			MessageBox(NULL, "Vertex buffer was not created.", "Error", MB_OK);
		}
	}

	RegistrationVertex(temp_mesh);

	// 頂点宣言作成
	pDevice->CreateVertexDeclaration(MFM_VERTEX_DECLARATION, &vertex_declaration_);
}



//================================================================================
//
// [ 頂点の登録関数 ]
//
//================================================================================

void ModelFBXObject::RegistrationVertex(std::vector<Shaderbuff>* temp_mesh)
{
	for (unsigned i = 0;  i < temp_mesh->size(); i++)
	{
		// 頂点の登録
		// 仮想アドレスをもらう頂点ポインタ
		VERTEX_3D* temp_vertex;

		// ロックする
		mfm_model_data_.VertexBuffer[i]->Lock(0,					// どこからロックしたいか
											  0,					// どのくらい借りたいか(0はVertexBuffer全部)
											  (void**)&temp_vertex,	// ロックするとVRAMの仮想アドレスがもらえる(実際に書き込んでいるわけではない)
											  D3DLOCK_DISCARD );	// 0でもよい


		for(unsigned j = 0; j < temp_mesh->at(i).Vertex.size(); j++)
		{
			temp_vertex[j] = temp_mesh->at(i).Vertex[j];
		}


		// アンロック
		mfm_model_data_.VertexBuffer[i]->Unlock();
	}
}



//================================================================================
//
// [ FBXModelセット関数 ]
//
//================================================================================

void ModelFBXObject::SetModelFBXObject()
{
	// エフェクトファイルのオブジェクト取得
	EffectFile* effect_file = EffectFile::GetPointer();

	effect_file->effect_->SetTechnique(shader_name_.c_str());

	// デバイスの取得
	LPDIRECT3DDEVICE9 device = RendererDirectX9::GetDevice();
	assert(device != nullptr && "Deviceの取得に失敗(ModelXObject.cpp)");

	// 頂点宣言の設定
	device->SetVertexDeclaration(vertex_declaration_);

	Mtx** bone_matrix;
	bone_matrix = new Mtx*[mfm_model_data_.VertexBuffer.size()];

	for (unsigned y = 0; y < mfm_model_data_.VertexBuffer.size(); y++)
	{
		bone_matrix[y] = new Mtx[mfm_model_data_.bone[y].size()];
		for (unsigned x = 0; x < mfm_model_data_.bone[y].size(); x++)
		{
			bone_matrix[y][x] = mfm_model_data_.bone[y][x].MatAry[effect_file->animation_num_];
		}
	}

	MatrixSRT_Axis temp_inv_mtx;

	temp_inv_mtx.UpdateTransposeMatrix(&effect_file->world_matrix_);
	temp_inv_mtx.TransposeMatrixTranslationOff();

	Mtx matrix_WVP = effect_file->world_matrix_ * effect_file->view_matrix_ * effect_file->projection_matrix_;

	// テクニックの開始
	unsigned num_pass;
	
	HRESULT hr = effect_file->effect_->Begin(&num_pass, 0);

	for (unsigned pass = 0; pass < num_pass; pass++)
	{
		hr = effect_file->effect_->BeginPass(pass);

		if (FAILED(hr)) break;

		D3DLIGHT9 light;
		// ライトカラー
		light.Diffuse.r = 1.0f;
		light.Diffuse.g = 1.0f;
		light.Diffuse.b = 1.0f;
		light.Diffuse.a = 1.0f;

		float brightess = 2.0f;

		D3DXVECTOR4 temp_vector;

		D3DXVec3Transform(&temp_vector, &light_vector_, &temp_inv_mtx.matrix_inverse_);


		for (DWORD i = 0; i < mfm_model_data_.VertexBuffer.size(); i++)
		{
			effect_file->effect_->SetVector("directional_light_vector", (D3DXVECTOR4*)&temp_vector);
			effect_file->effect_->SetVector("directional_light_diffuse",(D3DXVECTOR4*)&light.Diffuse);
			effect_file->effect_->SetFloat ("directional_light_brightness", brightess);
			effect_file->effect_->SetMatrix("matrix_world_View_projection", &matrix_WVP);
			effect_file->effect_->SetMatrixArray("bones", bone_matrix[i], mfm_model_data_.bone[i].size());
			effect_file->effect_->CommitChanges();
			device -> SetStreamSource(0,
									  mfm_model_data_.VertexBuffer[i],
									  0,					
									  sizeof(VERTEX_3D));

			// テクスチャセット
			texture_manager_->SetTextureObject(&mfm_model_data_.MeshData[i].TexName, 0);
	
			// マテリアルをデバイスにセット
			device->SetMaterial(&mfm_model_data_.Material[mfm_model_data_.MeshData[i].MaterialIndex]);

			
			device->DrawPrimitive(D3DPT_TRIANGLELIST,
								  0,				
								  mfm_model_data_.MeshData[i].PrimitiveNum);
		
			
		}

		effect_file->effect_->EndPass();
	}
	effect_file->effect_->End();

	for (unsigned i = 0; i < mfm_model_data_.VertexBuffer.size(); i++)
	{
		delete[] bone_matrix[i];
	}
	
	delete[] bone_matrix;
	
}



//================================================================================
//
// [ カラーセット関数 ]
//
//================================================================================

void ModelFBXObject::SetColor(XColor4 color)
{
	// メッシュ数分回す
	for(unsigned i = 0; i < mesh_.size(); i++)
	{
		for (unsigned j = 0; j < mesh_[i].Vertex.size(); j++)
		{
			mesh_[i].Vertex[j].color = (Color4)color;
		}
	}

	RegistrationVertex(&mesh_);
}



//================================================================================
//
// [ アニメーションパターン取得関数 ]
//
//================================================================================

int ModelFBXObject::GetAnimationFrameNum(const int animation_count, int animation_speed)
{
	if (animation_speed <= 0) animation_speed = 1;

	return animation_count / animation_speed % mfm_model_data_.nAnimFrame;
}