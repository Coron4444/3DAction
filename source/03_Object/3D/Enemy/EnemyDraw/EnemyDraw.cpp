//================================================================================
//
//    敵描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "EnemyDraw.h"



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void EnemyDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// ダウンキャスト
	enemy_ = (Enemy*)getpGameObject();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void EnemyDraw::Uninit()
{
	
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void EnemyDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	
	// キューブ描画
	enemy_->cube_polygon_->Draw();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned EnemyDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return enemy_->cube_polygon_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* EnemyDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return enemy_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* EnemyDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return enemy_->cube_polygon_->GetMaterial();
}