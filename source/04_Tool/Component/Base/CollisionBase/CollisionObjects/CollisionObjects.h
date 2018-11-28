//================================================================================
//
//    �����Փ˃I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/27
//
//================================================================================

#ifndef	_COLLISION_OBJECTS_H_
#define _COLLISION_OBJECTS_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <LimitedPointerArray\LimitedPointerArray.h>

#include "../CollisionObject/CollisionObject.h"
#include "../ComponentManager/CollisionManager/LinerOctree/ObjectOfTree/ObjectOfTree.h"


//****************************************
// �N���X�錾
//****************************************
class CollisionBase;



/*********************************************************//**
* @brief
* �����Փ˃I�u�W�F�N�g�N���X
*
* �����̏Փ˃I�u�W�F�N�g���Ǘ�����N���X
*************************************************************/
class CollisionObjects
{
//==============================
// �萔
//==============================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< �z��


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> collision_object_;	//!< �S�Փ˃I�u�W�F�N�g�z��
	CollisionBase* collision_base_ = nullptr;	//!< �Փˊ��N���X�̃|�C���^
	ObjectOfTree<CollisionObjects*>* object_of_tree_;	//!< ���؃I�u�W�F�N�g�̃|�C���^
	AABB octree_aabb_;					//!< 8���ؗpAABB
	bool is_judgment_ = true;			//!< ����t���O


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �Փ˃I�u�W�F�N�g�ǉ��֐�
	*/
	void AddCollisionObjectToArray(CollisionObject* object)
	{
		collision_object_.AddToArray(object);
	}

	/**
	* @brief
	* �Փ˃I�u�W�F�N�g�㏑���֐�
	*/
	void OverwriteArrayCollisionObject(CollisionObject* old_object,
									   CollisionObject* new_object)
	{
		collision_object_.OverwriteArray(old_object, new_object);
	}

	/**
	* @brief
	* �Փ˃I�u�W�F�N�g����֐�
	*/
	void ReleaseCollisionObjectFromArray(CollisionObject* object)
	{
		collision_object_.DeleteFromArrayAndSortArray(object);
	}

	/**
	* @brief
	* �Փ˃I�u�W�F�N�g�S����֐�
	*/
	void ReleaseAllCollisionObjectFromArray()
	{
		collision_object_.ReleaseObjectAndResetArray();
	}

	/**
	* @brief
	* �S�Ă̏Փ˗p�f�[�^�̃��Z�b�g�֐�
	*/
	void ResetHitDataAllCollisionObject()
	{
		for (unsigned i = 0; i < collision_object_.GetEndPointer(); i++)
		{
			collision_object_.GetArrayObject(i)->ResetHitData();
		}
	}

	// �v���p�e�B
	unsigned getEndIndexOfArray() { return collision_object_.GetEndPointer(); }
	CollisionObject* getCollisionObject(unsigned index) { return collision_object_.GetArrayObject(index); }
	CollisionBase* getCollisionBase() { return collision_base_; }
	void setCollisionBase(CollisionBase* value) { collision_base_ = value; }
	ObjectOfTree<CollisionObjects*>* getObjectOfTree() { return object_of_tree_; }
	void setObjectOfTree(ObjectOfTree<CollisionObjects*>* value) { object_of_tree_ = value; }
	AABB* getOctreeAABB() { return &octree_aabb_; }
	bool getIsJudgment() { return is_judgment_; }
	void setIsJudgment(bool value) { is_judgment_ = value; }
};



#endif
