//================================================================================
//
//    �������΂�J�����X�e�[�g
//    Author : Araki Kai                                �쐬�� : 2018/03/21
//
//================================================================================

#ifndef	_CAMERA_STATE_CRAWL_UP_H_
#define _CAMERA_STATE_CRAWL_UP_H_



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "../Camera.h"





//**********************************************************************
//
// �N���X��`
//
//**********************************************************************

class CameraState_CrawlUp : public Camera::State
{
// ============================================================
private :
	// �萔
	const float TRANSLATION_SPEED;
	const float ROTATION_SPEED;
	const float POSITION_Y;
	const float LOOK_AT_POSITION_Y;

// ============================================================
public :
	// �R���X�g���N�^
	CameraState_CrawlUp();


// ============================================================
public :
	// �f�X�g���N�^
	~CameraState_CrawlUp();


// ============================================================
public :
	// �����o�֐�
	void Init  (Camera* camera) override;
	void Uninit(Camera* camera) override {camera = camera;}
	void Update(Camera* camera) override;
};



#endif