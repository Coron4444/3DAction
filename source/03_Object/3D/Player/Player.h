//================================================================================
//
//    プレイヤークラス
//    Author : Araki Kai                                作成日 : 2018/04/01
//
//================================================================================

#ifndef	_PLAYER_H_
#define _PLAYER_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Scenes/GameScene/GameScene.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Player : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(UpdateComponent*        update_component,
			  DrawComponent*          draw_component,
			  CollisionComponent*     collision_component,
			  GameScene* game_scene);
	void Uninit() override;
	void Reset()  override;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ変数
	GameScene* game_scene_;
};



#endif