//================================================================================
//!	@file	 CameraState_HomingTarget.cpp
//!	@brief	 ターゲット追跡カメラステートClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "CameraState_HomingTarget.h"

#include <GameObjectBase/GameObjectBase.h>
#include <Vector3D.h>



//****************************************
// 定数定義
//****************************************
const float CameraState_HomingTarget::HOMING_CAMERA_POSITION_Y = 5.0f;
const float CameraState_HomingTarget::HOMING_CAMERA_POSITION_Z = -15.0f;
const float CameraState_HomingTarget::HOMING_CAMERA_LOOK_AT_POINT_Y = 1.0f;



//****************************************
// プロパティ定義
//****************************************
void CameraState_HomingTarget::setTargetObject(GameObjectBase* value) 
{
	target_object_ = value; 
}



//****************************************
// 関数定義
//****************************************
void CameraState_HomingTarget::Init()
{
	Update();
}



void CameraState_HomingTarget::Uninit()
{
}



void CameraState_HomingTarget::Update()
{
	if (target_object_ == nullptr) return;

	// カメラポジションの作成
	*getpCamera()->getpPositon() = *target_object_->GetTransform()->GetPosition();

	getpCamera()->getpPositon()->y += HOMING_CAMERA_POSITION_Y;
	getpCamera()->getpPositon()->z += HOMING_CAMERA_POSITION_Z;

	// 注視点の作成
	Vec3 temp_position = *target_object_->GetTransform()->GetPosition();
	temp_position.y += HOMING_CAMERA_LOOK_AT_POINT_Y;
	*getpCamera()->getpLookAtPoint() = temp_position;
}