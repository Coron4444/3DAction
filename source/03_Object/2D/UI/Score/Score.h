//================================================================================
//
//    スコアクラス
//    Author : Araki Kai                                作成日 : 2018/06/19
//
//================================================================================

#ifndef	_SCORE_H_
#define _SCORE_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>
#include <Numbers\Numbers.h>
#include <Scenes/GameScene/GameScene.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Score : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(UpdateComponent*		  update_component,
		      DrawComponent*          draw_component,
		      GameScene* game_scene);
	void Uninit() override;
	void Reset()  override;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ変数
	Numbers* score_num_;
	GameScene* game_scene_;
};



#endif