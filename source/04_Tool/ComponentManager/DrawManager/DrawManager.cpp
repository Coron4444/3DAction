//================================================================================
//
//    �`��R���|�[�l���g�}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "DrawComponentManager.h"
#include "Shader\FixedPipelineObject\FixedPipelineObject.h"
#include "Shader\TestShaderObject\TestShaderObject.h"
#include <GameObjectOrigin\GameObjectOrigin.h>
#include <Effekseer\EffekseerManager\EffekseerManager.h>

#include <Component\DrawComponent\DrawComponent.h>
#include <Renderer/Renderer.h>

#include <Transform\Transform.h>
#include <SafeRelease/SafeRelease.h>


//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

LimitedPointerArray<DrawComponent*, DrawComponentManager::DRAW_ARRAY_NUM> DrawComponentManager::all_draw_component_;
LimitedPointerArray<DrawComponent*, DrawComponentManager::DRAW_ARRAY_NUM> DrawComponentManager::all_opacity_draw_component_;
LimitedPointerArray<DrawComponent*, DrawComponentManager::DRAW_ARRAY_NUM> DrawComponentManager::all_transparent_draw_component_;
LimitedPointerArray<DrawComponent*, DrawComponentManager::DRAW_ARRAY_NUM> DrawComponentManager::all_2D_draw_component_;

LimitedPointerArray<Camera*, DrawComponentManager::CAMERA_ARRAY_NUM>	  DrawComponentManager::all_camera_;
Fade* DrawComponentManager::fade_;
bool DrawComponentManager::is_fade_;



//======================================================================
//
// �ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::Init()
{
	// �Œ�p�C�v���C���I�u�W�F�N�g�̏�����
	FixedPipelineObject::Init();

	// �e�X�g�V�F�[�_�[�̏�����
	TestShaderObject::Init();

	// �t�F�[�h�̏�����
	fade_    = new Fade();
	is_fade_ = false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::Uninit()
{
	// �Œ�p�C�v���C���̏I������
	FixedPipelineObject::Uninit();

	// �e�X�g�V�F�[�_�[�̏I������
	TestShaderObject::Uninit();

	// �R���|�[�l���g�z��̃��Z�b�g
	all_draw_component_.ResetArray();

	// �J�����z��̉��&���Z�b�g
	all_camera_.ReleaseObjectAndResetArray();

	// �t�F�[�h���
	SafeRelease::Normal(&fade_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �V�[���ύX���̏I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::Uninit_ChangeScene()
{
	// �p�C�v���C���̔z�񃊃Z�b�g
	ResetDrawComponentArray();

	// �R���|�[�l���g�z��̃��Z�b�g
	all_draw_component_.ResetArray();

	// �J�����z��̉��&���Z�b�g
	all_camera_.ReleaseObjectAndResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::Draw()
{
	for (unsigned i = 0; i < all_camera_.GetEndPointer(); i++)
	{
		if (all_camera_.GetArrayObject(i) == nullptr) return;

		if (all_camera_.GetArrayObject(i)->IsCameraTypeName(Camera::Type::NORMAL))
		{
			// �m�[�}���J�����p�C�v���C��
			NormalCameraPipeline(i);
		}
	}


#ifdef _DEBUG
	// �f�o�b�O
	for (unsigned i = 0; i < all_draw_component_.GetEndPointer(); i++)
	{
		if (all_draw_component_.GetArrayObject(i) == nullptr) continue;
		all_draw_component_.GetArrayObject(i)->Debug();
	}
#endif
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��R���|�[�l���g�o�^�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::RegistrationComponent(DrawComponent* draw_component)
{
	// �o�^
	all_draw_component_.AddToArray(draw_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�R���|�[�l���g�㏑���֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::OverwriteComponent(GameObjectOrigin* game_object, DrawComponent* new_draw_component)
{
	// �V�K�R���|�[�l���g��nullptr���ǂ���
	if (new_draw_component == nullptr)
	{
		// �Â��I�u�W�F�N�g�̉��
		ReleaseComponent(game_object->GetDrawComponent());

		// �Â��R���|�[�l���g�̏���
		DrawComponent* temp = game_object->GetDrawComponent();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g(nullptr)�̑��
		game_object->SetDrawComponent(new_draw_component);
	}
	else
	{
		// �z��̏㏑��
		all_draw_component_.OverwriteArray(game_object->GetDrawComponent(), new_draw_component);

		// �Â��R���|�[�l���g�̏���
		DrawComponent* temp = game_object->GetDrawComponent();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g�̏�����
		game_object->SetDrawComponent(new_draw_component);
		new_draw_component->SetGameObjectOrigin(game_object);
		new_draw_component->Init();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��R���|�[�l���g����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::ReleaseComponent(DrawComponent* draw_component)
{
	// �폜�ƃ\�[�g
	all_draw_component_.DeleteFromArrayAndSortArray(draw_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�J�����쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::CreateDefaultCamera(Camera::State* camera_state, Camera::Type camra_type)
{
	// �f�t�H���g�̃J�����̍쐬
	if (all_camera_.GetEndPointer() > 0) return;
	all_camera_.AddToArray(new Camera(camera_state, camra_type));
	all_camera_.GetArrayObject(0)->CreateProjectionMatrix_PerspectiveFov();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �J�����ǉ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::AddCamera(Camera::State* camera_state, Camera::Type camra_type)
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



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �J���������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::DeleteCamera(unsigned index)
{
	// �J�����̍폜
	all_camera_.DeleteFromArray(all_camera_.GetArrayObject(index));
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �J�����X�e�[�g�ύX�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::ChangeCameraState(unsigned index, Camera::State* camera_state_)
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



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �t�F�[�h�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::InitFade(Fade::Type type, Fade::State state, Vec2 size, 
									XColor4 fade_color, float fade_speed)
{
	// �t�F�[�h�̏�����
	fade_->Init(type, state, size, fade_color, fade_speed);

	// �t�F�[�h�t���OON
	is_fade_ = true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �t�F�[�h�I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::UninitFade()
{
	// �t�F�[�h�̏I������
	fade_->Uninit();

	// �t�F�[�h�t���OOFF
	is_fade_ = false;
}



//--------------------------------------------------------------------------------
//
// [ �X�V�֐� ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::Update(unsigned index)
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



//--------------------------------------------------------------------------------
//
// [ �`��R���|�[�l���g�z��̃��Z�b�g�֐� ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::ResetDrawComponentArray()
{
	all_opacity_draw_component_.ResetArray();
	all_transparent_draw_component_.ResetArray();
	all_2D_draw_component_.ResetArray();
}



//--------------------------------------------------------------------------------
//
// [ �`��R���|�[�l���g�U�蕪���֐� ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::DistributeDrawComponent(unsigned index)
{
	for (unsigned i = 0; i < all_draw_component_.GetEndPointer(); i++)
	{
		if (all_draw_component_.GetArrayObject(i) == nullptr) continue;

		switch (all_draw_component_.GetArrayObject(i)->GetState())
		{
			// �s����
			case DrawComponent::State::FIXED				 :
			case DrawComponent::State::FIXED_BILLBOARD	     :
			case DrawComponent::State::TEST_SHADER           :
			case DrawComponent::State::TEST_SHADER_BILLBOARD :
			{
				all_opacity_draw_component_.AddToArray(all_draw_component_.GetArrayObject(i));
				break;
			}
			// ����
			case DrawComponent::State::FIXED_ALPHA		     :
			case DrawComponent::State::FIXED_BILLBOARD_ALPHA :
			{
				all_transparent_draw_component_.AddToArray(all_draw_component_.GetArrayObject(i));
			}
			// 2D
			case DrawComponent::State::FIXED_2D :
			{
				all_2D_draw_component_.AddToArray(all_draw_component_.GetArrayObject(i));
				break;
			}
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ �����`��R���|�[�l���g�̃\�[�g�֐� ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::SortTransparent(unsigned index)
{
	// �����I�u�W�F�N�g�����邩�ǂ���
	if (all_transparent_draw_component_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparent_draw_component_.GetEndPointer() - 1; i++)
	{
		// �[�x�l���Z�o
		Vector3D temp_vector0 = *all_transparent_draw_component_.GetArrayObject(i)->GetGameObjectOrigin()->GetTransform()->GetPosition()
			                    - *all_camera_.GetArrayObject(index)->GetPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparent_draw_component_.GetEndPointer(); j++)
		{
			// �[�x�l���Z�o
			Vector3D temp_vector1 = *all_transparent_draw_component_.GetArrayObject(j)->GetGameObjectOrigin()->GetTransform()->GetPosition()
			                        - *all_camera_.GetArrayObject(index)->GetPositon();
			
			float depth_value1 = temp_vector1.GetLengthSquare();

			// �[�x�l���r
			if (depth_value0 < depth_value1)
			{
				// ���ёւ�
				all_transparent_draw_component_.SortTheTwoObject(i, j);
			}
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ �r���{�[�h�p�s��ύX�֐� ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::SetBillboardMatrix(DrawComponent* draw_component, unsigned index)
{
	// �r���[�s��̓]�u�s����Z�b�g
	draw_component->GetGameObjectOrigin()->GetTransform()->UpdateTransposeMatrix(all_camera_.GetArrayObject(index)->GetViewMatrix());
	
	// ���s�������J�b�g
	draw_component->GetGameObjectOrigin()->GetTransform()->TransposeMatrixTranslationOff();
	
	// ���[���h�s��̍X�V
	draw_component->GetGameObjectOrigin()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
}



//--------------------------------------------------------------------------------
//
// [ �e�p�C�v���C���`��֐� ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::DrawEachPipeline(LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM>* draw_components, unsigned index)
{
	for (unsigned i = 0; i < draw_components->GetEndPointer(); i++)
	{
		switch (draw_components->GetArrayObject(i)->GetState())
		{
			// �Œ�p�C�v���C��
			case DrawComponent::State::FIXED :
			{
				FixedPipelineObject::Draw3D(draw_components->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawComponent::State::FIXED_ALPHA :
			{
				FixedPipelineObject::Draw3D(draw_components->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawComponent::State::FIXED_BILLBOARD :
			{
				SetBillboardMatrix(draw_components->GetArrayObject(i), index);
				FixedPipelineObject::Draw3D(draw_components->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawComponent::State::FIXED_BILLBOARD_ALPHA :
			{
				SetBillboardMatrix(draw_components->GetArrayObject(i), index);
				FixedPipelineObject::Draw3D(draw_components->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawComponent::State::FIXED_2D :
			{
				FixedPipelineObject::Draw2D(draw_components->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			// �e�X�g�V�F�[�_�[
			case DrawComponent::State::TEST_SHADER :
			{
				TestShaderObject::Draw(draw_components->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
			case DrawComponent::State::TEST_SHADER_BILLBOARD :
			{
				SetBillboardMatrix(draw_components->GetArrayObject(i), index);
				TestShaderObject::Draw(draw_components->GetArrayObject(i), all_camera_.GetArrayObject(index));
				break;
			}
		}
	}
}


//--------------------------------------------------------------------------------
//
// [ �m�[�}���J�����p�C�v���C���֐� ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::NormalCameraPipeline(unsigned index)
{
	// ���ʍX�V
	Update(index);

	// �s�����I�u�W�F�N�g
	DrawEachPipeline(&all_opacity_draw_component_, index);

	// �����I�u�W�F�N�g
	DrawEachPipeline(&all_transparent_draw_component_, index);

	// �G�t�F�N�V�A�̕`��
	EffekseerManager::Draw();

	// 2D�I�u�W�F�N�g
	DrawEachPipeline(&all_2D_draw_component_, index);

	// �t�F�[�h�̏���
	FadeUpdate_Draw();
}



//--------------------------------------------------------------------------------
//
// [ �t�F�[�h�̍X�V�y�ѕ`��֐� ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::FadeUpdate_Draw()
{
	if (!is_fade_) return;

	// �X�V
	fade_->Update();

	// �`��
	switch(*fade_->GetType())
	{
		case Fade::Type::TYPE_NORMAL :
		{
			// �f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 device = nullptr;
			Renderer::GetInstance()->GetDevice(&device);
			assert(device != nullptr && "Device�̎擾�Ɏ��s(DrawComponentManager.cpp)");

			FixedPipelineObject::SetDraw2D();
			device->SetTransform(D3DTS_WORLD, fade_->GetTransform()->GetWorldMatrix());
			device->SetTexture(0, NULL);
			fade_->Draw();
			break;
		}
		case Fade::Type::TYPE_TRANSITION_01 :
		{
			fade_->GetTransition01Object();		// �e�N�X�`���Z�b�g�p�Ƀe�N�X�I�u�W�F�N�g�̎擾�\
			fade_->Draw();
			break;
		}
	}
}