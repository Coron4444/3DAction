//================================================================================
//!	@file	 ComponentBase.cpp
//!	@brief	 コンポーネントBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "ComponentBase.h"



//****************************************
// プロパティ定義
//****************************************
GameObjectBase* ComponentBase::getpGameObject()
{
	return game_object_; 
}



void ComponentBase::setGameObject(GameObjectBase* value)
{
	game_object_ = value; 
}



//****************************************
// 関数定義
//****************************************
ComponentBase::~ComponentBase()
{
}