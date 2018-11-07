//================================================================================
//
//    軸ベクトルクラス
//    Author : Araki Kai                                作成日 : 2018/01/08
//
//================================================================================

#ifndef	_AXIS_VECTOR_H_
#define _AXIS_VECTOR_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../../Vector3D.h"



//======================================================================
//
// クラス定義
//
//======================================================================

class AxisVector
{
//------------------------------------------------------------
private :
	static const Vector3D DEFAULT_FORWARD;
	static const Vector3D DEFAULT_UP;
	static const Vector3D DEFAULT_RIGHT;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	AxisVector();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// リセット
	void ResetAxisVector();

	// 回転
	void RotationMatrix(MATRIX* rotation_matrix);
	void RotationAxis_PivotX(const float radian);
	void RotationAxis_PivotY(const float radian);
	void RotationAxis_PivotZ(const float radian);

	void RotationAxis_PivotForward(const float radian);
	void RotationAxis_PivotUp     (const float radian);
	void RotationAxis_PivotRight  (const float radian);

	void RotationAxis_PivotFree(const Vec3 axis_vector, const float radian);

	// セット関数
	void SetForward(Vec3 forward);
	
	// ゲット関数
	const Vector3D* GetForawrd() const {return &forward_;}
	const Vector3D* GetUp     () const {return &up_;     }
	const Vector3D* GetRight  () const {return &right_;  }
	const Vector3D* GetDefaultForawrd() const {return &DEFAULT_FORWARD;}
	const Vector3D* GetDefaultUp     () const {return &DEFAULT_UP;}
	const Vector3D* GetDefaultRight  () const {return &DEFAULT_RIGHT;}


//------------------------------------------------------------
private :
	

	// 前ベクトル1つから残りを作成する
	void CalculationAxis_ConfirmAxisForward();

	// 正規化
	void NormalizeAxis_All();


//------------------------------------------------------------
private :
	// メンバ変数
	Vector3D forward_;
	Vector3D up_;
	Vector3D right_;
};



#endif