//================================================================================
//
//    �G�t�F�N�V�A�}�l�[�W���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/08/30
//
//================================================================================

#ifndef	_EFFEKSEER_MANAGER_H_
#define _EFFEKSEER_MANAGER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>
#include <vector>
#include <unordered_map>

#include "../EffekseerArray/EffekseerArray.h"
#include "../EffekseerObject/EffekseerObject.h"



//======================================================================
//
// �N���X��`
//
//======================================================================

class EffekseerManager
{
//------------------------------------------------------------
private :
	static const std::string DEFAULT_PATH;
	static const int MAX_SPRITE_NUM;


//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	EffekseerManager() = delete;

	// �R�s�[�R���X�g���N�^
	EffekseerManager(const EffekseerManager& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	EffekseerManager& operator = (const EffekseerManager& class_name) = delete;


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

	// �X�V
	static void Update();

	// �`��
	static void Draw();

	// �ǉ��֐�
	static void AddShareData (const std::string* key_name, const std::string* file_path = nullptr);
	static void AddUniqueData(const std::string* key_name, const std::string* file_path = nullptr);

	// �v���W�F�N�V�����s��
	static void CreateProjectionMatrix(int angle_of_view_);

	// �r���[�s��
	static void CreateViewMatrix(Vec3 position, Vec3 look_at_point, Vec3 camera_up);

	// �g���̂ăG�t�F�N�V�A�I�u�W�F�N�g�̍쐬
	static void CreateDisposableEffekseerObject(const std::string* key_name, Vec3 position, Vec3 scale = Vec3(1.0f, 1.0f, 1.0f));

	// �Q�ƃG�t�F�N�V�A�I�u�W�F�N�g�̎擾
	static EffekseerObject* GetReferenceEffekseerObject(const std::string* key_name);


//------------------------------------------------------------
private :
	static std::string MakeFilePath(const std::string* key_name, const std::string* file_path);
	static EffekseerObject* GetReferenceEffekseerObjectFromArray(EffekseerArray* effekseer_array);
	static void CreateDisposableEffekseerObjectFromArray(EffekseerArray* effekseer_array, Vec3 position, Vec3 scale);

//------------------------------------------------------------
private :
	// �����o�ϐ�
	static std::unordered_map<std::string, EffekseerArray*> share_effekseer_map_;
	static std::unordered_map<std::string, EffekseerArray*> unique_effekseer_map_;

	// �G�t�F�N�V�A�p�s��
	static Effekseer::Matrix44 projection_matrix_;
	static Effekseer::Matrix44 view_matrix_;
};



#endif