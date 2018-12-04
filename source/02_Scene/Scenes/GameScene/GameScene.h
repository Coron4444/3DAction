//================================================================================
//!	@file	 GameScene.h
//!	@brief	 �Q�[���V�[��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_GAME_SCENE_H_
#define _GAME_SCENE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <SceneBase/SceneBase.h>



//************************************************************														   
//! @brief   �Q�[���V�[��Class
//!
//! @details �Q�[���V�[�����Ǘ�����Class
//! @details �Q�[���V�[�����L�̋��L�f�[�^�������Ă���
//************************************************************
class GameScene : public SceneBase
{
//====================
// �ϐ�
//====================
private:
	bool is_clear_ = false;		//!< �N���A�t���O
	int score_ = 0;				//!< �X�R�A
	int game_over_ = -1;		//!< �Q�[���I�[�o�[�t���O


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param state �ŏ��̃X�e�[�g
	//----------------------------------------
	GameScene(StateBase* state) : SceneBase(state) {}

	// �v���p�e�B
	bool getIsClear() { return is_clear_; }
	void setIsClear(bool value) { is_clear_ = value; }
	int getScore() { return score_; }
	void setScore(int value) { score_ = value; }
	int getGameOver() { return game_over_; }
	void setGameOver(int value) { game_over_ = value; }
};



#endif