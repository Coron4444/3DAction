//================================================================================
//
//    クリアロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/06/19
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "ClearLogoDraw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string ClearLogoDraw::TEXTURE_NAME = "UI/Clear.png";
const float ClearLogoDraw::SCALE = 1.25f;



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void ClearLogoDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// ダウンキャスト
	clear_logo_ = (ClearLogo*)getpGameObject();

	// テクスチャの登録
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);

	// 拡縮&移動
	clear_logo_->GetTransform()->GetScale()->x = diffuse_texture_->getWidth() * SCALE;
	clear_logo_->GetTransform()->GetScale()->y = diffuse_texture_->getHeight() * (SCALE + 0.2f);
	*clear_logo_->GetTransform()->GetPosition() = Vec3(0.0f, 0.0f, 0.0f);
	clear_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void ClearLogoDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void ClearLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	clear_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned ClearLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return clear_logo_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* ClearLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* ClearLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return clear_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +ディヒューズテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 ClearLogoDraw::getpDiffuseTexture(unsigned object_index,
													unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}