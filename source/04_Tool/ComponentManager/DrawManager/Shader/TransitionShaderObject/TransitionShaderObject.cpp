//================================================================================
//
//    �g�����W�V�����V�F�[�_�[�I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/08/21
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "TransitionShaderObject.h"
#include <Component/DrawComponent/DrawComponent.h>
#include <GameObjectOrigin/GameObjectOrigin.h>

#include <assert.h>

#include <Translation\Translation3D.h>
#include <Matrix\MatrixSRT_Axis.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const char* TestShaderObject::EFFECT_PATH = "resource/HLSL/Effect/obj/LambertLightingModel.obj";



//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

LimitedPointerArray<DrawComponent*, DrawComponentManager::DRAW_ARRAY_NUM> TestShaderObject::shader_;
	
LPDIRECT3DDEVICE9 TestShaderObject::device_;

D3DXMATRIX TestShaderObject::math_matrix_;

LPD3DXEFFECT TestShaderObject::effect_;
D3DXHANDLE   TestShaderObject::technique_;
D3DXHANDLE   TestShaderObject::matrix_WVP_;
D3DXHANDLE   TestShaderObject::matrix_WIT_;
D3DXHANDLE   TestShaderObject::diffuse_light_vector_;
D3DXHANDLE   TestShaderObject::diffuse_light_intensity_;
D3DXHANDLE   TestShaderObject::ambient_light_intensity_;
D3DXHANDLE   TestShaderObject::object_color_diffuse_;
D3DXHANDLE   TestShaderObject::object_color_ambient_;



//======================================================================
//
// �ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Init()
{
	// �f�o�C�X�̎擾
	device_ = RendererDirectX9::GetDevice();
	assert(device_ != nullptr && "�f�o�C�X�̎擾�Ɏ��s(FixedPipelineObject.cpp)");

	// �G�t�F�N�g�t�@�C���̓ǂݍ���
	FILE* file_pointer = nullptr;
	file_pointer = fopen(EFFECT_PATH, "rb");
	if (file_pointer == nullptr)
	{
		MessageBox(nullptr, "�G�t�F�N�g�t�@�C���̓ǂݍ��݂Ɏ��s", "Error(TestShaderObject.cpp)", MB_OK);
	}

	// �t�@�C���|�C���^�[�̈ʒu����t�@�C���T�C�Y���擾����(�o�C�i���\�t�@�C���ł��邽�ߗL��)
	fseek(file_pointer, 0, SEEK_END);
	long file_size = ftell(file_pointer);
	fseek(file_pointer, 0, SEEK_SET);
	
	// �t�@�C���̓ǂݍ���
	char* file_data = new char[file_size];
	fread(file_data, file_size, sizeof(char), file_pointer);
	fclose(file_pointer);

	// �G�t�F�N�g�t�@�C���n���h���̎擾
	LPD3DXBUFFER error_message = nullptr;
	HRESULT h_result = D3DXCreateEffect(device_,			// �f�o�C�X
										file_data,			// �R���p�C���ς�fx�f�[�^
										file_size,			// �R���p�C���ς�fx�f�[�^�̃T�C�Y
										nullptr,			// �v���v���Z�b�T��`�ւ̃|�C���^
										nullptr,			// �I�v�V�����̃C���^�t�F�[�X�ւ̃|�C���^
										0,					// D3DXSHADER�Ŏ��ʂ����R���p�C���I�v�V����
										nullptr,			// ���L�����Ŏg��ID3DXEffectPool�I�u�W�F�N�g�ւ̃|�C���^
										&effect_,			// �R���p�C�����ꂽ�G�t�F�N�g�̊i�[��
										&error_message);	// �R���p�C���G���[�ꗗ�̊i�[��
	if (FAILED(h_result))
	{
		MessageBox(nullptr, "�G�t�F�N�g�t�@�C���n���h���̎擾�Ɏ��s", "Error(TestShaderObject.cpp)", MB_OK);
	}

	// �e�N�j�b�N�n���h���̎擾
	technique_  = effect_->GetTechniqueByName("Techique01");
	
	// �萔�n���h���̎擾
	matrix_WVP_				 = effect_->GetParameterByName(NULL, "MATRIX_WVP");
	matrix_WIT_				 = effect_->GetParameterByName(NULL, "MATRIX_WIT");
	diffuse_light_vector_    = effect_->GetParameterByName(NULL, "DIFFUSE_LIGHT_VECTOR");
	diffuse_light_intensity_ = effect_->GetParameterByName(NULL, "DIFFUSE_LIGHT_INTENSITY");
	ambient_light_intensity_ = effect_->GetParameterByName(NULL, "AMBIENT_LIGHT_INTENSITY");
	object_color_diffuse_    = effect_->GetParameterByName(NULL, "OBJECT_COLOR_DIFFUSE");
	object_color_ambient_    = effect_->GetParameterByName(NULL, "OBJECT_COLOR_AMBIENT");

	// �e��J��
	SafeReleaseDirectX9(&error_message);
	delete[] file_data;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Uninit()
{
	// �z��̃��Z�b�g
	ResetArray();

	// �e��J��
	SafeReleaseDirectX9(&effect_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Draw(Camera* camera)
{
	// �e�N�j�b�N�ݒ�
	effect_->SetTechnique(technique_);
	
	// �V�F�[�_�[�ł̃����_�����O�J�n
	effect_->Begin(nullptr, 0);
	
	// �p�X��ݒ�
	effect_->BeginPass(0);

	// ���_�錾
	LPDIRECT3DDEVICE9 device = RendererDirectX9::GetDevice();
	if (device == nullptr)
	{
		MessageBox(nullptr, "D3DDevice�̎擾�Ɏ��s", "Error(TestShaderObject.cpp)", MB_OK);
	}
	//device->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	device->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// �`��
	for(unsigned i = 0; i < shader_.GetEndPointer(); i++)
	{
		// ���[���h�ϊ��s��(WVP)���Z�b�g
		D3DXMatrixMultiply(&math_matrix_, shader_.GetArrayObject(i)->GetGameObjectOrigin()->matrix_->GetWorldMatrixPointer(), camera->GetViewMatrix());
		D3DXMatrixMultiply(&math_matrix_, &math_matrix_, camera->GetProjectionMatrix());
		effect_->SetMatrix(matrix_WVP_, &math_matrix_);

		// �@���p���[���h�ϊ��s��(WVP)���Z�b�g
		D3DXMatrixInverse(&math_matrix_, NULL, shader_.GetArrayObject(i)->GetGameObjectOrigin()->matrix_->GetWorldMatrixPointer());
		D3DXMatrixTranspose(&math_matrix_, &math_matrix_);
		effect_->SetMatrix(matrix_WIT_, &math_matrix_);

		// ���C�g�������Z�b�g
		Vec4 light_position(-0.577f, -0.577f, -0.577f, 0.0f);
		effect_->SetVector(diffuse_light_vector_, &light_position);

		// �}�e���A���̐ݒ�
		Vec4 temp_vector;
		for (unsigned j = 0; j < shader_.GetArrayObject(i)->GetMeshNum(); j++)
		{
			// �f�B�q���[�Y�F�̐ݒ�
			temp_vector.x = shader_.GetArrayObject(i)->GetMaterial(j)->Diffuse.r;
			temp_vector.y = shader_.GetArrayObject(i)->GetMaterial(j)->Diffuse.g;
			temp_vector.z = shader_.GetArrayObject(i)->GetMaterial(j)->Diffuse.b;
			temp_vector.w = shader_.GetArrayObject(i)->GetMaterial(j)->Diffuse.a;
			effect_->SetVector(object_color_diffuse_, &temp_vector);
			
			// �A���r�G���g�F�̐ݒ�
			temp_vector.x = shader_.GetArrayObject(i)->GetMaterial(j)->Ambient.r;
			temp_vector.y = shader_.GetArrayObject(i)->GetMaterial(j)->Ambient.g;
			temp_vector.z = shader_.GetArrayObject(i)->GetMaterial(j)->Ambient.b;
			temp_vector.w = shader_.GetArrayObject(i)->GetMaterial(j)->Ambient.a;
			effect_->SetVector(object_color_ambient_, &temp_vector);

			// �ݒ�m��
			effect_->CommitChanges();

			// �`��
			shader_.GetArrayObject(i)->Draw();
		}
	}
	
	// �p�X������
	effect_->EndPass();

	// �V�F�[�_�[�ł̃����_�����O�I��
	effect_->End();
}



//================================================================================
//
// [ �`��R���|�[�l���g�z��̃��Z�b�g�֐� ]
//
//================================================================================

void TestShaderObject::ResetArray()
{
	// �z�񃊃Z�b�g
	shader_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��R���|�[�l���g�U�蕪���֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::DistributeDrawComponent(DrawComponent* draw_component, Camera* camera)
{
	switch (draw_component->GetState())
	{
		case DrawComponent::State::TEST_SHADER :
		{
			shader_.AddToArray(draw_component);
			break;
		}

		case DrawComponent::State::FIXED_BILLBOARD :
		{
			ShaderObjectCommonMethod::SetBillboardMatrix(draw_component, camera);
			shader_.AddToArray(draw_component);
			break;
		}
		default :
		{
			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �����`��R���|�[�l���g�̃\�[�g�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::SortTransparent(Camera* camera)
{
	ShaderObjectCommonMethod::SortTransparent(&shader_, camera);
}