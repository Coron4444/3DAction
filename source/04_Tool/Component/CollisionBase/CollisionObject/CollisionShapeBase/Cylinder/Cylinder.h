//================================================================================
//
//    円柱クラス
//    Author : Araki Kai                                作成日 : 2017/12/21
//
//================================================================================

#ifndef	_CYLINDER_H_
#define _CYLINDER_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../CollisionShapeBase.h"

#include <Vector3D.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Cylinder : public CollisionShapeBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	Cylinder(Vec3 position0 = Vec3(0.0f, 0.0f, 0.0f), 
		     Vec3 position1 = Vec3(0.0f, 0.0f, 0.0f), 
		     float radius   = 1.0f);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	virtual ~Cylinder();



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ変数
	Vector3D position0_;
	Vector3D position1_;
	float radius_;



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

inline Cylinder::Cylinder(Vec3 position0, Vec3 position1, float radius)
	: CollisionShapeBase(CollisionShapeBase::Type::CYLINDER),
	  position0_(position0), 
	  position1_(position1), 
	  radius_   (radius)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Cylinder::~Cylinder() 
{
}



#endif