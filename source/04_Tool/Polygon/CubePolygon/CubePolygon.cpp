//================================================================================
//
//    キューブクラス
//    Author : Araki Kai                                作成日 : 2017/10/16
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "CubePolygon.h"
#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const int   CubePolygon::PRIMITIVE_NUM = 12;



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

CubePolygon::CubePolygon(XColor4 color)
	: vertex_buffer_(nullptr),
	index_buffer_(nullptr),
	device_(nullptr)
{
	CreateVertex((Color4)color);
	CreateIndex();

	CreateMaterial();

	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(CubePolygon.cpp)", "Error", MB_OK);
		return;
	}
	AccessVRAM();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

CubePolygon::~CubePolygon()
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

void CubePolygon::SetColor(XColor4 color)
{
	// 頂点情報の変更
	for (std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		vertex_[i].color_ = (Color4)color;
	}

	RegistrationVertex();

	// マテリアルの変更
	material_.Diffuse = color;
	material_.Ambient = color;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CubePolygon::Draw()
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

	device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
								 0,						// セットストリームからどれくらいずれているか
								 0,						// インデックスで一番小さい値
								 (UINT)vertex_.size(),	// 頂点数
								 0,						// スタートインデックス番号
								 PRIMITIVE_NUM);		// プリミティブ数
}



//--------------------------------------------------------------------------------
//
// [ 頂点作成関数 ]
//
//--------------------------------------------------------------------------------

void CubePolygon::CreateVertex(Color4 color)
{
	// 正面
	vertex_.push_back({Vec3(-0.5f,  0.5f, -0.5f), Vec3(0.0f,  0.0f, -1.0f), color, Vec2(0.0f,  0.0f)});
	vertex_.push_back({Vec3(0.5f,  0.5f, -0.5f), Vec3(0.0f,  0.0f, -1.0f), color, Vec2(0.25f, 0.0f)});
	vertex_.push_back({Vec3(-0.5f, -0.5f, -0.5f), Vec3(0.0f,  0.0f, -1.0f), color, Vec2(0.0f,  0.5f)});
	vertex_.push_back({Vec3(0.5f, -0.5f, -0.5f), Vec3(0.0f,  0.0f, -1.0f), color, Vec2(0.25f, 0.5f)});

	// 右面			  
	vertex_.push_back({Vec3(0.5f,  0.5f, -0.5f), Vec3(1.0f, 0.0f, 0.0f), color, Vec2(0.25f, 0.0f)});
	vertex_.push_back({Vec3(0.5f,  0.5f,  0.5f), Vec3(1.0f, 0.0f, 0.0f), color, Vec2(0.5f,  0.0f)});
	vertex_.push_back({Vec3(0.5f, -0.5f, -0.5f), Vec3(1.0f, 0.0f, 0.0f), color, Vec2(0.25f, 0.5f)});
	vertex_.push_back({Vec3(0.5f, -0.5f,  0.5f), Vec3(1.0f, 0.0f, 0.0f), color, Vec2(0.5f,  0.5f)});

	// 背面			  
	vertex_.push_back({Vec3(0.5f,  0.5f, 0.5f), Vec3(0.0f, 0.0f, 1.0f), color, Vec2(0.5f,  0.0f)});
	vertex_.push_back({Vec3(-0.5f,  0.5f, 0.5f), Vec3(0.0f, 0.0f, 1.0f), color, Vec2(0.75f, 0.0f)});
	vertex_.push_back({Vec3(0.5f, -0.5f, 0.5f), Vec3(0.0f, 0.0f, 1.0f), color, Vec2(0.5f,  0.5f)});
	vertex_.push_back({Vec3(-0.5f, -0.5f, 0.5f), Vec3(0.0f, 0.0f, 1.0f), color, Vec2(0.75f, 0.5f)});

	// 左面			  
	vertex_.push_back({Vec3(-0.5f,  0.5f,  0.5f), Vec3(-1.0f, 0.0f, 0.0f), color, Vec2(0.75f, 0.0f)});
	vertex_.push_back({Vec3(-0.5f,  0.5f, -0.5f), Vec3(-1.0f, 0.0f, 0.0f), color, Vec2(1.0f,  0.0f)});
	vertex_.push_back({Vec3(-0.5f, -0.5f,  0.5f), Vec3(-1.0f, 0.0f, 0.0f), color, Vec2(0.75f, 0.5f)});
	vertex_.push_back({Vec3(-0.5f, -0.5f, -0.5f), Vec3(-1.0f, 0.0f, 0.0f), color, Vec2(1.0f,  0.5f)});

	// 上面			  
	vertex_.push_back({Vec3(-0.5f, 0.5f,  0.5f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(0.0f,  0.5f)});
	vertex_.push_back({Vec3(0.5f, 0.5f,  0.5f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(0.25f, 0.5f)});
	vertex_.push_back({Vec3(-0.5f, 0.5f, -0.5f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(0.0f,  1.0f)});
	vertex_.push_back({Vec3(0.5f, 0.5f, -0.5f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(0.25f, 1.0f)});

	// 下面			  
	vertex_.push_back({Vec3(-0.5f, -0.5f, -0.5f), Vec3(0.0f, -1.0f, 0.0f), color, Vec2(0.25f, 0.5f)});
	vertex_.push_back({Vec3(0.5f, -0.5f, -0.5f), Vec3(0.0f, -1.0f, 0.0f), color, Vec2(0.5f,  0.5f)});
	vertex_.push_back({Vec3(-0.5f, -0.5f,  0.5f), Vec3(0.0f, -1.0f, 0.0f), color, Vec2(0.25f, 1.0f)});
	vertex_.push_back({Vec3(0.5f, -0.5f,  0.5f), Vec3(0.0f, -1.0f, 0.0f), color, Vec2(0.5f,  1.0f)});
}



//--------------------------------------------------------------------------------
//
// [ インデックス作成関数 ]
//
//--------------------------------------------------------------------------------

void CubePolygon::CreateIndex()
{
	std::vector< WORD > temp_index{
									// 正面
									0, 1, 2,
									2, 1, 3,

									// 背面
									4, 5, 6,
									6, 5, 7,

									// 右面
									8,  9, 10,
									10, 9, 11,

									// 左面
									12, 13, 14,
									14, 13, 15,

									//上面
									16, 17, 18,
									18, 17, 19,

									// 下面
									20, 21, 22,
									22, 21, 23
	};
	index_ = temp_index;
}



//--------------------------------------------------------------------------------
//
// [ マテリアル作成関数 ]
//
//--------------------------------------------------------------------------------

void CubePolygon::CreateMaterial()
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

void CubePolygon::AccessVRAM()
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
	hr = device_->CreateIndexBuffer(sizeof(WORD) * (int)index_.size(),	// 借りたいbafの量(バイト)、つまり1頂点の容量×必要頂点数
								   D3DUSAGE_WRITEONLY,					// 使用用途(今回は書き込みのみ、GPUが早く動くが書き込んだデータを読んではダメ(値が不定))
								   D3DFMT_INDEX16,						// 頂点フォーマット(WORD型だから16、DWORD型なら32)
								   D3DPOOL_MANAGED,					// 頂点バッファの管理方法( MANAGEDは管理はDirect3Dにお任せという意味 )
								   &index_buffer_,						// 管理者の居場所のメモ帳(ポインタのポインタ)(全てはこれの値を知るための作業)
								   NULL);								// なぞ？

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

void CubePolygon::RegistrationVertex()
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

void CubePolygon::RegistrationIndex()
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