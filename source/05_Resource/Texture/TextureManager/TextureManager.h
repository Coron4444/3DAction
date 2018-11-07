//================================================================================
//
//    �e�N�X�`���}�l�[�W���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2017/12/19
//
//================================================================================

#ifndef	_TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>
#include <vector>
#include <unordered_map>

#include <Texture\TextureObject\TextureObject.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class TextureManager
{
//------------------------------------------------------------
private :
	static const std::string DEFAULT_PATH;


//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	TextureManager() = delete;

	// �R�s�[�R���X�g���N�^
	TextureManager(const TextureManager& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	TextureManager& operator = (const TextureManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �������֐�
	static void InitAllData();
	static void InitShareData();
	static void InitUniqueData();

	// �I�������֐�
	static void UninitAllData();
	static void UninitShareData();
	static void UninitUniqueData();

	// �ǉ��֐�
	static TextureObject* AddShareData (const std::string* key_name, const std::string* file_path = nullptr, int pattern_num_all = 1, int pattern_num_width = 1, int pattern_num_height = 1);
	static TextureObject* AddUniqueData(const std::string* key_name, const std::string* file_path = nullptr, int pattern_num_all = 1, int pattern_num_width = 1, int pattern_num_height = 1);

	// �Q�b�^�\
	static TextureObject* GetTextureObject(const std::string* key_name);


//------------------------------------------------------------
private :
	static std::string MakeFilePath(const std::string* key_name, const std::string* file_path);


//------------------------------------------------------------
private :
	// �����o�ϐ�
	static std::unordered_map<std::string, TextureObject*> share_texture_map_;
	static std::unordered_map<std::string, TextureObject*> unique_texture_map_;
};



#endif