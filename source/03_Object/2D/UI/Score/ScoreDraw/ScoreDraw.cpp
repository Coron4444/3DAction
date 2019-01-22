//================================================================================
//
//    スコア描画クラス
//    Author : Araki Kai                                作成日 : 2018/06/20
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "ScoreDraw.h"



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void ScoreDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void ScoreDraw::Uninit()
{
	
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void ScoreDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* ScoreDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	// メッシュ数の取得
	return getpGameObject()->GetTransform()->getpWorldMatrix();
}