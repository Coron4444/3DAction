//================================================================================
//
//    バックバッファークラス
//    Author : Araki Kai                                作成日 : 2018/11/12
//
//================================================================================



//****************************************
// インクルード文
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
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
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



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
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



//--------------------------------------------------
// +シーン変更時の終了関数
//--------------------------------------------------
void BackBuffer::UninitWhenChangeScene()
{
	ResetAllArray();

	camera_->Uninit();
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
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
	EffekseerManager::CreateProjectionMatrix(camera_->GetAngleOfView());
	EffekseerManager::CreateViewMatrix(*camera_->GetPositon(),
									   *camera_->GetLookAtPoint(),
									   *camera_->GetUp());
	EffekseerManager::Update();
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void BackBuffer::Draw()
{
	// レンダーターゲットの切り替え
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	//device->SetRenderTarget(0, main_screen_surface_);
	bool is_begin = Renderer::getpInstance()->DrawBegin();

	// 不透明オブジェクト
	camera_->SetType(Camera::Type::PERSPECTIVE);
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		// シェーダーをセット
		shader_manager_->SetShader(all_opacity_draw_.GetArrayObject(i),
								   ShaderManager::VertexShaderType::VERTEX_NONE,
								   ShaderManager::PixelShaderType::PIXEL_NONE);

		// オブジェクト数分ループ
		for (unsigned j = 0; j < all_opacity_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// 描画前設定
			all_opacity_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// メッシュ間共通のグローバール変数をセット
			shader_manager_->CommonSetting(all_opacity_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// メッシュ数分ループ
			for (unsigned k = 0; k < all_opacity_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_opacity_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

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
		shader_manager_->SetShader(all_transparency_draw_.GetArrayObject(i),
								   ShaderManager::VertexShaderType::VERTEX_NONE,
								   ShaderManager::PixelShaderType::PIXEL_NONE);

		// オブジェクト数分ループ
		for (unsigned j = 0; j < all_transparency_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// 描画前設定
			all_transparency_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// メッシュ間共通のグローバール変数をセット
			shader_manager_->CommonSetting(all_transparency_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// メッシュ数分ループ
			for (unsigned k = 0; k < all_transparency_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_transparency_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_transparency_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// 描画後設定
			all_transparency_draw_.GetArrayObject(i)->SettingAfterDrawing(camera_, j);
		}
	}

	// エフェクシア
	EffekseerManager::Draw();

	// 2D
	camera_->SetType(Camera::Type::TWO_DIMENSIONAL);
	for (unsigned i = 0; i < all_2D_draw_.GetEndPointer(); i++)
	{
		// シェーダーをセット
		shader_manager_->SetShader(all_2D_draw_.GetArrayObject(i),
								   ShaderManager::VertexShaderType::VERTEX_NONE,
								   ShaderManager::PixelShaderType::PIXEL_NONE);

		// オブジェクト数分ループ
		for (unsigned j = 0; j < all_2D_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// 描画前設定
			all_2D_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// メッシュ間共通のグローバール変数をセット
			shader_manager_->CommonSetting(all_2D_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// メッシュ数分ループ
			for (unsigned k = 0; k < all_2D_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_2D_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

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

	// フェード
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
// +描画基底クラスの追加関数
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
// +全配列のリセット関数
//--------------------------------------------------
void BackBuffer::ResetAllArray()
{
	all_opacity_draw_.ResetArray();
	all_transparency_draw_.ResetArray();
	all_2D_draw_.ResetArray();
}



//--------------------------------------------------
// +フェード初期化関数
//--------------------------------------------------
void BackBuffer::InitFade(Fade::Type type, Fade::State state, Vec2 size,
						  XColor4 fade_color, float fade_speed)
{
	// フェードの初期化
	fade_->Init(type, state, size, fade_color, fade_speed);

	// フェードフラグON
	is_fade_ = true;
}



//--------------------------------------------------
// +フェード終了関数
//--------------------------------------------------
void BackBuffer::UninitFade()
{
	// フェードの終了処理
	fade_->Uninit();

	// フェードフラグOFF
	is_fade_ = false;
}



//--------------------------------------------------
// -透明描画基底クラスのソート関数 
//--------------------------------------------------
void BackBuffer::SortTransparent()
{
	// 透明オブジェクトがあるかどうか
	if (all_transparency_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer() - 1; i++)
	{
		// 深度値を算出
		Vector3D temp_vector0 = *all_transparency_draw_.GetArrayObject(i)->getpGameObject()
			->GetTransform()->GetPosition() - *camera_->GetPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparency_draw_.GetEndPointer(); j++)
		{
			// 深度値を算出
			Vector3D temp_vector1 = *all_transparency_draw_.GetArrayObject(j)
				->getpGameObject()->GetTransform()->GetPosition() - *camera_->GetPositon();

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



//--------------------------------------------------
// -2D描画基底クラスのソート関数 
//--------------------------------------------------
void BackBuffer::Sort2D()
{
	// 2Dオブジェクトがあるかどうか
	if (all_2D_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_2D_draw_.GetEndPointer() - 1; i++)
	{
		for (unsigned j = i + 1; j < all_2D_draw_.GetEndPointer(); j++)
		{
			if (all_2D_draw_.GetArrayObject(i)->getpDrawOrderList()->GetLayerNum()
		> all_2D_draw_.GetArrayObject(j)->getpDrawOrderList()->GetLayerNum())
			{
				// 並び替え
				all_2D_draw_.SortTheTwoObject(i, j);
			}
		}
	}
}



//--------------------------------------------------
// -ビルボード用行列変更関数
//--------------------------------------------------
void BackBuffer::SetBillboardMatrix(DrawBase* draw)
{
	// ビュー行列の転置行列をセット
	draw->getpGameObject()->GetTransform()->UpdateTransposeMatrix(camera_->GetViewMatrix());

	// 平行成分をカット
	draw->getpGameObject()->GetTransform()->TransposeMatrixTranslationOff();

	// ワールド行列の更新
	draw->getpGameObject()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
}



//--------------------------------------------------
// -全ビルボード更新関数
//--------------------------------------------------
void BackBuffer::AllBillboardUpdate()
{
	camera_->SetType(Camera::Type::PERSPECTIVE);

	// 不透明オブジェクト
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		if (!all_opacity_draw_.GetArrayObject(i)->getpDrawOrderList()
			->GetIsBillboard()) continue;
		SetBillboardMatrix(all_opacity_draw_.GetArrayObject(i));
	}

	// 透明オブジェクト
	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer(); i++)
	{
		if (!all_transparency_draw_.GetArrayObject(i)->getpDrawOrderList()
			->GetIsBillboard()) continue;
		SetBillboardMatrix(all_transparency_draw_.GetArrayObject(i));
	}
}



//--------------------------------------------------
// -フェード描画関数
//--------------------------------------------------
void BackBuffer::FadeDraw()
{
	// 描画
	switch (*fade_->GetType())
	{
		case Fade::Type::TYPE_NORMAL:
		{
			camera_->SetType(Camera::Type::TWO_DIMENSIONAL);
			// シェーダーをセット
			shader_manager_->SetShader(fade_,
									   ShaderManager::VertexShaderType::VERTEX_NONE,
									   ShaderManager::PixelShaderType::PIXEL_NONE);

			// オブジェクト数分ループ
			for (unsigned j = 0; j < fade_->getObjectNum(); j++)
			{
				// メッシュ間共通のグローバール変数をセット
				shader_manager_->CommonSetting(fade_,
											   camera_,
											   ShaderManager::VertexShaderType::VERTEX_NONE,
											   ShaderManager::PixelShaderType::PIXEL_NONE,
											   j);

				// メッシュ数分ループ
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