//================================================================================
//
//    �Q�[���I�u�W�F�N�g���N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "GameObjectBase.h"

#include "../GameObjectManager/GameObjectManager.h"
#include "../ComponentManager/UpdateComponentManager/UpdateComponentManager.h"
#include "../ComponentManager/DrawComponentManager/DrawComponentManager.h"
#include "../ComponentManager/CollisionComponentManager/CollisionComponentManager.h"



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�R���X�g���N�^
//--------------------------------------------------
GameObjectBase::GameObjectBase(bool is_registration)
	: is_registration_(is_registration),
	physics_(nullptr),
	update_component_(nullptr),
	draw_component_(nullptr),
	collision_component_(nullptr)
{
	// �I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	if (!is_registration_) return;
	GameObjectManager::Registration(this);
}



//--------------------------------------------------
// +�f�X�g���N�^
//--------------------------------------------------
GameObjectBase::~GameObjectBase()
{
	// �e��J��
	SafeRelease::Normal(&update_component_);
	SafeRelease::Normal(&draw_component_);
	SafeRelease::Normal(&collision_component_);
	SafeRelease::Normal(&physics_);
}


//--------------------------------------------------
// +�I�u�W�F�N�g����֐�
//--------------------------------------------------
void GameObjectBase::ReleaseObject()
{
	// �h����̏I������
	Uninit();
}



//--------------------------------------------------
// +�I�u�W�F�N�g����֐�
//--------------------------------------------------
void GameObjectBase::CreatePhysics()
{
	if (physics_ != nullptr) return;
	physics_ = new Physics(this);
}



//--------------------------------------------------
// #���N���X�������֐�
//--------------------------------------------------
void GameObjectBase::BaseClassInit(UpdateComponent* update_component, 
								   DrawComponent* draw_component, 
								   CollisionComponent* collision_component)
{
	// �R���|�[�l���g���Z�b�g
	SetAllComponent(update_component, draw_component, collision_component);
	
	// �R���|�[�l���g���}�l�[�W���֐ݒ�
	SetComponentToManager();

	// �Q�[���I�u�W�F�N�g���R���|�[�l���g�ɐݒ�
	SetGameObjectToComponent();

	// �R���|�[�l���g�̏�����
	InitComponent();
}



//--------------------------------------------------
// #���N���X�I���֐�
//--------------------------------------------------
void GameObjectBase::BaseClassUninit()
{
	// �R���|�[�l���g���}�l�[�W��������
	ReleaseComponentFromManager();

	// �R���|�[�l���g�̏I������
	UninitComponent();

}



//--------------------------------------------------
// -�R���|�[�l���g�������֐�
//--------------------------------------------------
void GameObjectBase::InitComponent()
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



//--------------------------------------------------
// -�R���|�[�l���g�I���֐�
//--------------------------------------------------
void GameObjectBase::UninitComponent()
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


//--------------------------------------------------
// -�R���|�[�l���g���}�l�[�W���[�֐ݒ�֐�
//--------------------------------------------------
void GameObjectBase::SetComponentToManager()
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


//--------------------------------------------------
// -�R���|�[�l���g���}�l�[�W���[�������֐�
//--------------------------------------------------
void GameObjectBase::ReleaseComponentFromManager()
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



//--------------------------------------------------
// -�Q�[���I�u�W�F�N�g���R���|�[�l���g�ɐݒ�֐�
//--------------------------------------------------
void GameObjectBase::SetGameObjectToComponent()
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