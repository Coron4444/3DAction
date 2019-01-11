//================================================================================
//!	@file	 ResourceManager.cpp
//!	@brief	 ���\�[�X�}�l�[�W��Class
//! @details static
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "ResourceManager.h"



//======================================================================
//
// �ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐�(�S�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::InitAllData()
{
	// �e�탊�\�[�X�̏�����
	TextureManager::InitAllData();
	ModelXManager::InitAllData();
	EffekseerManager::InitAllData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐�(���L�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::InitShareData()
{
	// �e�탊�\�[�X�̏�����
	TextureManager::InitShareData();
	ModelXManager::InitShareData();
	EffekseerManager::InitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐�(�ŗL�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::InitUniqueData()
{
	// �e�탊�\�[�X�̏�����
	TextureManager::InitUniqueData();
	ModelXManager::InitUniqueData();
	EffekseerManager::InitUniqueData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(�S�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::UninitAllData()
{
	// �e�탊�\�[�X�̏I������
	ModelXManager::UninitAllData();
	TextureManager::UninitAllData();
	EffekseerManager::UninitAllData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(���L�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::UninitShareData()
{
	// �e�탊�\�[�X�̏I������
	ModelXManager::UninitShareData();
	TextureManager::UninitShareData();
	EffekseerManager::UninitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(�ŗL�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::UninitUniqueData()
{
	// �e�탊�\�[�X�̏I������
	ModelXManager::UninitUniqueData();
	TextureManager::UninitUniqueData();
	EffekseerManager::UninitUniqueData();
}