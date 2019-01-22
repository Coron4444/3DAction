//================================================================================
//!	@file	 BackBuffer.cpp
//!	@brief	 バックバッファーClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "BackBuffer.h"

#include "../../Camera/Camera.h"

#include "../../ShaderManager/ShaderManager.h"
#include <Component/Draw/DrawBase/DrawBase.h>
#include <GameObjectBase/GameObjectBase.h>

#include <main.h>
#include <Renderer/Renderer.h>
#include <SafeRelease/SafeRelease.h>

#include <Effekseer/EffekseerManager/EffekseerManager.h>



//****************************************
// プロパティ定義
//****************************************
Camera* BackBuffer::getpCamera()
{
	return camera_;
}



void BackBuffer::setShaderManager(ShaderManager* value)
{
	shader_manager_ = value;
}



//****************************************
// 関数定義
//****************************************
void BackBuffer::Init()
{
	ResetAllArray();

	// カメラの初期化
	camera_ = new Camera();
	camera_->Init(nullptr);

	// フェードの初期化
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



void BackBuffer::Uninit()
{
	ResetAllArray();

	// フェード解放
	SafeRelease::PlusUninit(&camera_);
	SafeRelease::Normal(&fade_);

	render_texture_.Uninit();
	SafeRelease::PlusRelease(&main_screen_texture_);
	SafeRelease::PlusRelease(&post_effect_texture_);
	SafeRelease::PlusRelease(&main_screen_surface_);
	SafeRelease::PlusRelease(&post_effect_surface_);
}



void BackBuffer::UninitWhenChangeScene()
{
	ResetAllArray();

	camera_->Uninit();
}



void BackBuffer::Update()
{
	// カメラの更新
	camera_->Update();

	// 透明描画基底クラスの降順ソート
	SortTransparent();

	// 2D描画基底クラスのソート
	Sort2D();

	// ビルボード更新
	AllBillboardUpdate();

	// フェード更新
	if (is_fade_) fade_->Update();

	// エフェクシアの更新
	EffekseerManager::getpInstance()->CreateViewMatrix(*camera_->getpPositon(),
													   *camera_->getpLookAtPoint(),
													   *camera_->getpUp());
	EffekseerManager::getpInstance()->CreateProjectionMatrix(camera_->getAngleOfView());
	EffekseerManager::getpInstance()->Update();
}



void BackBuffer::Draw()
{
	// レンダーターゲットの切り替え
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	//device->SetRenderTarget(0, main_screen_surface_);
	bool is_begin = Renderer::getpInstance()->DrawBegin();

	// 不透明オブジェクト
	camera_->setType(Camera::Type::PERSPECTIVE);
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		// シェーダーセット
		shader_manager_->ShaderSetToDevice(all_opacity_draw_.GetArrayObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// 各オブジェクト描画
		for (unsigned j = 0; j < all_opacity_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// 描画前設定
			all_opacity_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// オブジェクト設定
			shader_manager_->ObjectSetting(all_opacity_draw_.GetArrayObject(i),
										   camera_, j);

			// 各メッシュ描画
			for (unsigned k = 0; k < all_opacity_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				// メッシュ設定
				shader_manager_->MeshSetting(all_opacity_draw_.GetArrayObject(i),
											 camera_, j, k);

				all_opacity_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// 描画後設定
			all_opacity_draw_.GetArrayObject(i)->SettingAfterDrawing(camera_, j);
		}
	}

	// 透明オブジェクト
	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer(); i++)
	{
		// シェーダーをセット
		shader_manager_->ShaderSetToDevice(all_transparency_draw_.GetArrayObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// 各オブジェクト描画
		for (unsigned j = 0; j < all_transparency_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// 描画前設定
			all_transparency_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// オブジェクト設定
			shader_manager_->ObjectSetting(all_transparency_draw_.GetArrayObject(i),
										   camera_, j);

			// 各メッシュ描画
			for (unsigned k = 0; k < all_transparency_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				// メッシュ設定
				shader_manager_->MeshSetting(all_transparency_draw_.GetArrayObject(i),
											 camera_, j, k);

				all_transparency_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// 描画後設定
			all_transparency_draw_.GetArrayObject(i)->SettingAfterDrawing(camera_, j);
		}
	}

	// エフェクシア描画
	EffekseerManager::getpInstance()->Draw();

	// 2Dオブジェクト
	camera_->setType(Camera::Type::TWO_DIMENSIONAL);
	for (unsigned i = 0; i < all_2D_draw_.GetEndPointer(); i++)
	{
		// シェーダーセット
		shader_manager_->ShaderSetToDevice(all_2D_draw_.GetArrayObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// 各オブジェクト描画
		for (unsigned j = 0; j < all_2D_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// 描画前設定
			all_2D_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// オブジェクト設定
			shader_manager_->ObjectSetting(all_2D_draw_.GetArrayObject(i),
										   camera_, j);

			// 各メッシュ描画
			for (unsigned k = 0; k < all_2D_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				// メッシュ設定
				shader_manager_->MeshSetting(all_2D_draw_.GetArrayObject(i),
											 camera_, j, k);

				all_2D_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// 描画後設定
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

	// フェード描画
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



void BackBuffer::AddDrawBaseToArray(DrawBase* draw)
{
	switch (draw->getpDrawOrderList()->getDrawType())
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



void BackBuffer::ResetAllArray()
{
	all_opacity_draw_.ResetArray();
	all_transparency_draw_.ResetArray();
	all_2D_draw_.ResetArray();
}



void BackBuffer::InitFade(Fade::Type type, Fade::State state, Vec2 size,
						  XColor4 fade_color, float fade_speed)
{
	// フェードの初期化
	fade_->Init(type, state, size, fade_color, fade_speed);

	// フェードフラグON
	is_fade_ = true;
}



void BackBuffer::UninitFade()
{
	// フェードの終了処理
	fade_->Uninit();

	// フェードフラグOFF
	is_fade_ = false;
}



bool BackBuffer::IsFadeEnd()
{
	return fade_->getpEndFlag();
}



bool BackBuffer::IsFadeStateName(Fade::State state)
{
	return *fade_->getpState() == state;
}



void BackBuffer::SortTransparent()
{
	// 透明オブジェクトがあるかどうか
	if (all_transparency_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer() - 1; i++)
	{
		// 深度値を算出
		Vector3D temp_vector0 = *all_transparency_draw_.GetArrayObject(i)->getpGameObject()
			->GetTransform()->GetPosition() - *camera_->getpPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparency_draw_.GetEndPointer(); j++)
		{
			// 深度値を算出
			Vector3D temp_vector1 = *all_transparency_draw_.GetArrayObject(j)
				->getpGameObject()->GetTransform()->GetPosition() - *camera_->getpPositon();

			float depth_value1 = temp_vector1.GetLengthSquare();

			// 深度値を比較
			if (depth_value0 < depth_value1)
			{
				// 並び替え
				all_transparency_draw_.SortTheTwoObject(i, j);
			}
		}
	}
}



void BackBuffer::Sort2D()
{
	// 2Dオブジェクトがあるかどうか
	if (all_2D_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_2D_draw_.GetEndPointer() - 1; i++)
	{
		for (unsigned j = i + 1; j < all_2D_draw_.GetEndPointer(); j++)
		{
			if (all_2D_draw_.GetArrayObject(i)->getpDrawOrderList()->getLayerNum()
		> all_2D_draw_.GetArrayObject(j)->getpDrawOrderList()->getLayerNum())
			{
				// 並び替え
				all_2D_draw_.SortTheTwoObject(i, j);
			}
		}
	}
}



void BackBuffer::SetBillboardMatrix(DrawBase* draw)
{
	// ビュー行列の転置行列をセット
	draw->getpGameObject()->GetTransform()->UpdateTransposeMatrix(camera_->getpViewMatrix());

	// 平行成分をカット
	draw->getpGameObject()->GetTransform()->TransposeMatrixTranslationOff();

	// ワールド行列の更新
	draw->getpGameObject()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
}



void BackBuffer::AllBillboardUpdate()
{
	camera_->setType(Camera::Type::PERSPECTIVE);

	// 不透明オブジェクト
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		if (!all_opacity_draw_.GetArrayObject(i)->getpDrawOrderList()
			->getIsBillboard()) continue;
		SetBillboardMatrix(all_opacity_draw_.GetArrayObject(i));
	}

	// 透明オブジェクト
	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer(); i++)
	{
		if (!all_transparency_draw_.GetArrayObject(i)->getpDrawOrderList()
			->getIsBillboard()) continue;
		SetBillboardMatrix(all_transparency_draw_.GetArrayObject(i));
	}
}



void BackBuffer::FadeDraw()
{
	// 描画
	switch (*fade_->getpType())
	{
		case Fade::Type::TYPE_NORMAL:
		{
			camera_->setType(Camera::Type::TWO_DIMENSIONAL);
			// シェーダーをセット
			shader_manager_->ShaderSetToDevice(fade_,
											   ShaderManager::VertexShaderType::NONE,
											   ShaderManager::PixelShaderType::NONE);

			// 各オブジェクト描画
			for (unsigned j = 0; j < fade_->getObjectNum(); j++)
			{
				// オブジェクト設定
				shader_manager_->ObjectSetting(fade_, camera_, j);

				// 各メッシュ描画
				for (unsigned k = 0; k < fade_->getMeshNum(j); k++)
				{
					// メッシュ設定
					shader_manager_->MeshSetting(fade_, camera_, j, k);

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