//================================================================================
//
//    平面ポリゴンクラス
//    Author : Araki Kai                                作成日 : 2017/12/06
//
//================================================================================




//======================================================================
//
// インクルード文
//
//======================================================================

#include "PlanePolygon.h"

#include <main.h>
#include <SafeRelease/SafeRelease.h>

#include <Texture\TextureObject\TextureObject.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const int PlanePolygon::PRIMITIVE_NUM = 2;



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

PlanePolygon::PlanePolygon(XColor4 color, Vec2 plane_size)
	: vertex_buffer_(nullptr),
	index_buffer_(nullptr),
	device_(nullptr)
{
	CreateVertex((Color4)color, plane_size);
	CreateIndex();

	CreateMaterial();

	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(PlanePolygon.cpp)", "Error", MB_OK);
		return;
	}

	AccessVRAM();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

PlanePolygon::~PlanePolygon()
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

void PlanePolygon::SetColor(XColor4 color)
{
	for (std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		vertex_[i].color_ = (Color4)color;
	}

	RegistrationVertex();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ UV設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlanePolygon::SetUV(TextureObject* texture, int pattern_num)
{
	vertex_[0].texcoord_ = Vec2(*texture->getpUV(pattern_num)->getpLeftUpU(), 
								*texture->getpUV(pattern_num)->getpLeftUpV());
	vertex_[1].texcoord_ = Vec2(*texture->getpUV(pattern_num)->getpRightButtomU(), 
								*texture->getpUV(pattern_num)->getpLeftUpV());
	vertex_[2].texcoord_ = Vec2(*texture->getpUV(pattern_num)->getpLeftUpU(), 
								*texture->getpUV(pattern_num)->getpRightButtomV());
	vertex_[3].texcoord_ = Vec2(*texture->getpUV(pattern_num)->getpRightButtomU(), 
								*texture->getpUV(pattern_num)->getpRightButtomV());

	RegistrationVertex();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlanePolygon::Draw()
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

	// ライティングをONにする(ライト全てをON、OFFする)
	device_->SetRenderState(D3DRS_LIGHTING, FALSE);

	device_->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
								 0,						// セットストリームからどれくらいずれているか
								 0,						// インデックスで一番小さい値
								 (UINT)vertex_.size(),	// 頂点数
								 0,						// スタートインデックス番号
								 PRIMITIVE_NUM);		// プリミティブ数


	// ライティングをONにする(ライト全てをON、OFFする)
	device_->SetRenderState(D3DRS_LIGHTING, TRUE);
}



//--------------------------------------------------------------------------------
//
// [ 頂点作成関数 ]
//
//--------------------------------------------------------------------------------

void PlanePolygon::CreateVertex(Color4 color, Vec2 plane_size)
{
	// 頂点情報の入力
	float temp_x = plane_size.x / 2;
	float temp_y = plane_size.y / 2;

	float u0 = 0.0f;
	float v0 = 0.0f;
	float u1 = 1.0f;
	float v1 = 1.0f;

	vertex_.push_back({Vec3(-temp_x,  temp_y, 0.0f), Vec3(0.0f, 0.0f, -1.0f), color, Vec2(u0, v0)});
	vertex_.push_back({Vec3(temp_x,  temp_y, 0.0f), Vec3(0.0f, 0.0f, -1.0f), color, Vec2(u1, v0)});
	vertex_.push_back({Vec3(-temp_x, -temp_y, 0.0f), Vec3(0.0f, 0.0f, -1.0f), color, Vec2(u0, v1)});
	vertex_.push_back({Vec3(temp_x, -temp_y, 0.0f), Vec3(0.0f, 0.0f, -1.0f), color, Vec2(u1, v1)});
}



//--------------------------------------------------------------------------------
//
// [ インデックス作成関数 ]
//
//--------------------------------------------------------------------------------

void PlanePolygon::CreateIndex()
{
	index_.push_back(2);
	index_.push_back(0);
	index_.push_back(3);
	index_.push_back(1);
}



//--------------------------------------------------------------------------------
//
// [ マテリアル作成関数 ]
//
//--------------------------------------------------------------------------------

void PlanePolygon::CreateMaterial()
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

void PlanePolygon::AccessVRAM()
{
	// VRAMのメモリを確保(GPUに依頼)(頂点バッファの作成)
	HRESULT  hr = device_->CreateVertexBuffer(sizeof(RendererDirectX9::VERTEX_3D) * (int)vertex_.size(),	// 借りたいbafの量(バイト)、つまり1頂点の容量×必要頂点数
											  D3DUSAGE_WRITEONLY,											// 使用用途(今回は書き込みのみ、GPUが早く動くが書き込んだデータを読んではダメ(値が不定))
											  RendererDirectX9::FVF_VERTEX_3D,								// 頂点属性
											  D3DPOOL_MANAGED,												// 頂点バッファの管理方法( MANAGEDは管理はDirect3Dにお任せという意味 )
											  &vertex_buffer_,												// 管理者の居場所のメモ帳(ポインタのポインタ)(全てはこれの値を知るための作業)
											  NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Vertex buffer was not created.", "Error", MB_OK);
	}


	// VRAMのメモリを確保(GPUに依頼)(インデックスバッファの作成)
	hr = device_->CreateIndexBuffer(sizeof(WORD) * (int)index_.size(),		// 借りたいbafの量(バイト)、つまり1頂点の容量×必要頂点数
									D3DUSAGE_WRITEONLY,		// 使用用途(今回は書き込みのみ、GPUが早く動くが書き込んだデータを読んではダメ(値が不定))
									D3DFMT_INDEX16,			// 頂点フォーマット(WORD型だから16、DWORD型なら32)
									D3DPOOL_MANAGED,			// 頂点バッファの管理方法( MANAGEDは管理はDirect3Dにお任せという意味 )
									&index_buffer_,			// 管理者の居場所のメモ帳(ポインタのポインタ)(全てはこれの値を知るための作業)
									NULL);					// なぞ？

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

void PlanePolygon::RegistrationVertex()
{
	// 頂点の登録
	// 仮想アドレスをもらう頂点ポインタ
	RendererDirectX9::VERTEX_3D* temp_vertex;

	// ロックする
	vertex_buffer_->Lock(0,						// どこからロックしたいか
						 0,						// どのくらい借りたいか(0はVertexBuffer全部)
						 (void**)&temp_vertex,	// ロックするとVRAMの仮想アドレスがもらえる(実際に書き込んでいるわけではない)
						 D3DLOCK_DISCARD);		// 0でもよい

	for (std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
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

void PlanePolygon::RegistrationIndex()
{
	// インデックスの登録
	// 仮想アドレスをもらう頂点ポインタ 
	LPWORD temp_index;


	// ロックする
	index_buffer_->Lock(0,						// どこからロックしたいか
						0,						// どのくらい借りたいか(0はVertexBuffer全部)
						(void**)&temp_index,	// ロックするとVRAMの仮想アドレスがもらえる(実際に書き込んでいるわけではない)
						D3DLOCK_DISCARD);		// 0でもよい

	for (std::vector< WORD >::size_type i = 0; i < index_.size(); i++)
	{
		temp_index[i] = index_[i];

	}

	// アンロック
	index_buffer_->Unlock();
}