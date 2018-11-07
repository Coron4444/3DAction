//================================================================================
//
//    �G�Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "EnemyCollision.h"
#include "../Enemy.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <GameObjectManager\GameObjectManager.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const float EnemyCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float EnemyCollision::SUBSTANCE_RADIUS	   = 1.0f;



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EnemyCollision::EnemyCollision()
		: CollisionComponent(CollisionComponent::State::ENEMY)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EnemyCollision::Init()
{
	// �o�E���f�B���O�X�t�B�A�̍쐬
	Sphere* temp_sphere = new Sphere(*GetGameObjectOrigin()->GetTransform()->GetPosition(), 
									 BOUNDING_SPHERE_RADIUS);
	
	bounding_sphere_ = new CollisionObject(temp_sphere, ObjectTag::BOUNDING_SPHERE);

	// �o�E���f�B���O�X�t�B�A�̓o�^
	AddCollisionObject(bounding_sphere_);


	// �{�̃X�t�B�A�̍쐬
	temp_sphere = new Sphere(*GetGameObjectOrigin()->GetTransform()->GetPosition(),
							 SUBSTANCE_RADIUS);

	substance_ = new CollisionObject(temp_sphere, ObjectTag::SUBSTANCE);

	// �{�̃X�t�B�A�̓o�^
	AddCollisionObject(substance_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EnemyCollision::Uninit()
{
	// �X�[�p�[�N���X�̏I������
	CollisionComponent::Uninit();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EnemyCollision::Update()
{
	// �o�E���f�B���O�X�t�B�A�̍X�V
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->GetCollisionShape();
	temp_sphere->position_ = *GetGameObjectOrigin()->GetTransform()->GetPosition();

	// �{�̃X�t�B�A�̍X�V
	temp_sphere = (Sphere*)substance_->GetCollisionShape();
	temp_sphere->position_ = *GetGameObjectOrigin()->GetTransform()->GetPosition();
}