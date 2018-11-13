//================================================================================
//
//    地面描画クラス
//    Author : Araki Kai                                作成日 : 2018/05/15
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "FieldDraw.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string FieldDraw::TEXTURE_NAME = "Field.png";



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FieldDraw::Init()
{
	// オーダーリスト設定
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::OPACITY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// テクスチャの登録
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FieldDraw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FieldDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// 地面にダウンキャスト
	Field* field = (Field*)GetGameObject();

	field->mesh_plane_polygon_->Draw();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 行列取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const MATRIX* FieldDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	// メッシュ数の取得
	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ メッシュ数取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned FieldDraw::GetMeshNum()
{
	// 地面にダウンキャスト
	Field* field = (Field*)GetGameObject();

	return field->mesh_plane_polygon_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ マテリアルの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* FieldDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// 地面にダウンキャスト
	Field* field = (Field*)GetGameObject();

	return field->mesh_plane_polygon_->GetMaterial();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デカールテクスチャ情報を取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 FieldDraw::GetDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}