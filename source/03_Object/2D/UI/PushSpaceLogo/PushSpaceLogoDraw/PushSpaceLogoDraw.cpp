//================================================================================
//
//    プッシュスペースロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "PushSpaceLogoDraw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// 定数定義
//****************************************
const std::string PushSpaceLogoDraw::TEXTURE_NAME = "UI/PushSpace_Rogo.png";
const float PushSpaceLogoDraw::SCALE = 0.5f;



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void PushSpaceLogoDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// ダウンキャスト
	push_space_logo_ = (PushSpaceLogo*)getpGameObject();

	// テクスチャの登録
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);
	
	// 拡縮&移動
	push_space_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth()  * SCALE;
	push_space_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * SCALE;
	push_space_logo_->GetTransform()->GetPosition()->y += -300.0f;
	push_space_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void PushSpaceLogoDraw::Uninit()
{
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void PushSpaceLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	push_space_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned PushSpaceLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return push_space_logo_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* PushSpaceLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	// メッシュ数の取得
	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* PushSpaceLogoDraw::getpMaterial(unsigned object_index, 
											  unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return push_space_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PushSpaceLogoDraw::getpDecaleTexture(unsigned object_index,
												   unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}