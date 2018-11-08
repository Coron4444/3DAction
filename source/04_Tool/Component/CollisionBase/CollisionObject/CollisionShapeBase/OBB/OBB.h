//================================================================================
//
//    OBBクラス
//    Author : Araki Kai                                作成日 : 2017/11/27
//
//================================================================================

#ifndef	_OBB_H_
#define _OBB_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../CollisionShapeBase.h"

#include <Vector3D.h>
#include <Transform\AxisVector\AxisVector.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class OBB : public CollisionShapeBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	OBB(float lenght_right   = 1.0f, 
		float lenght_up      = 1.0f, 
		float lenght_forward = 1.0f, 
		Vec3 position		 = Vec3(0.0f, 0.0f, 0.0f));


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	virtual ~OBB();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ゲッタ
	Vector3D* GetVectorForward();
	Vector3D* GetVectorUp     ();
	Vector3D* GetVectorRight  ();

	Vector3D* GetVectorForwardHalf();
	Vector3D* GetVectorUpHalf     ();
	Vector3D* GetVectorRightHalf  ();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ変数
	Vector3D   position_;
	AxisVector axis_;
	float      lenght_right_;
	float      lenght_up_;
	float      lenght_forward_;




//------------------------------------------------------------
private	:
	// 非公開メンバ変数
	Vector3D   math_vector_;
};






//======================================================================
//
// 非静的メンバ関数定義( inline )
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトコンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline OBB::OBB(float lenght_right, float lenght_up, float lenght_forward, Vec3 position )
	: CollisionShapeOrigin(CollisionShapeOrigin::Type::TYPE_OBB),
	  lenght_right_  ( lenght_right ),
	  lenght_up_     ( lenght_up ),
	  lenght_forward_( lenght_forward ),
	  position_      ( position )
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline OBB::~OBB() 
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 前ベクトルを取得 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorForward() 
{
	math_vector_ = *axis_.GetForawrd();

	math_vector_.AnyLengthVector(lenght_forward_);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 上ベクトルを取得 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorUp() 
{
	math_vector_ = *axis_.GetUp();

	math_vector_.AnyLengthVector(lenght_up_);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 右ベクトルを取得 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorRight() 
{
	math_vector_ = *axis_.GetRight();

	math_vector_.AnyLengthVector(lenght_right_);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 前ベクトルを取得( 半分 ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorForwardHalf() 
{
	math_vector_ = *axis_.GetForawrd();

	math_vector_.AnyLengthVector(lenght_forward_ / 2);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 上ベクトルを取得( 半分 ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorUpHalf() 
{
	math_vector_ = *axis_.GetUp();

	math_vector_.AnyLengthVector(lenght_up_ / 2);

	return &math_vector_;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 右ベクトルを取得( 半分 ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D* OBB::GetVectorRightHalf() 
{
	math_vector_ = *axis_.GetRight();

	math_vector_.AnyLengthVector(lenght_right_ / 2);

	return &math_vector_;
}




//======================================================================
//
// 非メンバ関数宣言
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 1次元線分と点のはみ出し部分のベクトルを求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void OverhangingPartOBB_Segment1D_Point( Vector3D* shortest_distance_vector, 
	                                            const Vector3D* obb_position, 
	                                            const Vector3D* obb_vector_half,
											    const Vector3D* obb_axis_vector,
	                                            const Vector3D* point )
{
	// 長さが0以上か
	float temp_length = obb_vector_half -> GetLength();
	if ( temp_length <= 0.0f ) return;
	
	// 点から直線に垂線を降ろしたときの交点の位置を表す値(tとする)を算出
	Vector3D temp_vector = *point - *obb_position;
	float t = temp_vector.CreateVectorDot( *obb_axis_vector ) / temp_length;

	// はみ出した部分のベクトルを算出
	if ( t < -1.0f )
	{
		*shortest_distance_vector += ( t + 1.0f ) * ( *obb_vector_half );
	}
	else if ( t > 1.0f )
	{
		*shortest_distance_vector += ( t - 1.0f ) * ( *obb_vector_half );
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ OBBと点の最短距離のベクトルを求める関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D ShortestDistance_OBB_Point( OBB* obb, const Vector3D* point )
{
	// OBBまでの最短距離を求めるベクトル
	Vector3D temp_vector;
	
	// 各軸に対してはみ出し部分を算出
	OverhangingPartOBB_Segment1D_Point( &temp_vector, 
	                                    &obb -> position_,
									    obb -> GetVectorForwardHalf(),
								        obb ->axis_.GetForawrd(),
	                                    point );

	OverhangingPartOBB_Segment1D_Point( &temp_vector, 
	                                    &obb -> position_,
									    obb -> GetVectorRightHalf(),
								        obb ->axis_.GetRight(),
	                                    point );

	OverhangingPartOBB_Segment1D_Point( &temp_vector, 
	                                    &obb -> position_,
									    obb -> GetVectorUpHalf(),
								        obb ->axis_.GetUp(),
	                                    point );
	return temp_vector;
}



#endif