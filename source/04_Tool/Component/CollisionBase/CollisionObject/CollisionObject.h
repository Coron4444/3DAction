//================================================================================
//
//    衝突オブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/04/25
//
//================================================================================

#ifndef	_COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_



//****************************************
// インクルード文
//****************************************
#include "CollisionShapeBase/AABB/AABB.h"
#include "CollisionShapeBase/Capsule/Capsule.h"
#include "CollisionShapeBase/Cylinder/Cylinder.h"
#include "CollisionShapeBase/OBB/OBB.h"
#include "CollisionShapeBase/Plane/Plane.h"
#include "CollisionShapeBase/Segment/Segment.h"
#include "CollisionShapeBase/Sphere/Sphere.h"
#include "CollisionShapeBase/Triangle/Triangle.h"



//======================================================================
//
// クラス定義
//
//======================================================================

class CollisionObject
{
//==============================
// 定数
//==============================
private:
	static const int TAG_NONE = -1;			//!< タグなし時の値


//==============================
// 非静的メンバ変数
//==============================
private:
	
	CollisionShapeBase* collision_shape_;		//!< 形状
	Vector3D hit_vector_;						//!< めり込みベクトル

	int		 tag_;			//!< タグ
	bool     is_judgment_;	//!< 判定するかフラグ
	bool     is_trigger_;	//!< 物理演算をするかのフラグ


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* コンストラクタ
	* @param
	* collision_shape : 衝突オブジェクトの形状
	* tag : コリジョンオブジェクトを識別するタグ
	*/
	CollisionObject(CollisionShapeBase* collision_shape, int tag = TAG_NONE);

	/**
	* @brief
	* デストラクタ
	*/
	~CollisionObject();

	/**
	* @brief
	* 衝突用データのリセット関数
	*/
	void ResetHitData();

	// プロパティ
	int	 GetTag() const { return tag_; }
	CollisionShapeBase* GetCollisionShape() const { return collision_shape_; }
	Vector3D* GetHitVector() { return &hit_vector_; }
	void SetHitVector(Vector3D value) { hit_vector_ = value; }
	bool GetIsJudgment() const { return is_judgment_; }
	void SetIsJudgment(bool value) { is_judgment_ = value; }
};



#endif
