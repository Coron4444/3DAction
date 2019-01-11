//================================================================================
//!	@file	 PixelShaderBumpMapping.cpp
//!	@brief	 �o���v�}�b�s���O�s�N�Z���V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "PixelShaderBumpMapping.h"

#include <GameObjectManager/GameObjectManager.h>



//****************************************
// �萔��`
//****************************************
const char* PixelShaderBumpMapping::PATH = "resource/HLSL/Effect/PixelShader/BumpMapping.psh";



//****************************************
// �֐���`
//****************************************
void PixelShaderBumpMapping::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �V�F�[�_�[�̃R���p�C��
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderBumpMapping::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleasePixelShader();
}



void PixelShaderBumpMapping::CommonSetting(DrawBase* draw, Camera* camera, 
										   unsigned object_index)
{
	camera = camera;

	// ���C�g�������Z�b�g
	Vec4 light_position = (Vec4)*GameObjectManager::GetDrawManager()
		->GetDirectionalLightVector();
	light_position.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->getpMatrix(object_index));
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vec3*)&light_position, (Vec3*)&light_position);
	light_position.w = -0.7f;		// �����̔䗦
	GetConstantTable()->SetVector(GetDevice(),
								  "LAMBERT_DIFFUSE_LIGHT_VECTOR",
								  &light_position);
}



void PixelShaderBumpMapping::SpecificSetting(DrawBase* draw, Camera* camera,
											  unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	// �f�J�[���e�N�X�`���̐ݒ�
	int sampler_index = GetConstantTable()->GetSamplerIndex("DECALE_SAMPLER");
	GetDevice()->SetTexture(sampler_index, 
							draw->getpDecaleTexture(object_index, mesh_index));

	// �@���e�N�X�`���̐ݒ�
	sampler_index = GetConstantTable()->GetSamplerIndex("NORMAL_SAMPLER");
	GetDevice()->SetTexture(sampler_index, 
							draw->getpNormalTexture(object_index, mesh_index));
}