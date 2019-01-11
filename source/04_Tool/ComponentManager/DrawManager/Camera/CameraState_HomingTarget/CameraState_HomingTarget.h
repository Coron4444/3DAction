//================================================================================
//!	@file	 CameraState_HomingTarget.h
//!	@brief	 ターゲット追跡カメラステートClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_CAMERA_STATE_HOMING_TARGET_H_
#define _CAMERA_STATE_HOMING_TARGET_H_



//****************************************
// インクルード文
//****************************************
#include "../Camera.h"



//****************************************
// クラス宣言
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   ターゲット追跡カメラステートClass
//!
//! @details ターゲット追跡のカメラステートClass
//************************************************************
class CameraState_HomingTarget : public Camera::State
{
//====================
// 定数
//====================
public:
	static const float HOMING_CAMERA_POSITION_Y;		//!< Y座標
	static const float HOMING_CAMERA_POSITION_Z;		//!< Z座標
	static const float HOMING_CAMERA_LOOK_AT_POINT_Y;	//!< 注視点のY座標


//====================
// 変数
//====================
private:
	GameObjectBase* target_object_;		//!< ターゲットオブジェクト

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ターゲットオブジェクト設定関数
	//! @details
	//! @param value ターゲットオブジェクト
	//! @retval void シーンマネージャ
	//----------------------------------------
	void setTargetObject(GameObjectBase* value);


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