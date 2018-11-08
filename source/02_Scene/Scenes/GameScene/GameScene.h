//================================================================================
//
//    �Q�[���V�[���N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/03
//
//================================================================================

#ifndef	_GAME_SCENE_H_
#define _GAME_SCENE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <SceneBase/SceneBase.h>



/*********************************************************//**
* @brief
* �Q�[���V�[���N���X
*
* �Q�[���V�[�����Ǘ�����N���X�B
* �Q�[���V�[�����L�̋��L�f�[�^�������Ă���B
*************************************************************/
class GameScene : public SceneBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	bool is_clear_ = false;
	int score_ = 0;



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
	GameScene(StateAbstract* state) : SceneBase(state) {}

	// �v���p�e�B
	bool GetIsClear() { return is_clear_; }
	void SetIsClear(bool value) { is_clear_ = value; }
	int GetScore() { return score_; }
	void SetScore(int value) { score_ = value; }
};



#endif