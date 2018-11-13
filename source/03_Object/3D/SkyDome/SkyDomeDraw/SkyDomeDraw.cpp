//================================================================================
//
//    �X�J�C�h�[���`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/15
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "SkyDomeDraw.h"

#include <Renderer/Renderer.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const std::string SkyDomeDraw::MODEL_NAME = "SkyDome/SkyDome.x";



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

void SkyDomeDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::OPACITY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// X���f���o�^
	sky_dome_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void SkyDomeDraw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void SkyDomeDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(SkyDomeDraw.cpp)", "Error", MB_OK);
		return;
	}

	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���݂̃��b�V���̕`��
	sky_dome_model_->GetMesh()->DrawSubset(mesh_index);

	device->SetRenderState(D3DRS_LIGHTING, TRUE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �s��擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const MATRIX* SkyDomeDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	// ���b�V�����̎擾
	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���b�V�����擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned SkyDomeDraw::GetMeshNum()
{
	return sky_dome_model_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �}�e���A���̎擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* SkyDomeDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->GetMaterial(mesh_index);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�J�[���e�N�X�`�������擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 SkyDomeDraw::GetDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}