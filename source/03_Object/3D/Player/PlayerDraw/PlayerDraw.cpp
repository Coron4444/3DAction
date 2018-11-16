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

//#include <ComponentManager/DrawManager/Shader/TestShaderObject/TestShaderObject.h>



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
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::OPACITY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// X���f���o�^
	player_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);

	// ���_�錾�p���b�V���X�V
	//TestShaderObject::UpdateMeshDeclaration(player_model_);

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
// +�s��擾�֐�
//--------------------------------------------------
const MATRIX* PlayerDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned PlayerDraw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;

	return player_model_->GetMeshNum();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* PlayerDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return player_model_->GetMaterial(mesh_index);
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::GetDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return player_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}



//--------------------------------------------------
// +�@���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::GetNormalTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return normal_texture_[mesh_index]->GetHandler();
}