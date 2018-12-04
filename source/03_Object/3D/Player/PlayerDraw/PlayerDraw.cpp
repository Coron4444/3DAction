//================================================================================
//
//    �v���C���[�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "PlayerDraw.h"

#include <ComponentManager/DrawManager/Shader/VertexShader/VertexShaderBumpMapping/VertexShaderBumpMapping.h>



//****************************************
// �萔��`
//****************************************
const std::string PlayerDraw::MODEL_NAME = "knight_low/knight_low.X";
const std::string PlayerDraw::TEXTURE_PATH = "resource/ModelX/";
const std::string PlayerDraw::NORMAL_TEXTURE_MODEL = "knight_low/knight_01.png";
const std::string PlayerDraw::NORMAL_TEXTURE_SWORD = "knight_low/sword_01.png";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void PlayerDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_BUMP_MAPPING);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_BUMP_MAPPING);

	// X���f���o�^
	player_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);

	// ���_�錾�p���b�V���X�V
	VertexShaderBumpMapping::UpdateMeshDeclaration(player_model_);

	// �@���}�b�v�̃��[�h
	normal_texture_[0] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_MODEL, &TEXTURE_PATH);
	normal_texture_[1] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_SWORD, &TEXTURE_PATH);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void PlayerDraw::Uninit()
{
	
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void PlayerDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	// ���݂̃��b�V���̕`��
	player_model_->GetMesh()->DrawSubset(mesh_index);
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned PlayerDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return player_model_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* PlayerDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* PlayerDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return player_model_->GetMaterial(mesh_index);
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::getpDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return player_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}



//--------------------------------------------------
// +�@���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::getpNormalTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return normal_texture_[mesh_index]->GetHandler();
}