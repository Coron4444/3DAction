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

#include <SafeRelease/SafeRelease.h>
#include <ModelX/ModelXManager/ModelXManager.h>



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
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
	getpDrawOrderList()->setIsLighting(false);

	// Xモデル登録
	sky_dome_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void SkyDomeDraw::Uninit()
{
	SafeRelease::PlusRelease(&sky_dome_model_);
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void SkyDomeDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// 現在のメッシュの描画
	sky_dome_model_->getpMesh()->DrawSubset(mesh_index);
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

	return sky_dome_model_->getpMaterial(mesh_index);
}



//--------------------------------------------------
// +ディヒューズテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 SkyDomeDraw::getpDiffuseTexture(unsigned object_index,
												  unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->getpDiffuseTextureObject(mesh_index)->getpHandler();
}