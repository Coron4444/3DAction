//================================================================================
//!	@file	 GameScene.h
//!	@brief	 ゲームシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_GAME_SCENE_H_
#define _GAME_SCENE_H_



//****************************************
// インクルード文
//****************************************
#include <SceneBase/SceneBase.h>



//************************************************************														   
//! @brief   ゲームシーンClass
//!
//! @details ゲームシーンを管理するClass
//! @details ゲームシーン特有の共有データを持っている
//************************************************************
class GameScene : public SceneBase
{
//====================
// 変数
//====================
private:
	bool is_clear_ = false;		//!< クリアフラグ
	int score_ = 0;				//!< スコア
	int game_over_ = -1;		//!< ゲームオーバーフラグ


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param state 最初のステート
	//----------------------------------------
	GameScene(StateBase* state) : SceneBase(state) {}

	// プロパティ
	bool getIsClear() { return is_clear_; }
	void setIsClear(bool value) { is_clear_ = value; }
	int getScore() { return score_; }
	void setScore(int value) { score_ = value; }
	int getGameOver() { return game_over_; }
	void setGameOver(int value) { game_over_ = value; }
};



#endif