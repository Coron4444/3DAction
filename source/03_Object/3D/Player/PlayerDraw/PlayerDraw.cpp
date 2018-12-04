//================================================================================
//
//    プレイヤー描画クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "PlayerDraw.h"

#include <ComponentManager/DrawManager/Shader/VertexShader/VertexShaderBumpMapping/VertexShaderBumpMapping.h>



//****************************************
// 定数定義
//****************************************
const std::string PlayerDraw::MODEL_NAME = "knight_low/knight_low.X";
const std::string PlayerDraw::TEXTURE_PATH = "resource/ModelX/";
const std::string PlayerDraw::NORMAL_TEXTURE_MODEL = "knight_low/knight_01.png";
const std::string PlayerDraw::NORMAL_TEXTURE_SWORD = "knight_low/sword_01.png";



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void PlayerDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_BUMP_MAPPING);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_BUMP_MAPPING);

	// Xモデル登録
	player_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);

	// 頂点宣言用メッシュ更新
	VertexShaderBumpMapping::UpdateMeshDeclaration(player_model_);

	// 法線マップのロード
	normal_texture_[0] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_MODEL, &TEXTURE_PATH);
	normal_texture_[1] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_SWORD, &TEXTURE_PATH);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void PlayerDraw::Uninit()
{
	
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void PlayerDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	// 現在のメッシュの描画
	player_model_->GetMesh()->DrawSubset(mesh_index);
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned PlayerDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return player_model_->getMeshNum();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* PlayerDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* PlayerDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return player_model_->GetMaterial(mesh_index);
}



//--------------------------------------------------
// +デカールテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::getpDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return player_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}



//--------------------------------------------------
// +法線テクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::getpNormalTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return normal_texture_[mesh_index]->GetHandler();
}