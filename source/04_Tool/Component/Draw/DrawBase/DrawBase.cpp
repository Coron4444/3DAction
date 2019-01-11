//================================================================================
//!	@file	 DrawBase.cpp
//!	@brief	 描画BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "DrawBase.h"



//****************************************
// プロパティ定義
//****************************************
DrawOrderList* DrawBase::getpDrawOrderList() 
{
	return &draw_order_list_; 
}



//****************************************
// 関数定義
//****************************************
DrawBase::~DrawBase()
{
}



void DrawBase::LimitedChangeCameraType(Camera* camera, Camera::Type type)
{
	save_camera_type_ = camera->getType();
	camera->setType(type);
}



void DrawBase::RevivalCameraType(Camera* camera)
{
	if (save_camera_type_ == Camera::Type::NONE) return;
	camera->setType(save_camera_type_);
}