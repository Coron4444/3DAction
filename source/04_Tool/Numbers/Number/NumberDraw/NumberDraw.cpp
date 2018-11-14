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
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// ダウンキャスト
	number_ = (Number*)GetGameObject();
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
// +行列取得関数
//--------------------------------------------------
const MATRIX* NumberDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned NumberDraw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;
	return number_->plane_polygon_->GetMeshNum();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* NumberDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return number_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 NumberDraw::GetDecaleTexture(unsigned object_index, 
												unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return number_->decale_texture_->GetHandler();
}