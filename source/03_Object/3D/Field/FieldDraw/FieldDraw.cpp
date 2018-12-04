//================================================================================
//
//    地面描画クラス
//    Author : Araki Kai                                作成日 : 2018/05/15
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "FieldDraw.h"

#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>



//****************************************
// 定数定義
//****************************************
const std::string FieldDraw::TEXTURE_NAME = "Field.png";



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void FieldDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// テクスチャの登録
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);

	// ダウンキャスト
	field_ = (Field*)getpGameObject();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void FieldDraw::Uninit()
{

}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void FieldDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	field_->mesh_plane_polygon_->Draw();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned FieldDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return field_->mesh_plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* FieldDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return field_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* FieldDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return field_->mesh_plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 FieldDraw::getpDecaleTexture(unsigned object_index,
												unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}