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
#include <SceneBace/SceneBace.h>



//****************************************
// �N���X�錾
//****************************************
class GameObjectOrigin;



/*********************************************************//**
* @brief
* �^�C�g���V�[���N���X
*
* �^�C�g���V�[���̃N���X
*************************************************************/
class TutorialScene : public SceneBace
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	GameObjectOrigin* logo_;



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
	TutorialScene(StateAbstract* state) : SceneBace(state) {}

	// �v���p�e�B
	GameObjectOrigin* GetLogo() { return logo_; }
	void SetLogo(GameObjectOrigin* value) { logo_ = value; }
};



#endif