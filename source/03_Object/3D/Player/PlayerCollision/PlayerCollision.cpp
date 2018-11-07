//================================================================================
//
//    �v���C���[�Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "PlayerCollision.h"
#include "../Player.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <GameObjectManager\GameObjectManager.h>
#include <3D\Coin\CoinCollision\CoinCollision.h>
#include <3D\Enemy\EnemyCollision\EnemyCollision.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const float PlayerCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float PlayerCollision::SUBSTANCE_RADIUS		= 1.0f;



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

PlayerCollision::PlayerCollision()
	: CollisionComponent(CollisionComponent::State::PLAYER)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Init()
{
	// �o�E���f�B���O�X�t�B�A�̍쐬
	Sphere* temp_sphere = new Sphere(*GetGameObjectOrigin()->GetTransform()->GetPosition(), 
									 BOUNDING_SPHERE_RADIUS);
	
	bounding_sphere_ = new CollisionObject(temp_sphere, ObjectTag::BOUNDING_SPHERE);

	// �o�E���f�B���O�X�t�B�A��ǉ�
	AddCollisionObject(bounding_sphere_);


	// �{�̃X�t�B�A�̍쐬
	temp_sphere = new Sphere(*GetGameObjectOrigin()->GetTransform()->GetPosition(),
							 SUBSTANCE_RADIUS);

	substance_ = new CollisionObject(temp_sphere, ObjectTag::SUBSTANCE);

	// �{�̃X�t�B�A��ǉ�
	AddCollisionObject(substance_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Uninit()
{
	// �X�[�p�[�N���X�̏I������
	CollisionComponent::Uninit();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Update()
{
	// �o�E���f�B���O�X�t�B�A�̍X�V
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->GetCollisionShape();
	temp_sphere->position_ = *GetGameObjectOrigin()->GetTransform()->GetPosition();

	// �{�̃X�t�B�A�̍X�V
	temp_sphere = (Sphere*)substance_->GetCollisionShape();
	temp_sphere->position_ = *GetGameObjectOrigin()->GetTransform()->GetPosition();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փˉ����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::HitCollision(CollisionComponent* hit_component, 
								   CollisionObject*    hit_opponent_object,
								   CollisionObject*    hit_myself_object)
{
	// �����̏Փ˃I�u�W�F�N�g�ŐU�蕪����
	switch (hit_myself_object->GetTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE :
		{
			HitBoundingSphere(hit_component, hit_opponent_object, hit_myself_object);
			break;
		}
		case PlayerCollision::ObjectTag::SUBSTANCE :
		{
			HitSubstance(hit_component, hit_opponent_object, hit_myself_object);
			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��Փˉ����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::NotHitCollision(CollisionComponent* hit_component, 
								      CollisionObject*    hit_opponent_object,
								      CollisionObject*    hit_myself_object)
{
	// �����̏Փ˃I�u�W�F�N�g�ŐU�蕪����
	switch (hit_myself_object->GetTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE :
		{
			NotHitBoundingSphere(hit_component, hit_opponent_object, hit_myself_object);
			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �n�ʂƂ̏Փˉ����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::HitGround(float position_y)
{
	// �_�E���L���X�g
	Player* player = (Player*)GetGameObjectOrigin();

	// �n�ʂ̏�ɗ���
	player->GetTransform()->GetPosition()->y = position_y;
	player->GetTransform()->UpdateWorldMatrixSRT();

	if (player->GetPhysics() == nullptr) return;
	player->GetPhysics()->SetOnTheGround();
}



//--------------------------------------------------------------------------------
//
// [ �o�E���f�B���O�X�t�B�A�Փˏ����֐� ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::HitBoundingSphere(CollisionComponent* hit_component, 
								        CollisionObject*    hit_opponent_object,
								        CollisionObject*    hit_myself_object)
{
	hit_myself_object = hit_myself_object;

	// �Փ˃R���|�[�l���g�ŐU�蕪��
	switch(hit_component->GetState())
	{
		case CollisionComponent::State::COIN :
		{
			//TestCubeCollisionComponent* temp_component = (TestCubeCollisionComponent*)hit_component;
	
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch(hit_opponent_object->GetTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB :
				{
					//game_object_origin_->translation_->position_ += hit_myself_object->hit_vector_;
					//game_object_origin_->matrix_->UpdateTranslationMatrix(game_object_origin_->translation_->position_);
					//game_object_origin_->matrix_->UpdateWorldMatrix();
					break;
				}
			
			}
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ �o�E���f�B���O�X�t�B�A��Փˏ����֐� ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::NotHitBoundingSphere(CollisionComponent* hit_component, 
								           CollisionObject*    hit_opponent_object,
								           CollisionObject*    hit_myself_object)
{
	hit_myself_object = hit_myself_object;

	// �Փ˃R���|�[�l���g�ŐU�蕪��
	switch(hit_component->GetState())
	{
		case CollisionComponent::State::COIN :
		{
			// �g��Ȃ���������
			hit_opponent_object = hit_opponent_object;

			// �o�E���f�B���O�X�t�B�A�������̏Փ˃I�u�W�F�N�g��OFF
			substance_->SetIsJudgment(false);

			break;
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ �T�u�X�^���X�Փˏ����֐� ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::HitSubstance(CollisionComponent* hit_component, 
								   CollisionObject*    hit_opponent_object,
								   CollisionObject*    hit_myself_object)
{
	// �Փ˃R���|�[�l���g�ŐU�蕪��
	switch(hit_component->GetState())
	{
		case CollisionComponent::State::COIN:
		{
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch(hit_opponent_object->GetTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB :
				{
					// �_�E���L���X�g
					Player* player = (Player*)GetGameObjectOrigin();
					
					// �߂荞�݉���
					EliminationOfNesting(player->GetTransform(), hit_myself_object->GetHitVector());

					// �X�R�A�A�b�v
					player->game_scene_->SetScore(player->game_scene_->GetScore() + 30);

					// ����̃I�u�W�F�N�g������
					GameObjectManager::Release(hit_component->GetGameObjectOrigin());
					
					break;
				}
			
			}
			break;
		}
		case CollisionComponent::State::ENEMY :
		{
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch(hit_opponent_object->GetTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE :
				{
					// �_�E���L���X�g
					Player* player = (Player*)GetGameObjectOrigin();
					
					// �߂荞�݉���
					EliminationOfNesting(player->GetTransform(), hit_myself_object->GetHitVector());

					// �X�R�A�_�E��
					player->game_scene_->SetScore(player->game_scene_->GetScore() - 9999);

					// ����̃I�u�W�F�N�g������
					GameObjectManager::Release(hit_component->GetGameObjectOrigin());
					
					break;
				}
			}
			break;
		}
	}
}