//================================================================================
//!	@file	 GameScene.cpp
//!	@brief	 ゲームシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "GameScene.h"



//****************************************
// プロパティ定義
//****************************************
bool GameScene::getIsClear() 
{ 
	return is_clear_; 
}



void GameScene::setIsClear(bool value) 
{ 
	is_clear_ = value; 
}



int GameScene::getScore() 
{ 
	return score_; 
}



void GameScene::setScore(int value) 
{ 
	score_ = value; 
}



int GameScene::getGameOver() 
{ 
	return game_over_; 
}



void GameScene::setGameOver(int value) 
{
	game_over_ = value; 
}



//****************************************
// 関数定義
//****************************************
GameScene::GameScene(StateBase* state)
	: SceneBase(state) 
{
}