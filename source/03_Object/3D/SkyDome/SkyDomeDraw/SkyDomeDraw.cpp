//================================================================================
//
//    スカイドーム描画クラス
//    Author : Araki Kai                                作成日 : 2018/05/15
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "SkyDomeDraw.h"



//****************************************
// 定数定義
//****************************************
const std::string SkyDomeDraw::MODEL_NAME = "SkyDome/SkyDome.x";



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void SkyDomeDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
	getpDrawOrderList()->SetIsLighting(false);

	// Xモデル登録
	sky_dome_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void SkyDomeDraw::Uninit()
{

}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void SkyDomeDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	// 現在のメッシュの描画
	sky_dome_model_->GetMesh()->DrawSubset(mesh_index);
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned SkyDomeDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return sky_dome_model_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* SkyDomeDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* SkyDomeDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->GetMaterial(mesh_index);
}



//--------------------------------------------------
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 SkyDomeDraw::getpDecaleTexture(unsigned object_index,
												  unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}