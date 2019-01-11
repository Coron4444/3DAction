//================================================================================
//!	@file	 DrawNull.cpp
//!	@brief	 �󔒕`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include <assert.h>

#include "DrawNull.h"



//****************************************
// �v���p�e�B��`
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



MATRIX* DrawNull::getpMatrix(unsigned object_index)
{
	object_index = object_index;
	assert("�s��擾�v���p�e�B���������ł�");
	return nullptr;
}



D3DMATERIAL9* DrawNull::getpMaterial(unsigned object_index,
									 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	return nullptr;
}



LPDIRECT3DTEXTURE9 DrawNull::getpDecaleTexture(unsigned object_index,
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
// �֐���`
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

	assert("�`��֐����������ł�");
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