//================================================================================
//
//    スカイドーム描画クラス
//    Author : Araki Kai                                作成日 : 2018/05/15
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "SkyDomeDraw.h"

#include <Renderer/Renderer.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string SkyDomeDraw::MODEL_NAME = "SkyDome/SkyDome.x";



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

void SkyDomeDraw::Init()
{
	// オーダーリスト設定
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::OPACITY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// Xモデル登録
	sky_dome_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void SkyDomeDraw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void SkyDomeDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(SkyDomeDraw.cpp)", "Error", MB_OK);
		return;
	}

	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 現在のメッシュの描画
	sky_dome_model_->GetMesh()->DrawSubset(mesh_index);

	device->SetRenderState(D3DRS_LIGHTING, TRUE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 行列取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const MATRIX* SkyDomeDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	// メッシュ数の取得
	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ メッシュ数取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned SkyDomeDraw::GetMeshNum()
{
	return sky_dome_model_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ マテリアルの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* SkyDomeDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->GetMaterial(mesh_index);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デカールテクスチャ情報を取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 SkyDomeDraw::GetDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}