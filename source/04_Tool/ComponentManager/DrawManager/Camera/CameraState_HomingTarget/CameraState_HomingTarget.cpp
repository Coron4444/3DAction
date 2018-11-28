//================================================================================
//
//    �^�[�Q�b�g�ǐՃJ�����X�e�[�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/21
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "CameraState_HomingTarget.h"
#include <GameObjectBase/GameObjectBase.h>

#include <Vector3D.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const float CameraState_HomingTarget::HOMING_CAMERA_POSITION_Y      = 5.0f;
const float CameraState_HomingTarget::HOMING_CAMERA_POSITION_Z      = -15.0f;
const float CameraState_HomingTarget::HOMING_CAMERA_LOOK_AT_POINT_Y = 1.0f;



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CameraState_HomingTarget::Init(Camera* camera)
{
	Update(camera);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CameraState_HomingTarget::Update(Camera* camera)
{
	if (target_ == nullptr) return;

	// �J�����|�W�V�����̍쐬
	*camera->GetPositon() = *target_->GetTransform()->GetPosition();

	camera->GetPositon()->y += HOMING_CAMERA_POSITION_Y;
	camera->GetPositon()->z += HOMING_CAMERA_POSITION_Z;

	// �����_�̍쐬
	Vec3 temp_position = *target_->GetTransform()->GetPosition();
	temp_position.y += HOMING_CAMERA_LOOK_AT_POINT_Y;
	*camera->GetLookAtPoint() = temp_position;
}