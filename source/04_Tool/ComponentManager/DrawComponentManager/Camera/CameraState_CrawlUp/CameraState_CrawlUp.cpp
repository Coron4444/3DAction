//================================================================================
//
//    �������΂�J�����X�e�[�g
//    Author : Araki Kai                                �쐬�� : 2018/03/21
//
//================================================================================



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "CameraState_CrawlUp.h"

#include <Keyboard\Keyboard.h>



//**********************************************************************
//
// ��ÓI�����o�֐���`
//
//**********************************************************************

//================================================================================
//
// [ �R���X�g���N�^ ]
//
//================================================================================

CameraState_CrawlUp::CameraState_CrawlUp()
	: // �萔
	  TRANSLATION_SPEED(0.1f),
	  ROTATION_SPEED   (0.8f),
	  POSITION_Y       (8.0f),
	  LOOK_AT_POSITION_Y(POSITION_Y - 5.0f)
{
}



//================================================================================
//
// [ �f�X�g���N�^ ]
//
//================================================================================

CameraState_CrawlUp::~CameraState_CrawlUp()
{
}



//================================================================================
//
// [ �������֐� ]
//
//================================================================================

void CameraState_CrawlUp::Init(Camera* camera)
{
	camera->GetPositon()->y     = POSITION_Y;
	camera->GetLookAtPoint()->y = LOOK_AT_POSITION_Y;
}



//================================================================================
//
// [ �X�V�֐� ]
//
//================================================================================

void CameraState_CrawlUp::Update(Camera* camera)
{
	// �O
	if (GetKeyboardPress(DIK_I))
	{
		// �O�x�N�g����ۑ�
		Vector3D temp_vector = *camera->GetAxis()->GetForawrd();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*camera->GetPositon() += temp_vector;
		*camera->GetLookAtPoint() += temp_vector;
	}

	// ���
	if (GetKeyboardPress(DIK_K))
	{
		// �O�x�N�g����ۑ�
		Vector3D temp_vector = *camera->GetAxis()->GetForawrd();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*camera->GetPositon() += -temp_vector;
		*camera->GetLookAtPoint() += -temp_vector;
	}


	// �E
	if (GetKeyboardPress(DIK_L))
	{
		// �E�x�N�g����ۑ�
		Vector3D temp_vector = *camera->GetAxis()->GetRight();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*camera->GetPositon() += temp_vector;
		*camera->GetLookAtPoint() += temp_vector;
	}


	// ��
	if (GetKeyboardPress(DIK_J))
	{
		// �E�x�N�g����ۑ�
		Vector3D temp_vector = *camera->GetAxis()->GetRight();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*camera->GetPositon() += -temp_vector;
		*camera->GetLookAtPoint() += -temp_vector;
	}


	// �E����
	if (GetKeyboardPress(DIK_E))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *camera->GetLookAtPoint() - *camera->GetPositon();
		camera->GetAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		camera->GetAxis()->RotationAxis_PivotY(D3DXToRadian(ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetLookAtPoint() = *camera->GetPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}


	// ������
	if (GetKeyboardPress(DIK_Q))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *camera->GetLookAtPoint() - *camera->GetPositon();
		camera->GetAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		camera->GetAxis()->RotationAxis_PivotY(D3DXToRadian(-ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetLookAtPoint() = *camera->GetPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}

	// �����
	if (GetKeyboardPress(DIK_T))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *camera->GetLookAtPoint() - *camera->GetPositon();
		camera->GetAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		camera->GetAxis()->RotationAxis_PivotRight(D3DXToRadian(-ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetLookAtPoint() = *camera->GetPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}

	// ������
	if (GetKeyboardPress(DIK_G))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *camera->GetLookAtPoint() - *camera->GetPositon();
		camera->GetAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		camera->GetAxis()->RotationAxis_PivotRight(D3DXToRadian(ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetLookAtPoint() = *camera->GetPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}


	// �E����( ���_���S )
	if (GetKeyboardPress(DIK_Y))
	{
		// �t�O�x�N�g���̍쐬
		Vector3D temp_vector = *camera->GetPositon() - *camera->GetLookAtPoint();
		camera->GetAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		camera->GetAxis()->RotationAxis_PivotY(D3DXToRadian(ROTATION_SPEED));

		// �J�������W�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetPositon() = *camera->GetLookAtPoint() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}
	
	// ������( ���_���S )
	if (GetKeyboardPress(DIK_H))
	{
		// �t�O�x�N�g���̍쐬
		Vector3D temp_vector = *camera->GetPositon() - *camera->GetLookAtPoint();
		camera->GetAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		camera->GetAxis()->RotationAxis_PivotY(D3DXToRadian(-ROTATION_SPEED));

		// �J�������W�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetPositon() = *camera->GetLookAtPoint()  + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}
}