//================================================================================
//
//    複数衝突オブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/11/27
//
//================================================================================

#ifndef	_COLLISION_OBJECTS_H_
#define _COLLISION_OBJECTS_H_



//****************************************
// インクルード文
//****************************************
#include <LimitedPointerArray\LimitedPointerArray.h>

#include "../CollisionObject/CollisionObject.h"
#include "../ComponentManager/CollisionManager/LinerOctree/ObjectOfTree/ObjectOfTree.h"


//****************************************
// クラス宣言
//****************************************
class CollisionBase;



/*********************************************************//**
* @brief
* 複数衝突オブジェクトクラス
*
* 複数の衝突オブジェクトを管理するクラス
*************************************************************/
class CollisionObjects
{
//==============================
// 定数
//==============================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< 配列数


//==============================
// 非静的メンバ変数
//==============================
private:
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> collision_object_;	//!< 全衝突オブジェクト配列
	CollisionBase* collision_base_ = nullptr;	//!< 衝突基底クラスのポインタ
	ObjectOfTree<CollisionObjects*>* object_of_tree_;	//!< 分木オブジェクトのポインタ
	AABB octree_aabb_;					//!< 8分木用AABB
	bool is_judgment_ = true;			//!< 判定フラグ


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 衝突オブジェクト追加関数
	*/
	void AddCollisionObjectToArray(CollisionObject* object)
	{
		collision_object_.AddToArray(object);
	}

	/**
	* @brief
	* 衝突オブジェクト上書き関数
	*/
	void OverwriteArrayCollisionObject(CollisionObject* old_object,
									   CollisionObject* new_object)
	{
		collision_object_.OverwriteArray(old_object, new_object);
	}

	/**
	* @brief
	* 衝突オブジェクト解放関数
	*/
	void ReleaseCollisionObjectFromArray(CollisionObject* object)
	{
		collision_object_.DeleteFromArrayAndSortArray(object);
	}

	/**
	* @brief
	* 衝突オブジェクト全解放関数
	*/
	void ReleaseAllCollisionObjectFromArray()
	{
		collision_object_.ReleaseObjectAndResetArray();
	}

	/**
	* @brief
	* 全ての衝突用データのリセット関数
	*/
	void ResetHitDataAllCollisionObject()
	{
		for (unsigned i = 0; i < collision_object_.GetEndPointer(); i++)
		{
			collision_object_.GetArrayObject(i)->ResetHitData();
		}
	}

	// プロパティ
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
