//================================================================================
//
//    �X�R�A�N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================

#ifndef	_SCORE_H_
#define _SCORE_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>
#include <Numbers\Numbers.h>
#include <Scenes/GameScene/GameScene.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Score : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init(UpdateComponent*		  update_component,
		      DrawComponent*          draw_component,
		      GameScene* game_scene);
	void Uninit() override;
	void Reset()  override;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���J�����o�ϐ�
	Numbers* score_num_;
	GameScene* game_scene_;
};



#endif