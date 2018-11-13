//================================================================================
//
//    コイン描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "CoinDraw.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string CoinDraw::DECALE_TEXTURE = "Coin.png";
const std::string CoinDraw::EFFECT = "CoinEffect/CoinEffect.efk";



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CoinDraw::Init()
{
	// オーダーリスト設定
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
	GetDrawOrderList()->SetIsBillboard(true);

	// ダウンキャスト
	coin_ = (Coin*)GetGameObject();

	// デカールテクスチャの読み込み
	decale_texture_ = TextureManager::AddUniqueData(&DECALE_TEXTURE);

	// エフェクトの読み込み
	EffekseerManager::AddUniqueData(&EFFECT);
	effekseer_object_ = EffekseerManager::GetReferenceEffekseerObject(&EFFECT);
	effekseer_object_->SetRepeat(true);
	effekseer_object_->Play();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CoinDraw::Uninit()
{
	effekseer_object_->Stop();
	effekseer_object_->SetRepeat(false);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CoinDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	*effekseer_object_->GetTransform()->GetPosition() = *GetGameObject()->GetTransform()->GetPosition();
	effekseer_object_->GetTransform()->UpdateWorldMatrixSRT();

	// ポリゴン描画
	coin_->GetPolygon()->Draw();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 行列取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const MATRIX* CoinDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	// メッシュ数の取得
	return coin_->GetTransform()->GetWorldMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ メッシュ数取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned CoinDraw::GetMeshNum()
{
	// メッシュ数の取得
	return coin_->GetPolygon()->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ マテリアルの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* CoinDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// メッシュ数の取得
	return coin_->GetPolygon()->GetMaterial();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デカールテクスチャの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 CoinDraw::GetDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}