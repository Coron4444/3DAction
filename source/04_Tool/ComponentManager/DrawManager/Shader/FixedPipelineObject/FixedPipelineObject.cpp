//================================================================================
//
//    �Œ�p�C�v���C���I�u�W�F�N�g�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <assert.h>

#include "FixedPipelineObject.h"
#include <ComponentManager\DrawComponentManager\Camera\Camera.h>
#include <Component/DrawComponent/DrawComponent.h>
#include <GameObjectOrigin/GameObjectOrigin.h>


#include <main.h>
#include <Transform\Transform.h>




//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

D3DLIGHT9		  FixedPipelineObject::directional_light_;
LPDIRECT3DDEVICE9 FixedPipelineObject::device_ = nullptr;



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

void FixedPipelineObject::Init()
{
	// �f�o�C�X�̎擾
	Renderer::GetInstance()->GetDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(FixedPipeline.cpp)", "Error", MB_OK);
		return;
	}

	// �f�B���N�V���i�����C�g������
	Init_DirectionalLignt();

	// �����_�[�X�e�[�g�̐ݒ�( �œK���̏ꍇ�͂��܂�Ă΂Ȃ��悤�ɐ݌v���� )
	UseAlphaBlending(true);
	SetAlphaBlending_Linear();

	// �e�N�X�`���[�X�e�[�W�X�e�[�g�̐ݒ�
	// �������e�N�X�`���X�e�[�W�ԍ�
	// ���������l�̉��Z����͏�Z(RG1*RG2�܂�ATEXTURE��DIFFUSE)
	device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// �T���v���[�X�e�[�g�̐ݒ�
	SetDefaultSamplerState();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::Uninit()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 3D�`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::Draw3D(DrawComponent* draw_component, Camera* camera)
{
	// ����ݒ�
	UnifiedSetting();
	
	// 3D�`��ݒ�
	SetDraw3D(camera);

	// ���[���h�s��Z�b�g
	SetWorldMatrix(draw_component);
	
	for (unsigned i = 0; i < draw_component->GetMeshNum(); i++)
	{
		// �e�N�X�`���̃Z�b�g
		SetTexture(draw_component, i);

		// �}�e���A���̃Z�b�g
		SetMaterial(draw_component, i);

		// �`��
		draw_component->Draw(i);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 2D�`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::Draw2D(DrawComponent* draw_component, Camera* camera)
{
	camera = camera;

	// ����ݒ�
	UnifiedSetting();

	// 2D�`��ݒ�
	SetDraw2D();

	// ���[���h�s��Z�b�g
	SetWorldMatrix(draw_component);
	
	for (unsigned i = 0; i < draw_component->GetMeshNum(); i++)
	{
		// �e�N�X�`���̃Z�b�g
		SetTexture(draw_component, i);

		// �}�e���A���̃Z�b�g
		SetMaterial(draw_component, i);

		// �`��
		draw_component->Draw(i);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 3D�`��ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::SetDraw3D(Camera* camera)
{
	device_->SetTransform( D3DTS_VIEW,		camera->GetViewMatrix());
	device_->SetTransform( D3DTS_PROJECTION, camera->GetProjectionMatrix());
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 2D�`��ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::SetDraw2D()
{
	// �r���[�s��̍쐬
	MatrixExtend matrix_view;

	// �v���W�F�N�V�����s��̍쐬
	MATRIX matrix_projection 
			= {2.0f/SCREEN_WIDTH,				0.0f, 0.0f, 0.0f,
						    0.0f, 2.0f/SCREEN_HEIGHT, 0.0f, 0.0f,
						    0.0f,               0.0f, 1.0f, 0.0f,
						    0.0f,               0.0f, 0.0f, 1.0f
			  };

	device_->SetTransform(D3DTS_VIEW,	   matrix_view.GetWorldMatrix());
	device_->SetTransform(D3DTS_PROJECTION, &matrix_projection);
}



//--------------------------------------------------------------------------------
//
// [ �Œ�p�C�v���C������ݒ�֐� ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::UnifiedSetting()
{
	// �@�������1�ɐ��K��
	device_->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
}



//--------------------------------------------------------------------------------
//
// [ ���[���h�s��ݒ�֐� ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::SetWorldMatrix(DrawComponent* draw_component)
{
	device_->SetTransform(D3DTS_WORLD, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix());
}



//--------------------------------------------------------------------------------
//
// [ �e�N�X�`���ݒ�֐� ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::SetTexture(DrawComponent* draw_component, unsigned mesh_index)
{
	LPDIRECT3DTEXTURE9 temp = draw_component->GetDecaleTexture(mesh_index);

	device_->SetTexture(0, temp);
}



//--------------------------------------------------------------------------------
//
// [ �}�e���A���ݒ�֐� ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::SetMaterial(DrawComponent* draw_component, unsigned mesh_index)
{
	D3DMATERIAL9* temp = draw_component->GetMaterial(mesh_index);

	if (temp == nullptr) return;

	device_->SetMaterial(temp);
}



//--------------------------------------------------------------------------------
//
// [ �f�B���N�V���i�����C�g�������֐� ]
//
//--------------------------------------------------------------------------------

void FixedPipelineObject::Init_DirectionalLignt()
{
	// ���C�g�̐ݒ�
	ZeroMemory(&directional_light_, sizeof(directional_light_));

	directional_light_.Type = D3DLIGHT_DIRECTIONAL;
	
	// ���C�g������P�ʃx�N�g���ő��
	Vec3 directional_light_vector = Vec3(0.5f, -1.0f, 0.8f);
	D3DXVec3Normalize((D3DXVECTOR3*)&directional_light_.Direction, &directional_light_vector);
	
	// ���C�g�J���[
	directional_light_.Diffuse.r = 1.0f;
	directional_light_.Diffuse.g = 1.0f;
	directional_light_.Diffuse.b = 1.0f;
	directional_light_.Diffuse.a = 1.0f;
	
	// �A���r�G���g���C�g
	directional_light_.Ambient.r = 0.1f;
	directional_light_.Ambient.g = 0.1f;
	directional_light_.Ambient.b = 0.1f;
	directional_light_.Ambient.a = 1.0f;
	
	// �O���[�o���A���r�G���g�̐ݒ�
	device_->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));

	// ���C�g���f�o�C�X�ɃZ�b�g(��������0�`4�̃��C�g�ԍ�)
	device_->SetLight(0, &directional_light_);

	// 0�ԃ��C�g���g����悤�ɂ���
	device_->LightEnable(0, TRUE);
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �A���t�@�����t���O�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::UseAlphaBlending(bool flag)
{
	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, flag);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �A���t�@�����֐�(���`����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Linear()
{
	// SRC --- ������`�����́B
	// DEST--- ���łɕ`�悳��Ă����ʂ̂��ƁB
	// 1��100%(255)�̂���
	// �����SRC_����0������w�i�F��100%�ŏo�Ă���B

	// {(1 - SRC_��) * DEST_RGB} + (SRC_RGB * SRC_��) 
	device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �A���t�@�����֐�(���Z����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Add()
{
	// (DST_RGB * 1) - (SRC_RGB * SRC_��) 
	device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �A���t�@�����֐�(���Z����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Sub()
{
	// (DST_RGB * 1) - (SRC_RGB * SRC_��) 
	device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �A���t�@�����֐�(��Z����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Mul()
{
	//device_-> SetRenderState( D3DRS_BLENDOP, �C�ӂ̒l)
	// ���L2�s�Ő������邽�ߏ�L�̐ݒ�Ɉˑ����Ȃ�

	// (DST_RGB * SRC_RGB) + (SRC_RGB * 0)
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �A���t�@�����֐�(�Ă����ݍ���) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Baking()
{
	//device_-> SetRenderState(D3DRS_BLENDOP, �C�ӂ̒l)
	// ���L2�s�Ő������邽�ߏ�L�̐ݒ�Ɉˑ����Ȃ�

	// (DST_RGB * DST_RGB) + ( SRC_RGB * 0 )
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �A���t�@�����֐�(�l�K�|�W���]����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Nega()
{
	//device_->SetRenderState(D3DRS_BLENDOP, �C�ӂ̒l)
	// ���L2�s�Ő������邽�ߏ�L�̐ݒ�Ɉˑ����Ȃ�

	// (DST_RGB * 0) + (1 - DST_RGB) * SRC_RGB
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �A���t�@�����֐�(�s��������) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void FixedPipelineObject::SetAlphaBlending_Opacity()
{
	//device_->SetRenderState(D3DRS_BLENDOP, �C�ӂ̒l)
	// ���L2�s�Ő������邽�ߏ�L�̐ݒ�Ɉˑ����Ȃ�

	// (DST_RGB * 0) + (SRC_RGB * 1)
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�T���v���[�X�e�[�g�ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FixedPipelineObject::SetDefaultSamplerState()
{
	// ������(UV�̐ݒ�)
	// ��O�����e�N�X�`���[���W�O�̏���
	// WRAP ( ���� )
	// CLAMP( ��ԍŌ�̃s�N�Z�����������΂��ĎQ�Ƃ��� )
	// MIRROR( �� )
	device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �t�B���^�����O
	// MIP�}�b�v(���炩���ߏ������摜�f�[�^�������ŗp�ӂ��Ă���)
	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �f�t�H���g��POINT(��\�_1���E���Ă���)
																				// LINEAR(����̓_���W�񂵂āA�܂�F���u�����h����1�_�ɂ���)����ĐF���ڂ��邪���炩
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �f�t�H���g��POINT
	device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);	// �f�t�H���g��NONE(MIP�}�b�v���g��Ȃ�)
																				// LINEAR�iMIP�}�b�v�Ԃ���`�⊮����j
}