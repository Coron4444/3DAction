//================================================================================
//!	@file	 TextureManager.cpp
//!	@brief	 �e�N�X�`���}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TextureManager.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string TextureManager::DEFAULT_PATH = "resource/Texture/";



//****************************************
// static�ϐ���`
//****************************************
TextureManager* TextureManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
TextureManager* TextureManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new TextureManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void TextureManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
TextureObject* TextureManager::getpObject(std::string* key_name,
									std::string* file_path,
									int pattern_num_all,
									int pattern_num_width,
									int pattern_num_height)
{
	// �}�b�v�ɂ��邩�̊m�F
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		// �Q�ƃJ�E���^��UP
		iterator->second->AddReferenceCounter();
		
		return iterator->second;
	}

	// �V�K�쐬
	std::string path = CreateFilePath(key_name, file_path);
	TextureObject* texture_object = new TextureObject();
	texture_object->Init(&path);
	texture_object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, texture_object));
	return texture_object;
}



//****************************************
// �֐���`
//****************************************
TextureManager::TextureManager()
{
}



void TextureManager::Init()
{
	// �}�b�v�̏�����
	object_map_.clear();
}



void TextureManager::Uninit()
{
	// �e�e�N�X�`���̉��
	for (auto& contents : object_map_)
	{
		contents.second->ResetReferenceCounter();
		SafeRelease::PlusRelease(&contents.second);
	}
}



std::string TextureManager::CreateFilePath(std::string* key_name,
										   std::string* file_path)
{
	// �f�t�H���g�̃p�X���g�p
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// �C�ӂ̃p�X���g�p
	return *file_path + *key_name;
}