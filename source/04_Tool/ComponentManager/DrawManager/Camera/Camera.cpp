//================================================================================
//
//    カメラクラス
//    Author : Araki Kai                                作成日 : 2017/12/07
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "Camera.h"

#include <main.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const float Camera::NEAR_CLIPPING_PLANE = 0.1f;
const float Camera::FAR_CLIPPING_PLANE = 1000.0f;
const int   Camera::DEFAULT_ANGLE_OF_VIEW = 60;



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void Camera::Init(State* state, Vec3 position, Vec3 look_at_point, Vec3 up)
{
	// 各種代入
	state_ = state;
	position_ = position;
	look_at_point_ = look_at_point;
	up_ = up;
	angle_of_view_ = DEFAULT_ANGLE_OF_VIEW;

	// 軸ベクトルを作成
	axis_.SetForward(look_at_point_ - position_);

	// ステートの初期化
	if (state_ != nullptr) state_->Init(this);

	// ビュー行列の作成
	D3DXMatrixIdentity(&view_2D_);
	CreateViewMatrix();

	// プロジェクション行列の作成
	CreateProjectionMatrix_PerspectiveFov();
	CreateProjectionMatrix_Ortho();
	CreateProjectionMatrix_2D();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void Camera::Uninit()
{
	SafeRelease::PlusUninit(&state_);
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void Camera::Update()
{
	if (state_ != nullptr) state_->Update(this);

	CreateViewMatrix();
}



//--------------------------------------------------
// +ビュー行列作成関数
//--------------------------------------------------
void Camera::CreateViewMatrix()
{
	// 行列初期化
	D3DXMatrixIdentity(&view_);

	// ビュー変換行列( LHは左手座標系の意味 )
	D3DXMatrixLookAtLH(&view_, &position_, &look_at_point_, &up_);
}



//--------------------------------------------------
// +プロジェクション行列作成関数(透視投影行列)
//--------------------------------------------------
void Camera::CreateProjectionMatrix_PerspectiveFov()
{
	// 行列初期化
	D3DXMatrixIdentity(&projection_perspective_);

	D3DXMatrixPerspectiveFovLH(&projection_perspective_,
							   D3DXToRadian(angle_of_view_),
							   (float)SCREEN_WIDTH / SCREEN_HEIGHT,
							   NEAR_CLIPPING_PLANE,
							   FAR_CLIPPING_PLANE);
}



//--------------------------------------------------
// + プロジェクション行列作成関数(正射影行列)
//--------------------------------------------------
void Camera::CreateProjectionMatrix_Ortho()
{
	// 行列初期化
	D3DXMatrixIdentity(&projection_ortho_);

	D3DXMatrixOrthoLH(&projection_ortho_,
		(float)SCREEN_WIDTH  * angle_of_view_,
					  (float)SCREEN_HEIGHT * angle_of_view_,
					  NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
}



//--------------------------------------------------
// + プロジェクション行列作成関数(2D)
//--------------------------------------------------
void Camera::CreateProjectionMatrix_2D()
{
	projection_2D_
		= {2.0f / SCREEN_WIDTH,					0.0f, 0.0f, 0.0f,
						  0.0f, 2.0f / SCREEN_HEIGHT, 0.0f, 0.0f,
						  0.0f,                 0.0f, 1.0f, 0.0f,
						  0.0f,                 0.0f, 0.0f, 1.0f
	};
}



//--------------------------------------------------
// + カメラステートの変更
//--------------------------------------------------
void Camera::ChangeState(State* new_camera_state)
{
	// 終了処理
	if (state_ != nullptr) state_->Uninit();

	// 新規ステートに変更
	SafeRelease::Normal(&state_);
	state_ = new_camera_state;

	// 初期化処理
	if (state_ != nullptr) state_->Init(this);
}
