//================================================================================
//
//    描画マネージャークラス(static)
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================



//****************************************
// インクルード文
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
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void DrawManager::Init()
{
	// 固定パイプラインオブジェクトの初期化
	FixedPipelineObject::Init();

	// テストシェーダーの初期化
	TestShaderObject::Init();

	// フェードの初期化
	fade_ = new Fade();
	is_fade_ = false;
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void DrawManager::Uninit()
{
	// 固定パイプラインの終了処理
	FixedPipelineObject::Uninit();

	// テストシェーダーの終了処理
	TestShaderObject::Uninit();

	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全描画配列のリセット
	all_draw_.ResetArray();

	// カメラ配列の解放&リセット
	all_camera_.ReleaseObjectAndResetArray();

	// フェード解放
	SafeRelease::Normal(&fade_);
}



//--------------------------------------------------
// +シーン変更時の終了関数
//--------------------------------------------------
void DrawManager::UninitWhenChangeScene()
{
	// パイプラインの配列リセット
	ResetDrawComponentArray();

	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全描画配列のリセット
	all_draw_.ResetArray();

	// カメラ配列の解放&リセット
	all_camera_.ReleaseObjectAndResetArray();
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void DrawManager::Draw()
{
	// 追加待ち配列の中身を追加
	AddContentsOfAwaitAddArray();

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	for (unsigned i = 0; i < all_camera_.GetEndPointer(); i++)
	{
		if (all_camera_.GetArrayObject(i) == nullptr) return;

		if (all_camera_.GetArrayObject(i)->IsCameraTypeName(Camera::Type::NORMAL))
		{
			// ノーマルカメラパイプライン
			NormalCameraPipeline(i);
		}
	}


	// デバッグ
#ifdef _DEBUG
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		if (all_draw_.GetArrayObject(i) == nullptr) continue;
		all_draw_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



//--------------------------------------------------
// +描画基底クラスの追加関数
//--------------------------------------------------
void DrawManager::AddDrawBaseToArray(DrawBase* draw)
{
	// 追加待ち配列に追加
	await_add_.AddToArray(draw);
}



//--------------------------------------------------
// +描画基底クラスの上書き関数
//--------------------------------------------------
void DrawManager::OverwriteArrayDrawBase(GameObjectBase* game_object,
										 DrawBase* new_draw)
{
	// 新規がnullptrの場合
	if (new_draw == nullptr)
	{
		// 古い描画基底クラスの解放
		ReleaseDrawBaseFromArray(game_object->GetDraw());

		// 古い描画基底クラスの消去
		DrawBase* temp = game_object->GetDraw();
		SafeRelease::Normal(&temp);

		// nullptrの代入
		game_object->SetDraw(new_draw);
	}
	else
	{
		// 配列の上書き
		all_draw_.OverwriteArray(game_object->GetDraw(), new_draw);

		// 古い描画基底クラスの消去
		DrawBase* temp = game_object->GetDraw();
		SafeRelease::Normal(&temp);

		// 新規コンポーネントの初期化
		game_object->SetDraw(new_draw);
		new_draw->SetGameObject(game_object);
		new_draw->Init();
	}
}



//--------------------------------------------------
// +描画基底クラスの解放関数
//--------------------------------------------------
void DrawManager::ReleaseDrawBaseFromArray(DrawBase* draw)
{
	// 解放待ち配列に追加
	await_release_.AddToArray(draw);
}



//--------------------------------------------------
// +デフォルトカメラの作成関数
//--------------------------------------------------
void DrawManager::CreateDefaultCamera(Camera::State* camera_state, Camera::Type camra_type)
{
	// デフォルトのカメラの作成
	if (all_camera_.GetEndPointer() > 0) return;
	all_camera_.AddToArray(new Camera(camera_state, camra_type));
	all_camera_.GetArrayObject(0)->CreateProjectionMatrix_PerspectiveFov();
}



//--------------------------------------------------
// +カメラの追加関数
//--------------------------------------------------
void DrawManager::AddCamera(Camera::State* camera_state, Camera::Type camra_type)
{
	// カメラが最大数の時
	if (all_camera_.IsMax())
	{
		// ステートの解放
		SafeRelease::Normal(&camera_state);
		return;
	}

	// カメラの追加
	all_camera_.AddToArray(new Camera(camera_state, camra_type));
}



//--------------------------------------------------
// +カメラの解放関数
//--------------------------------------------------
void DrawManager::ReleaseCamera(unsigned index)
{
	// カメラの削除
	all_camera_.DeleteFromArray(all_camera_.GetArrayObject(index));
}



//--------------------------------------------------
// +カメラのステート変更関数
//--------------------------------------------------
void DrawManager::ChangeCameraState(unsigned index, Camera::State* camera_state_)
{
	// カメラがないとき
	if (all_camera_.GetArrayObject(index) == nullptr)
	{
		// ステートの解放
		SafeRelease::Normal(&camera_state_);
		return;
	}

	// ステートの変更
	all_camera_.GetArrayObject(index)->ChangeState(camera_state_);
}



//--------------------------------------------------
// +フェード初期化関数
//--------------------------------------------------
void DrawManager::InitFade(Fade::Type type, Fade::State state, Vec2 size,
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
void DrawManager::UninitFade()
{
	// フェードの終了処理
	fade_->Uninit();

	// フェードフラグOFF
	is_fade_ = false;
}



//--------------------------------------------------
// -追加待ち配列の中身を追加関数
//--------------------------------------------------
void DrawManager::AddContentsOfAwaitAddArray()
{
	// 追加待ちがあるかどうか
	if (await_add_.GetEndPointer() <= 0) return;

	// 追加
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_draw_.AddToArray(await_add_.GetArrayObject(i));
	}

	// 追加待ち配列をリセット
	await_add_.ResetArray();
}



//--------------------------------------------------
// -解放待ち配列の中身を解放関数
//--------------------------------------------------
void DrawManager::ReleaseContentsOfAwaitReleaseArray()
{
	// 解放待ちがあるかどうか
	if (await_release_.GetEndPointer() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		all_draw_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// 解放待ち配列をリセット
	await_release_.ResetArray();
}



//--------------------------------------------------
// -更新関数
//--------------------------------------------------
void DrawManager::Update(unsigned index)
{
	// カメラの更新
	all_camera_.GetArrayObject(index)->Update();

	// 登録用配列のリセット
	ResetDrawComponentArray();

	// 描画コンポーネントを各配列に振り分け
	DistributeDrawComponent(index);

	// 透明描画コンポーネントの降順ソート
	SortTransparent(index);

	// エフェクシアの更新
	EffekseerManager::CreateProjectionMatrix(*all_camera_.GetArrayObject(index)->GetAngleOfView());
	EffekseerManager::CreateViewMatrix(*all_camera_.GetArrayObject(index)->GetPositon(),
									   *all_camera_.GetArrayObject(index)->GetLookAtPoint(),
									   *all_camera_.GetArrayObject(index)->GetUp());
	EffekseerManager::Update();
}



//--------------------------------------------------
// -描画コンポーネント配列のリセット関数
//--------------------------------------------------
void DrawManager::ResetDrawComponentArray()
{
	all_opacity_draw_.ResetArray();
	all_transparent_draw_.ResetArray();
	all_2D_draw_.ResetArray();
}



//--------------------------------------------------
// -描画コンポーネント振り分け関数
//--------------------------------------------------
void DrawManager::DistributeDrawComponent(unsigned index)
{
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		if (all_draw_.GetArrayObject(i) == nullptr) continue;

		switch (all_draw_.GetArrayObject(i)->GetState())
		{
			// 不透明
			case DrawBase::State::FIXED:
			case DrawBase::State::FIXED_BILLBOARD:
			case DrawBase::State::TEST_SHADER:
			case DrawBase::State::TEST_SHADER_BILLBOARD:
			{
				all_opacity_draw_.AddToArray(all_draw_.GetArrayObject(i));
				break;
			}
			// 透明
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
// -透明描画コンポーネントのソート関数 
//--------------------------------------------------
void DrawManager::SortTransparent(unsigned index)
{
	// 透明オブジェクトがあるかどうか
	if (all_transparent_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparent_draw_.GetEndPointer() - 1; i++)
	{
		// 深度値を算出
		Vector3D temp_vector0 = *all_transparent_draw_.GetArrayObject(i)->GetGameObject()->GetTransform()->GetPosition()
			- *all_camera_.GetArrayObject(index)->GetPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparent_draw_.GetEndPointer(); j++)
		{
			// 深度値を算出
			Vector3D temp_vector1 = *all_transparent_draw_.GetArrayObject(j)->GetGameObject()->GetTransform()->GetPosition()
				- *all_camera_.GetArrayObject(index)->GetPositon();

			float depth_value1 = temp_vector1.GetLengthSquare();

			// 深度値を比較
			if (depth_value0 < depth_value1)
			{
				// 並び替え
				all_transparent_draw_.SortTheTwoObject(i, j);
			}
		}
	}
}



//--------------------------------------------------
// -ビルボード用行列変更関数
//--------------------------------------------------
void DrawManager::SetBillboardMatrix(DrawBase* draw, unsigned index)
{
	// ビュー行列の転置行列をセット
	draw->GetGameObject()->GetTransform()->UpdateTransposeMatrix(all_camera_.GetArrayObject(index)->GetViewMatrix());

	// 平行成分をカット
	draw->GetGameObject()->GetTransform()->TransposeMatrixTranslationOff();

	// ワールド行列の更新
	draw->GetGameObject()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
}



//--------------------------------------------------
// -各パイプライン描画関数
//--------------------------------------------------
void DrawManager::DrawEachPipeline(LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM>* draw,
								   unsigned index)
{
	for (unsigned i = 0; i < draw->GetEndPointer(); i++)
	{
		switch (draw->GetArrayObject(i)->GetState())
		{
			// 固定パイプライン
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
			// テストシェーダー
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
// -各パイプライン描画関数
//--------------------------------------------------
void DrawManager::NormalCameraPipeline(unsigned index)
{
	// 共通更新
	Update(index);

	// 不透明オブジェクト
	DrawEachPipeline(&all_opacity_draw_, index);

	// 透明オブジェクト
	DrawEachPipeline(&all_transparent_draw_, index);

	// エフェクシアの描画
	EffekseerManager::Draw();

	// 2Dオブジェクト
	DrawEachPipeline(&all_2D_draw_, index);

	// フェードの処理
	FadeUpdate_Draw();
}



//--------------------------------------------------
// -各パイプライン描画関数
//--------------------------------------------------
void DrawManager::FadeUpdate_Draw()
{
	if (!is_fade_) return;

	// 更新
	fade_->Update();

	// 描画
	switch (*fade_->GetType())
	{
		case Fade::Type::TYPE_NORMAL:
		{
			// デバイスの取得
			LPDIRECT3DDEVICE9 device = nullptr;
			Renderer::GetInstance()->GetDevice(&device);
			assert(device != nullptr && "Deviceの取得に失敗(DrawManager.cpp)");

			FixedPipelineObject::SetDraw2D();
			device->SetTransform(D3DTS_WORLD, fade_->GetTransform()->GetWorldMatrix());
			device->SetTexture(0, NULL);
			fade_->Draw();
			break;
		}
		case Fade::Type::TYPE_TRANSITION_01:
		{
			fade_->GetTransition01Object();		// テクスチャセット用にテクスオブジェクトの取得可能
			fade_->Draw();
			break;
		}
	}
}