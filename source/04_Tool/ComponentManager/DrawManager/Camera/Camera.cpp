//================================================================================
//!	@file	 Camera.cpp
//!	@brief	 カメラClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
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
// プロパティ定義
//****************************************
Camera* Camera::State::getpCamera()
{
	return camera_;
}



void Camera::State::setCamera(Camera* value)
{
	camera_ = value;
}



const MATRIX* Camera::getpViewMatrix() const
{
	if (type_ == Type::TWO_DIMENSIONAL) return &view_2D_;
	return &view_;
}



const MATRIX* Camera::getpProjectionMatrix() const
{
	if (type_ == Type::PERSPECTIVE) return &projection_perspective_;
	if (type_ == Type::ORTHO) return &projection_ortho_;
	return &projection_2D_;
}



Vector3D* Camera::getpPositon()
{
	return &position_;
}



Vector3D* Camera::getpLookAtPoint()
{
	return &look_at_point_;
}



Vector3D* Camera::getpUp()
{
	return &up_;
}



int Camera::getAngleOfView()
{
	return angle_of_view_;
}



void Camera::setAngleOfView(int value)
{
	angle_of_view_ = value;
	CreateProjectionMatrix_PerspectiveFov();
	CreateProjectionMatrix_Ortho();
}



AxisVector* Camera::getpAxis()
{
	return &axis_;
}



const Vector3D* Camera::getpForwardVector() const
{
	return axis_.GetForawrd();
}



const Camera::State* Camera::getpState() const
{
	return state_;
}



void Camera::setState(Camera::State* value)
{
	if (state_ != nullptr)
	{
		SafeRelease::PlusUninit(&state_);
	}

	state_ = value;

	if (state_ != nullptr)
	{
		state_->setCamera(this);
		state_->Init();
	}
}



Camera::Type Camera::getType()
{
	return type_;
}



void Camera::setType(Camera::Type value)
{
	type_ = value;
}



//****************************************
// 関数定義
//****************************************
Camera::State::~State()
{
}



void Camera::Init(State* state, Vec3 position, Vec3 look_at_point, Vec3 up)
{
	// 各種代入
	position_ = position;
	look_at_point_ = look_at_point;
	up_ = up;
	angle_of_view_ = DEFAULT_ANGLE_OF_VIEW;

	// 軸ベクトルを作成
	axis_.SetForward(look_at_point_ - position_);

	// ステートの初期化
	setState(state);

	// ビュー行列の作成
	D3DXMatrixIdentity(&view_2D_);
	CreateViewMatrix();

	// プロジェクション行列の作成
	CreateProjectionMatrix_PerspectiveFov();
	CreateProjectionMatrix_Ortho();
	CreateProjectionMatrix_2D();
}



void Camera::Uninit()
{
	SafeRelease::PlusUninit(&state_);
}



void Camera::Update()
{
	if (state_ != nullptr) state_->Update();

	CreateViewMatrix();
}



void Camera::CreateViewMatrix()
{
	// 行列初期化
	D3DXMatrixIdentity(&view_);

	// ビュー変換行列( LHは左手座標系の意味 )
	D3DXMatrixLookAtLH(&view_, &position_, &look_at_point_, &up_);
}



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



void Camera::CreateProjectionMatrix_Ortho()
{
	// 行列初期化
	D3DXMatrixIdentity(&projection_ortho_);

	D3DXMatrixOrthoLH(&projection_ortho_,
		(float)SCREEN_WIDTH  * angle_of_view_,
					  (float)SCREEN_HEIGHT * angle_of_view_,
					  NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
}



void Camera::CreateProjectionMatrix_2D()
{
	projection_2D_
		= {2.0f / SCREEN_WIDTH,					0.0f, 0.0f, 0.0f,
						  0.0f, 2.0f / SCREEN_HEIGHT, 0.0f, 0.0f,
						  0.0f,                 0.0f, 1.0f, 0.0f,
						  0.0f,                 0.0f, 0.0f, 1.0f
	};
}