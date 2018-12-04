//================================================================================
//
//    変形クラス
//    Author : Araki Kai                                作成日 : 2018/08/16
//
//================================================================================

#ifndef	_TRANSFORM_H_
#define _TRANSFORM_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../Vector3D.h"
#include "AxisVector/AxisVector.h"
#include "MatrixExtend/MatrixExtend.h"
#include "LimitedPointerArray\LimitedPointerArray.h"


//======================================================================
//
// クラス定義
//
//======================================================================

class Transform
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	Transform();



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	~Transform();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 座標
	Vector3D* GetPosition(){return &position_;}

	// 拡縮
	Vector3D* GetScale(){return &scale_;}

	// 回転
	float* GetAnglePitch(){return &yaw_pitch_roll_.x;}
	float* GetAngleYaw()  {return &yaw_pitch_roll_.y;}
	float* GetAngleRoll() {return &yaw_pitch_roll_.z;}
	Vector3D* GetAngleYawPitchRoll(){return &yaw_pitch_roll_;}

	void  SetLookAtSpeed(float look_at_speed){look_at_speed_ = look_at_speed;}
	float GetLookAtSpeed(){return look_at_speed_;}
	float GetLookAtChangeAmount(){return look_at_change_amount_;}
	void  SetLookAtVector(Vector3D look_at_vector);
	void  SetTargetQuaternion(Vec3 axis, float angle);
	
	// 軸
	void UpdateAxisVector();
	const Vector3D* GetForawrd(){return axis_vector_.GetForawrd();}
	const Vector3D* GetUp(){return axis_vector_.GetUp();}
	const Vector3D* GetRight(){return axis_vector_.GetRight();}
	AxisVector* GetAxisVector(){return &axis_vector_;}

	// 行列
	void UpdateWorldMatrixSRT();
	void UpdateWorldMatrixISRT();
	void UpdateInverseMatrix(const MATRIX* matrix){matrix_extend_.UpdateInverseMatrix(matrix);}
	void UpdateTransposeMatrix(const MATRIX* matrix){matrix_extend_.UpdateTransposeMatrix(matrix);}
	void TransposeMatrixTranslationOff(){matrix_extend_.TransposeMatrixTranslationOff();}
	MATRIX* getpWorldMatrix(){return matrix_extend_.GetWorldMatrix();}
	MatrixExtend* getpMatrixExtend(){return &matrix_extend_;}

	// 全体
	void UpdateAxisVector_WorldMatrixSRT();
	void UpdateAxisVector_WorldMatrixISRT();


//------------------------------------------------------------
private :
	// 回転
	void CreateQuaternion();


//------------------------------------------------------------
private :
	// 座標
	Vector3D position_;
	
	// 拡縮
	Vector3D scale_;
	
	// 回転
	Quaternion now_quaternion_;
	Quaternion yaw_pitch_roll_quaternion_;
	Vector3D   yaw_pitch_roll_;
	Quaternion old_target_quaternion_;
	Quaternion target_quaternion_;
	float      look_at_speed_;
	float      look_at_change_amount_;
	
	// 行列
	MatrixExtend matrix_extend_;

	// 軸
	AxisVector axis_vector_;
};



#endif