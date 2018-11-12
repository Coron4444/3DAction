//================================================================================
//
//    �Փ˃}�l�[�W���[�N���X
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
// ��ÓI�����o�ϐ�
//==============================
private:
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> all_collision_;	//!< �S�Փ˔z��
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_release_;	//!< ����҂��z��

	MeshPlanePolygon* ground_polygon_;		//!< �n�ʃ|���S��


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	void Init();

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit();

	/**
	* @brief
	* �V�[���ύX���̏I���֐�
	*/
	void UninitWhenChangeScene();

	/**
	* @brief
	* �X�V�֐�
	*/
	void Update();

	/**
	* @brief
	* �Փˊ��N���X�̒ǉ��֐�
	*/
	void AddCollisionBaseToArray(CollisionBase* collision);

	/**
	* @brief
	* �Փˊ��N���X�̏㏑���֐�
	*/
	void OverwriteArrayCollisionBase(GameObjectBase* game_object,
									 CollisionBase* new_collision);

	/**
	* @brief
	* �Փˊ��N���X�̉���֐�
	*/
	void ReleaseCollisionBaseFromArray(CollisionBase* collision);


	// �v���p�e�B
	void SetGround(MeshPlanePolygon* ground_polygon);

private:
	/**
	* @brief
	* �ǉ��҂��z��̒��g��ǉ��֐�
	*/
	void AddContentsOfAwaitAddArray();

	/**
	* @brief
	* ����҂��z��̒��g������֐�
	*/
	void ReleaseContentsOfAwaitReleaseArray();

	/**
	* @brief
	* �Փ˔���֐�
	*/
	void CollisionDetermination();

	/**
	* @brief
	* �n�ʂƂ̏Փ˔���֐�
	*/
	void CollisionGround();

	/**
	* @brief
	* ���ۂ̌v�Z�֐�
	*/
	void ActualCalculation(CollisionBase* collision0, CollisionBase* collision1);

	/**
	* @brief
	* �Փˌv�Z�U�蕪���֐�
	*/
	bool SortCollisionCalculation(CollisionObject* collision_object0,
								  CollisionObject* collision_object1);
};



#endif
