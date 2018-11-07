//================================================================================
//
//    プレイヤーファクトリークラス
//    Author : Araki Kai                                作成日 : 2018/07/23
//
//================================================================================

#ifndef	_PLAYER_FACTORY_H_
#define _PLAYER_FACTORY_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../Player.h"
#include "../PlayerUpdate/PlayerUpdate.h"
#include "../PlayerDraw/PlayerDraw.h"
#include "../PlayerCollision/PlayerCollision.h"


//======================================================================
//
// クラス定義
//
//======================================================================

class PlayerFactory
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	Player* Create(GameScene* game_scene)
	{
		Player* temp = new Player();

		// 初期化
		temp->Init(new PlayerUpdate(),
				   new PlayerDraw(),
				   new PlayerCollision(),
			       game_scene);

		return temp;
	}
};



#endif