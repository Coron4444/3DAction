//================================================================================
//!	@file	 CollisionShapeBase.h
//!	@brief	 衝突形状BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COLLISION_SHAPE_BASE_H_
#define _COLLISION_SHAPE_BASE_H_



//************************************************************														   
//! @brief   衝突形状BaseClass
//!
//! @details 衝突形状のBaseClass
//************************************************************
class CollisionShapeBase
{
//====================
// 列挙型定義
//====================
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
		LINE_SEGMENT,
		SPHERE,
		TRIANGLE,
		MAX
	};


//====================
// 変数
//====================
private:
	Type type_;				//!< 形状タイプ


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param[in] type 形状タイプ
	//----------------------------------------
	CollisionShapeBase(Type type) : type_(type) {}

	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @param void なし
	//----------------------------------------
	virtual ~CollisionShapeBase() {}

	// プロパティ
	Type getType() { return type_; }
};



#endif