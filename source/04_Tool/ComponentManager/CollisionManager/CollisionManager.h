//================================================================================
//
//    �Փ˃}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/04/17
//
//================================================================================

#ifndef	_COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <LimitedPointerArray\LimitedPointerArray.h>



//****************************************
// �N���X�錾
//****************************************
class CollisionBase;
class CollisionObject;
class GameObjectBase;
class MeshPlanePolygon;



/*********************************************************//**
* @brief
* �Փ˃}�l�[�W���[�N���X
*
* �o�^����Ă���Փˊ��N���X���Ǘ�����N���X
*************************************************************/
class CollisionManager
{
//==============================
// �萔
//==============================
public:
	static const unsigned ARRAY_NUM = 1000;		//!< �z��


//==============================
// �ÓI�����o�ϐ�
//==============================
private:
	static LimitedPointerArray<CollisionBase*, ARRAY_NUM> all_collision_;	//!< �S�Փ˔z��
	static LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	static LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_release_;	//!< ����҂��z��

	static MeshPlanePolygon* ground_polygon_;		//!< �n�ʃ|���S��


//==============================
// �ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	static void Init();

	/**
	* @brief
	* �I���֐�
	*/
	static void Uninit();

	/**
	* @brief
	* �V�[���ύX���̏I���֐�
	*/
	static void UninitWhenChangeScene();

	/**
	* @brief
	* �X�V�֐�
	*/
	static void Update();

	/**
	* @brief
	* �Փˊ��N���X�̒ǉ��֐�
	*/
	static void AddCollisionBaseToArray(CollisionBase* collision);

	/**
	* @brief
	* �Փˊ��N���X�̏㏑���֐�
	*/
	static void OverwriteArrayCollisionBase(GameObjectBase* game_object,
											CollisionBase* new_collision);

	/**
	* @brief
	* �Փˊ��N���X�̉���֐�
	*/
	static void ReleaseCollisionBaseFromArray(CollisionBase* collision);


	// �v���p�e�B
	static void SetGround(MeshPlanePolygon* ground_polygon);

private:
	/**
	* @brief
	* �ǉ��҂��z��̒��g��ǉ��֐�
	*/
	static void AddContentsOfAwaitAddArray();

	/**
	* @brief
	* ����҂��z��̒��g������֐�
	*/
	static void ReleaseContentsOfAwaitReleaseArray();

	/**
	* @brief
	* �Փ˔���֐�
	*/
	static void CollisionDetermination();
	
	/**
	* @brief
	* �n�ʂƂ̏Փ˔���֐�
	*/
	static void CollisionGround();
	
	/**
	* @brief
	* ���ۂ̌v�Z�֐�
	*/
	static void ActualCalculation(CollisionBase* collision0, CollisionBase* collision1);
	
	/**
	* @brief
	* �Փˌv�Z�U�蕪���֐�
	*/
	static bool SortCollisionCalculation(CollisionObject* collision_object0, 
										 CollisionObject* collision_object1);



//==============================
// ��ÓI�����o�֐�
//==============================
private:
	/**
	* @brief
	* �R���X�g���N�^(�폜)
	*/
	CollisionManager() = delete;

	/**
	* @brief
	* �R�s�[�R���X�g���N�^(�폜)
	*/
	CollisionManager(const CollisionManager& value) = delete;

	/**
	* @brief
	* ������Z�q�̃I�[�o�[���[�h(�폜)
	*/
	CollisionManager& operator = (const CollisionManager& value) = delete;
};



#endif
