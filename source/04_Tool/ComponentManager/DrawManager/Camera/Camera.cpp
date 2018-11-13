//================================================================================
//
//    �J�����N���X
//    Author : Araki Kai                                �쐬�� : 2017/12/07
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "Camera.h"

#include <main.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const float Camera::NEAR_CLIPPING_PLANE = 0.1f;
const float Camera::FAR_CLIPPING_PLANE = 1000.0f;
const int   Camera::DEFAULT_ANGLE_OF_VIEW = 60;



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void Camera::Init(State* state, Vec3 position, Vec3 look_at_point, Vec3 up)
{
	// �e����
	state_ = state;
	position_ = position;
	look_at_point_ = look_at_point;
	up_ = up;
	angle_of_view_ = DEFAULT_ANGLE_OF_VIEW;

	// ���x�N�g�����쐬
	axis_.SetForward(look_at_point_ - position_);

	// �X�e�[�g�̏�����
	if (state_ != nullptr) state_->Init(this);

	// �r���[�s��̍쐬
	D3DXMatrixIdentity(&view_2D_);
	CreateViewMatrix();

	// �v���W�F�N�V�����s��̍쐬
	CreateProjectionMatrix_PerspectiveFov();
	CreateProjectionMatrix_Ortho();
	CreateProjectionMatrix_2D();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void Camera::Uninit()
{
	SafeRelease::PlusUninit(&state_);
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void Camera::Update()
{
	if (state_ != nullptr) state_->Update(this);

	CreateViewMatrix();
}



//--------------------------------------------------
// +�r���[�s��쐬�֐�
//--------------------------------------------------
void Camera::CreateViewMatrix()
{
	// �s�񏉊���
	D3DXMatrixIdentity(&view_);

	// �r���[�ϊ��s��( LH�͍�����W�n�̈Ӗ� )
	D3DXMatrixLookAtLH(&view_, &position_, &look_at_point_, &up_);
}



//--------------------------------------------------
// +�v���W�F�N�V�����s��쐬�֐�(�������e�s��)
//--------------------------------------------------
void Camera::CreateProjectionMatrix_PerspectiveFov()
{
	// �s�񏉊���
	D3DXMatrixIdentity(&projection_perspective_);

	D3DXMatrixPerspectiveFovLH(&projection_perspective_,
							   D3DXToRadian(angle_of_view_),
							   (float)SCREEN_WIDTH / SCREEN_HEIGHT,
							   NEAR_CLIPPING_PLANE,
							   FAR_CLIPPING_PLANE);
}



//--------------------------------------------------
// + �v���W�F�N�V�����s��쐬�֐�(���ˉe�s��)
//--------------------------------------------------
void Camera::CreateProjectionMatrix_Ortho()
{
	// �s�񏉊���
	D3DXMatrixIdentity(&projection_ortho_);

	D3DXMatrixOrthoLH(&projection_ortho_,
		(float)SCREEN_WIDTH  * angle_of_view_,
					  (float)SCREEN_HEIGHT * angle_of_view_,
					  NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
}



//--------------------------------------------------
// + �v���W�F�N�V�����s��쐬�֐�(2D)
//--------------------------------------------------
void Camera::CreateProjectionMatrix_2D()
{
	projection_2D_
		= {2.0f / SCREEN_WIDTH,					0.0f, 0.0f, 0.0f,
						  0.0f, 2.0f / SCREEN_HEIGHT, 0.0f, 0.0f,
						  0.0f,                 0.0f, 1.0f, 0.0f,
						  0.0f,                 0.0f, 0.0f, 1.0f
	};
}



//--------------------------------------------------
// + �J�����X�e�[�g�̕ύX
//--------------------------------------------------
void Camera::ChangeState(State* new_camera_state)
{
	// �I������
	if (state_ != nullptr) state_->Uninit();

	// �V�K�X�e�[�g�ɕύX
	SafeRelease::Normal(&state_);
	state_ = new_camera_state;

	// ����������
	if (state_ != nullptr) state_->Init(this);
}
