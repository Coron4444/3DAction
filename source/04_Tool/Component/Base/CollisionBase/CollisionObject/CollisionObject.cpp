//================================================================================
//
//    �Փ˃I�u�W�F�N�g�N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2017/12/10
//
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionObject.h"

#include <SafeRelease/SafeRelease.h>


//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�R���X�g���N�^
//--------------------------------------------------
CollisionObject::CollisionObject(CollisionShapeBase* collision_shape, int tag)
	: collision_shape_(collision_shape),
	tag_(tag),
	is_judgment_(true)
{
}



//--------------------------------------------------
// +�f�X�g���N�^
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
// +�Փ˗p�f�[�^�̃��Z�b�g�֐�
//--------------------------------------------------
void CollisionObject::ResetHitData()
{
	hit_vector_.ResetVector();
	is_judgment_ = true;
}