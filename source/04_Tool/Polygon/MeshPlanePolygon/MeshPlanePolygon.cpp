//================================================================================
//
//    メッシュ平面ポリゴンクラスヘッダ
//    Author : Araki Kai                                作成日 : 2017/11/22
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "MeshPlanePolygon.h"
#include <Random.h>
#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const float MeshPlanePolygon::TEXTURE_WIDTH  = 1.0f;
const float MeshPlanePolygon::TEXTURE_HEIGHT = 1.0f;

const float MeshPlanePolygon::MESH_MIN = 1.0f;

const float field_height[100000] = {0.0f};
/*const float field_height[121] =
{
	//0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	//0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 4.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 4.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	//0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f, 
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f
};*/				  



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

MeshPlanePolygon::MeshPlanePolygon(Vec2 mesh_num, Vec2 mesh_scale, XColor4 color)
	: device_(nullptr)
{
	// メッシュフィールドの数チェック
	mesh_num_.x = max(mesh_num.x, MESH_MIN);
	mesh_num_.y = max(mesh_num.y, MESH_MIN);

	// メッシュフィールドのスケールチェック
	mesh_scale.x = max(mesh_scale.x, MESH_MIN);
	mesh_scale.y = max(mesh_scale.y, MESH_MIN);
	
	CreateVertex(mesh_num_, mesh_scale, (Color4)color);
	CreateIndex(mesh_num_);
	CreatePrimitiveNum(mesh_num_);

	CreateMaterial();

	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(MeshPlanePolygon.cpp)", "Error", MB_OK);
		return;
	}

	AccessVRAM();

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

MeshPlanePolygon::~MeshPlanePolygon()
{
	// 頂点バッファの解放
	SafeRelease::PlusRelease(&vertex_buffer_);

	// インデックスバッファの解放
	SafeRelease::PlusRelease(&index_buffer_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ カラーセット関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void MeshPlanePolygon::SetColor(XColor4 color)
{
	for(std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		vertex_[i].color_ = (Color4)color;
	}

	RegistrationVertex();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 高さ取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float MeshPlanePolygon::GetHeight(Vec3 position)
{
	// 座標からエリアを算出し計算
	int left_up_index = 0;
	int right_bottom_index = 0;
	for (int i = 0; i < (int)(mesh_num_.x * mesh_num_.y); i++)
	{
		// 左上頂点の確認
		left_up_index = i + (i / ((int)mesh_num_.x));
		if (vertex_[left_up_index].posisiont_.x > position.x) continue;
		if (vertex_[left_up_index].posisiont_.z < position.z) continue;

		// 右下頂点の確認
		right_bottom_index = left_up_index + (int)mesh_num_.x + 2;
		if (vertex_[right_bottom_index].posisiont_.x < position.x) continue;
		if (vertex_[right_bottom_index].posisiont_.z > position.z) continue;

		// 左下の三角形(N字でメッシュを作っているため)
		if (CalculationHeight(&position, left_up_index, right_bottom_index, right_bottom_index - 1))
		{
			return position.y;
		}

		// 右上の三角形(N字でメッシュを作っているため)
		if (CalculationHeight(&position, left_up_index, left_up_index + 1, right_bottom_index))
		{
			return position.y;
		}
	}

	return position.y = -100.0f;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void MeshPlanePolygon::Draw()
{
	// FVFの設定(デバイスの方に頂点の属性を教える)
	device_->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// 頂点バッファを使うGPUとバーテックスバッファのパイプライン
	// 使いたくなかったらNULLをいれる
	device_->SetStreamSource(0,										// パイプライン番号
		                    vertex_buffer_,							// バーテックスバッファ変数名
							0,										// どこから流し込むか
							sizeof(RendererDirectX9::VERTEX_3D));	// ストライド値(隣の頂点までの長さ＝1頂点の大きさ)


	// インデックスをセットする
	device_->SetIndices(index_buffer_);

	device_->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 
								 0,						// セットストリームからどれくらいずれているか
								 0,						// インデックスで一番小さい値
								 (UINT)vertex_.size(),	// 頂点数
								 0,						// スタートインデックス番号
								 primitive_num_);		// プリミティブ数
}



//--------------------------------------------------------------------------------
//
// [ 頂点作成関数 ]
//
//--------------------------------------------------------------------------------

void MeshPlanePolygon::CreateVertex(Vec2 mesh_num, Vec2 mesh_scale, Color4 color)
{
	// 頂点数の決定
	int temp_vertex_num = 4 + 2 * (((int)mesh_num.x) - 1);
	temp_vertex_num += temp_vertex_num / 2 * (((int)mesh_num.y) - 1);
	vertex_.resize(temp_vertex_num);

	// 頂点情報の入力
	float coordinate_x = -((mesh_scale.x  / 2) * ((int)mesh_num.x));
	float coordinate_z =  ((mesh_scale.y / 2) * ((int)mesh_num.y));
	float tex_widht    =  0.0f;
	float tex_heihgt   =  0.0f;
	int   x_count      =  0;

	for(std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		vertex_[i].posisiont_ = Vec3(coordinate_x, field_height[i], coordinate_z);
		vertex_[i].color_	  = color;
		vertex_[i].texcoord_  = Vec2(tex_widht, tex_heihgt);
		
		coordinate_x += mesh_scale.x;
		tex_widht    += TEXTURE_WIDTH;

		bool is_x_end = x_count == ((int)mesh_num.x);

		if (is_x_end)
		{
			x_count		  = 0;
			coordinate_x  = -((mesh_scale.x  / 2) * ((int)mesh_num.x));
			tex_widht     =  0.0f;

			coordinate_z += -mesh_scale.y;
			tex_heihgt   +=  TEXTURE_HEIGHT;
		}
		else
		{
			x_count++;
		}
	}


	// 法線計算
	for(std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		// フィールドの後ろ端の頂点
		if (i / (unsigned)(mesh_num.x + 1.0f) == 0)
		{
			vertex_[i].normal_ = Vec3(0.0f, 1.0f, 0.0f);
			continue;
		}

		// フィールドの前端の頂点
		if (i / (unsigned)(mesh_num.x + 1.0f) == (unsigned)mesh_num.y)
		{
			vertex_[i].normal_ = Vec3(0.0f, 1.0f, 0.0f);
			continue;
		}

		// フィールドの左端の頂点
		if (i % (unsigned)(mesh_num.x + 1.0f) == 0)
		{
			vertex_[i].normal_ = Vec3(0.0f, 1.0f, 0.0f);
			continue;
		}

		// フィールドの右端の頂点
		if (i % (unsigned)(mesh_num.x + 1.0f) == (unsigned)mesh_num.x)
		{
			vertex_[i].normal_ = Vec3(0.0f, 1.0f, 0.0f);
			continue;
		}

		// それ以外の頂点
		// x方向
		Vec3 temp_vector = vertex_[i + 1].posisiont_ - vertex_[i - 1].posisiont_;
		Vec3 normal_x = Vec3(-temp_vector.y, temp_vector.x, 0.0f);
	
		// z方向
		temp_vector = vertex_[i - 5].posisiont_ - vertex_[i + 5].posisiont_;
		Vec3 normal_z = Vec3(0.0f, temp_vector.z, -temp_vector.y);
	
		Vector3D normal = normal_x + normal_z;
		
		vertex_[i].normal_ = normal.CreateNormalize();
	}
}



//--------------------------------------------------------------------------------
//
// [ インデックス作成関数 ]
//
//--------------------------------------------------------------------------------

void MeshPlanePolygon::CreateIndex(Vec2 mesh_num)
{
	// インデックス数の決定
	int temp_index_num = 4 + 2 * (((int)mesh_num.x) - 1);

	temp_index_num += temp_index_num * (((int)mesh_num.y) - 1);
	temp_index_num += 2 * (((int)mesh_num.y) - 1);

	index_.resize(temp_index_num);


	// インデックスの入力
	WORD down_num = (WORD)(((int)mesh_num.x) + 1);
	WORD up_num   = 0;
	int  x_num	  = ((int)mesh_num.x) + 1;
	int  y_num	  = ((int)mesh_num.y);

	for(std::vector< WORD >::size_type i = 0; i < index_.size(); i++)
	{
		index_[i] = down_num;

		i++;

		index_[i] = up_num;

		down_num++;
		up_num++;
		x_num--;

		bool is_end_x = x_num == 0;

		if (is_end_x)
		{
			y_num--;

			bool is_remain_y = y_num != 0;

			if (is_remain_y)
			{
				i++;

				index_[i] = up_num - 1;

				i++;

				index_[i] = down_num;

				x_num = ((int)mesh_num.x) + 1;
			}
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ プリミティブ数作成関数 ]
//
//--------------------------------------------------------------------------------

void MeshPlanePolygon::CreatePrimitiveNum(Vec2 mesh_num)
{
	// プリミティブ数の決定
	primitive_num_ = 2 * ((int)mesh_num.x) * ((int)mesh_num.y);

	primitive_num_ += 4 * (((int)mesh_num.y) - 1);
}



//--------------------------------------------------------------------------------
//
// [ マテリアル作成関数 ]
//
//--------------------------------------------------------------------------------

void MeshPlanePolygon::CreateMaterial()
{
	// マテリアルの設定
	ZeroMemory(&material_, sizeof(material_));	// 第一引数のアドレスからsizeof()分を0で埋める(クラスには使わない)
													
	// マテリアルカラーを白にする
	material_.Diffuse.r = 1.0f;
	material_.Diffuse.g = 1.0f;
	material_.Diffuse.b = 1.0f;
	material_.Diffuse.a = 1.0f;

	// アンビエントマテリアルの設定
	material_.Ambient.r = 1.0f;
	material_.Ambient.g = 1.0f;
	material_.Ambient.b = 1.0f;
	material_.Ambient.a = 1.0f;
}



//--------------------------------------------------------------------------------
//
// [ VRAMへのアクセス操作関数 ]
//
//--------------------------------------------------------------------------------

void MeshPlanePolygon::AccessVRAM()
{
	// VRAMのメモリを確保(GPUに依頼)(頂点バッファの作成)
	HRESULT  hr = device_->CreateVertexBuffer(sizeof(RendererDirectX9::VERTEX_3D) * (int)vertex_.size(),	// 借りたいbafの量(バイト)、つまり1頂点の容量×必要頂点数
											  D3DUSAGE_WRITEONLY,											// 使用用途(今回は書き込みのみ、GPUが早く動くが書き込んだデータを読んではダメ(値が不定))
											  RendererDirectX9::FVF_VERTEX_3D,								// 頂点属性
											  D3DPOOL_MANAGED,												// 頂点バッファの管理方法( MANAGEDは管理はDirect3Dにお任せという意味 )
											  &vertex_buffer_,												// 管理者の居場所のメモ帳(ポインタのポインタ)(全てはこれの値を知るための作業)
											  NULL);														// なぞ？

	if (FAILED(hr))
	{
		MessageBox(NULL, "Vertex buffer was not created.", "Error", MB_OK);
	}


	// VRAMのメモリを確保(GPUに依頼)(インデックスバッファの作成)
	hr = device_->CreateIndexBuffer(sizeof(WORD) * ( int )index_.size(),	// 借りたいbafの量(バイト)、つまり1頂点の容量×必要頂点数
									D3DUSAGE_WRITEONLY,						// 使用用途(今回は書き込みのみ、GPUが早く動くが書き込んだデータを読んではダメ(値が不定))
									D3DFMT_INDEX16,							// 頂点フォーマット(WORD型だから16、DWORD型なら32)
									D3DPOOL_MANAGED,						// 頂点バッファの管理方法( MANAGEDは管理はDirect3Dにお任せという意味 )
									&index_buffer_,							// 管理者の居場所のメモ帳(ポインタのポインタ)(全てはこれの値を知るための作業)
									NULL);									// なぞ？

	if (FAILED(hr))
	{
		MessageBox(NULL, "Index buffer was not created.", "Error", MB_OK);
	}

	RegistrationVertex();

	RegistrationIndex();
}



//--------------------------------------------------------------------------------
//
// [ 頂点の登録関数 ]
//
//--------------------------------------------------------------------------------

void MeshPlanePolygon::RegistrationVertex()
{
	// 頂点の登録
	// 仮想アドレスをもらう頂点ポインタ
	RendererDirectX9::VERTEX_3D* temp_vertex;

	// ロックする
	vertex_buffer_->Lock(0,						// どこからロックしたいか
						  0,					// どのくらい借りたいか(0はVertexBuffer全部)
						  (void**)&temp_vertex,	// ロックするとVRAMの仮想アドレスがもらえる(実際に書き込んでいるわけではない)
						  D3DLOCK_DISCARD );	// 0でもよい

	for(std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		temp_vertex[i] = vertex_[i];
	}



	// アンロック
	vertex_buffer_->Unlock();
}



//--------------------------------------------------------------------------------
//
// [ インデックスの登録関数 ]
//
//--------------------------------------------------------------------------------

void MeshPlanePolygon::RegistrationIndex()
{
	// インデックスの登録
	// 仮想アドレスをもらう頂点ポインタ 
	LPWORD temp_index;


	// ロックする
	index_buffer_->Lock(0,						// どこからロックしたいか
						0,						// どのくらい借りたいか(0はVertexBuffer全部)
						(void**)&temp_index,	// ロックするとVRAMの仮想アドレスがもらえる(実際に書き込んでいるわけではない)
						D3DLOCK_DISCARD);		// 0でもよい

	for(std::vector<WORD>::size_type i = 0; i < index_.size(); i++)
	{
		temp_index[i] = index_[i];

	}

	// アンロック
	index_buffer_->Unlock();
}



//--------------------------------------------------------------------------------
//
// [ 高さ計算関数 ]
//
//--------------------------------------------------------------------------------

bool MeshPlanePolygon::CalculationHeight(Vec3* position, int index0, int index1, int index2)
{
	// 三角形の各辺に沿うベクトルを算出
	Vector3D v01 = vertex_[index1].posisiont_ - vertex_[index0].posisiont_;
	Vector3D v12 = vertex_[index2].posisiont_ - vertex_[index1].posisiont_;
	Vector3D v20 = vertex_[index0].posisiont_ - vertex_[index2].posisiont_;

	// 各頂点から自分へのベクトル
	Vector3D v0p = *position - vertex_[index0].posisiont_;
	Vector3D v1p = *position - vertex_[index1].posisiont_;
	Vector3D v2p = *position - vertex_[index2].posisiont_;

	// 上記2つの外積を求める(2D外積)
	float c0 = (v01.x * v0p.z) - (v01.z * v0p.x);
	float c1 = (v12.x * v1p.z) - (v12.z * v1p.x);
	float c2 = (v20.x * v2p.z) - (v20.z * v2p.x);

	// 自分がポリゴン内にいる場合
	if (c0 <= 0.0f && c1 <= 0.0f && c2 <= 0.0f)
	{
		// y座標を求める
		Vec3 temp_normal = v01.CreateVectorCross(v12);
		Vec3 p0 = vertex_[index0].posisiont_;
		position->y = p0.y - ((temp_normal.x * (position->x - p0.x) + 
					 temp_normal.z * (position->z - p0.z)) / temp_normal.y);

		 return true;
	}

	return false;
}