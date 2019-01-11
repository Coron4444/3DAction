//================================================================================
//!	@file	 CollisionObjects.h
//!	@brief	 複数衝突オブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
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



//************************************************************														   
//! @brief   複数衝突オブジェクトClass
//!
//! @details 複数の衝突オブジェクトを管理するClass
//************************************************************
class CollisionObjects
{
//====================
// 定数
//====================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< 配列数


//====================
// 変数
//====================
private:
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> collision_object_;	//!< 全衝突オブジェクト配列
	CollisionBase* collision_base_ = nullptr;			//!< 衝突基底クラス
	ObjectOfTree<CollisionObjects*>* object_of_tree_;	//!< 分木オブジェクト
	AABB octree_aabb_;									//!< 8分木用AABB
	bool is_judgment_ = true;							//!< 判定フラグ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 配列の最後の末尾のインデックス取得関数
	//! @details
	//! @param void なし
	//! @retval unsigned 配列の最後の末尾のインデックス
	//----------------------------------------
	unsigned getEndIndexOfArray();
	
	//----------------------------------------
	//! @brief 衝突オブジェクト取得関数
	//! @details
	//! @param index 衝突オブジェクトのインデックス
	//! @retval CollisionObject* 衝突オブジェクト
	//----------------------------------------
	CollisionObject* getpCollisionObject(unsigned index);

	//----------------------------------------
	//! @brief 衝突基底クラス取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionBase* 衝突基底クラス
	//----------------------------------------
	CollisionBase* getpCollisionBase();
	
	//----------------------------------------
	//! @brief 衝突基底クラス設定関数
	//! @details
	//! @param *value 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void setCollisionBase(CollisionBase* value);
	
	//----------------------------------------
	//! @brief 分木オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval ObjectOfTree<CollisionObjects*>* 分木オブジェクト
	//----------------------------------------
	ObjectOfTree<CollisionObjects*>* getpObjectOfTree();
	
	//----------------------------------------
	//! @brief 分木オブジェクト設定関数
	//! @details
	//! @param value 分木オブジェクト
	//! @retval void なし
	//----------------------------------------
	void setObjectOfTree(ObjectOfTree<CollisionObjects*>* value);

	//----------------------------------------
	//! @brief 8分木用AABBポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval AABB* 8分木用AABBポインタ
	//----------------------------------------
	AABB* getOctreeAABB();
	
	//----------------------------------------
	//! @brief 判定フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 判定フラグ
	//----------------------------------------
	bool getIsJudgment();
	
	//----------------------------------------
	//! @brief 判定フラグ設定関数
	//! @details
	//! @param value 判定フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsJudgment(bool value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 衝突オブジェクト追加関数
	//! @details
	//! @param *object 衝突オブジェクトポインタ
	//! @retval void なし
	//----------------------------------------
	void AddCollisionObjectToArray(CollisionObject* object);

	//----------------------------------------
	//! @brief 衝突オブジェクト上書き関数
	//! @details
	//! @param *old_object 古い衝突オブジェクトポインタ
	//! @param *new_object 新しい衝突オブジェクトポインタ
	//! @retval void なし
	//----------------------------------------
	void OverwriteArrayCollisionObject(CollisionObject* old_object,
									   CollisionObject* new_object);

	//----------------------------------------
	//! @brief 衝突オブジェクト解放関数
	//! @details
	//! @param *object 衝突オブジェクトポインタ
	//! @retval void なし
	//----------------------------------------
	void ReleaseCollisionObjectFromArray(CollisionObject* object);

	//----------------------------------------
	//! @brief 衝突オブジェクト全解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseAllCollisionObjectFromArray();

	//----------------------------------------
	//! @brief 全衝突用データのリセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetHitDataAllCollisionObject();
};



#endif
