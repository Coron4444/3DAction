//================================================================================
//!	@file	 CollisionBase.cpp
//!	@brief	 衝突BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "CollisionBase.h"



//****************************************
// プロパティ定義
//****************************************
unsigned CollisionBase::getEndIndexOfArray()
{
	return collision_objects_.GetEndPointer();
}



CollisionObjects* CollisionBase::getpCollisionObjects(unsigned index)
{
	return collision_objects_.GetArrayObject(index);
}



CollisionBase::Type CollisionBase::getType()
{
	return type_;
}



void CollisionBase::setType(CollisionBase::Type value)
{
	type_ = value;
}



bool CollisionBase::getIsJudgmentGround()
{
	return is_judgment_ground_;
}



void CollisionBase::setIsJudgmentGround(bool value)
{
	is_judgment_ground_ = value;
}



//****************************************
// 関数定義
//****************************************
CollisionBase::~CollisionBase()
{
}



void CollisionBase::AddCollisionObjectsToArray(CollisionObjects* object)
{
	collision_objects_.AddToArray(object);
}



void CollisionBase::OverwriteArrayCollisionsObject(CollisionObjects* old_object,
												   CollisionObjects* new_object)
{
	old_object->ReleaseAllCollisionObjectFromArray();
	collision_objects_.OverwriteArray(old_object, new_object);
}



void CollisionBase::ReleaseCollisionObjectsFromArray(CollisionObjects* object)
{
	object->ReleaseAllCollisionObjectFromArray();
	collision_objects_.DeleteFromArrayAndSortArray(object);
}



void CollisionBase::ReleaseAllCollisionObjectsFromArray()
{
	for (unsigned i = 0; i < collision_objects_.GetEndPointer(); i++)
	{
		collision_objects_.GetArrayObject(i)
			->ReleaseAllCollisionObjectFromArray();
	}
	collision_objects_.ReleaseObjectAndResetArray();
}



void CollisionBase::EliminationOfNesting(Transform* transform, const Vec3* hit_vector)
{
	*transform->GetPosition() += *hit_vector;
	transform->UpdateWorldMatrixISRT();
}