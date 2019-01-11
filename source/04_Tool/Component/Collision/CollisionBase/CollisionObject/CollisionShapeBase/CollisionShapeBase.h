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
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 形状タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval Type 形状タイプ
	//----------------------------------------
	Type getType();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param type 形状タイプ
	//----------------------------------------
	CollisionShapeBase(Type type);

	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~CollisionShapeBase() = 0;
};



#endif