//================================================================================
//
//    �G�t�F�N�V�A�z��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/01
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "EffekseerArray.h"

#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const unsigned EffekseerArray::DISPOSABLE_ARRAY_NUM = 5;
const unsigned EffekseerArray::REFERENCE_ARRAY_NUM  = 5;


//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerArray::EffekseerArray(const std::string* file_path)
	: next_reference_index_(0)
{
	// �g���̂ăG�t�F�N�V�A�I�u�W�F�N�g�̍쐬
	disposable_effekseer_array_.resize(DISPOSABLE_ARRAY_NUM);
	for (auto& contents : disposable_effekseer_array_)
	{
		contents = new EffekseerObject(file_path);
	}

	// �Q�ƃG�t�F�N�V�A�I�u�W�F�N�g�̍쐬
	reference_effekseer_array_.resize(REFERENCE_ARRAY_NUM);
	for (auto& contents : reference_effekseer_array_)
	{
		contents = new EffekseerObject(file_path);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerArray::~EffekseerArray()
{
	// �g���̂ăG�t�F�N�V�A�I�u�W�F�N�g�̉��
	for (auto& contents : disposable_effekseer_array_)
	{
		SafeRelease::Normal(&contents);
	}

	// �Q�ƃG�t�F�N�V�A�I�u�W�F�N�g�̉��
	for (auto& contents : reference_effekseer_array_)
	{
		SafeRelease::Normal(&contents);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerArray::Update(Effekseer::Matrix44* projection_matrix, Effekseer::Matrix44* view_matrix)
{
	// ���X�g�̍X�V
	UpdateList();

	// �g���̂ăG�t�F�N�V�A�I�u�W�F�N�g�̍X�V
	for (auto contents : disposable_effekseer_list_)
	{
		contents->SetProjectionMatrix(projection_matrix);
		contents->SetViewMatrix(view_matrix);
		contents->Update();
	}

	// �Q�ƃG�t�F�N�V�A�I�u�W�F�N�g�̍X�V
	for (unsigned i = 0; i < next_reference_index_; i++)
	{
		reference_effekseer_array_[i]->SetProjectionMatrix(projection_matrix);
		reference_effekseer_array_[i]->SetViewMatrix(view_matrix);
		reference_effekseer_array_[i]->Update();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerArray::Draw()
{
	// �g���̂ăG�t�F�N�V�A�I�u�W�F�N�g�̕`��
	for (auto contents : disposable_effekseer_list_)
	{
		contents->Draw();
	}

	// �Q�ƃG�t�F�N�V�A�I�u�W�F�N�g�̕`��
	for (unsigned i = 0; i < next_reference_index_; i++)
	{
		reference_effekseer_array_[i]->Draw();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �g���̂ăG�t�F�N�V�A�I�u�W�F�N�g�̍쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerArray::CreateDisposableEffekseerObject(Vec3 position, Vec3 scale)
{
	// ��~���Ă���I�u�W�F�N�g��T��
	for (auto contents : disposable_effekseer_array_)
	{
		if (contents->IsPlaing()) continue;

		// ���X�g�֒ǉ�
		disposable_effekseer_list_.push_back(contents);

		// ��ԍX�V
		*contents->GetTransform()->GetPosition() = position;
		*contents->GetTransform()->GetScale()    = scale;
		contents->GetTransform()->UpdateWorldMatrixSRT();

		// �Đ�
		contents->Play();
		
		break;
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Q�ƃI�u�W�F�N�g�̎擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerObject* EffekseerArray::GetReferenceEffekseerObject()
{
	if (next_reference_index_ == reference_effekseer_array_.size()) return nullptr;

	return reference_effekseer_array_[next_reference_index_++];
}



//--------------------------------------------------------------------------------
//
// [ ���X�g�X�V�֐� ]
//
//--------------------------------------------------------------------------------

void EffekseerArray::UpdateList()
{
	auto iterator = disposable_effekseer_list_.begin();

	while (iterator != disposable_effekseer_list_.end())
	{
		// �Đ������ǂ���
		if ((*iterator)->IsPlaing())
		{
			iterator++;
		}
		else
		{
			// �Đ����I������I�u�W�F�N�g������
			iterator = disposable_effekseer_list_.erase(iterator);
		}
	}
}