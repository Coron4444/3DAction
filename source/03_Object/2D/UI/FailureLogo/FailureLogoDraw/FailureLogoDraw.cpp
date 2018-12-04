//================================================================================
//
//    失敗ロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "FailureLogoDraw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// 定数定義
//****************************************
const std::string FailureLogoDraw::TEXTURE_NAME = "UI/GameOver.png";

const float FailureLogoDraw::SCALE = 1.25f;



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void FailureLogoDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);


	// ダウンキャスト
	failure_logo_ = (FailureLogo*)getpGameObject();

	// テクスチャの登録
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);

	// 拡縮&移動
	failure_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth() * SCALE;
	failure_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * (SCALE + 0.2f);
	*failure_logo_->GetTransform()->GetPosition() = Vec3(0.0f, 0.0f, 0.0f);
	failure_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void FailureLogoDraw::Uninit()
{
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void FailureLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	failure_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned FailureLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return failure_logo_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* FailureLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	// メッシュ数の取得
	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* FailureLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return failure_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 FailureLogoDraw::getpDecaleTexture(unsigned object_index,
													  unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}