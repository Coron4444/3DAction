//================================================================================
//
//    ゴール描画クラス
//    Author : Araki Kai                                作成日 : 2018/11/28
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "GoalDraw.h"

#include <ResourceManager/ResourceManager.h>



//****************************************
// 定数定義
//****************************************
const std::string GoalDraw::EFFECT = "CoinEffect/CoinEffect.efk";



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void GoalDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// ダウンキャスト
	goal_ = (Goal*)getpGameObject();

	// キューブポリゴンの生成
	cube_polygon_ = new CubePolygon();
	cube_polygon_->SetColor(XColor4(0.5f, 1.0f, 1.0f, 1.0f));

	// エフェクトの読み込み
	EffekseerManager::AddUniqueData(&EFFECT);
	effekseer_object_ = EffekseerManager::GetReferenceEffekseerObject(&EFFECT);
	effekseer_object_->SetColor(255, 255, 255, 255);
	effekseer_object_->SetRepeat(true);
	effekseer_object_->Play();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void GoalDraw::Uninit()
{
	// 各種消去
	SafeRelease::Normal(&cube_polygon_);

	effekseer_object_->Stop();
	effekseer_object_->SetRepeat(false);
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void GoalDraw::Update()
{
	// エフェクト座標更新
	*effekseer_object_->GetTransform()->GetPosition() = *goal_->GetTransform()->GetPosition();
	effekseer_object_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void GoalDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	
	// キューブ描画
	cube_polygon_->Draw();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned GoalDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return cube_polygon_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* GoalDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return goal_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* GoalDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return cube_polygon_->GetMaterial();
}