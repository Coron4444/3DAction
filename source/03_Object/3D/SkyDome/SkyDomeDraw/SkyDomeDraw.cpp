//================================================================================
//
//    �X�J�C�h�[���`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/15
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "SkyDomeDraw.h"



//****************************************
// �萔��`
//****************************************
const std::string SkyDomeDraw::MODEL_NAME = "SkyDome/SkyDome.x";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void SkyDomeDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::OPACITY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
	GetDrawOrderList()->SetIsLighting(false);

	// X���f���o�^
	sky_dome_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void SkyDomeDraw::Uninit()
{
	
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void SkyDomeDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	// ���݂̃��b�V���̕`��
	sky_dome_model_->GetMesh()->DrawSubset(mesh_index);
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
const MATRIX* SkyDomeDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned SkyDomeDraw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;

	return sky_dome_model_->GetMeshNum();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* SkyDomeDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->GetMaterial(mesh_index);
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 SkyDomeDraw::GetDecaleTexture(unsigned object_index, 
												 unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}