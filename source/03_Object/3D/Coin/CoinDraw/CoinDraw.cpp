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

#include <ResourceManager/ResourceManager.h>



//****************************************
// 定数定義
//****************************************
const std::string CoinDraw::DECALE_TEXTURE = "Coin.png";



//****************************************
// 関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void CoinDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
	getpDrawOrderList()->SetIsBillboard(true);

	// ダウンキャスト
	coin_ = (Coin*)getpGameObject();

	// デカールテクスチャの読み込み
	decale_texture_ = TextureManager::AddUniqueData(&DECALE_TEXTURE);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void CoinDraw::Uninit()
{
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
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CoinDraw::getpDecaleTexture(unsigned object_index,
											   unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}