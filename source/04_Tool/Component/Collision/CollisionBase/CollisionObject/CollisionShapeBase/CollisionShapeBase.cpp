//================================================================================
//!	@file	 CollisionShapeBase.cpp
//!	@brief	 衝突形状BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "CollisionShapeBase.h"



//****************************************
// プロパティ定義
//****************************************
CollisionShapeBase::Type CollisionShapeBase::getType()
{
	return type_; 
}



//****************************************
// 関数定義
//****************************************
CollisionShapeBase::CollisionShapeBase(Type type) 
	: type_(type) 
{
}



CollisionShapeBase::~CollisionShapeBase()
{
}