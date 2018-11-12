//================================================================================
//
//    数字描画クラス
//    Author : Araki Kai                                作成日 : 2018/06/19
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "NumberDraw.h"

#include <assert.h>

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <ResourceManager\ResourceManager.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



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

void NumberDraw::Init()
{
	// ステートの変更
	SetState(DrawBase::State::FIXED_2D);

	// Numberにダウンキャスト
	number_ = (Number*)GetGameObject();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void NumberDraw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void NumberDraw::Draw(unsigned mesh_index)
{
	mesh_index = mesh_index;

	number_->plane_polygon_->Draw();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ メッシュ数取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned NumberDraw::GetMeshNum()
{
	return number_->plane_polygon_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ マテリアルの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* NumberDraw::GetMaterial(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return number_->plane_polygon_->GetMaterial();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デカールテクスチャ情報を取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 NumberDraw::GetDecaleTexture(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return number_->decale_texture_->GetHandler();
}