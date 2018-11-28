//================================================================================
//
//    �S�[���Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/28
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "GoalCollision.h"
#include "../Goal.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <GameObjectManager\GameObjectManager.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>



//****************************************
// �萔��`
//****************************************
const float GoalCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float GoalCollision::SUBSTANCE_RADIUS = 1.0f;



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void GoalCollision::Init()
{
	// �X�e�[�g
	CollisionBase::setState(CollisionBase::State::GOAL);

	// �����Փ˃I�u�W�F�N�g
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()
		->Init(*GetGameObject()->GetTransform()->GetPosition(),
			   Vec3(1.0f, 1.0f, 1.0f));
	CollisionBase::AddCollisionObjectsToArray(collision_objects_);

	// �o�E���f�B���O�X�t�B�A�̍쐬
	Sphere* temp_sphere = new Sphere(*GetGameObject()->GetTransform()->GetPosition(),
									 BOUNDING_SPHERE_RADIUS);

	bounding_sphere_ = new CollisionObject(temp_sphere, ObjectTag::BOUNDING_SPHERE);

	// �o�E���f�B���O�X�t�B�A�̓o�^
	collision_objects_->AddCollisionObjectToArray(bounding_sphere_);


	// �{�̃X�t�B�A�̍쐬
	temp_sphere = new Sphere(*GetGameObject()->GetTransform()->GetPosition(),
							 SUBSTANCE_RADIUS);

	substance_ = new CollisionObject(temp_sphere, ObjectTag::SUBSTANCE);

	// �{�̃X�t�B�A�̓o�^
	collision_objects_->AddCollisionObjectToArray(substance_);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void GoalCollision::Uninit()
{
	// �X�[�p�[�N���X�̏I������
	CollisionNull::Uninit();
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void GoalCollision::Update()
{
	// �����Փ˃I�u�W�F�N�g�̍X�V
	collision_objects_->getOctreeAABB()
		->setPosition(*GetGameObject()->GetTransform()->GetPosition());
	collision_objects_->getOctreeAABB()->Update();

	// �o�E���f�B���O�X�t�B�A�̍X�V
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->getCollisionShape();
	temp_sphere->position_ = *GetGameObject()->GetTransform()->GetPosition();

	// �{�̃X�t�B�A�̍X�V
	temp_sphere = (Sphere*)substance_->getCollisionShape();
	temp_sphere->position_ = *GetGameObject()->GetTransform()->GetPosition();
}