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
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// ダウンキャスト
	enemy_ = (Enemy*)GetGameObject();
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
// +行列取得関数
//--------------------------------------------------
const MATRIX* EnemyDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	return enemy_->GetTransform()->GetWorldMatrix();
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned EnemyDraw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;

	return enemy_->cube_polygon_->GetMeshNum();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* EnemyDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return enemy_->cube_polygon_->GetMaterial();
}