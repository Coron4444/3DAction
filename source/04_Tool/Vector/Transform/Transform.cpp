//================================================================================
//
//    変形クラス
//    Author : Araki Kai                                作成日 : 2018/08/16
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "Transform.h"



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ コンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Transform::Transform()
	: position_		        (0.0f, 0.0f, 0.0f),
	  scale_		        (1.0f, 1.0f, 1.0f),
	  yaw_pitch_roll_       (0.0f, 0.0f, 0.0f),
	  look_at_speed_        (1.0f),
	  look_at_change_amount_(0.0f)
{
	// クォータニオンの初期化
	D3DXQuaternionIdentity(&now_quaternion_);
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionIdentity(&old_target_quaternion_);
	D3DXQuaternionIdentity(&target_quaternion_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Transform::~Transform()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 軸更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateAxisVector()
{
	// 軸をリセット
	axis_vector_.ResetAxisVector();

	// 回転行列の更新
	CreateQuaternion();
	matrix_extend_.UpdateRotationMatrix(&now_quaternion_);

	// 軸の更新
	axis_vector_.RotationMatrix(matrix_extend_.GetRotationMatrix());
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 見る方向のベクトル設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::SetLookAtVector(Vector3D look_at_vector)
{
	// 入力ベクトルの正規化
	look_at_vector.CreateNormalize();

	// 初期状態の前ベクトルと見る方向との外積を算出
	Vector3D temp_vector = axis_vector_.GetDefaultForawrd()->CreateVectorCross(look_at_vector);

	// ターゲットクォータニオンの回転角度の算出
	float temp_dot = axis_vector_.GetDefaultForawrd()->CreateVectorDot(look_at_vector);

	// 外積に使用したベクトルが平行だった場合
	if ((int)temp_vector.GetLengthSquare() == 0)
	{
		// 更にベクトルの向きが真逆だった場合
		if (temp_dot < 0)
		{
			// 初期値のクォータニオンと真逆のターゲットクォータニオンの作成
			SetTargetQuaternion(*axis_vector_.GetDefaultUp(), D3DXToRadian(180.0f));
			D3DXQuaternionInverse(&target_quaternion_, &target_quaternion_);
			return;
		}
	}


	// ターゲットクォータニオンの作成
	temp_vector.CreateNormalize();
	SetTargetQuaternion(temp_vector, acosf(temp_dot));
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ターゲットクォータニオン作成関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::SetTargetQuaternion(Vec3 axis, float angle)
{
	// 変化量をリセット
	look_at_change_amount_ = 0.0f;

	// ターゲットの保存
	old_target_quaternion_ = now_quaternion_;
	
	// クォータニオンの作成
	D3DXQuaternionIdentity(&target_quaternion_);
	D3DXQuaternionRotationAxis(&target_quaternion_, &axis, angle);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ワールド行列更新関数(SRT) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateWorldMatrixSRT()
{
	// 拡縮行列の更新
	matrix_extend_.UpdateScaleMatrix(&scale_);

	// 回転行列の更新
	CreateQuaternion();
	matrix_extend_.UpdateRotationMatrix(&now_quaternion_);

	// 平行移動行列の更新
	matrix_extend_.UpdateTranslationMatrix(&position_);

	// ワールド行列の更新
	matrix_extend_.UpdateWorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ワールド行列更新関数(ISRT) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateWorldMatrixISRT()
{
	// 拡縮行列の更新
	matrix_extend_.UpdateScaleMatrix(&scale_);

	// 回転行列の更新
	CreateQuaternion();
	matrix_extend_.UpdateRotationMatrix(&now_quaternion_);

	// 平行移動行列の更新
	matrix_extend_.UpdateTranslationMatrix(&position_);

	// ワールド行列の更新
	matrix_extend_.UpdateWorldMatrixISRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 軸＆ワールド行列更新関数(SRT) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateAxisVector_WorldMatrixSRT()
{
	// 軸
	UpdateAxisVector();

	// 拡縮行列の更新
	matrix_extend_.UpdateScaleMatrix(&scale_);

	// 平行移動行列の更新
	matrix_extend_.UpdateTranslationMatrix(&position_);

	// ワールド行列の更新
	matrix_extend_.UpdateWorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 軸＆ワールド行列更新関数(ISRT) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateAxisVector_WorldMatrixISRT()
{
	// 軸
	UpdateAxisVector();

	// 拡縮行列の更新
	matrix_extend_.UpdateScaleMatrix(&scale_);

	// 平行移動行列の更新
	matrix_extend_.UpdateTranslationMatrix(&position_);

	// ワールド行列の更新
	matrix_extend_.UpdateWorldMatrixISRT();
}



//--------------------------------------------------------------------------------
//
// [ クォータニオン作成関数 ]
//
//--------------------------------------------------------------------------------

void Transform::CreateQuaternion()
{
	// YawPitchRollクォータニオンの作成
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionRotationYawPitchRoll(&yaw_pitch_roll_quaternion_, yaw_pitch_roll_.y, yaw_pitch_roll_.x, yaw_pitch_roll_.z);

	// 球面線形補完によるクォータニオンの作成
	look_at_change_amount_ += look_at_speed_;
	if (look_at_change_amount_ >= 1.0f) look_at_change_amount_ = 1.0f;
	D3DXQuaternionSlerp(&now_quaternion_, &old_target_quaternion_, &target_quaternion_, look_at_change_amount_);

	// クォータニオンの結合
	D3DXQuaternionMultiply(&now_quaternion_, &now_quaternion_, &yaw_pitch_roll_quaternion_);
}