//================================================================================
//
//    ターゲット追跡カメラステートクラス
//    Author : Araki Kai                                作成日 : 2018/03/21
//
//================================================================================

#ifndef	_CAMERA_STATE_HOMING_TARGET_H_
#define _CAMERA_STATE_HOMING_TARGET_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../Camera.h"



//======================================================================
//
// クラス宣言
//
//======================================================================

class GameObjectOrigin;



//======================================================================
//
// クラス定義
//
//======================================================================

class CameraState_HomingTarget : public Camera::State
{
//------------------------------------------------------------
private :
	// 定数
	static const float HOMING_CAMERA_POSITION_Y;
	static const float HOMING_CAMERA_POSITION_Z;
	static const float HOMING_CAMERA_LOOK_AT_POINT_Y;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init  (Camera* camera) override;
	void Uninit(Camera* camera) override {camera = camera;}
	void Update(Camera* camera) override;

	void SetTarget(GameObjectOrigin* target) {target_ = target;}


//------------------------------------------------------------
private :
	// メンバ変数
	GameObjectOrigin* target_;
};



#endif