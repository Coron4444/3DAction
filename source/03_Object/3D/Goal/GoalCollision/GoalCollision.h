//================================================================================
//
//    ゴール衝突クラス
//    Author : Araki Kai                                作成日 : 2018/11/28
//
//================================================================================

#ifndef	_GOAL_COLLISION_H_
#define _GOAL_COLLISION_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Collision/CollisionNull/CollisionNull.h>




/*********************************************************//**
* @brief
* ゴール衝突クラス
*
* ゴールの衝突クラス
*************************************************************/
class GoalCollision : public CollisionNull
{
//==============================
// 定数
//==============================
private:
	static const float BOUNDING_SPHERE_RADIUS;
	static const float SUBSTANCE_RADIUS;


//==============================
// 列挙型定義
//==============================
public:
	enum ObjectTag
	{
		NONE = -1,
		BOUNDING_SPHERE,
		SUBSTANCE,
		MAX
	};


//==============================
// 非静的メンバ変数
//==============================
private:
	CollisionObjects* collision_objects_;
	CollisionObject* bounding_sphere_;
	CollisionObject* substance_;


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init() override;

	/**
	* @brief
	* 終了関数
	*/
	void Uninit() override;

	/**
	* @brief
	* 更新関数
	*/
	virtual void Update() override;
};



#endif