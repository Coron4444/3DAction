//================================================================================
//
//    敵衝突クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================

#ifndef	_ENEMY_COLLISION_H_
#define _ENEMY_COLLISION_H_



//======================================================================
//
// インクルード文
//
//======================================================================


#include <Component\CollisionComponent\CollisionComponent.h>

#include <string>



//======================================================================
//
// クラス定義
//
//======================================================================

class EnemyCollision : public CollisionComponent
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
	// コンストラクタ
	EnemyCollision();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()   override;
	void Uninit() override;
	void Update() override;


//------------------------------------------------------------
private :
	// メンバ変数
	CollisionObject* bounding_sphere_;
	CollisionObject* substance_;
};



#endif