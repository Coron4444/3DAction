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
	// ステートの変更
	SetState(DrawComponent::State::FIXED_BILLBOARD_ALPHA);

	// ダウンキャスト
	coin_ = (Coin*)GetGameObjectOrigin();

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

void CoinDraw::Draw(unsigned mesh_index)
{
	mesh_index = mesh_index;

	*effekseer_object_->GetTransform()->GetPosition() = *GetGameObjectOrigin()->GetTransform()->GetPosition();
	effekseer_object_->GetTransform()->UpdateWorldMatrixSRT();

	// ポリゴン描画
	coin_->GetPolygon()->Draw();
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

D3DMATERIAL9* CoinDraw::GetMaterial(unsigned mesh_index)
{
	mesh_index = mesh_index;

	// メッシュ数の取得
	return coin_->GetPolygon()->GetMaterial();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デカールテクスチャの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 CoinDraw::GetDecaleTexture(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}