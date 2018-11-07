//================================================================================
//
//    �v���C���[�Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================

#ifndef	_PLAYER_COLLISION_H_
#define _PLAYER_COLLISION_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================


#include <Component\CollisionComponent\CollisionComponent.h>

#include <string>



//======================================================================
//
// �N���X��`
//
//======================================================================

class PlayerCollision : public CollisionComponent
{
//------------------------------------------------------------
private :
	// �萔
	static const float BOUNDING_SPHERE_RADIUS;
	static const float SUBSTANCE_RADIUS;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	enum ObjectTag
	{
		NONE = -1,
		BOUNDING_SPHERE,
		SUBSTANCE,
		MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �R���X�g���N�^
	PlayerCollision();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()   override;
	void Uninit() override;
	void Update() override;

	void HitCollision(CollisionComponent* hit_component, 
					  CollisionObject*    hit_opponent_object,
					  CollisionObject*    hit_myself_object) override;

	void NotHitCollision(CollisionComponent* hit_component, 
					     CollisionObject*    hit_opponent_object,
					     CollisionObject*    hit_myself_object) override;

	void HitGround(float position_y)    override;


//------------------------------------------------------------
private :
	// �o�E���f�B���O�X�t�B�A
	void HitBoundingSphere(CollisionComponent* hit_component, 
					       CollisionObject*    hit_opponent_object,
					       CollisionObject*    hit_myself_object);

	void NotHitBoundingSphere(CollisionComponent* hit_component, 
							  CollisionObject*    hit_opponent_object,
							  CollisionObject*    hit_myself_object);

	// �T�u�X�^���X
	void HitSubstance(CollisionComponent* hit_component, 
					  CollisionObject*    hit_opponent_object,
					  CollisionObject*    hit_myself_object);

	

//------------------------------------------------------------
private :
	// �����o�ϐ�
	CollisionObject* bounding_sphere_;
	CollisionObject* substance_;
};



#endif