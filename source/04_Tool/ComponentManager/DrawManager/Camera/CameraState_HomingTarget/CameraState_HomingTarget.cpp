//================================================================================
//
//    ターゲット追跡カメラステートクラス
//    Author : Araki Kai                                作成日 : 2018/03/21
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "CameraState_HomingTarget.h"
#include <GameObjectBase/GameObjectBase.h>

#include <Vector3D.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const float CameraState_HomingTarget::HOMING_CAMERA_POSITION_Y      = 5.0f;
const float CameraState_HomingTarget::HOMING_CAMERA_POSITION_Z      = -15.0f;
const float CameraState_HomingTarget::HOMING_CAMERA_LOOK_AT_POINT_Y = 1.0f;



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CameraState_HomingTarget::Init(Camera* camera)
{
	Update(camera);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CameraState_HomingTarget::Update(Camera* camera)
{
	if (target_ == nullptr) return;

	// カメラポジションの作成
	*camera->GetPositon() = *target_->GetTransform()->GetPosition();

	camera->GetPositon()->y += HOMING_CAMERA_POSITION_Y;
	camera->GetPositon()->z += HOMING_CAMERA_POSITION_Z;

	// 注視点の作成
	Vec3 temp_position = *target_->GetTransform()->GetPosition();
	temp_position.y += HOMING_CAMERA_LOOK_AT_POINT_Y;
	*camera->GetLookAtPoint() = temp_position;
}