//================================================================================
//
//    プレイヤー衝突クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================

#ifndef	_PLAYER_COLLISION_H_
#define _PLAYER_COLLISION_H_



//======================================================================
//
// インクルード文
//
//======================================================================


#include <Component/Collision/CollisionNull/CollisionNull.h>

#include <string>



//======================================================================
//
// クラス定義
//
//======================================================================

class PlayerCollision : public CollisionNull
{
//------------------------------------------------------------
private :
	// 定数
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
	// メンバ関数
	void Init()   override;
	void Uninit() override;
	void Update() override;

	void HitCollision(CollisionBase* hit_collision,
					  CollisionObject*  hit_object,
					  CollisionObject*  hit_my_object) override;

	void NotHitCollision(CollisionBase* hit_collision,
						 CollisionObject*  hit_object,
						 CollisionObject*  hit_my_object) override;

	void HitGround(float position_y)    override;


//------------------------------------------------------------
private :
	// バウンディングスフィア
	void HitBoundingSphere(CollisionBase* hit_collision,
						   CollisionObject*  hit_object,
						   CollisionObject*  hit_my_object);

	void NotHitBoundingSphere(CollisionBase* hit_collision,
							  CollisionObject*  hit_object,
							  CollisionObject*  hit_my_object);

	// サブスタンス
	void HitSubstance(CollisionBase* hit_collision,
					  CollisionObject*  hit_object,
					  CollisionObject*  hit_my_object);

	

//------------------------------------------------------------
private :
	// メンバ変数
	CollisionObjects* collision_objects_;
	CollisionObject* bounding_sphere_;
	CollisionObject* substance_;
};



#endif