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
#include <SafeRelease/SafeRelease.h>
#include <ModelX/ModelXManager/ModelXManager.h>
#include <MdBin/MdBinManager/MdBinManager.h>



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
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	//getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::VERTEX_BUMP_MAPPING);
	//getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::PIXEL_BUMP_MAPPING);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::ANIMATED_DEFAULT);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::DEFAULT);

	// Xモデル登録
	player_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);

	// 頂点宣言用メッシュ更新
	VertexShaderBumpMapping::UpdateMeshDeclaration(player_model_);

	// 法線マップのロード
	normal_texture_[0] = TextureManager::getpInstance()->getpObject(&NORMAL_TEXTURE_MODEL, &TEXTURE_PATH);
	normal_texture_[1] = TextureManager::getpInstance()->getpObject(&NORMAL_TEXTURE_SWORD, &TEXTURE_PATH);

	// テスト用オブジェクト
	//std::string test = "neko_anime_hasiru3/neko_anime_hasiru3.mdbin_l";
	std::string test = "unitychan_Jump/unitychan_Jump.mdbin_l";
	//std::string test = "Unarmed Equip Over Shoulder/Unarmed Equip Over Shoulder.mdbin_l";
	//std::string test = "unitychan/unitychan.mdbin_l";
	//std::string test = "goblin-sapper/goblin-sapper.mdbin_l";
	//std::string test = "humanoid/humanoid.mdbin_l";
	test_object_ = MdBinManager::getpInstance()->getpObject(&test);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void PlayerDraw::Uninit()
{
	SafeRelease::PlusRelease(&player_model_);

	for (int i = 0; i < 2; i++)
	{

		SafeRelease::PlusRelease(&normal_texture_[i]);
	}

	//テスト用
	SafeRelease::PlusRelease(&test_object_);
}

void PlayerDraw::Update()
{
	frame_ = ++count_ % 30;
}


//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void PlayerDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	// 現在のメッシュの描画
	//player_model_->getpMesh()->DrawSubset(mesh_index);
	
	test_object_->Draw(mesh_index);
}



//--------------------------------------------------
// +メッシュ数取得関数
//--------------------------------------------------
unsigned PlayerDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	//return player_model_->getMeshNum();
	
	return test_object_->getMeshNum();
}



unsigned PlayerDraw::getBoneNum(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return test_object_->getpMesh(mesh_index)->getBoneArraySize();
}



//--------------------------------------------------
// +行列取得関数
//--------------------------------------------------
MATRIX* PlayerDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



MATRIX* PlayerDraw::getpBoneMatrix(unsigned object_index, unsigned mesh_index,
								   unsigned bone_index)
{
	object_index = object_index;

	return test_object_->getpMesh(mesh_index)->getpBone(bone_index)
		->getpAnimationMatrix(0);// frame_);
}



//--------------------------------------------------
// +マテリアル取得関数
//--------------------------------------------------
D3DMATERIAL9* PlayerDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	//return player_model_->getpMaterial(mesh_index);

	return test_object_->getpMaterial(mesh_index);
}



//--------------------------------------------------
// +ディヒューズテクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::getpDiffuseTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	//return player_model_->getpDiffuseTextureObject(mesh_index)->getpHandler();

	return test_object_->getpDiffuseTextureHandler(mesh_index);
}



//--------------------------------------------------
// +法線テクスチャ取得関数
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::getpNormalTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return normal_texture_[mesh_index]->getpHandler();
}