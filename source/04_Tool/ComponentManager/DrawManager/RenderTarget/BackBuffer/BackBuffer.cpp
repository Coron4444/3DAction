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
#include <Component/Base/DrawBase/DrawBase.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>
#include <GameObjectBase/GameObjectBase.h>

#include <main.h>

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

	// 
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	D3DXCreateTexture(device, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
					  D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
					  D3DPOOL_DEFAULT, &main_screen_texture_);
	main_screen_texture_->GetSurfaceLevel(0, &main_screen_surface_);

	D3DXCreateTexture(device, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
					  D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
					  D3DPOOL_DEFAULT, &post_effect_texture_);
	post_effect_texture_->GetSurfaceLevel(0, &post_effect_surface_);

	device->GetRenderTarget(0, &back_buffer_surface_);

	render_texture_.Init();
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

	render_texture_.Uninit();
	SafeRelease::PlusRelease(&main_screen_texture_);
	SafeRelease::PlusRelease(&post_effect_texture_);
	SafeRelease::PlusRelease(&main_screen_surface_);
	SafeRelease::PlusRelease(&post_effect_surface_);
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

	// �����`����N���X�̍~���\�[�g
	SortTransparent();

	// 2D�`����N���X�̃\�[�g
	Sort2D();

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
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	//device->SetRenderTarget(0, main_screen_surface_);
	bool is_begin = Renderer::getpInstance()->DrawBegin();

	// �s�����I�u�W�F�N�g
	camera_->SetType(Camera::Type::PERSPECTIVE);
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		// �V�F�[�_�[���Z�b�g
		shader_manager_->SetShader(all_opacity_draw_.GetArrayObject(i),
								   ShaderManager::VertexShaderType::VERTEX_NONE,
								   ShaderManager::PixelShaderType::PIXEL_NONE);

		// �I�u�W�F�N�g�������[�v
		for (unsigned j = 0; j < all_opacity_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// �`��O�ݒ�
			all_opacity_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// ���b�V���ԋ��ʂ̃O���[�o�[���ϐ����Z�b�g
			shader_manager_->CommonSetting(all_opacity_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// ���b�V���������[�v
			for (unsigned k = 0; k < all_opacity_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_opacity_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_opacity_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// �`���ݒ�
			all_opacity_draw_.GetArrayObject(i)->SettingAfterDrawing(camera_, j);
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
		for (unsigned j = 0; j < all_transparency_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// �`��O�ݒ�
			all_transparency_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// ���b�V���ԋ��ʂ̃O���[�o�[���ϐ����Z�b�g
			shader_manager_->CommonSetting(all_transparency_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// ���b�V���������[�v
			for (unsigned k = 0; k < all_transparency_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_transparency_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_transparency_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// �`���ݒ�
			all_transparency_draw_.GetArrayObject(i)->SettingAfterDrawing(camera_, j);
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
		for (unsigned j = 0; j < all_2D_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// �`��O�ݒ�
			all_2D_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// ���b�V���ԋ��ʂ̃O���[�o�[���ϐ����Z�b�g
			shader_manager_->CommonSetting(all_2D_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// ���b�V���������[�v
			for (unsigned k = 0; k < all_2D_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_2D_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_2D_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// �`���ݒ�
			all_2D_draw_.GetArrayObject(i)->SettingAfterDrawing(camera_, j);
		}
	}

	//camera_->SetType(Camera::Type::TWO_DIMENSIONAL);
	//device->SetVertexShader(nullptr);
	//device->SetPixelShader(nullptr);
	//device->SetMaterial(render_texture_.getpMaterial(0, 0));
	//device->SetTransform(D3DTS_VIEW, camera_->GetViewMatrix());
	//device->SetTransform(D3DTS_PROJECTION, camera_->GetProjectionMatrix());
	//render_texture_.Update(SCREEN_WIDTH * 1.03f,
	//					   SCREEN_HEIGHT * 1.03f,
	//					   XColor4(1.0f, 1.0f, 1.0f, 0.96f));
	//device->SetTransform(D3DTS_WORLD, render_texture_.getpMatrix(0));
	//device->SetTexture(0, post_effect_texture_);
	//render_texture_.Draw(0, 0);

	// �t�F�[�h
	FadeDraw();

	Renderer::getpInstance()->DrawEnd(is_begin);

	/*device->SetRenderTarget(0, back_buffer_surface_);
	is_begin = Renderer::getpInstance()->DrawBegin();

	camera_->SetType(Camera::Type::TWO_DIMENSIONAL);
	device->SetVertexShader(nullptr);
	device->SetPixelShader(nullptr);
	device->SetMaterial(render_texture_.getpMaterial(0, 0));
	device->SetTransform(D3DTS_VIEW, camera_->GetViewMatrix());
	device->SetTransform(D3DTS_PROJECTION, camera_->GetProjectionMatrix());
	render_texture_.Update(SCREEN_WIDTH,
						   SCREEN_HEIGHT,
						   XColor4(1.0f, 1.0f, 1.0f, 1.0f));
	device->SetTransform(D3DTS_WORLD, render_texture_.getpMatrix(0));
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	device->SetTexture(0, main_screen_texture_);
	render_texture_.Draw(0, 0);

	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->SetDefaultSamplerState();

	Renderer::getpInstance()->DrawEnd(is_begin);

	LPDIRECT3DTEXTURE9 temp;
	temp = main_screen_texture_;
	main_screen_texture_ = post_effect_texture_;
	post_effect_texture_ = temp;

	LPDIRECT3DSURFACE9 temp2;
	temp2 = main_screen_surface_;
	main_screen_surface_ = post_effect_surface_;
	post_effect_surface_ = temp2;*/
}



//--------------------------------------------------
// +�`����N���X�̒ǉ��֐�
//--------------------------------------------------
void BackBuffer::AddDrawBaseToArray(DrawBase* draw)
{
	switch (draw->getpDrawOrderList()->GetDrawType())
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
// -�����`����N���X�̃\�[�g�֐� 
//--------------------------------------------------
void BackBuffer::SortTransparent()
{
	// �����I�u�W�F�N�g�����邩�ǂ���
	if (all_transparency_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer() - 1; i++)
	{
		// �[�x�l���Z�o
		Vector3D temp_vector0 = *all_transparency_draw_.GetArrayObject(i)->getpGameObject()
			->GetTransform()->GetPosition() - *camera_->GetPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparency_draw_.GetEndPointer(); j++)
		{
			// �[�x�l���Z�o
			Vector3D temp_vector1 = *all_transparency_draw_.GetArrayObject(j)
				->getpGameObject()->GetTransform()->GetPosition() - *camera_->GetPositon();

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
// -2D�`����N���X�̃\�[�g�֐� 
//--------------------------------------------------
void BackBuffer::Sort2D()
{
	// 2D�I�u�W�F�N�g�����邩�ǂ���
	if (all_2D_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_2D_draw_.GetEndPointer() - 1; i++)
	{
		for (unsigned j = i + 1; j < all_2D_draw_.GetEndPointer(); j++)
		{
			if (all_2D_draw_.GetArrayObject(i)->getpDrawOrderList()->GetLayerNum()
		> all_2D_draw_.GetArrayObject(j)->getpDrawOrderList()->GetLayerNum())
			{
				// ���ёւ�
				all_2D_draw_.SortTheTwoObject(i, j);
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
	draw->getpGameObject()->GetTransform()->UpdateTransposeMatrix(camera_->GetViewMatrix());

	// ���s�������J�b�g
	draw->getpGameObject()->GetTransform()->TransposeMatrixTranslationOff();

	// ���[���h�s��̍X�V
	draw->getpGameObject()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
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
		if (!all_opacity_draw_.GetArrayObject(i)->getpDrawOrderList()
			->GetIsBillboard()) continue;
		SetBillboardMatrix(all_opacity_draw_.GetArrayObject(i));
	}

	// �����I�u�W�F�N�g
	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer(); i++)
	{
		if (!all_transparency_draw_.GetArrayObject(i)->getpDrawOrderList()
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
			for (unsigned j = 0; j < fade_->getObjectNum(); j++)
			{
				// ���b�V���ԋ��ʂ̃O���[�o�[���ϐ����Z�b�g
				shader_manager_->CommonSetting(fade_,
											   camera_,
											   ShaderManager::VertexShaderType::VERTEX_NONE,
											   ShaderManager::PixelShaderType::PIXEL_NONE,
											   j);

				// ���b�V���������[�v
				for (unsigned k = 0; k < fade_->getMeshNum(j); k++)
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