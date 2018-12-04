//================================================================================
//!	@file	 TutorialScene.h
//!	@brief	 チュートリアルシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_TUTORIAL_SCENE_H_
#define _TUTORIAL_SCENE_H_



//****************************************
// インクルード文
//****************************************
#include <SceneBase/SceneBase.h>

#include <2D/UI/TutorialLogo/TutorialLogo.h>



//************************************************************														   
//! @brief   チュートリアルシーンClass
//!
//! @details チュートリアルシーンを管理するClass
//! @details チュートリアルシーン特有の共有データを持っている
//************************************************************
class TutorialScene : public SceneBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	TutorialLogo* tutorial_logo_;		//!< チュートリアルロゴ


//==============================
// 非静的メンバ関数
//==============================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param state 最初のステート
	//----------------------------------------
	TutorialScene(StateBase* state) : SceneBase(state) {}

	// プロパティ
	TutorialLogo* getpTutorialLogo() { return tutorial_logo_; }
	void setTutorialLogo(TutorialLogo* value) { tutorial_logo_ = value; }
};



#endif