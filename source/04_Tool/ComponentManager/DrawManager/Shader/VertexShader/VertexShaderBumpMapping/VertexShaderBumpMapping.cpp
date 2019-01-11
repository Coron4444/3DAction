//================================================================================
//
//    �o���v�}�b�s���O���_�V�F�[�_�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/17
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "VertexShaderBumpMapping.h"

#include <GameObjectManager/GameObjectManager.h>



//****************************************
// �萔��`
//****************************************
const char* VertexShaderBumpMapping::PATH = "resource/HLSL/Effect/VertexShader/BumpMapping.vsh";
const D3DVERTEXELEMENT9 VertexShaderBumpMapping::DECLARATION[]
= {{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
   {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
   {0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
   {0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
   D3DDECL_END()
};



//****************************************
// �ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +���_�錾�p���b�V���X�V�֐�
//--------------------------------------------------
void VertexShaderBumpMapping::UpdateMeshDeclaration(ModelXObject* model_x)
{
	model_x->UpdateMeshDeclaration(DECLARATION);					// ���b�V���̕ύX
	D3DXComputeNormals(model_x->GetMesh(), nullptr);				// �@�����Z�o
	D3DXComputeTangent(model_x->GetMesh(), 0, 0, 0, TRUE, nullptr);	//�ڃx�N�g�����Z�o
}



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void VertexShaderBumpMapping::Init()
{
	// �f�o�C�X������
	InitDevice();

	// ���_�錾�I�u�W�F�N�g�̐���
	HRESULT hr = GetDevice()->CreateVertexDeclaration(DECLARATION,
													  &declaration_object_);

#ifdef _DEBUG
	assert(SUCCEEDED(hr) && "���_�錾�I�u�W�F�N�g�̐����Ɏ��s(FixedPipelineObject.cpp)");
#else
	hr = hr;
#endif

	// �V�F�[�_�[�̃R���p�C��
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void VertexShaderBumpMapping::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleaseVertexShader();
}



//--------------------------------------------------
// +���ʐݒ�֐�
//--------------------------------------------------
void VertexShaderBumpMapping::CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index)
{
	// �s��̃Z�b�g
	GetConstantTable()->SetMatrix(ShaderBase::GetDevice(),
								  "MATRIX_WORLD",
								  draw->getpMatrix(object_index));
	GetConstantTable()->SetMatrix(ShaderBase::GetDevice(),
								  "MATRIX_VIEW",
								  camera->getpViewMatrix());
	GetConstantTable()->SetMatrix(ShaderBase::GetDevice(),
								  "MATRIX_PROJECTION",
								  camera->getpProjectionMatrix());

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

	// ���_�̐ݒ�(�I�u�W�F�N�g���Ƃ̃��[�J�����W�ł̃J�����̍��W���擾����)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw->getpMatrix(object_index),
					   camera->getpViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	GetConstantTable()->SetVector(GetDevice(),
								  "CAMERA_POSITION",
								  &object_local_camera_position);

	// ���_�錾
	GetDevice()->SetVertexDeclaration(declaration_object_);
}



//--------------------------------------------------
// +�ŗL�ݒ�֐�
//--------------------------------------------------
void VertexShaderBumpMapping::SpecificSetting(DrawBase* draw, Camera* camera,
											  unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	// �f�B�q���[�Y�F�̐ݒ�
	Vec4 lambert_diffuse_light_color_;
	lambert_diffuse_light_color_.x = draw->getpMaterial(object_index, mesh_index)->Diffuse.r;
	lambert_diffuse_light_color_.y = draw->getpMaterial(object_index, mesh_index)->Diffuse.g;
	lambert_diffuse_light_color_.z = draw->getpMaterial(object_index, mesh_index)->Diffuse.b;
	lambert_diffuse_light_color_.w = draw->getpMaterial(object_index, mesh_index)->Diffuse.a;
	GetConstantTable()->SetVector(GetDevice(),
								  "LAMBERT_DIFFUSE_LIGHT_COLOR",
								  &lambert_diffuse_light_color_);
}
