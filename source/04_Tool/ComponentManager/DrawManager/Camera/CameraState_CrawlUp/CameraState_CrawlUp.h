//================================================================================
//!	@file	 CameraState_CrawlUp.h
//!	@brief	 這いつくばりカメラステートClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_CAMERA_STATE_CRAWL_UP_H_
#define _CAMERA_STATE_CRAWL_UP_H_



//****************************************
// インクルード文
//****************************************
#include "../Camera.h"



//************************************************************														   
//! @brief   這いつくばりカメラステートClass
//!
//! @details 這いつくばりカメラのステートClass
//************************************************************
class CameraState_CrawlUp : public Camera::State
{
//====================
// 定数
//====================
public:
	static const float TRANSLATION_SPEED;		//!< 速度
	static const float ROTATION_SPEED;			//!< 回転速度
	static const float POSITION_Y;				//!< Y座標
	static const float LOOK_AT_POSITION_Y;		//!< 注視点のY座標


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param camera カメラ
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
};



#endif