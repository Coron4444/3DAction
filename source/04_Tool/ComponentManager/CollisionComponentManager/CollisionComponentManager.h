//================================================================================
//
//    �Փ˃R���|�[�l���g�}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/04/17
//
//================================================================================

#ifndef	_COLLISION_COMPONENT_MANAGER_H_
#define _COLLISION_COMPONENT_MANAGER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <LimitedPointerArray\LimitedPointerArray.h>



//======================================================================
//
// �N���X�錾
//
//**********************************************************************

class CollisionComponent;
class CollisionObject;
class GameObjectOrigin;
class MeshPlanePolygon;


//======================================================================
//
// �N���X��`
//
//======================================================================

class CollisionComponentManager
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	static const unsigned ARRAY_NUM = 1000;


//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	CollisionComponentManager() = delete;

	// �R�s�[�R���X�g���N�^
	CollisionComponentManager(const CollisionComponentManager& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	CollisionComponentManager& operator = (const CollisionComponentManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �ÓI���J�����o�֐�
	static void Init();
	static void Uninit();
	static void Uninit_ChangeScene();
	static void Update();

	static void RegistrationComponent(CollisionComponent* collision_component);
	static void OverwriteComponent   (GameObjectOrigin* game_object, CollisionComponent* new_collision_component);
	static void ReleaseComponent	 (CollisionComponent* collision_component);

	// �n��
	static void SetGround(MeshPlanePolygon* ground_polygon);
	

//------------------------------------------------------------
private :
	// �ÓI����J�����o�֐�
	static void ReleaseUpdateComponentALL();
	static void CollisionDetermination();
	static void CollisionGround();
	static void ActualCalculation		(CollisionComponent* collision_component_0, CollisionComponent* collision_component_1);
	static bool SortCollisionCalculation(CollisionObject* collision_object_0, CollisionObject* collision_object_1);

//------------------------------------------------------------
private :
	// �ÓI�����o�ϐ�
	static LimitedPointerArray<CollisionComponent*, ARRAY_NUM> all_collision_component_;
	static LimitedPointerArray<CollisionComponent*, ARRAY_NUM> release_;

	// �n�ʃ|���S��
	static MeshPlanePolygon* ground_polygon_;
};



#endif
