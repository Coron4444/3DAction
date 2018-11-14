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
#include <Component/DrawBase/DrawBase.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>
#include <GameObjectBase/GameObjectBase.h>

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

	// 透明描画コンポーネントの降順ソート
	SortTransparent();

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

	// 不透明オブジェクト
	camera_->SetType(Camera::Type::PERSPECTIVE);
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		// シェーダーをセット
		shader_manager_->SetShader(all_opacity_draw_.GetArrayObject(i),
								   ShaderManager::VertexShaderType::VERTEX_NONE,
								   ShaderManager::PixelShaderType::PIXEL_NONE);

		// オブジェクト数分ループ
		for (unsigned j = 0; j < all_opacity_draw_.GetArrayObject(i)->GetDrawObjectNum(); j++)
		{
			// 限定カメラタイプ変更
			all_opacity_draw_.GetArrayObject(i)->LimitedChangeCameraType(camera_, j);

			// メッシュ間共通のグローバール変数をセット
			shader_manager_->CommonSetting(all_opacity_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// メッシュ数分ループ
			for (unsigned k = 0; k < all_opacity_draw_.GetArrayObject(i)->GetMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_opacity_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_opacity_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// カメラタイプ復活
			all_opacity_draw_.GetArrayObject(i)->RevivalCameraType(camera_);
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
		for (unsigned j = 0; j < all_transparency_draw_.GetArrayObject(i)->GetDrawObjectNum(); j++)
		{
			// 限定カメラタイプ変更
			all_transparency_draw_.GetArrayObject(i)->LimitedChangeCameraType(camera_, j);

			// メッシュ間共通のグローバール変数をセット
			shader_manager_->CommonSetting(all_transparency_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// メッシュ数分ループ
			for (unsigned k = 0; k < all_transparency_draw_.GetArrayObject(i)->GetMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_transparency_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_transparency_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// カメラタイプ復活
			all_transparency_draw_.GetArrayObject(i)->RevivalCameraType(camera_);
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
		for (unsigned j = 0; j < all_2D_draw_.GetArrayObject(i)->GetDrawObjectNum(); j++)
		{
			// 限定カメラタイプ変更
			all_2D_draw_.GetArrayObject(i)->LimitedChangeCameraType(camera_, j);

			// メッシュ間共通のグローバール変数をセット
			shader_manager_->CommonSetting(all_2D_draw_.GetArrayObject(i),
										   camera_,
										   ShaderManager::VertexShaderType::VERTEX_NONE,
										   ShaderManager::PixelShaderType::PIXEL_NONE,
										   j);

			// メッシュ数分ループ
			for (unsigned k = 0; k < all_2D_draw_.GetArrayObject(i)->GetMeshNum(j); k++)
			{
				shader_manager_->SpecificSetting(all_2D_draw_.GetArrayObject(i),
												 camera_,
												 ShaderManager::VertexShaderType::VERTEX_NONE,
												 ShaderManager::PixelShaderType::PIXEL_NONE,
												 j, k);

				all_2D_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// カメラタイプ復活
			all_2D_draw_.GetArrayObject(i)->RevivalCameraType(camera_);
		}
	}

	// フェード
	FadeDraw();
}



//--------------------------------------------------
// +描画基底クラスの追加関数
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
// -透明描画コンポーネントのソート関数 
//--------------------------------------------------
void BackBuffer::SortTransparent()
{
	// 透明オブジェクトがあるかどうか
	if (all_transparency_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer() - 1; i++)
	{
		// 深度値を算出
		Vector3D temp_vector0 = *all_transparency_draw_.GetArrayObject(i)->GetGameObject()
			->GetTransform()->GetPosition() - *camera_->GetPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparency_draw_.GetEndPointer(); j++)
		{
			// 深度値を算出
			Vector3D temp_vector1 = *all_transparency_draw_.GetArrayObject(j)
				->GetGameObject()->GetTransform()->GetPosition() - *camera_->GetPositon();

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
// -ビルボード用行列変更関数
//--------------------------------------------------
void BackBuffer::SetBillboardMatrix(DrawBase* draw)
{
	// ビュー行列の転置行列をセット
	draw->GetGameObject()->GetTransform()->UpdateTransposeMatrix(camera_->GetViewMatrix());

	// 平行成分をカット
	draw->GetGameObject()->GetTransform()->TransposeMatrixTranslationOff();

	// ワールド行列の更新
	draw->GetGameObject()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
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
		if (!all_opacity_draw_.GetArrayObject(i)->GetDrawOrderList()
			->GetIsBillboard()) continue;
		SetBillboardMatrix(all_opacity_draw_.GetArrayObject(i));
	}

	// 透明オブジェクト
	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer(); i++)
	{
		if (!all_transparency_draw_.GetArrayObject(i)->GetDrawOrderList()
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
			for (unsigned j = 0; j < fade_->GetDrawObjectNum(); j++)
			{
				// メッシュ間共通のグローバール変数をセット
				shader_manager_->CommonSetting(fade_,
											   camera_,
											   ShaderManager::VertexShaderType::VERTEX_NONE,
											   ShaderManager::PixelShaderType::PIXEL_NONE,
											   j);

				// メッシュ数分ループ
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