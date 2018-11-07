//================================================================================
//
//    衝突オブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/04/25
//
//================================================================================

#ifndef	_COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "CollisionShapeOrigin\CollisionShapeOrigin.h"

#include "CollisionShapeOrigin\AABB\AABB.h"
#include "CollisionShapeOrigin\Capsule\Capsule.h"
#include "CollisionShapeOrigin\Cylinder\Cylinder.h"
#include "CollisionShapeOrigin\OBB\OBB.h"
#include "CollisionShapeOrigin\Plane\Plane.h"
#include "CollisionShapeOrigin\Segment\Segment.h"
#include "CollisionShapeOrigin\Sphere\Sphere.h"
#include "CollisionShapeOrigin\Triangle\Triangle.h"



//======================================================================
//
// クラス定義
//
//======================================================================

class CollisionObject
{
//------------------------------------------------------------
private :
	static const int TAG_NONE = -1;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	CollisionObject(CollisionShapeOrigin* collision_shape, 
		            int tag = TAG_NONE);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	~CollisionObject();
	

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void ResetHitData();

	// セッタ
	void SetHitVector(Vector3D hit_vector) {hit_vector_ = hit_vector;}
	void SetIsJudgment(bool is_judgment)   {is_judgment_ = is_judgment;}
	
	// ゲッタ
	CollisionShapeOrigin* GetCollisionShape() const {return collision_shape_;}
	int	 GetTag()		 const {return tag_;}
	bool GetIsJudgment() const {return is_judgment_;}
	Vector3D* GetHitVector() {return &hit_vector_;}


//------------------------------------------------------------
private :
	// 形状
	CollisionShapeOrigin* collision_shape_;
	
	// めり込み
	Vector3D hit_vector_;
	
	// 状態
	int		 tag_;
	bool     is_judgment_;
	bool     is_trigger_;
	
};



#endif
