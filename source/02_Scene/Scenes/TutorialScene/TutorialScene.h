//================================================================================
//
//    チュートリアルシーンクラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_SCENE_H_
#define _TUTORIAL_SCENE_H_



//****************************************
// インクルード文
//****************************************
#include <SceneBase/SceneBase.h>

#include <2D/UI/TutorialLogo/TutorialLogo.h>



/*********************************************************//**
* @brief
* タイトルシーンクラス
*
* タイトルシーンのクラス
*************************************************************/
class TutorialScene : public SceneBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	TutorialLogo* tutorial_logo_;


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
	TutorialScene(StateAbstract* state) : SceneBase(state) {}

	// プロパティ
	TutorialLogo* GetTutorialLogo() { return tutorial_logo_; }
	void SetTutorialLogo(TutorialLogo* value) { tutorial_logo_ = value; }
};



#endif