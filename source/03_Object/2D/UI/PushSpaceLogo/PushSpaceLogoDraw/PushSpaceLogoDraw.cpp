//================================================================================
//
//    プッシュスペースロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "PushSpaceLogoDraw.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string PushSpaceLogoDraw::TEXTURE_NAME = "UI/PushSpace_Rogo.png";
const float PushSpaceLogoDraw::SCALE = 0.5f;



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

void PushSpaceLogoDraw::Init()
{
	// ステートの変更
	SetState(DrawComponent::State::FIXED_2D);

	// TitleLogoにダウンキャスト
	push_space_logo_ = (PushSpaceLogo*)GetGameObjectOrigin();

	// テクスチャの登録
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);
	
	// 拡縮
	push_space_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth()  * SCALE;
	push_space_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * SCALE;

	// 移動
	push_space_logo_->GetTransform()->GetPosition()->y += -300.0f;

	// 行列更新
	push_space_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PushSpaceLogoDraw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PushSpaceLogoDraw::Draw(unsigned mesh_index)
{
	mesh_index = mesh_index;

	push_space_logo_->plane_polygon_->Draw();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ メッシュ数取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned PushSpaceLogoDraw::GetMeshNum()
{
	return push_space_logo_->plane_polygon_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ マテリアルの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* PushSpaceLogoDraw::GetMaterial(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return push_space_logo_->plane_polygon_->GetMaterial();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デカールテクスチャ情報を取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 PushSpaceLogoDraw::GetDecaleTexture(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}