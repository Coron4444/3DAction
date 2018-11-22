//================================================================================
//
//    �`���[�g���A���V�[���N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_SCENE_H_
#define _TUTORIAL_SCENE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <SceneBase/SceneBase.h>

#include <2D/UI/TutorialLogo/TutorialLogo.h>



/*********************************************************//**
* @brief
* �^�C�g���V�[���N���X
*
* �^�C�g���V�[���̃N���X
*************************************************************/
class TutorialScene : public SceneBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	TutorialLogo* tutorial_logo_;


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �R���X�g���N�^
	* @param
	* state : �ŏ��̃X�e�[�g
	*/
	TutorialScene(StateAbstract* state) : SceneBase(state) {}

	// �v���p�e�B
	TutorialLogo* GetTutorialLogo() { return tutorial_logo_; }
	void SetTutorialLogo(TutorialLogo* value) { tutorial_logo_ = value; }
};



#endif