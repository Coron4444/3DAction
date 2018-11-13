//================================================================================
//
//    �o�b�N�o�b�t�@�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/12
//
//================================================================================

#ifndef	_BACK_BUFFER_H_
#define _BACK_BUFFER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../Camera/Camera.h"
#include "../../Camera/CameraState_CrawlUp/CameraState_CrawlUp.h"
#include "../../Camera/CameraState_HomingTarget/CameraState_HomingTarget.h"

#include "../../Fade/Fade.h"

#include <LimitedPointerArray\LimitedPointerArray.h>



//****************************************
// �N���X�錾
//****************************************
class DrawBase;
class ShaderManager;



/*********************************************************//**
* @brief
* �o�b�N�o�b�t�@�[�N���X
*
* �o�b�N�o�b�t�@�[�֕`�悷��`����N���X���Ǘ�����N���X
*************************************************************/
class BackBuffer
{
//==============================
// �萔
//==============================
public:
	static const unsigned ARRAY_NUM = 1000;	//!< �z��



//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_opacity_draw_;		//!< �s�����z��
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_transparency_draw_;	//!< �����z��
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_2D_draw_;				//!< 2D�z��

	Camera* camera_ = false;	//!< �J����

	Fade* fade_ = false;		//!< �t�F�[�h
	bool  is_fade_ = false;		//!< �t�F�[�h���t���O

	ShaderManager* shader_manager_ = nullptr;	//!< �V�F�[�_�[�}�l�[�W��


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	void Init();

	/**
	* @brief
	* �V�[���ύX���̏I���֐�
	*/
	void UninitWhenChangeScene();

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit();

	/**
	* @brief
	* �X�V�֐�
	*/
	void Update();

	/**
	* @brief
	* �`��֐�
	*/
	void Draw();

	/**
	* @brief
	* �`����N���X�̒ǉ��֐�
	*/
	void AddDrawBaseToArray(DrawBase* draw);

	/**
	* @brief
	* �S�z��̃��Z�b�g�֐�
	*/
	void ResetAllArray();

	/**
	* @brief
	* �t�F�[�h�������֐�
	*/
	void InitFade(Fade::Type type, Fade::State state, Vec2 size, XColor4 fade_color,
				  float fade_speed);

	/**
	* @brief
	* �t�F�[�h�I���֐�
	*/
	void UninitFade();

	/**
	* @brief
	* �t�F�[�h�I�����̊m�F�֐�
	*/
	bool IsFadeEnd() { return fade_->GetEndFlag(); }

	/**
	* @brief
	* �t�F�[�h�X�e�[�g�̖��O����֐�
	*/
	bool IsFadeStateName(Fade::State state) { return *fade_->GetState() == state; }

	// �v���p�e�B
	Camera* GetCamera() { return camera_; }
	void SetShaderManager(ShaderManager* value) { shader_manager_ = value; }

private:
	/**
	* @brief
	* �����`��R���|�[�l���g�̃\�[�g�֐�
	*/
	void SortTransparent();

	/**
	* @brief
	* �r���{�[�h�p�s��ύX�֐�
	*/
	void SetBillboardMatrix(DrawBase* draw);
	
	/**
	* @brief
	* �S�r���{�[�h�X�V�֐�
	*/
	void AllBillboardUpdate();

	/**
	* @brief
	* �t�F�[�h�`��֐�
	*/
	void FadeDraw();
};



#endif
