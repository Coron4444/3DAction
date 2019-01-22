//================================================================================
//!	@file	 VertexShaderNull.cpp
//!	@brief	 空白頂点シェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "VertexShaderNull.h"



//****************************************
// 関数定義
//****************************************
void VertexShaderNull::Init()
{
	InitDevice();
}



void VertexShaderNull::Uninit()
{
}



void VertexShaderNull::ObjectSetting(DrawBase* draw, Camera* camera,
									unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



void VertexShaderNull::MeshSetting(DrawBase* draw, Camera* camera,
								  unsigned object_index, unsigned mesh_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
	mesh_index = mesh_index;
}