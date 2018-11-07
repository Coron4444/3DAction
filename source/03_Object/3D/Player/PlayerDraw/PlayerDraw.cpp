//================================================================================
//
//    �v���C���[�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "PlayerDraw.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <ComponentManager\DrawComponentManager\Shader\TestShaderObject\TestShaderObject.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const std::string PlayerDraw::MODEL_NAME   = "knight_low/knight_low.X";//"kyouryuu/kyouryuu.x";//"BlockSphere/BlockSphere.x";
const std::string PlayerDraw::TEXTURE_PATH = "resource/ModelX/";
const std::string PlayerDraw::NORMAL_TEXTURE_NAME01 = "knight_low/knight_01.png";
const std::string PlayerDraw::NORMAL_TEXTURE_NAME02 = "knight_low/sword_01.png";



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerDraw::Init()
{
	// �X�e�[�g�̕ύX
	SetState(DrawComponent::State::TEST_SHADER);

	// X���f���o�^
	player_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);

	// ���_�錾�p���b�V���X�V
	TestShaderObject::UpdateMeshDeclaration(player_model_);

	// �@���}�b�v�̃��[�h
	normal_texture_[0] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_NAME01, &TEXTURE_PATH);
	normal_texture_[1] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_NAME02, &TEXTURE_PATH);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerDraw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerDraw::Draw(unsigned mesh_index)
{
	// ���݂̃��b�V���̕`��
	player_model_->GetMesh()->DrawSubset(mesh_index);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���b�V�����擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned PlayerDraw::GetMeshNum()
{
	return player_model_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �}�e���A���̎擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* PlayerDraw::GetMaterial(unsigned mesh_index)
{
	return player_model_->GetMaterial(mesh_index);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�J�[���e�N�X�`�������擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 PlayerDraw::GetDecaleTexture(unsigned mesh_index)
{
	return player_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �m�[�}���e�N�X�`�������擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 PlayerDraw::GetNormalTexture(unsigned mesh_index)
{
	return normal_texture_[mesh_index]->GetHandler();
}