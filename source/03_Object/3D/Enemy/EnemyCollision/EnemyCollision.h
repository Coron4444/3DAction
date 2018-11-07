//================================================================================
//
//    �G�Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================

#ifndef	_ENEMY_COLLISION_H_
#define _ENEMY_COLLISION_H_



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

class EnemyCollision : public CollisionComponent
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
	EnemyCollision();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()   override;
	void Uninit() override;
	void Update() override;


//------------------------------------------------------------
private :
	// �����o�ϐ�
	CollisionObject* bounding_sphere_;
	CollisionObject* substance_;
};



#endif