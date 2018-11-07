//================================================================================
//
//    X���f���}�l�[�W���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2018/01/21
//
//================================================================================



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "ModelXManager.h"

#include <Texture\TextureManager\TextureManager.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const std::string ModelXManager::DEFAULT_PATH = "resource/ModelX/";



//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

std::unordered_map<std::string, ModelXObject*> ModelXManager::share_model_map_;
std::unordered_map<std::string, ModelXObject*> ModelXManager::unique_model_map_;



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

void ModelXManager::InitAllData()
{
	// �e�평����
	InitUniqueData();
	InitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐�(���L�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXManager::InitShareData()
{
	// �}�b�v�̏�����
	share_model_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐�(�ŗL�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXManager::InitUniqueData()
{
	// �}�b�v�̏�����
	unique_model_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(�S�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXManager::UninitAllData()
{
	// �e��I������
	UninitUniqueData();
	UninitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(���L�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXManager::UninitShareData()
{
	// �eX���f���̉��
	for(auto& contents : share_model_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// �}�b�v�̑S����
	share_model_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(�ŗL�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXManager::UninitUniqueData()
{
	// �eX���f���̉��
	for(auto& contents : unique_model_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// �}�b�v�̑S����
	unique_model_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���L�f�[�^�̒ǉ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject* ModelXManager::AddShareData(const std::string* key_name, const std::string* file_path)
{
	ModelXObject* temp_object = GetModelXObject(key_name);

	// ���݂���ꍇ
	if (temp_object != nullptr) return temp_object;

	// ���݂��Ȃ��ꍇ
	std::string temp_path = MakeFilePath(key_name, file_path);
	temp_object = new ModelXObject(&temp_path, true);
	share_model_map_.insert(std::make_pair(*key_name, temp_object));
	return temp_object;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �ŗL�f�[�^�̒ǉ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject* ModelXManager::AddUniqueData(const std::string* key_name, const std::string* file_path)
{
	ModelXObject* temp_object = GetModelXObject(key_name);

	// ���݂���ꍇ
	if (temp_object != nullptr) return temp_object;

	// ���݂��Ȃ��ꍇ
	std::string temp_path = MakeFilePath(key_name, file_path);
	temp_object = new ModelXObject(&temp_path, false);
	unique_model_map_.insert(std::make_pair(*key_name, temp_object));
	return temp_object;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���f��X�I�u�W�F�N�g�擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject* ModelXManager::GetModelXObject(const std::string* key_name)
{
	// ���L�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_share = share_model_map_.find(*key_name);
	if (itr_share != share_model_map_.end()) return itr_share->second;
	
	// �ŗL�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_unique = unique_model_map_.find(*key_name);
	if (itr_unique != unique_model_map_.end()) return itr_unique->second;

	return nullptr;
}



//--------------------------------------------------------------------------------
//
// [ �t�@�C���p�X�쐬�֐� ]
//
//--------------------------------------------------------------------------------

std::string ModelXManager::MakeFilePath(const std::string* key_name, const std::string* file_path)
{
	// �f�t�H���g�̃p�X���g�p
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;
	
	// �C�ӂ̃p�X���g�p
	return *file_path + *key_name;
}