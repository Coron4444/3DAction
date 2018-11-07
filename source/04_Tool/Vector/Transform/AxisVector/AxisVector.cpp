//================================================================================
//
//    軸ベクトルクラス
//    Author : Araki Kai                                作成日 : 2018/01/08
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "AxisVector.h"



//======================================================================
//
// 定数定義
//
//======================================================================

const Vector3D AxisVector::DEFAULT_FORWARD(0.0f, 0.0f, 1.0f);
const Vector3D AxisVector::DEFAULT_UP	  (0.0f, 1.0f, 0.0f);
const Vector3D AxisVector::DEFAULT_RIGHT  (1.0f, 0.0f, 0.0f);



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

AxisVector::AxisVector()
	: forward_(DEFAULT_FORWARD), 
	  up_     (DEFAULT_UP), 
	  right_  (DEFAULT_RIGHT)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 軸ベクトルのリセット関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::ResetAxisVector()
{
	forward_ = DEFAULT_FORWARD; 
	up_      = DEFAULT_UP;
	right_   = DEFAULT_RIGHT;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 回転関数(行列) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationMatrix(MATRIX* rotation_matrix)
{
	// 前、上ベクトルの回転
	forward_.RotationVector_Matrix(rotation_matrix);
	up_.RotationVector_Matrix(rotation_matrix);

	// 右ベクトルの作成及び上ベクトルの再作成
	CalculationAxis_ConfirmAxisForward();

	// 正規化
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Xベクトル中心回転関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotX(const float radian)
{
	// 前ベクトルを回転させる
	forward_.RotationVector_AxisX(radian);

	// 上ベクトルを回転させる
	up_.RotationVector_AxisX(radian);

	// 右ベクトルの作成及び上ベクトルの再作成
	CalculationAxis_ConfirmAxisForward();

	// 正規化
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Yベクトル中心回転関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotY(const float radian)
{
	// 前ベクトルを回転させる
	forward_.RotationVector_AxisY(radian);

	// 上ベクトルを回転させる
	up_.RotationVector_AxisY(radian);

	// 右ベクトルの作成及び上ベクトルの再作成
	CalculationAxis_ConfirmAxisForward();

	// 正規化
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Zベクトル中心回転関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotZ(const float radian)
{
	// 前ベクトルを回転させる
	forward_.RotationVector_AxisZ(radian);

	// 上ベクトルを回転させる
	up_.RotationVector_AxisZ(radian);

	// 右ベクトルの作成及び上ベクトルの再作成
	CalculationAxis_ConfirmAxisForward();

	// 正規化
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 前ベクトル中心回転関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotForward(const float radian)
{
	// 上ベクトルを回転させる
	up_.RotationVector_AxisFree(forward_, radian);

	// 右ベクトルの作成及び上ベクトルの再作成
	CalculationAxis_ConfirmAxisForward();

	// 正規化
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 上ベクトル中心回転関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotUp(const float radian)
{
	// 前ベクトルを回転させる
	forward_.RotationVector_AxisFree(up_, radian);

	// 右ベクトルの作成及び上ベクトルの再作成
	CalculationAxis_ConfirmAxisForward();

	// 正規化
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 右ベクトル中心回転関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotRight(const float radian)
{
	// 前ベクトルを回転させる
	forward_.RotationVector_AxisFree(right_, radian);

	// 上ベクトルの回転
	up_.RotationVector_AxisFree(right_, radian);

	// 右ベクトルの作成及び上ベクトルの再作成
	CalculationAxis_ConfirmAxisForward();

	// 正規化
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 任意ベクトル中心回転関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotFree(const Vec3 axis_vector, const float radian)
{
	// 前ベクトルを回転させる
	forward_.RotationVector_AxisFree(axis_vector, radian);

	// 上ベクトルの回転
	up_.RotationVector_AxisFree(axis_vector, radian);

	// 右ベクトルの作成及び上ベクトルの再作成
	CalculationAxis_ConfirmAxisForward();

	// 正規化
	NormalizeAxis_All();

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 前ベクトル設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::SetForward(Vec3 forward)
{
	forward_ = forward;

	// 右ベクトルの作成及び上ベクトルの再作成
	CalculationAxis_ConfirmAxisForward();

	// 正規化
	NormalizeAxis_All();
}



//--------------------------------------------------------------------------------
//
// [ 前ベクトル1つから残りを作成する関数 ]
//
//--------------------------------------------------------------------------------

void AxisVector::CalculationAxis_ConfirmAxisForward()
{
	// 右ベクトルの作成
	right_ = up_.CreateVectorCross(forward_);

	// 上ベクトルの作成
	up_ = forward_.CreateVectorCross(right_);
}



//--------------------------------------------------------------------------------
//
// [ 全軸ベクトルの正規化関数 ]
//
//--------------------------------------------------------------------------------

void AxisVector::NormalizeAxis_All()
{
	forward_.CreateNormalize();

	up_.CreateNormalize();

	right_.CreateNormalize();

}