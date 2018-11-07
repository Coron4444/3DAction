//================================================================================
//
//    �R�C���Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "CoinCollision.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>



//**********************************************************************
//
// �萔��`
//
//**********************************************************************

const float CoinCollision::BOUNDING_OBB_RIGHT   = 1.0f;
const float CoinCollision::BOUNDING_OBB_UP      = 1.0f;
const float CoinCollision::BOUNDING_OBB_FORWARD = 1.0f;

const float CoinCollision::SUBSTANCE_RIGHT   = 1.0f;
const float CoinCollision::SUBSTANCE_UP	  = 1.0f;
const float CoinCollision::SUBSTANCE_FORWARD = 1.0f;



//**********************************************************************
//
// ��ÓI�����o�֐���`
//
//**********************************************************************

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

CoinCollision::CoinCollision()
	: CollisionComponent(CollisionComponent::State::COIN)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CoinCollision::Init()
{
	// �o�E���f�B���OOBB�̍쐬
	OBB* temp_obb_ = new OBB(BOUNDING_OBB_RIGHT,
							 BOUNDING_OBB_UP, 
							 BOUNDING_OBB_FORWARD,
							 *GetGameObjectOrigin()->GetTransform()->GetPosition());
	
	bounding_obb_ = new CollisionObject(temp_obb_, ObjectTag::BOUNDING_OBB);

	// �o�E���f�B���OOBB�̓o�^
	AddCollisionObject(bounding_obb_);


	// �{��OBB�̍쐬
	temp_obb_ = new OBB(SUBSTANCE_RIGHT,
						SUBSTANCE_UP, 
						SUBSTANCE_FORWARD,
						*GetGameObjectOrigin()->GetTransform()->GetPosition());

	substance_ = new CollisionObject(temp_obb_, ObjectTag::SUBSTANCE);

	// �{��OBB�̓o�^
	AddCollisionObject(substance_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CoinCollision::Uninit()
{
	// �X�[�p�[�N���X�̏I������
	CollisionComponent::Uninit();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CoinCollision::Update()
{
	// �o�E���f�B���OOBB�̍X�V
	OBB* temp_obb = (OBB*)bounding_obb_->GetCollisionShape();

	temp_obb->position_		  = *GetGameObjectOrigin()->GetTransform()->GetPosition();
	temp_obb->axis_			  = *GetGameObjectOrigin()->GetTransform()->GetAxisVector();
	temp_obb->lenght_right_	  = GetGameObjectOrigin()->GetTransform()->GetScale()->x * BOUNDING_OBB_RIGHT;
	temp_obb->lenght_up_	  = GetGameObjectOrigin()->GetTransform()->GetScale()->y * BOUNDING_OBB_UP;
	temp_obb->lenght_forward_ = GetGameObjectOrigin()->GetTransform()->GetScale()->z * BOUNDING_OBB_FORWARD;


	// �{�̃X�t�B�AOBB�̍X�V
	temp_obb = (OBB*)substance_->GetCollisionShape();

	temp_obb->position_		  = *GetGameObjectOrigin()->GetTransform()->GetPosition();
	temp_obb->axis_			  = *GetGameObjectOrigin()->GetTransform()->GetAxisVector();
	temp_obb->lenght_right_	  = GetGameObjectOrigin()->GetTransform()->GetScale()->x * SUBSTANCE_RIGHT;
	temp_obb->lenght_up_	  = GetGameObjectOrigin()->GetTransform()->GetScale()->y * SUBSTANCE_UP;
	temp_obb->lenght_forward_ = GetGameObjectOrigin()->GetTransform()->GetScale()->z * SUBSTANCE_FORWARD;
}