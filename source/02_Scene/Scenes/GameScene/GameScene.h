//================================================================================
//
//    ゲームシーンクラス
//    Author : Araki Kai                                作成日 : 2018/07/03
//
//================================================================================

#ifndef	_GAME_SCENE_H_
#define _GAME_SCENE_H_



//****************************************
// インクルード文
//****************************************
#include <SceneBase/SceneBase.h>



/*********************************************************//**
* @brief
* ゲームシーンクラス
*
* ゲームシーンを管理するクラス。
* ゲームシーン特有の共有データを持っている。
*************************************************************/
class GameScene : public SceneBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	bool is_clear_ = false;
	int score_ = 0;



//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* コンストラクタ
	* @param
	* state : 最初のステート
	*/
	GameScene(StateAbstract* state) : SceneBase(state) {}

	// プロパティ
	bool GetIsClear() { return is_clear_; }
	void SetIsClear(bool value) { is_clear_ = value; }
	int GetScore() { return score_; }
	void SetScore(int value) { score_ = value; }
};



#endif