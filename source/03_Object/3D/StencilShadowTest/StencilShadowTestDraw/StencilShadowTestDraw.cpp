//================================================================================
//
//    ステンシルシャドウ描画クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "StencilShadowTestDraw.h"

#include <main.h>

#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <ModelX/ModelXManager/ModelXManager.h>



//****************************************
// 定数定義
//****************************************
const std::string StencilShadowTestDraw::MODEL_NAME = "knight_low/knight_low.X";



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void StencilShadowTestDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// Xモデル登録
	player_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);
	getpGameObject()->GetTransform()->GetPosition()->y += -1.0f;
	getpGameObject()->GetTransform()->UpdateWorldMatrixSRT();

	// プレーンポリゴン作成
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->SetColor(XColor4(0.0f, 0.0f, 0.0f, 1.0f));
	plane_polygon_transform_.GetScale()->x = SCREEN_WIDTH;
	plane_polygon_transform_.GetScale()->y = SCREEN_HEIGHT;
	plane_polygon_transform_.UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void StencilShadowTestDraw::Uninit()
{
	// 各種開放
	SafeRelease::Normal(&plane_polygon_);
	SafeRelease::PlusRelease(&player_model_);
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void StencilShadowTestDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	if (object_index != 2)
	{
		player_model_->getpMesh()->DrawSubset(mesh_index);
	}
	else
	{	
		// ポリゴン描画
		plane_polygon_->Draw();
	}
}



//--------------------------------------------------
// +描画前設定関数
//--------------------------------------------------
void StencilShadowTestDraw::SettingBeforeDrawing(Camera* camera, unsigned object_index)
{
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	switch (object_index)
	{
		case 0: 
		{
			device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
			device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
			device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
			device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
			device->SetRenderState(D3DRS_STENCILREF, 1);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			break;
		}
		case 1:
		{
			device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			break;
		}
		case 2:
		{
			DrawBase::LimitedChangeCameraType(camera, Camera::Type::TWO_DIMENSIONAL);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
			device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
			break;
		}
	}
}



//--------------------------------------------------
// +描画後設定関数
//--------------------------------------------------
void StencilShadowTestDraw::SettingAfterDrawing(Camera* camera, unsigned object_index)
{
	if (object_index == 2)
	{
		LPDIRECT3DDEVICE9 device;
		Renderer::getpInstance()->getDevice(&device);
		DrawBase::RevivalCameraType(camera);
		device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}
}



//--------------------------------------------------
// +オブジェクト数取得関数
//--------------------------------------------------
unsigned StencilShadowTestDraw::getObjectNum()
{
	return 3;
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned StencilShadowTestDraw::getMeshNum(unsigned object_index)
{
	if (object_index == 2) return 1;

	return player_model_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* StencilShadowTestDraw::getpMatrix(unsigned object_index)
{
	if (object_index == 2)
	{
		return plane_polygon_transform_.getpWorldMatrix();
	}
	
	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* StencilShadowTestDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	if (object_index == 2) return nullptr;

	object_index = object_index;

	return player_model_->getpMaterial(mesh_index);
}



//--------------------------------------------------
// +ディヒューズテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 StencilShadowTestDraw::getpDiffuseTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	if (object_index == 2) return nullptr;

	return player_model_->getpDiffuseTextureObject(mesh_index)->getpHandler();
}