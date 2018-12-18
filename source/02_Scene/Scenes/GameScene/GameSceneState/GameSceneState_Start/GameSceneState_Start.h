//================================================================================
//!	@file	 GameSceneState_Start.h
//!	@brief	 ゲームシーンステート(スタート)Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/06
//================================================================================
#ifndef	_GAME_SCENE_STATE_START_H_
#define _GAME_SCENE_STATE_START_H_



//****************************************
// インクルード文
//****************************************
#include <SceneBase/SceneBase.h>



//****************************************
// クラス宣言
//****************************************
class GameScene;



//************************************************************														   
//! @brief   ゲームシーンステート(スタート)Class
//!
//! @details ゲームシーンのステート(スタート)Class
//! @details 最初の状態を表す
//************************************************************
class GameSceneState_Start : public SceneBase::StateBase
{
//====================
// 変数
//====================
private:
	GameScene* game_scene_ = nullptr;	//!< ゲームシーン


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init() override;

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Reset() override;
};



#endif