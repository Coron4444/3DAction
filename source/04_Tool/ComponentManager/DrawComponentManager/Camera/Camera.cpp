//================================================================================
//
//    �J�����N���X
//    Author : Araki Kai                                �쐬�� : 2017/12/07
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "Camera.h"

#include <main.h>
#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const float Camera::NEAR_CLIPPING_PLANE   = 0.1f;
const float Camera::FAR_CLIPPING_PLANE    = 1000.0f;
const int   Camera::DEFAULT_ANGLE_OF_VIEW = 60;



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Camera::Camera(State* state, Type type, Vec3 position, Vec3 look_at_point, Vec3 up)
	: state_        (state),
	  type_         (type),
	  position_     (position), 
	  look_at_point_(look_at_point), 
	  up_			(up),
	  angle_of_view_(DEFAULT_ANGLE_OF_VIEW)
{
	// ���x�N�g�����쐬
	axis_.SetForward(look_at_point_ - position_);

	// �X�e�[�g�̏�����
	if (state_ != nullptr) state_->Init(this);

	// �r���[�s��̍쐬
	CreateViewMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Camera::~Camera()
{
	SafeRelease::Normal(&state_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �J�����X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::Update()
{
	if (state_ != nullptr) state_->Update(this);

	CreateViewMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �r���[�s��쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::CreateViewMatrix()
{
	// �r���[�ϊ��s��( LH�͍�����W�n�̈Ӗ� )
	D3DXMatrixLookAtLH(&matrix_view_, &position_, &look_at_point_, &up_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �v���W�F�N�V�����s��쐬�֐�() ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::CreateProjectionMatrix(float angle_of_view, float aspect, 
									float near_clipping_plane, float far_clipping_plane)
{
	D3DXMatrixPerspectiveFovLH(&matrix_projection_,
							   D3DXToRadian(angle_of_view),
							   aspect,
							   near_clipping_plane,
							   far_clipping_plane);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �v���W�F�N�V�����s��쐬�֐�(�������e�s��) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::CreateProjectionMatrix_PerspectiveFov()
{
	D3DXMatrixPerspectiveFovLH(&matrix_projection_, 
							   D3DXToRadian(angle_of_view_), 
							   (float)SCREEN_WIDTH / SCREEN_HEIGHT, 
							   NEAR_CLIPPING_PLANE, 
							   FAR_CLIPPING_PLANE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �v���W�F�N�V�����s��쐬�֐�(���ˉe�s��) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::CreateProjectionMatrix_Ortho()
{
	D3DXMatrixOrthoLH(&matrix_projection_, 
		              (float)SCREEN_WIDTH  * angle_of_view_,
		              (float)SCREEN_HEIGHT * angle_of_view_,
		              NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �J�����X�e�[�g�̕ύX�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::ChangeState(State* new_camera_state)
{
	// �I������
	if (state_ != nullptr) state_->Uninit(this);

	// �V�K�X�e�[�g�ɕύX
	SafeRelease::Normal(&state_);
	state_ = new_camera_state;

	// ����������
	if (state_ != nullptr) state_->Init(this);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �J�����^�C�v����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool Camera::IsCameraTypeName(Type type)
{
	return type_ == type;
}