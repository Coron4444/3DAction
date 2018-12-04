//================================================================================
//!	@file	 TitleScene.h
//!	@brief	 タイトルシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_TITLE_SCENE_H_
#define _TITLE_SCENE_H_



//****************************************
// インクルード文
//****************************************
#include <SceneBase/SceneBase.h>



//************************************************************														   
//! @brief   タイトルシーンClass
//!
//! @details タイトルシーンを管理するClass
//! @details タイトルシーン特有の共有データを持っている
//************************************************************
class TitleScene : public SceneBase
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param state 最初のステート
	//----------------------------------------
	TitleScene(StateBase* state) : SceneBase(state) {}
};



#endif