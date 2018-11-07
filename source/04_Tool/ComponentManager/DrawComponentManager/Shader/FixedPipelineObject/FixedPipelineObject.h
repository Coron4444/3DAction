//================================================================================
//
//    �Œ�p�C�v���C���I�u�W�F�N�g�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_FIXED_PIPELINE_OBJECT_H_
#define _FIXED_PIPELINE_OBJECT_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <Renderer/Renderer.h>



//======================================================================
//
// �N���X�錾
//
//======================================================================

class Camera;
class DrawComponent;



//======================================================================
//
// �N���X��`
//
//======================================================================

class FixedPipelineObject 
{
//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	FixedPipelineObject() = delete;

	// �R�s�[�R���X�g���N�^
	FixedPipelineObject(const FixedPipelineObject& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	FixedPipelineObject& operator = (const FixedPipelineObject& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �ÓI���J�����o�֐�
	static void Init();
	static void Uninit();
	static void Draw3D(DrawComponent* draw_component, Camera* camera);
	static void Draw2D(DrawComponent* draw_component, Camera* camera);
	
	static void SetDraw3D(Camera* camera);
	static void SetDraw2D();

	// �A���t�@�u�����h
	static void UseAlphaBlending(bool flag);
	static void SetAlphaBlending_Linear();
	static void SetAlphaBlending_Add();
	static void SetAlphaBlending_Sub();
	static void SetAlphaBlending_Mul();
	static void SetAlphaBlending_Baking();
	static void SetAlphaBlending_Nega();
	static void SetAlphaBlending_Opacity();

	// �T���v���[�X�e�[�g
	static void SetDefaultSamplerState();

//------------------------------------------------------------
private :
	// �Œ�p�C�v���C������ݒ�
	static void UnifiedSetting();

	// ���[���h�s��ݒ�
	static void SetWorldMatrix(DrawComponent* draw_component);

	// �e�N�X�`���ݒ�
	static void SetTexture(DrawComponent* draw_component, unsigned mesh_index);

	// �}�e���A���ݒ�
	static void SetMaterial(DrawComponent* draw_component, unsigned mesh_index);

	// ���C�g
	static void Init_DirectionalLignt();

//------------------------------------------------------------
private :
	// �ÓI�����o�ϐ�
	static D3DLIGHT9 directional_light_;

	static LPDIRECT3DDEVICE9 device_;
};



#endif
