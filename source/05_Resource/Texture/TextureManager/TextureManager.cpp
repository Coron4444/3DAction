//================================================================================
//
//    �e�N�X�`���}�l�[�W���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2017/12/19
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "TextureManager.h"



//======================================================================
//
// �萔��`
//
//======================================================================

const std::string TextureManager::DEFAULT_PATH = "resource/Texture/";



//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

std::unordered_map<std::string, TextureObject*> TextureManager::share_texture_map_;
std::unordered_map<std::string, TextureObject*> TextureManager::unique_texture_map_;



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

void TextureManager::InitAllData()
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

void TextureManager::InitShareData()
{
	// �}�b�v�̏�����
	share_texture_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐�(�ŗL�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TextureManager::InitUniqueData()
{
	// �}�b�v�̏�����
	unique_texture_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(�S�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TextureManager::UninitAllData()
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

void TextureManager::UninitShareData()
{
	// �e�e�N�X�`���̉��
	for(auto& contents : share_texture_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// �}�b�v�̑S����
	share_texture_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(�ŗL�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TextureManager::UninitUniqueData()
{
	// �e�e�N�X�`���̉��
	for(auto& contents : unique_texture_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// �}�b�v�̑S����
	unique_texture_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���L�f�[�^�̒ǉ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject* TextureManager::AddShareData(const std::string* key_name, const std::string* file_path, 
											int pattern_num_all, int pattern_num_width, int pattern_num_height)
{
	TextureObject* temp_object = GetTextureObject(key_name);

	// ���݂���ꍇ
	if (temp_object != nullptr) return temp_object;

	// ���݂��Ȃ��ꍇ
	std::string temp_path = MakeFilePath(key_name, file_path);
	temp_object = new TextureObject(&temp_path, pattern_num_all, pattern_num_width, pattern_num_height);
	share_texture_map_.insert(std::make_pair(*key_name, temp_object));
	return temp_object;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �ŗL�f�[�^�̒ǉ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject* TextureManager::AddUniqueData(const std::string* key_name, const std::string* file_path, 
											 int pattern_num_all, int pattern_num_width, int pattern_num_height)
{
	TextureObject* temp_object = GetTextureObject(key_name);

	// ���݂���ꍇ
	if (temp_object != nullptr) return temp_object;

	// ���݂��Ȃ��ꍇ
	std::string temp_path = MakeFilePath(key_name, file_path);
	temp_object = new TextureObject(&temp_path, pattern_num_all, pattern_num_width, pattern_num_height);
	unique_texture_map_.insert(std::make_pair(*key_name, temp_object));
	return temp_object;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �e�N�X�`���I�u�W�F�N�g�擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject* TextureManager::GetTextureObject(const std::string* key_name)
{
	// ���L�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_share = share_texture_map_.find(*key_name);
	if (itr_share != share_texture_map_.end()) return itr_share->second;
	
	// �ŗL�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_unique = unique_texture_map_.find(*key_name);
	if (itr_unique != unique_texture_map_.end()) return itr_unique->second;

	return nullptr;
}



//--------------------------------------------------------------------------------
//
// [ �t�@�C���p�X�쐬�֐� ]
//
//--------------------------------------------------------------------------------

std::string TextureManager::MakeFilePath(const std::string* key_name, const std::string* file_path)
{
	// �f�t�H���g�̃p�X���g�p
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;
	
	// �C�ӂ̃p�X���g�p
	return *file_path + *key_name;
}