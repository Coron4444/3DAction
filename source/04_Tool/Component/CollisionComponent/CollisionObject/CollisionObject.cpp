//================================================================================
//
//    衝突オブジェクトクラスヘッダ
//    Author : Araki Kai                                作成日 : 2017/12/10
//
//================================================================================


//======================================================================
//
// インクルード文
//
//======================================================================

#include "CollisionObject.h"

#include <SafeRelease/SafeRelease.h>



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

CollisionObject::CollisionObject(CollisionShapeOrigin* collision_shape,
								 int tag)
	: collision_shape_(collision_shape),
	  is_judgment_    (true),
	  tag_			  (tag)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

CollisionObject::~CollisionObject()
{
	switch(collision_shape_->GetType())
	{
		case CollisionShapeOrigin::Type::TYPE_AABB :
		{
			AABB* temp = (AABB*)collision_shape_;
			SafeRelease::Normal(&temp);
			break;
		}
		case CollisionShapeOrigin::Type::TYPE_CAPSULE :
		{
			Capsule* temp = (Capsule*)collision_shape_;
			SafeRelease::Normal(&temp);
			break;
		}
		case CollisionShapeOrigin::Type::TYPE_CYLINDER :
		{
			Cylinder* temp = (Cylinder*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeOrigin::Type::TYPE_OBB :
		{
			OBB* temp = (OBB*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeOrigin::Type::TYPE_PLANE :
		{
			Plane* temp = (Plane*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeOrigin::Type::TYPE_SEGMENT :
		{
			Segment* temp = (Segment*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeOrigin::Type::TYPE_SPHERE :
		{
			Sphere* temp = (Sphere*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeOrigin::Type::TYPE_TRIANGLE :
		{
			Triangle* temp = (Triangle*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突用データリセット関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionObject::ResetHitData()
{
	hit_vector_.ResetVector();
	is_judgment_ = true;
}