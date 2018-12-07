//================================================================================
//!	@file	 AABB.h
//!	@brief	 AABBClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_AABB_H_
#define _AABB_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>


//************************************************************														   
//! @brief   AABBClass
//!
//! @details AABBのClass
//************************************************************
class AABB : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Vector3D position_;	//!< 座標
	Vector3D length_;	//!< 各辺の長さ
	Vector3D min_;		//!< 最小値
	Vector3D max_;		//!< 最大値


//====================
// 関数
//====================
public:
	/**
	* @brief
	* コンストラクタ
	*/
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	AABB() : CollisionShapeBase(CollisionShapeBase::Type::AABB) {}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param[in] position 座標
	//! @param[in] length   各辺の長さ
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D length)
	{
		// 座標を設定
		position_ = position;

		// 長さを設定
		length_ = length;

		// 最小値と最大値
		UpdateMinAndMax();
	}

	//----------------------------------------
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update()
	{
		// 最小値と最大値
		UpdateMinAndMax();
	}

	// プロパティ
	Vector3D* getpPositon() { return &position_; }
	Vector3D* getpLength() { return &length_; }
	void setLength(Vector3D value) { length_ = value; };
	Vector3D* getpMin() { return &min_; }
	Vector3D* getpMax() { return &max_; }


private:
	//----------------------------------------
	//! @brief 最小値と最大値更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateMinAndMax()
	{
		min_ = position_ - length_;
		max_ = position_ + length_;
	}
};



#endif