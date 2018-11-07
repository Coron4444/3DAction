//================================================================================
//
//    �v���C���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/04/01
//
//================================================================================

#ifndef	_PLAYER_H_
#define _PLAYER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Scenes/GameScene/GameScene.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Player : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init(UpdateComponent*        update_component,
			  DrawComponent*          draw_component,
			  CollisionComponent*     collision_component,
			  GameScene* game_scene);
	void Uninit() override;
	void Reset()  override;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���J�����o�ϐ�
	GameScene* game_scene_;
};



#endif