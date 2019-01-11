//================================================================================
//!	@file	 ResourceManager.h
//!	@brief	 ���\�[�X�}�l�[�W��Class
//! @details static
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Texture\TextureManager\TextureManager.h>
#include <ModelX\ModelXManager\ModelXManager.h>
#include <Effekseer\EffekseerManager\EffekseerManager.h>



//======================================================================
//
// �N���X��`
//
//======================================================================
//************************************************************														   
//! @brief   ���\�[�X�}�l�[�W��Class
//!
//! @details ���\�[�X�S�̂̃}�l�[�W��Class
//************************************************************
class ResourceManager
{
//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	ResourceManager() = delete;

	// �R�s�[�R���X�g���N�^
	ResourceManager(const ResourceManager& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	ResourceManager& operator = (const ResourceManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	static void InitAllData();
	static void InitShareData();
	static void InitUniqueData();

	static void UninitAllData();
	static void UninitShareData();
	static void UninitUniqueData();
};



#endif