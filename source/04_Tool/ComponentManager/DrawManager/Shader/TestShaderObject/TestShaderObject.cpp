//================================================================================
//
//    �e�X�g�V�F�[�_�[�I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/09
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <assert.h>

#include "TestShaderObject.h"
#include <ComponentManager/DrawManager/Camera/Camera.h>
#include <Component/DrawBase/DrawBase.h>
#include <GameObjectBase/GameObjectBase.h>

#include <Renderer/Renderer.h>
#include <Transform\Transform.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const char* TestShaderObject::EFFECT_PATH = "resource/HLSL/Effect/obj/BumpMapping.obj";
const D3DVERTEXELEMENT9 TestShaderObject::DECLARATION[] 
	= {{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	   {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
       {0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
       {0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	   D3DDECL_END()
      };


//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

LPDIRECT3DDEVICE9 TestShaderObject::device_;

D3DXMATRIX TestShaderObject::math_matrix_;

IDirect3DVertexDeclaration9* TestShaderObject::declaration_object_;

LPD3DXEFFECT TestShaderObject::effect_;
D3DXHANDLE   TestShaderObject::technique_;
D3DXHANDLE   TestShaderObject::matrix_WVP_;
D3DXHANDLE   TestShaderObject::lambert_diffuse_light_vector_;
D3DXHANDLE   TestShaderObject::lambert_diffuse_light_color_;
D3DXHANDLE   TestShaderObject::camera_position_;
D3DXHANDLE   TestShaderObject::decale_texture_;
D3DXHANDLE   TestShaderObject::normal_texture_;




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
	Renderer::GetInstance()->GetDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(TestShaderObject.cpp)", "Error", MB_OK);
		return;
	}

	// ���_�錾�I�u�W�F�N�g�̐���
	HRESULT hr = device_->CreateVertexDeclaration(DECLARATION, &declaration_object_);
	

#ifdef _DEBUG
	assert(SUCCEEDED(hr) && "���_�錾�I�u�W�F�N�g�̐����Ɏ��s(FixedPipelineObject.cpp)");
#else
	hr = hr;
#endif

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
	matrix_WVP_					  = effect_->GetParameterByName(NULL, "MATRIX_WVP");
	lambert_diffuse_light_vector_ = effect_->GetParameterByName(NULL, "LAMBERT_DIFFUSE_LIGHT_VECTOR");
	lambert_diffuse_light_color_  = effect_->GetParameterByName(NULL, "LAMBERT_DIFFUSE_LIGHT_COLOR");
	camera_position_			  = effect_->GetParameterByName(NULL, "CAMERA_POSITION");
	decale_texture_			      = effect_->GetParameterByName(NULL, "DECALE_TEXTURE");
	normal_texture_			      = effect_->GetParameterByName(NULL, "NORMAL_TEXTURE");

	// �e��J��
	SafeRelease::PlusRelease(&error_message);
	delete[] file_data;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Uninit()
{
	// �e��J��
	SafeRelease::PlusRelease(&effect_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Draw(DrawBase* draw, Camera* camera)
{
	// �e�N�j�b�N�ݒ�
	effect_->SetTechnique(technique_);
	
	// �V�F�[�_�[�ł̃����_�����O�J�n
	effect_->Begin(nullptr, 0);
	
	// �p�X��ݒ�
	effect_->BeginPass(0);
	
	// �`��

	// ���[���h�ϊ��s��(WVP)���Z�b�g
	D3DXMatrixMultiply(&math_matrix_, draw->GetGameObject()->GetTransform()->GetWorldMatrix(), camera->GetViewMatrix());
	D3DXMatrixMultiply(&math_matrix_, &math_matrix_, camera->GetProjectionMatrix());
	effect_->SetMatrix(matrix_WVP_, &math_matrix_);

	// ���C�g�������Z�b�g
	D3DXMatrixIdentity(&math_matrix_);
	Vec4 light_position(0.5f, -1.0f, 0.8f, 0.0f);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->GetGameObject()->GetTransform()->GetWorldMatrix());
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vec3*)&light_position, (Vec3*)&light_position);
	light_position.w = -0.7f;		// �����̔䗦
	effect_->SetVector(lambert_diffuse_light_vector_, &light_position);
	
	// ���_�̐ݒ�(�I�u�W�F�N�g���Ƃ̃��[�J�����W�ł̃J�����̍��W���擾����)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw->GetGameObject()->GetTransform()->GetWorldMatrix(), camera->GetViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	effect_->SetVector(camera_position_, &object_local_camera_position);

	// ���_�錾
	device_->SetVertexDeclaration(declaration_object_);

	// ���b�V�������`��
	Vec4 temp_vector;
	for (unsigned i = 0; i < draw->GetMeshNum(); i++)
	{
		// �f�B�q���[�Y�F�̐ݒ�
		temp_vector.x = draw->GetMaterial(i)->Diffuse.r;
		temp_vector.y = draw->GetMaterial(i)->Diffuse.g;
		temp_vector.z = draw->GetMaterial(i)->Diffuse.b;
		temp_vector.w = draw->GetMaterial(i)->Diffuse.a;
		effect_->SetVector(lambert_diffuse_light_color_, &temp_vector);
		
		// �f�J�[���e�N�X�`���̐ݒ�
		LPDIRECT3DTEXTURE9 temp = draw->GetDecaleTexture(i);
		temp = temp;
		effect_->SetTexture(decale_texture_, temp);

		// �@���}�b�v�̐ݒ�
		effect_->SetTexture(normal_texture_, draw->GetNormalTexture(i));

		// �V�F�[�_�[�̐ݒ�m��
		effect_->CommitChanges();
		
		// �`��
		draw->Draw(i);
	}
	
	
	// �p�X������
	effect_->EndPass();

	// �V�F�[�_�[�ł̃����_�����O�I��
	effect_->End();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���_�錾�p���b�V���X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::UpdateMeshDeclaration(ModelXObject* model_x)
{
	model_x->UpdateMeshDeclaration(DECLARATION);					// ���b�V���̕ύX
	D3DXComputeNormals(model_x->GetMesh(), nullptr);				// �@�����Z�o
	D3DXComputeTangent(model_x->GetMesh(), 0, 0, 0, TRUE,nullptr);	//�ڃx�N�g�����Z�o
}