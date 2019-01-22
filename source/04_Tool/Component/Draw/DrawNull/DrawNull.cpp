//================================================================================
//!	@file	 DrawNull.cpp
//!	@brief	 空白描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================


//****************************************
// インクルード文
//****************************************
#include <assert.h>

#include "DrawNull.h"



//****************************************
// プロパティ定義
//****************************************
unsigned DrawNull::getObjectNum()
{
	return 1;
}



unsigned DrawNull::getMeshNum(unsigned object_index)
{
	object_index = object_index;
	return 1;
}



unsigned DrawNull::getBoneNum(unsigned object_index,
							  unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	return 1;
}



MATRIX* DrawNull::getpMatrix(unsigned object_index)
{
	object_index = object_index;
	assert("行列取得プロパティが未実装です");
	return nullptr;
}



MATRIX* DrawNull::getpBoneMatrix(unsigned object_index,
								 unsigned mesh_index,
								 unsigned bone_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	bone_index = bone_index;
	return nullptr;
}



D3DMATERIAL9* DrawNull::getpMaterial(unsigned object_index,
									 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	return nullptr;
}



LPDIRECT3DTEXTURE9 DrawNull::getpDiffuseTexture(unsigned object_index,
												unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	return nullptr;
}



LPDIRECT3DTEXTURE9 DrawNull::getpNormalTexture(unsigned object_index,
											   unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	return nullptr;
}



//****************************************
// 関数定義
//****************************************
DrawNull::~DrawNull()
{
}



void DrawNull::Init()
{
}



void DrawNull::Uninit()
{
}



void DrawNull::Update()
{
}



void DrawNull::DebugDisplay()
{
}



void DrawNull::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	assert("描画関数が未実装です");
}



void DrawNull::SettingBeforeDrawing(Camera* camera, unsigned object_index)
{
	camera = camera;
	object_index = object_index;
}



void DrawNull::SettingAfterDrawing(Camera* camera, unsigned object_index)
{
	camera = camera;
	object_index = object_index;
}