//================================================================================
//
//    �t�F�[�h�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "Fade.h"

#include <assert.h>
#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <SafeRelease/SafeRelease.h>
#include <Vector\ConvertToFrame\TimeToFrame\TimeToFrame.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// �萔��`
//****************************************
const std::string Fade::TEXTURE_NAME_TRANSITION_01 = "Fade/Transition_01.png";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�R���X�g���N�^
//--------------------------------------------------
Fade::Fade()
	: plane_polygon_(nullptr)
{
	plane_polygon_ = new PlanePolygon();

	// �e�N�X�`���̓o�^
	transition01_texture_ = TextureManager::AddShareData(&TEXTURE_NAME_TRANSITION_01);

	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
}



//--------------------------------------------------
// +�f�X�g���N�^
//--------------------------------------------------
Fade::~Fade()
{
	// �e��J��
	SafeRelease::Normal(&plane_polygon_);
}



//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void Fade::Init(Type type, State state, Vec2 size, XColor4 color, float speed)
{
	// �A�T�[�g�Q
	assert(state != State::STATE_NONE && state != State::STATE_MAX && "�s���ȃX�e�[�g�̓��͂��m�F(fade.cpp)");

	// �e����
	type_ = type;
	state_ = state;

	// �t�F�[�h���w��T�C�Y�ɕύX
	transform_.GetScale()->x = size.x;
	transform_.GetScale()->y = size.y;
	transform_.UpdateWorldMatrixSRT();

	// �G���h�t���OOFF
	end_flag_ = false;

	// �X�e�[�g���Ƃ̏���
	if (state_ == State::STATE_FADE_IN)
	{
		// �J���[
		color.a = 1.0f;
		color_ = color;
		plane_polygon_->SetColor(color_);

		// �t�F�[�h���x(�P�ʁF�b)
		speed_ = -(1.0f / (float)Second_To_Frame(speed));
	}
	else if (state_ == State::STATE_FADE_OUT)
	{
		// �J���[
		color.a = 0.0f;
		color_ = color;
		plane_polygon_->SetColor(color_);

		// �t�F�[�h���x(�P�ʁF�b)
		speed_ = 1.0f / (float)Second_To_Frame(speed);
	}
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void Fade::Uninit()
{
	// �X�e�[�g���Ƃ̏���
	if (state_ == State::STATE_FADE_IN)
	{
		
	}
	else if (state_ == State::STATE_FADE_OUT)
	{
		
	}

	end_flag_ = false;
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void Fade::Update()
{
	// ���l��ύX
	color_.a += speed_;
	plane_polygon_->SetColor(color_);

	// �t�F�[�h�I�u�W�F�N�g�̍X�V
	if (state_ == State::STATE_FADE_IN)
	{
		// ���l��1����������
		if (color_.a <= 0.0f)
		{
			end_flag_ = true;
		}
	}
	else if (state_ == State::STATE_FADE_OUT)
	{
		// ���l��1����������
		if (color_.a >= 1.0f)
		{
			end_flag_ = true;
		}
	}
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void Fade::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// �|���S���`��
	plane_polygon_->Draw();
}