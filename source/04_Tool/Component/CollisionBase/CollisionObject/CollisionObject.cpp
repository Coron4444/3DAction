//================================================================================
//
//    衝突オブジェクトクラスヘッダ
//    Author : Araki Kai                                作成日 : 2017/12/10
//
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "CollisionObject.h"

#include <SafeRelease/SafeRelease.h>


//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +コンストラクタ
//--------------------------------------------------
CollisionObject::CollisionObject(CollisionShapeBase* collision_shape, int tag)
	: collision_shape_(collision_shape),
	tag_(tag),
	is_judgment_(true)
{
}



//--------------------------------------------------
// +デストラクタ
//--------------------------------------------------
CollisionObject::~CollisionObject()
{
	switch (collision_shape_->GetType())
	{
		case CollisionShapeBase::Type::AABB:
		{
			AABB* temp = (AABB*)collision_shape_;
			SafeRelease::Normal(&temp);
			break;
		}
		case CollisionShapeBase::Type::CAPSULE:
		{
			Capsule* temp = (Capsule*)collision_shape_;
			SafeRelease::Normal(&temp);
			break;
		}
		case CollisionShapeBase::Type::CYLINDER:
		{
			Cylinder* temp = (Cylinder*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::OBB:
		{
			OBB* temp = (OBB*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::PLANE:
		{
			Plane* temp = (Plane*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::SEGMENT:
		{
			Segment* temp = (Segment*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::SPHERE:
		{
			Sphere* temp = (Sphere*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::TRIANGLE:
		{
			Triangle* temp = (Triangle*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
	}
}



//--------------------------------------------------
// +衝突用データのリセット関数
//--------------------------------------------------
void CollisionObject::ResetHitData()
{
	hit_vector_.ResetVector();
	is_judgment_ = true;
}