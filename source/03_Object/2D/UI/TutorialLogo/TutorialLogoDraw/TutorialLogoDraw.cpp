//================================================================================
//
//    チュートリアルロゴ01描画クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "TutorialLogoDraw.h"

#include <main.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// 定数定義
//****************************************
const std::string TutorialLogoDraw::TEXTURE_NAME[TEXTURE_NUM] = {"UI/Tutorial01.png",
																 "UI/Tutorial02.png"};



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void TutorialLogoDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
	getpDrawOrderList()->SetLayerNum(0);

	// ダウンキャスト
	tutorial_logo_ = (TutorialLogo*)getpGameObject();

	// 平面ポリゴン作成
	plane_polygon_ = new PlanePolygon();

	// テクスチャの登録
	for (unsigned i = 0; i < TEXTURE_NUM; i++)
	{
		decale_texture_[i] = TextureManager::AddUniqueData(&TEXTURE_NAME[i]);
	}

	// 拡縮
	tutorial_logo_->GetTransform()->GetScale()->x = SCREEN_WIDTH;
	tutorial_logo_->GetTransform()->GetScale()->y = SCREEN_HEIGHT;
	tutorial_logo_->GetTransform()->UpdateWorldMatrixSRT();

	// テクスチャインデックス
	texture_index_ = 0;
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void TutorialLogoDraw::Uninit()
{
	SafeRelease::Normal(&plane_polygon_);
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void TutorialLogoDraw::Update()
{
	// テクスチャ番号変更
	texture_index_ = tutorial_logo_->GetLogoNum();
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void TutorialLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	plane_polygon_->Draw();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned TutorialLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* TutorialLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return tutorial_logo_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* TutorialLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 TutorialLogoDraw::getpDecaleTexture(unsigned object_index,
														unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_[texture_index_]->GetHandler();
}