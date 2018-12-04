//================================================================================
//
//    タイトルロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/03
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "TitleLogoDraw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// 定数定義
//****************************************
const std::string TitleLogoDraw::TEXTURE_NAME = "UI/Title.png";
const float TitleLogoDraw::SCALE = 1.25f;



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void TitleLogoDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// ダウンキャスト
	title_logo_ = (TitleLogo*)getpGameObject();

	// テクスチャの登録
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);
	
	// 拡縮
	title_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth() * SCALE;
	title_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * (SCALE + 0.2f);
	title_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void TitleLogoDraw::Uninit()
{
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void TitleLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	title_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned TitleLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return title_logo_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* TitleLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	// メッシュ数の取得
	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* TitleLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return title_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 TitleLogoDraw::getpDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}