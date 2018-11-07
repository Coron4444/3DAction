//================================================================================
//
//    �Q�[���I�u�W�F�N�g�̌��_�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================

#ifndef	_GAME_OBJECT_ORIGIN_H_
#define _GAME_OBJECT_ORIGIN_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../Component/UpdateComponent/UpdateComponent.h"
#include "../Component/DrawComponent/DrawComponent.h"
#include "../Component/CollisionComponent/CollisionComponent.h"

#include <Transform\Transform.h>
#include <Physics\Physics.h>
#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	GameObjectOrigin(bool is_registration = true);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~GameObjectOrigin();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �}�l�[�W���[�p
	virtual void Reset() = 0;
	void ReleaseObject();
	
	// �Z�b�^
	void SetComponentAll(UpdateComponent* update_component, DrawComponent* draw_component, CollisionComponent* collision_component)
	{
		SetUpdateComponent(update_component);
		SetDrawComponent(draw_component);
		SetCollisionComponent(collision_component);
	}
	void SetUpdateComponent(UpdateComponent* component)		  {update_component_ = component;}
	void SetDrawComponent(DrawComponent* component)			  {draw_component_ = component;}
	void SetCollisionComponent(CollisionComponent* component) {collision_component_ = component;}

	// �Q�b�^
	UpdateComponent*	GetUpdateComponent()	{return update_component_;}
	DrawComponent*		GetDrawComponent()		{return draw_component_;}
	CollisionComponent* GetCollisionComponent() {return collision_component_;}

	Transform* GetTransform(){return &transform_;}
	
	// ����
	void CreatePhysics()
	{
		if (physics_ != nullptr) return;
		physics_ = new Physics(this);
	}

	Physics* GetPhysics(){return physics_;}


//############################################################
protected :
	// �X�[�p�[�N���X
	void Init_SuperClass(UpdateComponent* update_component, DrawComponent* draw_component, CollisionComponent* collision_component);
	void Uninit_SuperClass();
	
	// �T�u�N���X
	virtual void Uninit() = 0;

	// �R���|�[�l���g
	void SetGameObject();
	void InitComponent();
	void UninitComponent();
	void RegistrationComponentManager();
	void ReleaseComponentManager();


//------------------------------------------------------------
private :
	// ����J�����o�ϐ�
	Transform transform_;
	Physics*  physics_;

	bool is_registration_;

	UpdateComponent*    update_component_;
	DrawComponent*      draw_component_;
	CollisionComponent* collision_component_;
};



#endif
