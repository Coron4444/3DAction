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
#include "../Shader/VertexShader/FixedVertexShader/FixedVertexShader.h"
#include "../Shader/PixelShader/FixedPixelShader/FixedPixelShader.h"
#include <Component/DrawBase/DrawBase.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>

#include <Renderer/Renderer.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void ShaderManager::Init()
{
	fixed_vertex_shader_ = new FixedVertexShader();
	fixed_vertex_shader_->Init();
	fixed_pixel_shader_ = new FixedPixelShader();
	fixed_pixel_shader_->Init();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void ShaderManager::Uninit()
{
	SafeRelease::PlusUninit(&fixed_vertex_shader_);
	SafeRelease::PlusUninit(&fixed_pixel_shader_);
}



//--------------------------------------------------
// +�V�F�[�_�[�ݒ�֐�
//--------------------------------------------------
void ShaderManager::SetShader(DrawBase* draw, VertexShaderType forced_vertex_type,
							  PixelShaderType forced_pixel_type)
{
	forced_vertex_type = forced_vertex_type;
	forced_pixel_type = forced_pixel_type;

	// ���_�V�F�[�_�[
	switch (draw->GetDrawOrderList()->GetVertexShaderType())
	{
		case VertexShaderType::VERTEX_FIXED:
		{
			fixed_vertex_shader_->SetShader();
			break;
		}
	}

	// �s�N�Z���V�F�[�_�[
	switch (draw->GetDrawOrderList()->GetPixelShaderType())
	{
		case PixelShaderType::PIXEL_FIXED:
		{
			fixed_pixel_shader_->SetShader();
			break;
		}
	}
}



//--------------------------------------------------
// +���ʐݒ�֐�
//--------------------------------------------------
void ShaderManager::CommonSetting(DrawBase* draw, Camera* camera, 
								  VertexShaderType forced_vertex_type,
								  PixelShaderType forced_pixel_type, unsigned object_index)
{
	forced_vertex_type = forced_vertex_type;
	forced_pixel_type = forced_pixel_type;

	// ���_�V�F�[�_�[
	switch (draw->GetDrawOrderList()->GetVertexShaderType())
	{
		case VertexShaderType::VERTEX_FIXED:
		{
			fixed_vertex_shader_->CommonSetting(draw, camera, object_index);
			break;
		}
	}

	// �s�N�Z���V�F�[�_�[
	switch (draw->GetDrawOrderList()->GetPixelShaderType())
	{
		case PixelShaderType::PIXEL_FIXED:
		{
			fixed_pixel_shader_->CommonSetting(draw, camera, object_index);
			break;
		}
	}
}



//--------------------------------------------------
// +���ʐݒ�֐�
//--------------------------------------------------
void ShaderManager::SpecificSetting(DrawBase* draw, Camera* camera, 
									VertexShaderType forced_vertex_type,
									PixelShaderType forced_pixel_type,
									unsigned object_index, unsigned mesh_index)
{
	forced_vertex_type = forced_vertex_type;
	forced_pixel_type = forced_pixel_type;

	// ���_�V�F�[�_�[
	switch (draw->GetDrawOrderList()->GetVertexShaderType())
	{
		case VertexShaderType::VERTEX_FIXED:
		{
			fixed_vertex_shader_->SpecificSetting(draw, camera, object_index, mesh_index);
				break;
		}
	}

	// �s�N�Z���V�F�[�_�[
	switch (draw->GetDrawOrderList()->GetPixelShaderType())
	{
		case PixelShaderType::PIXEL_FIXED:
		{
			fixed_pixel_shader_->SpecificSetting(draw, camera, object_index, mesh_index);
			break;
		}
	}
}