//================================================================================
//
//    �`��}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "DrawManager.h"
#include "Shader/FixedPipelineObject/FixedPipelineObject.h"
#include "Shader/TestShaderObject/TestShaderObject.h"
#include <Component/DrawBase/DrawBase.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>
#include <GameObjectBase/GameObjectBase.h>

#include <Renderer/Renderer.h>

#include <Transform/Transform.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void DrawManager::Init()
{
	// �Œ�p�C�v���C���I�u�W�F�N�g�̏�����
	FixedPipelineObject::Init();

	// �e�X�g�V�F�[�_�[�̏�����
	TestShaderObject::Init();

	// �t�F�[�h�̏�����
	fade_ = new Fade();
	is_fade_ = false;
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void DrawManager::Uninit()
{
	// �Œ�p�C�v���C���̏I������
	FixedPipelineObject::Uninit();

	// �e�X�g�V�F�[�_�[�̏I������
	TestShaderObject::Uninit();

	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�`��z��̃��Z�b�g
	all_draw_.ResetArray();

	// �J�����z��̉��&���Z�b�g
	all_camera_.ReleaseObjectAndResetArray();

	// �t�F�[�h���
	SafeRelease::Normal(&fade_);
}



//--------------------------------------------------
// +�V�[���ύX���̏I���֐�
//--------------------------------------------------
void DrawManager::UninitWhenChangeScene()
{
	// �p�C�v���C���̔z�񃊃Z�b�g
	ResetDrawComponentArray();

	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�`��z��̃��Z�b�g
	all_draw_.ResetArray();

	// �J�����z��̉��&���Z�b�g
	all_camera_.ReleaseObjectAndResetArray();
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void DrawManager::Draw()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	for (unsigned i = 0; i < all_camera_.GetEndPointer(); i++)
	{
		if (all_camera_.GetArrayObject(i) == nullptr) return;

		if (all_camera_.GetArrayObject(i)->IsCameraTypeName(Camera::Type::NORMAL))
		{
			// �m�[�}���J�����p�C�v���C��
			NormalCameraPipeline(i);
		}
	}


	// �f�o�b�O
#ifdef _DEBUG
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		if (all_draw_.GetArrayObject(i) == nullptr) continue;
		all_draw_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



//--------------------------------------------------
// +�`����N���X�̒ǉ��֐�
//--------------------------------------------------
void DrawManager::AddDrawBaseToArray(DrawBase* draw)
{
	// �ǉ��҂��z��ɒǉ�
	await_add_.AddToArray(draw);
}



//--------------------------------------------------
// +�`����N���X�̏㏑���֐�
//--------------------------------------------------
void DrawManager::OverwriteArrayDrawBase(GameObjectBase* game_object,
										 DrawBase* new_draw)
{
	// �V�K��nullptr�̏ꍇ
	if (new_draw == nullptr)
	{
		// �Â��`����N���X�̉��
		ReleaseDrawBaseFromArray(game_object->GetDraw());

		// �Â��`����N���X�̏���
		DrawBase* temp = game_object->GetDraw();
		SafeRelease::Normal(&temp);

		// nullptr�̑��
		game_object->SetDraw(new_draw);
	}
	else
	{
		// �z��̏㏑��
		all_draw_.OverwriteArray(game_object->GetDraw(), new_draw);

		// �Â��`����N���X�̏���
		DrawBase* temp = game_object->GetDraw();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g�̏�����
		game_object->SetDraw(new_draw);
		new_draw->SetGameObject(game_object);
		new_draw->Init();
	}
}



//--------------------------------------------------
// +�`����N���X�̉���֐�
//--------------------------------------------------
void DrawManager::ReleaseDrawBaseFromArray(DrawBase* draw)
{
	// ����҂��z��ɒǉ�
	await_release_.AddToArray(draw);
}



//--------------------------------------------------
// +�f�t�H���g�J�����̍쐬�֐�
//--------------------------------------------------
void DrawManager::CreateDefaultCamera(Camera::State* camera_state, Camera::Type camra_type)
{
	// �f�t�H���g�̃J�����̍쐬
	if (all_camera_.GetEndPointer() > 0) return;
	all_camera_.AddToArray(new Camera(camera_state, camra_type));
	all_camera_.GetArrayObject(0)->CreateProjectionMatrix_PerspectiveFov();
}



//--------------------------------------------------
// +�J�����̒ǉ��֐�
//--------------------------------------------------
void DrawManager::AddCamera(Camera::State* camera_state, Camera::Type camra_type)
{
	// �J�������ő吔�̎�
	if (all_camera_.IsMax())
	{
		// �X�e�[�g�̉��
		SafeRelease::Normal(&camera_state);
		return;
	}

	// �J�����̒ǉ�
	all_camera_.AddToArray(new Camera(camera_state, camra_type));
}



//--------------------------------------------------
// +�J�����̉���֐�
//--------------------------------------------------
void DrawManager::ReleaseCamera(unsigned index)
{
	// �J�����̍폜
	all_camera_.DeleteFromArray(all_camera_.GetArrayObject(index));
}



//--------------------------------------------------
// +�J�����̃X�e�[�g�ύX�֐�
//--------------------------------------------------
void DrawManager::ChangeCameraState(unsigned index, Camera::State* camera_state_)
{
	// �J�������Ȃ��Ƃ�
	if (all_camera_.GetArrayObject(index) == nullptr)
	{
		// �X�e�[�g�̉��
		SafeRelease::Normal(&camera_state_);
		return;
	}

	// �X�e�[�g�̕ύX
	all_camera_.GetArrayObject(index)->ChangeState(camera_state_);
}



//--------------------------------------------------
// +�t�F�[�h�������֐�
//--------------------------------------------------
void DrawManager::InitFade(Fade::Type type, Fade::State state, Vec2 size,
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
void DrawManager::UninitFade()
{
	// �t�F�[�h�̏I������
	fade_->Uninit();

	// �t�F�[�h�t���OOFF
	is_fade_ = false;
}



//--------------------------------------------------
// -�ǉ��҂��z��̒��g��ǉ��֐�
//--------------------------------------------------
void DrawManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if (await_add_.GetEndPointer() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_draw_.AddToArray(await_add_.GetArrayObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.ResetArray();
}



//--------------------------------------------------
// -����҂��z��̒��g������֐�
//--------------------------------------------------
void DrawManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if (await_release_.GetEndPointer() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		all_draw_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.ResetArray();
}



//--------------------------------------------------
// -�X�V�֐�
//--------------------------------------------------
void DrawManager::Update(unsigned index)
{
	// �J�����̍X�V
	all_camera_.GetArrayObject(index)->Update();

	// �o�^�p�z��̃��Z�b�g
	ResetDrawComponentArray();

	// �`��R���|�[�l���g���e�z��ɐU�蕪��
	DistributeDrawComponent(index);

	// �����`��R���|�[�l���g�̍~���\�[�g
	SortTransparent(index);

	// �G�t�F�N�V�A�̍X�V
	EffekseerManager::CreateProjectionMatrix(*all_camera_.GetArrayObject(index)->GetAngleOfView());
	EffekseerManager::CreateViewMatrix(*all_camera_.GetArrayObject(index)->GetPositon(),
									   *all_camera_.GetArrayObject(index)->GetLookAtPoint(),
									   *all_camera_.GetArrayObject(index)->GetUp());
	EffekseerManager::Update();
}



//--------------------------------------------------
// -�`��R���|�[�l���g�z��̃��Z�b�g�֐�
//--------------------------------------------------
void DrawManager::ResetDrawComponentArray()
{
	all_opacity_draw_.ResetArray();
	all_transparent_draw_.ResetArray();
	all_2D_draw_.ResetArray();
}



//--------------------------------------------------
// -�`��R���|�[�l���g�U�蕪���֐�
//--------------------------------------------------
void DrawManager::DistributeDrawComponent(unsigned index)
{
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		if (all_draw_.GetArrayObject(i) == nullptr) continue;

		switch (all_draw_.GetArrayObject(i)->GetState())
		{
			// �s����
			case DrawBase::State::FIXED:
			case DrawBase::State::FIXED_BILLBOARD:
			case DrawBase::State::TEST_SHADER:
			case DrawBase::State::TEST_SHADER_BILLBOARD:
			{
				all_opacity_draw_.AddToArray(all_draw_.GetArrayObject(i));
				break;
			}
			// ����
			case DrawBase::State::FIXED_ALPHA:
			case DrawBase::State::FIXED_BILLBOARD_ALPHA:
			{
				all_transparent_draw_.AddToArray(all_draw_.GetArrayObject(i));
			}
			// 2D
			case DrawBase::State::FIXED_2D:
			{
				all_2D_draw_.AddToArray(all_draw_.GetArrayObject(i));
				break;
			}
		}
	}
}



//--------------------------------------------------
// -�����`��R���|�[�l���g�̃\�[�g�֐� 
//--------------------------------------------------
void DrawManager::SortTransparent(unsigned index)
{
	// �����I�u�W�F�N�g�����邩�ǂ���
	if (all_transparent_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparent_draw_.GetEndPointer() - 1; i++)
	{
		// �[�x�l���Z�o
		Vector3D temp_vector0 = *all_transparent_draw_.GetArrayObject(i)->GetGameObject()->GetTransform()->GetPosition()
			- *all_camera_.GetArrayObject(index)->GetPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparent_draw_.GetEndPointer(); j++)
		{
			// �[�x�l���Z�o
			Vector3D temp_vector1 = *all_transparent_draw_.GetArrayObject(j)->GetGameObject()->GetTransform()->GetPosition()
				- *all_camera_.GetArrayObject(index)->GetPositon();

			float depth_value1 = temp_vector1.GetLengthSquare();

			// �[�x�l���r
			if (depth_value0 < depth_value1)
			{
				// ���ёւ�
				all_transparent_draw_.SortTheTwoObject(i, j);
			}
		}
	}
}



//--------------------------------------------------
// -�r���{�[�h�p�s��ύX�֐�
//--------------------------------------------------
void DrawManager::SetBillboardMatrix(DrawBase* draw, unsigned index)
{
	// �r���[�s��̓]�u�s����Z�b�g
	draw->GetGameObject()->GetTransform()->UpdateTransposeMatrix(all_camera_.GetArrayObject(index)->GetViewMatrix());

	// ���s�������J�b�g
	draw->GetGameObject()->GetTransform()->TransposeMatrixTranslationOff();

	// ���[���h�s��̍X�V
	draw->GetGameObject()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
}



//--------------------------------------------------
// -�e�p�C�v���C���`��֐�
//--------------------------------------------------
void DrawManager::DrawEachPipeline(LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM>* draw,
								   unsigned index)
{
	for (unsigned i = 0; i < draw->GetEndPointer(); i++)
	{
		switch (draw->GetArrayObject(i)->GetState())
		{
			// �Œ�p�C�v���C��
			case DrawBase::State::FIXED:
			{
				FixedPipelineObject::Draw3D(draw->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawBase::State::FIXED_ALPHA:
			{
				FixedPipelineObject::Draw3D(draw->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawBase::State::FIXED_BILLBOARD:
			{
				SetBillboardMatrix(draw->GetArrayObject(i), index);
				FixedPipelineObject::Draw3D(draw->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawBase::State::FIXED_BILLBOARD_ALPHA:
			{
				SetBillboardMatrix(draw->GetArrayObject(i), index);
				FixedPipelineObject::Draw3D(draw->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawBase::State::FIXED_2D:
			{
				FixedPipelineObject::Draw2D(draw->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			// �e�X�g�V�F�[�_�[
			case DrawBase::State::TEST_SHADER:
			{
				TestShaderObject::Draw(draw->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawBase::State::TEST_SHADER_BILLBOARD:
			{
				SetBillboardMatrix(draw->GetArrayObject(i), index);
				TestShaderObject::Draw(draw->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
		}
	}
}



//--------------------------------------------------
// -�e�p�C�v���C���`��֐�
//--------------------------------------------------
void DrawManager::NormalCameraPipeline(unsigned index)
{
	// ���ʍX�V
	Update(index);

	// �s�����I�u�W�F�N�g
	DrawEachPipeline(&all_opacity_draw_, index);

	// �����I�u�W�F�N�g
	DrawEachPipeline(&all_transparent_draw_, index);

	// �G�t�F�N�V�A�̕`��
	EffekseerManager::Draw();

	// 2D�I�u�W�F�N�g
	DrawEachPipeline(&all_2D_draw_, index);

	// �t�F�[�h�̏���
	FadeUpdate_Draw();
}



//--------------------------------------------------
// -�e�p�C�v���C���`��֐�
//--------------------------------------------------
void DrawManager::FadeUpdate_Draw()
{
	if (!is_fade_) return;

	// �X�V
	fade_->Update();

	// �`��
	switch (*fade_->GetType())
	{
		case Fade::Type::TYPE_NORMAL:
		{
			// �f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 device = nullptr;
			Renderer::GetInstance()->GetDevice(&device);
			assert(device != nullptr && "Device�̎擾�Ɏ��s(DrawManager.cpp)");

			FixedPipelineObject::SetDraw2D();
			device->SetTransform(D3DTS_WORLD, fade_->GetTransform()->GetWorldMatrix());
			device->SetTexture(0, NULL);
			fade_->Draw();
			break;
		}
		case Fade::Type::TYPE_TRANSITION_01:
		{
			fade_->GetTransition01Object();		// �e�N�X�`���Z�b�g�p�Ƀe�N�X�I�u�W�F�N�g�̎擾�\
			fade_->Draw();
			break;
		}
	}
}