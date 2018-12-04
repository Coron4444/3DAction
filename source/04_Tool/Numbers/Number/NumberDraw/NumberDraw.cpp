//================================================================================
//
//    数字描画クラス
//    Author : Araki Kai                                作成日 : 2018/06/19
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include <assert.h>

#include "NumberDraw.h"

#include <ResourceManager\ResourceManager.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void NumberDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// ダウンキャスト
	number_ = (Number*)getpGameObject();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void NumberDraw::Uninit()
{

}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void NumberDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	number_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned NumberDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;
	return number_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* NumberDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* NumberDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return number_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 NumberDraw::getpDecaleTexture(unsigned object_index,
												 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return number_->decale_texture_->GetHandler();
}