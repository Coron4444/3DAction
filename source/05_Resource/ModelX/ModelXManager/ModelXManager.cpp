//================================================================================
//!	@file	 ModelXManager.cpp
//!	@brief	 X���f���}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "ModelXManager.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string ModelXManager::DEFAULT_PATH = "resource/ModelX/";



//****************************************
// static�ϐ���`
//****************************************
ModelXManager* ModelXManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
ModelXManager* ModelXManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new ModelXManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void ModelXManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
ModelXObject* ModelXManager::getpObject(const std::string* key_name,
										const std::string* file_path)
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
	ModelXObject* model_x_object = new ModelXObject();
	model_x_object->Init(&path, key_name);
	model_x_object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, model_x_object));
	return model_x_object;
}



//****************************************
// �֐���`
//****************************************
ModelXManager::ModelXManager()
{
}



void ModelXManager::Init()
{
	// �}�b�v�̏�����
	object_map_.clear();
}



void ModelXManager::Uninit()
{
	// �eX���f���̋������
	auto iterator = object_map_.begin();
	while (iterator != object_map_.end())
	{
		iterator->second->ForcedRelease();
		iterator = object_map_.begin();
	}
	object_map_.clear();
}



void ModelXManager::ReleaseFromTheMap(std::string* key_name)
{
	// �}�b�v������
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		object_map_.erase(iterator);
	}
}



std::string ModelXManager::CreateFilePath(const std::string* key_name,
										  const std::string* file_path)
{
	// �f�t�H���g�̃p�X���g�p
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// �C�ӂ̃p�X���g�p
	return *file_path + *key_name;
}