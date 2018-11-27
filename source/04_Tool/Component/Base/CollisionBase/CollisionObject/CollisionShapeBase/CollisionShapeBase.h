//================================================================================
//
//    衝突形状基底クラス
//    Author : Araki Kai                                作成日 : 2018/04/25
//
//================================================================================

#ifndef	_COLLISION_SHAPE_BASE_H_
#define _COLLISION_SHAPE_BASE_H_



//****************************************
// インクルード文
//****************************************
#include <Vector3D.h>



/*********************************************************//**
* @brief
* 衝突形状基底クラス
*
* 衝突形状の基底クラス
*************************************************************/
class CollisionShapeBase
{
//==============================
// 列挙型定義
//==============================
public:
	// 形状タイプ
	enum Type
	{
		NONE = -1,
		AABB,
		CAPSULE,
		CYLINDER,
		OBB,
		PLANE,
		SEGMENT,
		SPHERE,
		TRIANGLE,
		MAX
	};


//==============================
// 非静的メンバ関数
//==============================
private:
	Type type_;				//!< 形状タイプ
	Vector3D position_;		//!< 座標


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* コンストラクタ
	*/
	CollisionShapeBase(Type type) : type_(type) {}

	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~CollisionShapeBase() {}

	// プロパティ
	Type getType() { return type_; }
	const Vector3D* getPositon() const { return &position_; }
	void setPosition(Vector3D value) { position_ = value; }
};



#endif