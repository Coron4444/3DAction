//================================================================================
//
//    �G�t�F�N�V�A�}�l�[�W���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/08/30
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "EffekseerManager.h"
#include <main.h>
#include <Renderer/Renderer.h>
#include <ComponentManager/DrawManager/Camera/Camera.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const std::string EffekseerManager::DEFAULT_PATH = "resource/Effekseer/";
const int MAX_SPRITE_NUM = 2000;


//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

std::unordered_map<std::string, EffekseerArray*> EffekseerManager::share_effekseer_map_;
std::unordered_map<std::string, EffekseerArray*> EffekseerManager::unique_effekseer_map_;

Effekseer::Matrix44 EffekseerManager::projection_matrix_;
Effekseer::Matrix44 EffekseerManager::view_matrix_;



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

void EffekseerManager::InitAllData()
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

void EffekseerManager::InitShareData()
{
	// �}�b�v�̏�����
	share_effekseer_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐�(�ŗL�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::InitUniqueData()
{
	// �}�b�v�̏�����
	unique_effekseer_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(�S�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::UninitAllData()
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

void EffekseerManager::UninitShareData()
{
	// �e�G�t�F�N�V�A�I�u�W�F�N�g�z��̉��
	for(auto& contents : share_effekseer_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// �}�b�v�̑S����
	share_effekseer_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐�(�ŗL�f�[�^) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::UninitUniqueData()
{
	// �e�G�t�F�N�V�A�I�u�W�F�N�g�z��̉��
	for(auto& contents : unique_effekseer_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// �}�b�v�̑S����
	unique_effekseer_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::Update()
{
	for (auto contents : share_effekseer_map_)
	{
		contents.second->Update(&projection_matrix_, &view_matrix_);
	}

	for (auto contents : unique_effekseer_map_)
	{
		contents.second->Update(&projection_matrix_, &view_matrix_);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::Draw()
{
	bool is_draw = false;

	for (auto contents : share_effekseer_map_)
	{
		contents.second->Draw();
		is_draw = true;
	}

	for (auto contents : unique_effekseer_map_)
	{
		contents.second->Draw();
		is_draw = true;
	}

	if (!is_draw) return;

	// �T���v���[�X�e�[�g�����ɖ߂�
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->SetDefaultSamplerState();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���L�f�[�^�̒ǉ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::AddShareData(const std::string* key_name, const std::string* file_path)
{
	// ���L�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_share = share_effekseer_map_.find(*key_name);
	if (itr_share != share_effekseer_map_.end()) return;
	
	// �ŗL�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_unique = unique_effekseer_map_.find(*key_name);
	if (itr_unique != unique_effekseer_map_.end()) return;

	// ���݂��Ȃ��ꍇ
	std::string temp_path = MakeFilePath(key_name, file_path);
	EffekseerArray* temp_array = new EffekseerArray(&temp_path);
	share_effekseer_map_.insert(std::make_pair(*key_name, temp_array));
	return;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �ŗL�f�[�^�̒ǉ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::AddUniqueData(const std::string* key_name, const std::string* file_path)
{
	// ���L�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_share = share_effekseer_map_.find(*key_name);
	if (itr_share != share_effekseer_map_.end()) return;
	
	// �ŗL�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_unique = unique_effekseer_map_.find(*key_name);
	if (itr_unique != unique_effekseer_map_.end()) return;

	// ���݂��Ȃ��ꍇ
	std::string temp_path = MakeFilePath(key_name, file_path);
	EffekseerArray* temp_array = new EffekseerArray(&temp_path);
	unique_effekseer_map_.insert(std::make_pair(*key_name, temp_array));
	return;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �G�t�F�N�V�A�I�u�W�F�N�g�擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::CreateDisposableEffekseerObject(const std::string* key_name, Vec3 position, 
													   Vec3 scale)
{
	// ���L�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_share = share_effekseer_map_.find(*key_name);
	if (itr_share != share_effekseer_map_.end())
	{
		CreateDisposableEffekseerObjectFromArray(itr_share->second, position, scale);
		return;
	}
	
	// �ŗL�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_unique = unique_effekseer_map_.find(*key_name);
	if (itr_unique != unique_effekseer_map_.end())
	{
		CreateDisposableEffekseerObjectFromArray(itr_unique->second, position, scale);
		return;
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �G�t�F�N�V�A�I�u�W�F�N�g�擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerObject* EffekseerManager::GetReferenceEffekseerObject(const std::string* key_name)
{
	// ���L�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_share = share_effekseer_map_.find(*key_name);
	if (itr_share != share_effekseer_map_.end()) return GetReferenceEffekseerObjectFromArray(itr_share->second);
	
	// �ŗL�f�[�^�}�b�v�ɂ��邩�̊m�F
	auto itr_unique = unique_effekseer_map_.find(*key_name);
	if (itr_unique != unique_effekseer_map_.end()) return GetReferenceEffekseerObjectFromArray(itr_unique->second);

	return nullptr;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �v���W�F�N�V�����s��쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::CreateProjectionMatrix(int angle_of_view_)
{
	projection_matrix_ = Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(angle_of_view_), 
																(float)SCREEN_WIDTH / SCREEN_HEIGHT,  
																Camera::NEAR_CLIPPING_PLANE, 
																Camera::FAR_CLIPPING_PLANE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �r���[�s��쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::CreateViewMatrix(Vec3 position, Vec3 look_at_point, Vec3 camera_up)
{
	view_matrix_ = Effekseer::Matrix44().LookAtLH(Effekseer::Vector3D(position.x, position.y, position.z),
												  Effekseer::Vector3D(look_at_point.x, look_at_point.y, look_at_point.z),
												  Effekseer::Vector3D(camera_up.x, camera_up.y, camera_up.z));
}



//--------------------------------------------------------------------------------
//
// [ �t�@�C���p�X�쐬�֐� ]
//
//--------------------------------------------------------------------------------

std::string EffekseerManager::MakeFilePath(const std::string* key_name, const std::string* file_path)
{
	// �f�t�H���g�̃p�X���g�p
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;
	
	// �C�ӂ̃p�X���g�p
	return *file_path + *key_name;
}



//--------------------------------------------------------------------------------
//
// [ �Q�ƃG�t�F�N�V�A�I�u�W�F�N�g�擾�֐� ]
//
//--------------------------------------------------------------------------------

EffekseerObject* EffekseerManager::GetReferenceEffekseerObjectFromArray(EffekseerArray* effekseer_array)
{
	return effekseer_array->GetReferenceEffekseerObject();
}



//--------------------------------------------------------------------------------
//
// [ �g���̂ăG�t�F�N�V�A�I�u�W�F�N�g�擾�֐� ]
//
//--------------------------------------------------------------------------------

void EffekseerManager::CreateDisposableEffekseerObjectFromArray(EffekseerArray* effekseer_array,
																Vec3 position, Vec3 scale)
{
	return effekseer_array->CreateDisposableEffekseerObject(position, scale);
}