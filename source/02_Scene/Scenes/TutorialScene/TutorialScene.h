//================================================================================
//!	@file	 TutorialScene.h
//!	@brief	 �`���[�g���A���V�[��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_TUTORIAL_SCENE_H_
#define _TUTORIAL_SCENE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <SceneBase/SceneBase.h>

#include <2D/UI/TutorialLogo/TutorialLogo.h>



//************************************************************														   
//! @brief   �`���[�g���A���V�[��Class
//!
//! @details �`���[�g���A���V�[�����Ǘ�����Class
//! @details �`���[�g���A���V�[�����L�̋��L�f�[�^�������Ă���
//************************************************************
class TutorialScene : public SceneBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	TutorialLogo* tutorial_logo_;		//!< �`���[�g���A�����S


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param state �ŏ��̃X�e�[�g
	//----------------------------------------
	TutorialScene(StateBase* state) : SceneBase(state) {}

	// �v���p�e�B
	TutorialLogo* getpTutorialLogo() { return tutorial_logo_; }
	void setTutorialLogo(TutorialLogo* value) { tutorial_logo_ = value; }
};



#endif