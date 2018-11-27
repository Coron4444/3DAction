//================================================================================
//
//    コイン衝突クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================

#ifndef	_COIN_COLLISION_H_
#define _COIN_COLLISION_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../Coin.h"
#include <Component/Collision/CollisionNull/CollisionNull.h>

#include <string>




//======================================================================
//
// クラス定義
//
//======================================================================

class CoinCollision : public CollisionNull
{
//------------------------------------------------------------
private :
	// 定数
	static const float BOUNDING_OBB_RIGHT;
	static const float BOUNDING_OBB_UP;
	static const float BOUNDING_OBB_FORWARD;

	static const float SUBSTANCE_RIGHT;
	static const float SUBSTANCE_UP;
	static const float SUBSTANCE_FORWARD;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	enum ObjectTag
	{
		NONE = -1,
		BOUNDING_OBB,
		SUBSTANCE,
		MAX
	};



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()   override;
	void Uninit() override;
	void Update() override;


//------------------------------------------------------------
private :
	// メンバ変数
	CollisionObjects* collision_objects_;
	CollisionObject* bounding_obb_;
	CollisionObject* substance_;
};



#endif