//================================================================================
//
//    �V�F�[�_�[�}�l�[�W���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "ShaderManager.h"
#include "../Shader/ShaderBase/VertexShaderNull.h"
#include "../Shader/ShaderBase/PixelShaderNull.h"
#include "../Shader/VertexShader/VertexShaderFixed/VertexShaderFixed.h"
#include "../Shader/VertexShader/VertexShaderBumpMapping/VertexShaderBumpMapping.h"
#include "../Shader/PixelShader/PixelShaderBumpMapping/PixelShaderBumpMapping.h"

#include <Component/Base/DrawBase/DrawBase.h>

#include <SafeRelease/SafeRelease.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void ShaderManager::Init()
{
	InitVertexShaders();
	InitPixelShaders();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void ShaderManager::Uninit()
{
	UninitVertexShaders();
	UninitPixelShaders();
}



//--------------------------------------------------
// +�V�F�[�_�[�ݒ�֐�
//--------------------------------------------------
void ShaderManager::SetShader(DrawBase* draw, VertexShaderType forced_vertex_type,
							  PixelShaderType forced_pixel_type)
{
	// ���_�V�F�[�_�[
	SetVertexShader(draw, forced_vertex_type);

	// �s�N�Z���V�F�[�_�[
	SetPixelShader(draw, forced_pixel_type);
}



//--------------------------------------------------
// +���ʐݒ�֐�
//--------------------------------------------------
void ShaderManager::CommonSetting(DrawBase* draw, Camera* camera,
								  VertexShaderType forced_vertex_type,
								  PixelShaderType forced_pixel_type,
								  unsigned object_index)
{
	// ���_�V�F�[�_�[
	CommonSettingVertexShader(draw, camera, forced_vertex_type, object_index);

	// �s�N�Z���V�F�[�_�[
	CommonSettingPixelShader(draw, camera, forced_pixel_type, object_index);
}



//--------------------------------------------------
// +���ʐݒ�֐�
//--------------------------------------------------
void ShaderManager::SpecificSetting(DrawBase* draw, Camera* camera,
									VertexShaderType forced_vertex_type,
									PixelShaderType forced_pixel_type,
									unsigned object_index, unsigned mesh_index)
{
	// ���_�V�F�[�_�[
	SpecificSettingVertexShader(draw, camera, forced_vertex_type, object_index,
								mesh_index);

	// �s�N�Z���V�F�[�_�[
	SpecificSettingPixelShader(draw, camera, forced_pixel_type, object_index,
							   mesh_index);
}



//--------------------------------------------------
// -���_�V�F�[�_�[�������֐�
//--------------------------------------------------
void ShaderManager::InitVertexShaders()
{
	// ����
	vertex_shaders_[VertexShaderType::VERTEX_FIXED] = new VertexShaderFixed();
	vertex_shaders_[VertexShaderType::VERTEX_BUMP_MAPPING] = new VertexShaderBumpMapping();

	// ������
	for (unsigned i = 0; i < VertexShaderType::VERTEX_MAX; i++)
	{
		vertex_shaders_[i]->Init();
	}
}



//--------------------------------------------------
// -�s�N�Z���V�F�[�_�[�������֐�
//--------------------------------------------------
void ShaderManager::InitPixelShaders()
{
	// ����
	pixel_shaders_[PixelShaderType::PIXEL_FIXED] = new PixelShaderNull();
	pixel_shaders_[PixelShaderType::PIXEL_BUMP_MAPPING] = new PixelShaderBumpMapping();

	// ������
	for (unsigned i = 0; i < PixelShaderType::PIXEL_MAX; i++)
	{
		pixel_shaders_[i]->Init();
	}
}



//--------------------------------------------------
// -���_�V�F�[�_�[�I���֐�
//--------------------------------------------------
void ShaderManager::UninitVertexShaders()
{
	// ���
	for (unsigned i = 0; i < VertexShaderType::VERTEX_MAX; i++)
	{
		SafeRelease::PlusUninit(&vertex_shaders_[i]);
	}
}



//--------------------------------------------------
// -�s�N�Z���V�F�[�_�[�I���֐�
//--------------------------------------------------
void ShaderManager::UninitPixelShaders()
{
	// ���
	for (unsigned i = 0; i < PixelShaderType::PIXEL_MAX; i++)
	{
		SafeRelease::PlusUninit(&pixel_shaders_[i]);
	}
}



//--------------------------------------------------
// -���_�V�F�[�_�[�ݒ�֐�
//--------------------------------------------------
void ShaderManager::SetVertexShader(DrawBase* draw,
									VertexShaderType forced_vertex_type)
{
	if (forced_vertex_type != VertexShaderType::VERTEX_NONE)
	{
		vertex_shaders_[forced_vertex_type]->SetShader();
		return;
	}

	vertex_shaders_[draw->GetDrawOrderList()->GetVertexShaderType()]->SetShader();
}



//--------------------------------------------------
// -�s�N�Z���V�F�[�_�[�ݒ�֐�
//--------------------------------------------------
void ShaderManager::SetPixelShader(DrawBase* draw, PixelShaderType forced_pixel_type)
{
	// �����ݒ肪���邩�ǂ���
	if (forced_pixel_type != PixelShaderType::PIXEL_NONE)
	{
		pixel_shaders_[forced_pixel_type]->SetShader();
		return;
	}

	pixel_shaders_[draw->GetDrawOrderList()->GetPixelShaderType()]->SetShader();
}



//--------------------------------------------------
// +���_�V�F�[�_�[���ʐݒ�֐�
//--------------------------------------------------
void ShaderManager::CommonSettingVertexShader(DrawBase* draw, Camera* camera,
											  VertexShaderType forced_vertex_type,
											  unsigned object_index)
{
	// �����ݒ肪���邩�ǂ���
	if (forced_vertex_type != VertexShaderType::VERTEX_NONE)
	{
		vertex_shaders_[forced_vertex_type]->CommonSetting(draw, camera, object_index);
		return;
	}

	vertex_shaders_[draw->GetDrawOrderList()->GetVertexShaderType()]
		->CommonSetting(draw, camera, object_index);
}



//--------------------------------------------------
// +�s�N�Z���V�F�[�_�[���ʐݒ�֐�
//--------------------------------------------------
void ShaderManager::CommonSettingPixelShader(DrawBase* draw, Camera* camera,
											 PixelShaderType forced_pixel_type,
											 unsigned object_index)
{
	// �����ݒ肪���邩�ǂ���
	if (forced_pixel_type != PixelShaderType::PIXEL_NONE)
	{
		pixel_shaders_[forced_pixel_type]->CommonSetting(draw, camera, object_index);
		return;
	}

	pixel_shaders_[draw->GetDrawOrderList()->GetPixelShaderType()]
		->CommonSetting(draw, camera, object_index);
}



//--------------------------------------------------
// +���_�V�F�[�_�[���ʐݒ�֐�
//--------------------------------------------------
void ShaderManager::SpecificSettingVertexShader(DrawBase* draw, Camera* camera,
												VertexShaderType forced_vertex_type,
												unsigned object_index,
												unsigned mesh_index)
{
	// �����ݒ肪���邩�ǂ���
	if (forced_vertex_type != VertexShaderType::VERTEX_NONE)
	{
		vertex_shaders_[forced_vertex_type]->SpecificSetting(draw, camera,
															 object_index, mesh_index);
		return;
	}

	vertex_shaders_[draw->GetDrawOrderList()->GetVertexShaderType()]
		->SpecificSetting(draw, camera, object_index, mesh_index);
}



//--------------------------------------------------
// +�s�N�Z���V�F�[�_�[���ʐݒ�֐�
//--------------------------------------------------
void ShaderManager::SpecificSettingPixelShader(DrawBase* draw, Camera* camera,
											   PixelShaderType forced_pixel_type,
											   unsigned object_index,
											   unsigned mesh_index)
{
	// �����ݒ肪���邩�ǂ���
	if (forced_pixel_type != PixelShaderType::PIXEL_NONE)
	{
		pixel_shaders_[forced_pixel_type]->SpecificSetting(draw, camera,
														   object_index, mesh_index);
		return;
	}

	pixel_shaders_[draw->GetDrawOrderList()->GetPixelShaderType()]
		->SpecificSetting(draw, camera, object_index, mesh_index);
}