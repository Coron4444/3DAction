//================================================================================
//
//    失敗ロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "FailureLogoDraw.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string FailureLogoDraw::TEXTURE_NAME = "UI/GameOver.png";

const float FailureLogoDraw::SCALE = 1.25f;



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

void FailureLogoDraw::Init()
{
	// ステートの変更
	SetState(DrawComponent::State::FIXED_2D);

	// FailureLogoにダウンキャスト
	failure_logo_ = (FailureLogo*)GetGameObjectOrigin();

	// テクスチャの登録
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);

	// 拡縮
	failure_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth() * SCALE;
	failure_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * (SCALE + 0.2f);

	// 移動
	*failure_logo_->GetTransform()->GetPosition() = Vec3(0.0f, 0.0f, 0.0f);
	
	failure_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FailureLogoDraw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FailureLogoDraw::Draw(unsigned mesh_index)
{
	mesh_index = mesh_index;

	failure_logo_->plane_polygon_->Draw();
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ メッシュ数取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned FailureLogoDraw::GetMeshNum()
{
	return failure_logo_->plane_polygon_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ マテリアルの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* FailureLogoDraw::GetMaterial(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return failure_logo_->plane_polygon_->GetMaterial();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デカールテクスチャ情報を取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 FailureLogoDraw::GetDecaleTexture(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}