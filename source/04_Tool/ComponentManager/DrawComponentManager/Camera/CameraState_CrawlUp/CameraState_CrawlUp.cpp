//================================================================================
//
//    這いつくばりカメラステート
//    Author : Araki Kai                                作成日 : 2018/03/21
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "CameraState_CrawlUp.h"

#include <Keyboard\Keyboard.h>



//**********************************************************************
//
// 非静的メンバ関数定義
//
//**********************************************************************

//================================================================================
//
// [ コンストラクタ ]
//
//================================================================================

CameraState_CrawlUp::CameraState_CrawlUp()
	: // 定数
	  TRANSLATION_SPEED(0.1f),
	  ROTATION_SPEED   (0.8f),
	  POSITION_Y       (8.0f),
	  LOOK_AT_POSITION_Y(POSITION_Y - 5.0f)
{
}



//================================================================================
//
// [ デストラクタ ]
//
//================================================================================

CameraState_CrawlUp::~CameraState_CrawlUp()
{
}



//================================================================================
//
// [ 初期化関数 ]
//
//================================================================================

void CameraState_CrawlUp::Init(Camera* camera)
{
	camera->GetPositon()->y     = POSITION_Y;
	camera->GetLookAtPoint()->y = LOOK_AT_POSITION_Y;
}



//================================================================================
//
// [ 更新関数 ]
//
//================================================================================

void CameraState_CrawlUp::Update(Camera* camera)
{
	// 前
	if (GetKeyboardPress(DIK_I))
	{
		// 前ベクトルを保存
		Vector3D temp_vector = *camera->GetAxis()->GetForawrd();

		// 地をはう準備
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*camera->GetPositon() += temp_vector;
		*camera->GetLookAtPoint() += temp_vector;
	}

	// 後ろ
	if (GetKeyboardPress(DIK_K))
	{
		// 前ベクトルを保存
		Vector3D temp_vector = *camera->GetAxis()->GetForawrd();

		// 地をはう準備
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*camera->GetPositon() += -temp_vector;
		*camera->GetLookAtPoint() += -temp_vector;
	}


	// 右
	if (GetKeyboardPress(DIK_L))
	{
		// 右ベクトルを保存
		Vector3D temp_vector = *camera->GetAxis()->GetRight();

		// 地をはう準備
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*camera->GetPositon() += temp_vector;
		*camera->GetLookAtPoint() += temp_vector;
	}


	// 左
	if (GetKeyboardPress(DIK_J))
	{
		// 右ベクトルを保存
		Vector3D temp_vector = *camera->GetAxis()->GetRight();

		// 地をはう準備
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*camera->GetPositon() += -temp_vector;
		*camera->GetLookAtPoint() += -temp_vector;
	}


	// 右周り
	if (GetKeyboardPress(DIK_E))
	{
		// 前ベクトルの作成
		Vector3D temp_vector = *camera->GetLookAtPoint() - *camera->GetPositon();
		camera->GetAxis()->SetForward(temp_vector);

		// 軸ベクトルの回転
		camera->GetAxis()->RotationAxis_PivotY(D3DXToRadian(ROTATION_SPEED));

		// 注視点の作成
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetLookAtPoint() = *camera->GetPositon() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}


	// 左周り
	if (GetKeyboardPress(DIK_Q))
	{
		// 前ベクトルの作成
		Vector3D temp_vector = *camera->GetLookAtPoint() - *camera->GetPositon();
		camera->GetAxis()->SetForward(temp_vector);

		// 軸ベクトルの回転
		camera->GetAxis()->RotationAxis_PivotY(D3DXToRadian(-ROTATION_SPEED));

		// 注視点の作成
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetLookAtPoint() = *camera->GetPositon() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}

	// 上周り
	if (GetKeyboardPress(DIK_T))
	{
		// 前ベクトルの作成
		Vector3D temp_vector = *camera->GetLookAtPoint() - *camera->GetPositon();
		camera->GetAxis()->SetForward(temp_vector);

		// 軸ベクトルの回転
		camera->GetAxis()->RotationAxis_PivotRight(D3DXToRadian(-ROTATION_SPEED));

		// 注視点の作成
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetLookAtPoint() = *camera->GetPositon() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}

	// 下周り
	if (GetKeyboardPress(DIK_G))
	{
		// 前ベクトルの作成
		Vector3D temp_vector = *camera->GetLookAtPoint() - *camera->GetPositon();
		camera->GetAxis()->SetForward(temp_vector);

		// 軸ベクトルの回転
		camera->GetAxis()->RotationAxis_PivotRight(D3DXToRadian(ROTATION_SPEED));

		// 注視点の作成
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetLookAtPoint() = *camera->GetPositon() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}


	// 右周り( 視点中心 )
	if (GetKeyboardPress(DIK_Y))
	{
		// 逆前ベクトルの作成
		Vector3D temp_vector = *camera->GetPositon() - *camera->GetLookAtPoint();
		camera->GetAxis()->SetForward(temp_vector);

		// 軸ベクトルの回転
		camera->GetAxis()->RotationAxis_PivotY(D3DXToRadian(ROTATION_SPEED));

		// カメラ座標の作成
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetPositon() = *camera->GetLookAtPoint() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}
	
	// 左周り( 視点中心 )
	if (GetKeyboardPress(DIK_H))
	{
		// 逆前ベクトルの作成
		Vector3D temp_vector = *camera->GetPositon() - *camera->GetLookAtPoint();
		camera->GetAxis()->SetForward(temp_vector);

		// 軸ベクトルの回転
		camera->GetAxis()->RotationAxis_PivotY(D3DXToRadian(-ROTATION_SPEED));

		// カメラ座標の作成
		float length = temp_vector.GetLength();
		temp_vector = *camera->GetAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*camera->GetPositon() = *camera->GetLookAtPoint()  + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		camera->GetAxis()->SetForward(*camera->GetLookAtPoint() - *camera->GetPositon());
	}
}