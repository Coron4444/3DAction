//================================================================================
//
//    X���f���}�l�[�W���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2018/01/21
//
//================================================================================

#ifndef	_MODEL_X_MANAGER_H_
#define _MODEL_X_MANAGER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>
#include <vector>
#include <unordered_map>

#include <ModelX\ModelXObject\ModelXObject.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class ModelXManager
{
//------------------------------------------------------------
private :
	static const std::string DEFAULT_PATH;


//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	ModelXManager() = delete;

	// �R�s�[�R���X�g���N�^
	ModelXManager(const ModelXManager& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	ModelXManager& operator = (const ModelXManager& class_name) = delete;


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
	static ModelXObject* AddShareData (const std::string* key_name, const std::string* file_path = nullptr);
	static ModelXObject* AddUniqueData(const std::string* key_name, const std::string* file_path = nullptr);

	// �Q�b�^�\
	static ModelXObject* GetModelXObject(const std::string* key_name);


//------------------------------------------------------------
private :
	static std::string MakeFilePath(const std::string* key_name, const std::string* file_path);


//------------------------------------------------------------
private :
	// �����o�ϐ�
	static std::unordered_map<std::string, ModelXObject*> share_model_map_;
	static std::unordered_map<std::string, ModelXObject*> unique_model_map_;
};



#endif