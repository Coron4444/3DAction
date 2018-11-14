//================================================================================
//
//    プレイヤー描画クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "StencilShadowTestDraw.h"

#include <main.h>

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string StencilShadowTestDraw::MODEL_NAME   = "knight_low/knight_low.X";//"kyouryuu/kyouryuu.x";//"BlockSphere/BlockSphere.x";
const std::string StencilShadowTestDraw::TEXTURE_PATH = "resource/ModelX/";
const std::string StencilShadowTestDraw::NORMAL_TEXTURE_NAME01 = "knight_low/knight_01.png";
const std::string StencilShadowTestDraw::NORMAL_TEXTURE_NAME02 = "knight_low/sword_01.png";



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

void StencilShadowTestDraw::Init()
{
	// オーダーリスト設定
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// Xモデル登録
	player_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);
	GetGameObject()->GetTransform()->GetPosition()->y += -1.0f;
	GetGameObject()->GetTransform()->UpdateWorldMatrixSRT();


	// プレーンポリゴン作成
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->SetColor(XColor4(0.0f, 0.0f, 0.0f, 1.0f));
	temp_transform_.GetScale()->x = SCREEN_WIDTH;
	temp_transform_.GetScale()->y = SCREEN_HEIGHT;
	temp_transform_.UpdateWorldMatrixSRT();

	// 法線マップのロード
	normal_texture_[0] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_NAME01, &TEXTURE_PATH);
	normal_texture_[1] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_NAME02, &TEXTURE_PATH);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StencilShadowTestDraw::Uninit()
{
	// 各種開放
	SafeRelease::Normal(&plane_polygon_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StencilShadowTestDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	LPDIRECT3DDEVICE9 device;
	Renderer::GetInstance()->GetDevice(&device);
	if (object_index == 0)
	{
		device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		device->SetRenderState(D3DRS_STENCILREF, 1);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// 現在のメッシュの描画
		player_model_->GetMesh()->DrawSubset(mesh_index);
	}
	else if (object_index == 1)
	{
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		// 現在のメッシュの描画
		player_model_->GetMesh()->DrawSubset(mesh_index);
	}
	else
	{
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		
		// ポリゴン描画
		plane_polygon_->Draw();
		
		device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 行列取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const MATRIX* StencilShadowTestDraw::GetMatrix(unsigned object_index)
{
	if (object_index == 2)
	{
		return temp_transform_.GetWorldMatrix();
	}
	
	// メッシュ数の取得
	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ メッシュ数取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned StencilShadowTestDraw::GetMeshNum(unsigned object_index)
{
	if (object_index == 2) return 1;

	return player_model_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ マテリアルの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* StencilShadowTestDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	if (object_index == 2) return nullptr;

	object_index = object_index;

	return player_model_->GetMaterial(mesh_index);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デカールテクスチャ情報を取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 StencilShadowTestDraw::GetDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	if (object_index == 2) return nullptr;

	return player_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ノーマルテクスチャ情報を取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 StencilShadowTestDraw::GetNormalTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	if (object_index == 2) return nullptr;

	return normal_texture_[mesh_index]->GetHandler();
}