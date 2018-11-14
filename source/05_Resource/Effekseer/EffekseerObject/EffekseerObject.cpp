//================================================================================
//
//    �G�t�F�N�V�A�I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2017/12/18
//
//================================================================================




//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <codecvt>

#include "EffekseerObject.h"

#include <Renderer\Renderer.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const int EffekseerObject::MAX_SPRITE_NUM = 2000;



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

EffekseerObject::EffekseerObject(const std::string* file_path)
	: effekseer_handle_(0),
	  effekseer_effect_(nullptr),
	  is_playing_      (false),
	  is_repeat_       (false),
	  is_pause_        (false)
{
	// �������Ɠǂݍ���
	InitRenderer_Manager();
	InputEffect(file_path);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerObject::~EffekseerObject()
{
	//�G�t�F�N�g�̒�~
	Stop();

	//�G�t�F�N�g�����
	ES_SAFE_RELEASE(effekseer_effect_);

	//�G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	effekseer_manager_->Destroy();

	//�`��p�C���X�^���X��j��
	effekseer_renderer_->Destroy();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::Update()
{
	// ���[���h�s��̐ݒ�
	SetWorldMatrix(transform_.GetWorldMatrix());

	// �Đ������ǂ���
	is_playing_ = effekseer_manager_->Exists(effekseer_handle_);

	if (!is_playing_)
	{
		// ���s�[�g���邩�ǂ���
		if (is_repeat_)
		{
			Play();
		}
		else
		{
			Stop();
		}
	}

	effekseer_manager_->Flip();
	
	//���ׂẴG�t�F�N�g�̍X�V
	effekseer_manager_->Update();

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::Draw()
{
	effekseer_renderer_->BeginRendering();
	effekseer_manager_->Draw();
	effekseer_renderer_->EndRendering();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Đ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::Play()
{
	//�G�t�F�N�g�̍Đ�
	effekseer_handle_ = effekseer_manager_->Play(effekseer_effect_, 0.0f, 0.0f, 0.0f);
	effekseer_manager_->Flip();
	is_playing_ = true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��~�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::Stop()
{
	//�G�t�F�N�g�̒�~
	effekseer_manager_->StopEffect(effekseer_handle_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �ꎞ��~�ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetPause(bool is_pause)
{
	//�G�t�F�N�g�̈ꎞ��~
	is_pause_ = is_pause;
	effekseer_manager_->SetPaused(effekseer_handle_, is_pause_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���x�ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetVelocity(float velocity)
{
	//�G�t�F�N�g�̑��x�w��
	effekseer_manager_->SetSpeed(effekseer_handle_, velocity);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �J���[�ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	effekseer_manager_->SetAllColor(effekseer_handle_, Effekseer::Color(r, g, b, a));
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �v���W�F�N�V�����s��ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetProjectionMatrix(Effekseer::Matrix44* projection_matrix)
{
	effekseer_renderer_->SetProjectionMatrix(*projection_matrix);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �r���[�s��ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerObject::SetViewMatrix(Effekseer::Matrix44* view_matrix)
{
	effekseer_renderer_->SetCameraMatrix(*view_matrix);
}



//--------------------------------------------------------------------------------
//
// [ �����_���[&�}�l�[�W���������֐� ]
//
//--------------------------------------------------------------------------------

void EffekseerObject::InitRenderer_Manager()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(EffekseerObject.cpp)", "Error", MB_OK);
		return;
	}

	// �G�t�F�N�V�A�̏�����
	effekseer_renderer_ = EffekseerRendererDX9::Renderer::Create(device, MAX_SPRITE_NUM);
	effekseer_manager_ = Effekseer::Manager::Create(MAX_SPRITE_NUM);

	// �`��@�\�̐ݒ�
	effekseer_manager_->SetSpriteRenderer(effekseer_renderer_->CreateSpriteRenderer());
	effekseer_manager_->SetRibbonRenderer(effekseer_renderer_->CreateRibbonRenderer());
	effekseer_manager_->SetRingRenderer  (effekseer_renderer_->CreateRingRenderer());
	effekseer_manager_->SetTrackRenderer (effekseer_renderer_->CreateTrackRenderer());
	effekseer_manager_->SetModelRenderer (effekseer_renderer_->CreateModelRenderer());

	// �e�N�X�`���̓ǂݍ��݂�ݒ�(����̓t�@�C������ǂݍ���)
	effekseer_manager_->SetTextureLoader(effekseer_renderer_->CreateTextureLoader());
	effekseer_manager_->SetModelLoader  (effekseer_renderer_->CreateModelLoader());

	// ������W�n�ɐݒ�
	effekseer_manager_->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);
}



//--------------------------------------------------------------------------------
//
// [ �G�t�F�N�g�̓ǂݍ��݊֐� ]
//
//--------------------------------------------------------------------------------

void EffekseerObject::InputEffect(const std::string* file_path)
{
	// wchar_t�ɃR���o�[�g
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
	std::wstring temp_file_path = convert.from_bytes(*file_path);


	// �G�t�F�N�g�̓ǂݍ���
	effekseer_effect_ = Effekseer::Effect::Create(effekseer_manager_, 
												  (const EFK_CHAR*)temp_file_path.c_str());	
}



//--------------------------------------------------------------------------------
//
// [ ���[���h�s��ݒ�֐� ]
//
//--------------------------------------------------------------------------------

void EffekseerObject::SetWorldMatrix(const MATRIX* world_matrix)
{
	// �G�t�F�N�V�A�p���[���h�s��
	world_matrix_.Value[0][0] = world_matrix->_11;
	world_matrix_.Value[0][1] = world_matrix->_12;
	world_matrix_.Value[0][2] = world_matrix->_13;
	world_matrix_.Value[1][0] = world_matrix->_21;
	world_matrix_.Value[1][1] = world_matrix->_22;
	world_matrix_.Value[1][2] = world_matrix->_23;
	world_matrix_.Value[2][0] = world_matrix->_31;
	world_matrix_.Value[2][1] = world_matrix->_32;
	world_matrix_.Value[2][2] = world_matrix->_33;
	world_matrix_.Value[3][0] = world_matrix->_41;
	world_matrix_.Value[3][1] = world_matrix->_42;
	world_matrix_.Value[3][2] = world_matrix->_43;

	// ���[���h�s����Z�b�g
	effekseer_manager_->SetMatrix(effekseer_handle_, world_matrix_);
}