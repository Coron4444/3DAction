//================================================================================
//
//    �e�X�g�V�F�[�_�[�I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/09
//
//================================================================================

#ifndef	_TEST_SHADER_OBJECT_H_
#define _TEST_SHADER_OBJECT_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// �N���X�錾
//
//======================================================================

class Camera;
class DrawBase;



//======================================================================
//
// �N���X��`
//
//======================================================================

class TestShaderObject
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �萔
	static const char* EFFECT_PATH;
	static const D3DVERTEXELEMENT9 DECLARATION[];


//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	TestShaderObject() = delete;

	// �R�s�[�R���X�g���N�^
	TestShaderObject(const TestShaderObject& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	TestShaderObject& operator = (const TestShaderObject& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���J�����o�֐�
	static void Init();
	static void Uninit();
	static void Draw(DrawBase* draw, Camera* camera);

	static void UpdateMeshDeclaration(ModelXObject* model_x);


//------------------------------------------------------------
private :
	// �����o�ϐ�	
	static LPDIRECT3DDEVICE9 device_;

	// �v�Z�p
	static D3DXMATRIX math_matrix_;

	// ���_�錾�I�u�W�F�N�g
	static IDirect3DVertexDeclaration9* declaration_object_;

	// �G�t�F�N�g�t�@�C���n���h���Q
	static LPD3DXEFFECT effect_;
	static D3DXHANDLE   technique_;
	static D3DXHANDLE   matrix_WVP_;
	static D3DXHANDLE   lambert_diffuse_light_vector_;
	static D3DXHANDLE   lambert_diffuse_light_color_;
	static D3DXHANDLE   camera_position_;
	static D3DXHANDLE   decale_texture_;
	static D3DXHANDLE   normal_texture_;

};



#endif
