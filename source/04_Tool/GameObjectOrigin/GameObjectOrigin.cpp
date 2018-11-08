//================================================================================
//
//    �Q�[���I�u�W�F�N�g�̌��_�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "GameObjectOrigin.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../ComponentManager/UpdateComponentManager/UpdateComponentManager.h"
#include "../ComponentManager/DrawComponentManager/DrawComponentManager.h"
#include "../ComponentManager/CollisionComponentManager/CollisionComponentManager.h"



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

GameObjectOrigin::GameObjectOrigin(bool is_registration)
	: is_registration_    (is_registration),
	  update_component_   (nullptr),
	  draw_component_     (nullptr),
	  collision_component_(nullptr),
	  physics_            (nullptr)
{
	// �I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	if (!is_registration_) return;
	GameObjectManager::Registration(this);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GameObjectOrigin::~GameObjectOrigin()
{
	// �e��J��
	SafeRelease::Normal(&update_component_);
	SafeRelease::Normal(&draw_component_);
	SafeRelease::Normal(&collision_component_);
	SafeRelease::Normal(&physics_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�u�W�F�N�g��������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectOrigin::ReleaseObject()
{
	// �h����̏I������
	Uninit();
}



//################################################################################
//
// [ �X�[�p�[�N���X�������֐� ]
//
//################################################################################

void GameObjectOrigin::Init_SuperClass(UpdateComponent* update_component, DrawComponent* draw_component, CollisionComponent* collision_component)
{
	// �R���|�[�l���g���Z�b�g
	SetComponentAll(update_component, draw_component, collision_component);

	// �Q�[���I�u�W�F�N�g�̓o�^
	SetGameObject();

	// �R���|�[�l���g�̏�����
	InitComponent();

	// �R���|�[�l���g�̓o�^
	RegistrationComponentManager();
}



//################################################################################
//
// [ �X�[�p�[�N���X�I���֐� ]
//
//################################################################################

void GameObjectOrigin::Uninit_SuperClass()
{
	// �R���|�[�l���g�̏I������
	UninitComponent();

	// �R���|�[�l���g�̉��
	ReleaseComponentManager();
}



//################################################################################
//
// [ �Q�[���I�u�W�F�N�g���Z�b�g����֐� ]
//
//################################################################################

void GameObjectOrigin::SetGameObject()
{
	if (update_component_ != nullptr)
	{
		update_component_->SetGameObjectOrigin(this);
	}

	if (draw_component_ != nullptr)
	{
		draw_component_->SetGameObjectOrigin(this);
	}

	if (collision_component_ != nullptr)
	{
		collision_component_->SetGameObjectOrigin(this);
	}
}



//################################################################################
//
// [ �R���|�[�l���g�������֐� ]
//
//################################################################################

void GameObjectOrigin::InitComponent()
{
	if (update_component_ != nullptr)
	{
		update_component_->Init();
	}

	if (draw_component_ != nullptr)
	{
		draw_component_->Init();
	}

	if (collision_component_ != nullptr)
	{
		collision_component_->Init();
	}
}



//################################################################################
//
// [ �R���|�[�l���g�I�������֐� ]
//
//################################################################################

void GameObjectOrigin::UninitComponent()
{
	if (update_component_ != nullptr)
	{
		update_component_->Uninit();
	}

	if (draw_component_ != nullptr)
	{
		draw_component_->Uninit();
	}

	if (collision_component_ != nullptr)
	{
		collision_component_->Uninit();
	}
}



//################################################################################
//
// [ �R���|�[�l���g�}�l�[�W���[�ւ̓o�^�֐� ]
//
//################################################################################

void GameObjectOrigin::RegistrationComponentManager()
{
	if (update_component_ != nullptr)
	{
		UpdateComponentManager::RegistrationComponent(update_component_);
	}

	if (draw_component_ != nullptr)
	{
		DrawComponentManager::RegistrationComponent(draw_component_);
	}

	if (collision_component_ != nullptr)
	{
		CollisionComponentManager::RegistrationComponent(collision_component_);
	}
}



//################################################################################
//
// [ �R���|�[�l���g�}�l�[�W���[����̉���֐� ]
//
//################################################################################

void GameObjectOrigin::ReleaseComponentManager()
{
	if (update_component_ != nullptr)
	{
		UpdateComponentManager::ReleaseComponent(update_component_);
	}

	if (draw_component_ != nullptr)
	{
		DrawComponentManager::ReleaseComponent(draw_component_);
	}

	if (collision_component_ != nullptr)
	{
		CollisionComponentManager::ReleaseComponent(collision_component_);
	}
}