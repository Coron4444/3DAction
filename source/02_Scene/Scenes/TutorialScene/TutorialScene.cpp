//================================================================================
//!	@file	 TutorialScene.cpp
//!	@brief	 チュートリアルシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "TutorialScene.h"



//****************************************
// プロパティ定義
//****************************************
TutorialLogo* TutorialScene::getpTutorialLogo()
{ 
	return tutorial_logo_; 
}

void TutorialScene::setTutorialLogo(TutorialLogo* value)
{ 
	tutorial_logo_ = value; 
}



//****************************************
// 関数定義
//****************************************
TutorialScene::TutorialScene(StateBase* state)
	: SceneBase(state)
{
}