//================================================================================
//
//    チュートリアルロゴ02描画クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "TutorialLogo02Draw.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string TutorialLogo02Draw::TEXTURE_NAME = "UI/Tutorial02.png";
const float TutorialLogo02Draw::SCALE = 1.25f;



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

void TutorialLogo02Draw::Init()
{
	// ステートの変更
	SetState(DrawComponent::State::FIXED_2D);

	// TutorialLogo02にダウンキャスト
	title_logo_ = (TutorialLogo02*)GetGameObjectOrigin();

	// テクスチャの登録
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);
	
	// 拡縮
	title_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth() * SCALE;
	title_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * (SCALE + 0.2f);

	// 行列更新
	title_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo02Draw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo02Draw::Draw(unsigned mesh_index)
{
	mesh_index = mesh_index;

	title_logo_->plane_polygon_->Draw();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ メッシュ数取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned TutorialLogo02Draw::GetMeshNum()
{
	return title_logo_->plane_polygon_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ マテリアルの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* TutorialLogo02Draw::GetMaterial(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return title_logo_->plane_polygon_->GetMaterial();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デカールテクスチャ情報を取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 TutorialLogo02Draw::GetDecaleTexture(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}