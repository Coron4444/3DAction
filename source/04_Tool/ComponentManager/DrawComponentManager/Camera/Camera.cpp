//================================================================================
//
//    カメラクラス
//    Author : Araki Kai                                作成日 : 2017/12/07
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "Camera.h"

#include <main.h>
#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const float Camera::NEAR_CLIPPING_PLANE   = 0.1f;
const float Camera::FAR_CLIPPING_PLANE    = 1000.0f;
const int   Camera::DEFAULT_ANGLE_OF_VIEW = 60;



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ コンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Camera::Camera(State* state, Type type, Vec3 position, Vec3 look_at_point, Vec3 up)
	: state_        (state),
	  type_         (type),
	  position_     (position), 
	  look_at_point_(look_at_point), 
	  up_			(up),
	  angle_of_view_(DEFAULT_ANGLE_OF_VIEW)
{
	// 軸ベクトルを作成
	axis_.SetForward(look_at_point_ - position_);

	// ステートの初期化
	if (state_ != nullptr) state_->Init(this);

	// ビュー行列の作成
	CreateViewMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Camera::~Camera()
{
	SafeRelease::Normal(&state_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ カメラ更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::Update()
{
	if (state_ != nullptr) state_->Update(this);

	CreateViewMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ビュー行列作成関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::CreateViewMatrix()
{
	// ビュー変換行列( LHは左手座標系の意味 )
	D3DXMatrixLookAtLH(&matrix_view_, &position_, &look_at_point_, &up_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ プロジェクション行列作成関数() ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::CreateProjectionMatrix(float angle_of_view, float aspect, 
									float near_clipping_plane, float far_clipping_plane)
{
	D3DXMatrixPerspectiveFovLH(&matrix_projection_,
							   D3DXToRadian(angle_of_view),
							   aspect,
							   near_clipping_plane,
							   far_clipping_plane);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ プロジェクション行列作成関数(透視投影行列) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::CreateProjectionMatrix_PerspectiveFov()
{
	D3DXMatrixPerspectiveFovLH(&matrix_projection_, 
							   D3DXToRadian(angle_of_view_), 
							   (float)SCREEN_WIDTH / SCREEN_HEIGHT, 
							   NEAR_CLIPPING_PLANE, 
							   FAR_CLIPPING_PLANE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ プロジェクション行列作成関数(正射影行列) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::CreateProjectionMatrix_Ortho()
{
	D3DXMatrixOrthoLH(&matrix_projection_, 
		              (float)SCREEN_WIDTH  * angle_of_view_,
		              (float)SCREEN_HEIGHT * angle_of_view_,
		              NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ カメラステートの変更関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Camera::ChangeState(State* new_camera_state)
{
	// 終了処理
	if (state_ != nullptr) state_->Uninit(this);

	// 新規ステートに変更
	SafeRelease::Normal(&state_);
	state_ = new_camera_state;

	// 初期化処理
	if (state_ != nullptr) state_->Init(this);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ カメラタイプ判定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool Camera::IsCameraTypeName(Type type)
{
	return type_ == type;
}