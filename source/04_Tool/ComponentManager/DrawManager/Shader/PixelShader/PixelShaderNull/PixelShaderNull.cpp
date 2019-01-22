//================================================================================
//!	@file	 PixelShaderNull.cpp
//!	@brief	 空白ピクセルシェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "PixelShaderNull.h"



//****************************************
// 関数定義
//****************************************
void PixelShaderNull::Init()
{
	InitDevice();
}



void PixelShaderNull::Uninit()
{
}



void PixelShaderNull::ObjectSetting(DrawBase* draw, Camera* camera,
									unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



void PixelShaderNull::MeshSetting(DrawBase* draw, Camera* camera,
								  unsigned object_index, unsigned mesh_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
	mesh_index = mesh_index;
}