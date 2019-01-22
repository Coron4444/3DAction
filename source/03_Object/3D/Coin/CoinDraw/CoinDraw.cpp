//================================================================================
//!	@file	 CoinDraw.cpp
//!	@brief	 コイン描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "CoinDraw.h"

#include <SafeRelease/SafeRelease.h>
#include <Texture/TextureManager/TextureManager.h>



//****************************************
// 定数定義
//****************************************
const std::string CoinDraw::diffuse_TEXTURE = "Coin.png";



//****************************************
// 関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void CoinDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
	getpDrawOrderList()->setIsBillboard(true);

	// ダウンキャスト
	coin_ = (Coin*)getpGameObject();

	// ディヒューズテクスチャの読み込み
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&diffuse_TEXTURE);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void CoinDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void CoinDraw::Update()
{
	if (coin_->getCount() > 0)
	{
		coin_->GetPolygon()->SetColor(XColor4(1.0f, 0.0f, 0.0f, 1.0f));

		coin_->setCount(coin_->getCount() - 1);
	}
	else
	{
		coin_->GetPolygon()->SetColor(XColor4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void CoinDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// ポリゴン描画
	coin_->GetPolygon()->Draw();
}



//--------------------------------------------------
// +描画前設定関数
//--------------------------------------------------
void CoinDraw::SettingBeforeDrawing(Camera* camera, unsigned object_index)
{
	camera = camera;
	object_index = object_index;
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned CoinDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return coin_->GetPolygon()->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* CoinDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return coin_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* CoinDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return coin_->GetPolygon()->GetMaterial();
}



//--------------------------------------------------
// +ディヒューズテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CoinDraw::getpDiffuseTexture(unsigned object_index,
											   unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}