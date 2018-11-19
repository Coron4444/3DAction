//================================================================================
//
//    �o���v�}�b�s���O�s�N�Z���V�F�[�_�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/17
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "PixelShaderBumpMapping.h"

#include <GameObjectManager/GameObjectManager.h>



//****************************************
// �萔��`
//****************************************
const char* PixelShaderBumpMapping::PATH = "resource/HLSL/Effect/PixelShader/PixelShaderBumpMapping.psh";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void PixelShaderBumpMapping::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �V�F�[�_�[�̃R���p�C��
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void PixelShaderBumpMapping::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleasePixelShader();
}



//--------------------------------------------------
// +���ʐݒ�֐�
//--------------------------------------------------
void PixelShaderBumpMapping::CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index)
{
	// ���C�g�������Z�b�g
	Vec4 light_position = (Vec4)*GameObjectManager::GetDrawManager()
		->GetDirectionalLightVector();
	light_position.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->GetMatrix(object_index));
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vec3*)&light_position, (Vec3*)&light_position);
	light_position.w = -0.7f;		// �����̔䗦
	GetConstantTable()->SetVector(GetDevice(),
								  "LAMBERT_DIFFUSE_LIGHT_VECTOR",
								  &light_position);
}



//--------------------------------------------------
// +�ŗL�ݒ�֐�
//--------------------------------------------------
void PixelShaderBumpMapping::SpecificSetting(DrawBase* draw, Camera* camera,
											  unsigned object_index, unsigned mesh_index)
{
	// �f�J�[���e�N�X�`���̐ݒ�
	int sampler_index = GetConstantTable()->GetSamplerIndex("DECALE_SAMPLER");
	GetDevice()->SetTexture(sampler_index, 
							draw->GetDecaleTexture(object_index, mesh_index));

	// �@���e�N�X�`���̐ݒ�
	sampler_index = GetConstantTable()->GetSamplerIndex("NORMAL_SAMPLER");
	GetDevice()->SetTexture(sampler_index, 
							draw->GetNormalTexture(object_index, mesh_index));
}