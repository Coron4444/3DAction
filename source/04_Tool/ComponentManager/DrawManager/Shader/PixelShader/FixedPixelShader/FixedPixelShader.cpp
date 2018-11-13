//================================================================================
//
//    �Œ�@�\�s�N�Z���V�F�[�_�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include <assert.h>

#include "FixedPixelShader.h"
#include "../../../Camera/Camera.h"

#include <Component/DrawBase/DrawBase.h>
#include <Renderer/Renderer.h>
#include <GameObjectManager/GameObjectManager.h>


//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void FixedPixelShader::Init()
{
	// �f�o�C�X�̎擾
	Renderer::GetInstance()->GetDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(FixedPipeline.cpp)", "Error", MB_OK);
		return;
	}
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void FixedPixelShader::Uninit()
{

}



//--------------------------------------------------
// +�V�F�[�_�[�ݒ�֐�
//--------------------------------------------------
void FixedPixelShader::SetShader()
{
	device_->SetPixelShader(nullptr);
}



//--------------------------------------------------
// +���ʐݒ�֐�
//--------------------------------------------------
void FixedPixelShader::CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



//--------------------------------------------------
// +�ŗL�ݒ�֐�
//--------------------------------------------------
void FixedPixelShader::SpecificSetting(DrawBase* draw, Camera* camera,
									   unsigned object_index, unsigned mesh_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
	mesh_index = mesh_index;
}