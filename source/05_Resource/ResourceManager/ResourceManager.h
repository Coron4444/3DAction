//================================================================================
//
//    ���\�[�X�}�l�[�W���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2017/12/19
//
//================================================================================

#ifndef	_RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <Texture\TextureManager\TextureManager.h>
#include <ModelX\ModelXManager\ModelXManager.h>
#include <Effekseer\EffekseerManager\EffekseerManager.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

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