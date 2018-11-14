//================================================================================
//
//    �o�b�N�o�b�t�@�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/12
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "BackBuffer.h"
#include "../../ShaderManager/ShaderManager.h"
#include <Component/DrawBase/DrawBase.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>
#include <GameObjectBase/GameObjectBase.h>

#include <Renderer/Renderer.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void BackBuffer::Init()
{
	ResetAllArray();

	// �J�����̏�����
	camera_ = new Camera();
	camera_->Init(nullptr);

	// �t�F�[�h�̏�����
	fade_ = new Fade();
	is_fade_ = false;
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void BackBuffer::Uninit()
{
	ResetAllArray();

	// �t�F�[�h���
	SafeRelease::PlusUninit(&camera_);
	SafeRelease::Normal(&fade_);
}



//--------------------------------------------------
// +�V�[���ύX���̏I���֐�
//--------------------------------------------------
void BackBuffer::UninitWhenChangeScene()
{
	ResetAllArray();

	camera_->Uninit();
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void BackBuffer::Update()
{
	// �J�����̍X�V
	camera_->Update();

	// �����`��R���|�[�l���g�̍~���\�[�g
	SortTransparent();

	// �r���{�[�h�X�V
	AllBillboardUpdate();

	// �t�F�[�h�X�V
	if (is_fade_) fade_->Update();

	// �G�t�F�N�V�A�̍X�V
	EffekseerManager::CreateProjectionMatrix(camera_->GetAngleOfView());
	EffekseerManager::CreateViewMatrix(*camera_->GetPositon(),
									   *camera_->GetLookAtPoint(),
									   *camera_->GetUp());
	EffekseerManager::Update();
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void BackBuffer::Draw()
{
	// �����_�[�^�[�Q�b�g�̐؂�ւ�

	// �s�����I�u�W�F�N�g
	camera_->SetType(Camera::Type::PERSPECTIVE);
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		// �V�F�[�_�[���Z�b�g
		shader_manager_->SetShader(all_opacity_draw_.GetArrayObject(i),
								   ShaderManager::VertexShaderType::VERTEX_NONE,
								   ShaderManager::PixelShaderType::PIXEL_NONE);

		// �I�u�W�F�N�g�������[�v
		for (unsigned j = 0; j < all_opacity_draw_.GetArrayObject(i)->GetDrawObjectNum(); j++)
		{
			// ����J�����^�C�v�ύX
			all_opacity_draw_.GetArrayObject(i)->LimitedChangeCameraType(camera_, j);

			// ���b�V���ԋ��ʂ̃O���[�o�[���ϐ����Z�b�g
			shader_manager_->CommonSetting(all_opacity_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// ���b�V���������[�v
			for (unsigned k = 0; k < all_opacity_draw_.GetArrayObject(i)->GetMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_opacity_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_opacity_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// �J�����^�C�v����
			all_opacity_draw_.GetArrayObject(i)->RevivalCameraType(camera_);
		}
	}
	
	// �����I�u�W�F�N�g
	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer(); i++)
	{
		// �V�F�[�_�[���Z�b�g
		shader_manager_->SetShader(all_transparency_draw_.GetArrayObject(i),
								   ShaderManager::VertexShaderType::VERTEX_NONE,
								   ShaderManager::PixelShaderType::PIXEL_NONE);

		// �I�u�W�F�N�g�������[�v
		for (unsigned j = 0; j < all_transparency_draw_.GetArrayObject(i)->GetDrawObjectNum(); j++)
		{
			// ����J�����^�C�v�ύX
			all_transparency_draw_.GetArrayObject(i)->LimitedChangeCameraType(camera_, j);

			// ���b�V���ԋ��ʂ̃O���[�o�[���ϐ����Z�b�g
			shader_manager_->CommonSetting(all_transparency_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// ���b�V���������[�v
			for (unsigned k = 0; k < all_transparency_draw_.GetArrayObject(i)->GetMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_transparency_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_transparency_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// �J�����^�C�v����
			all_transparency_draw_.GetArrayObject(i)->RevivalCameraType(camera_);
		}
	}

	// �G�t�F�N�V�A
	EffekseerManager::Draw();

	// 2D
	camera_->SetType(Camera::Type::TWO_DIMENSIONAL);
	for (unsigned i = 0; i < all_2D_draw_.GetEndPointer(); i++)
	{
		// �V�F�[�_�[���Z�b�g
		shader_manager_->SetShader(all_2D_draw_.GetArrayObject(i),
								   ShaderManager::VertexShaderType::VERTEX_NONE,
								   ShaderManager::PixelShaderType::PIXEL_NONE);

		// �I�u�W�F�N�g�������[�v
		for (unsigned j = 0; j < all_2D_draw_.GetArrayObject(i)->GetDrawObjectNum(); j++)
		{
			// ����J�����^�C�v�ύX
			all_2D_draw_.GetArrayObject(i)->LimitedChangeCameraType(camera_, j);

			// ���b�V���ԋ��ʂ̃O���[�o�[���ϐ����Z�b�g
			shader_manager_->CommonSetting(all_2D_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// ���b�V���������[�v
			for (unsigned k = 0; k < all_2D_draw_.GetArrayObject(i)->GetMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_2D_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_2D_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// �J�����^�C�v����
			all_2D_draw_.GetArrayObject(i)->RevivalCameraType(camera_);
		}
	}

	// �t�F�[�h
	FadeDraw();
}



//--------------------------------------------------
// +�`����N���X�̒ǉ��֐�
//--------------------------------------------------
void BackBuffer::AddDrawBaseToArray(DrawBase* draw)
{
	switch (draw->GetDrawOrderList()->GetDrawType())
	{
		case DrawOrderList::DrawType::OPACITY:
		{
			all_opacity_draw_.AddToArray(draw);
			break;
		}
		case DrawOrderList::DrawType::TRANSPARENCY:
		{
			all_transparency_draw_.AddToArray(draw);
			break;
		}
		case DrawOrderList::DrawType::TWO_DIMENSIONAL:
		{
			all_2D_draw_.AddToArray(draw);
			break;
		}
	}
}



//--------------------------------------------------
// +�S�z��̃��Z�b�g�֐�
//--------------------------------------------------
void BackBuffer::ResetAllArray()
{
	all_opacity_draw_.ResetArray();
	all_transparency_draw_.ResetArray();
	all_2D_draw_.ResetArray();
}



//--------------------------------------------------
// +�t�F�[�h�������֐�
//--------------------------------------------------
void BackBuffer::InitFade(Fade::Type type, Fade::State state, Vec2 size,
						  XColor4 fade_color, float fade_speed)
{
	// �t�F�[�h�̏�����
	fade_->Init(type, state, size, fade_color, fade_speed);

	// �t�F�[�h�t���OON
	is_fade_ = true;
}



//--------------------------------------------------
// +�t�F�[�h�I���֐�
//--------------------------------------------------
void BackBuffer::UninitFade()
{
	// �t�F�[�h�̏I������
	fade_->Uninit();

	// �t�F�[�h�t���OOFF
	is_fade_ = false;
}



//--------------------------------------------------
// -�����`��R���|�[�l���g�̃\�[�g�֐� 
//--------------------------------------------------
void BackBuffer::SortTransparent()
{
	// �����I�u�W�F�N�g�����邩�ǂ���
	if (all_transparency_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer() - 1; i++)
	{
		// �[�x�l���Z�o
		Vector3D temp_vector0 = *all_transparency_draw_.GetArrayObject(i)->GetGameObject()
			->GetTransform()->GetPosition() - *camera_->GetPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparency_draw_.GetEndPointer(); j++)
		{
			// �[�x�l���Z�o
			Vector3D temp_vector1 = *all_transparency_draw_.GetArrayObject(j)
				->GetGameObject()->GetTransform()->GetPosition() - *camera_->GetPositon();

			float depth_value1 = temp_vector1.GetLengthSquare();

			// �[�x�l���r
			if (depth_value0 < depth_value1)
			{
				// ���ёւ�
				all_transparency_draw_.SortTheTwoObject(i, j);
			}
		}
	}
}



//--------------------------------------------------
// -�r���{�[�h�p�s��ύX�֐�
//--------------------------------------------------
void BackBuffer::SetBillboardMatrix(DrawBase* draw)
{
	// �r���[�s��̓]�u�s����Z�b�g
	draw->GetGameObject()->GetTransform()->UpdateTransposeMatrix(camera_->GetViewMatrix());

	// ���s�������J�b�g
	draw->GetGameObject()->GetTransform()->TransposeMatrixTranslationOff();

	// ���[���h�s��̍X�V
	draw->GetGameObject()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
}



//--------------------------------------------------
// -�S�r���{�[�h�X�V�֐�
//--------------------------------------------------
void BackBuffer::AllBillboardUpdate()
{
	camera_->SetType(Camera::Type::PERSPECTIVE);

	// �s�����I�u�W�F�N�g
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		if (!all_opacity_draw_.GetArrayObject(i)->GetDrawOrderList()
			->GetIsBillboard()) continue;
		SetBillboardMatrix(all_opacity_draw_.GetArrayObject(i));
	}

	// �����I�u�W�F�N�g
	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer(); i++)
	{
		if (!all_transparency_draw_.GetArrayObject(i)->GetDrawOrderList()
			->GetIsBillboard()) continue;
		SetBillboardMatrix(all_transparency_draw_.GetArrayObject(i));
	}
}



//--------------------------------------------------
// -�t�F�[�h�`��֐�
//--------------------------------------------------
void BackBuffer::FadeDraw()
{
	// �`��
	switch (*fade_->GetType())
	{
		case Fade::Type::TYPE_NORMAL:
		{
			camera_->SetType(Camera::Type::TWO_DIMENSIONAL);
			// �V�F�[�_�[���Z�b�g
			shader_manager_->SetShader(fade_,
									   ShaderManager::VertexShaderType::VERTEX_NONE,
									   ShaderManager::PixelShaderType::PIXEL_NONE);

			// �I�u�W�F�N�g�������[�v
			for (unsigned j = 0; j < fade_->GetDrawObjectNum(); j++)
			{
				// ���b�V���ԋ��ʂ̃O���[�o�[���ϐ����Z�b�g
				shader_manager_->CommonSetting(fade_,
											   camera_,
											   ShaderManager::VertexShaderType::VERTEX_NONE,
											   ShaderManager::PixelShaderType::PIXEL_NONE,
											   j);

				// ���b�V���������[�v
				for (unsigned k = 0; k < fade_->GetMeshNum(j); k++)
				{
					shader_manager_->SpecificSetting(fade_,
													 camera_,
													 ShaderManager::VertexShaderType::VERTEX_NONE,
													 ShaderManager::PixelShaderType::PIXEL_NONE,
													 j, k);

					fade_->Draw(j, k);
				}
			}
			break;
		}
		case Fade::Type::TYPE_TRANSITION_01:
		{
			break;
		}
	}
}