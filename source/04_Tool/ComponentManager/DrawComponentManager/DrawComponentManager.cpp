//================================================================================
//
//    描画コンポーネントマネージャークラス(static)
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================



//======================================================================
//
// インクルード文
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
// 静的メンバ変数定義
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
// 静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::Init()
{
	// 固定パイプラインオブジェクトの初期化
	FixedPipelineObject::Init();

	// テストシェーダーの初期化
	TestShaderObject::Init();

	// フェードの初期化
	fade_    = new Fade();
	is_fade_ = false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::Uninit()
{
	// 固定パイプラインの終了処理
	FixedPipelineObject::Uninit();

	// テストシェーダーの終了処理
	TestShaderObject::Uninit();

	// コンポーネント配列のリセット
	all_draw_component_.ResetArray();

	// カメラ配列の解放&リセット
	all_camera_.ReleaseObjectAndResetArray();

	// フェード解放
	SafeRelease::Normal(&fade_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ シーン変更時の終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::Uninit_ChangeScene()
{
	// パイプラインの配列リセット
	ResetDrawComponentArray();

	// コンポーネント配列のリセット
	all_draw_component_.ResetArray();

	// カメラ配列の解放&リセット
	all_camera_.ReleaseObjectAndResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::Draw()
{
	for (unsigned i = 0; i < all_camera_.GetEndPointer(); i++)
	{
		if (all_camera_.GetArrayObject(i) == nullptr) return;

		if (all_camera_.GetArrayObject(i)->IsCameraTypeName(Camera::Type::NORMAL))
		{
			// ノーマルカメラパイプライン
			NormalCameraPipeline(i);
		}
	}


#ifdef _DEBUG
	// デバッグ
	for (unsigned i = 0; i < all_draw_component_.GetEndPointer(); i++)
	{
		if (all_draw_component_.GetArrayObject(i) == nullptr) continue;
		all_draw_component_.GetArrayObject(i)->Debug();
	}
#endif
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画コンポーネント登録関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::RegistrationComponent(DrawComponent* draw_component)
{
	// 登録
	all_draw_component_.AddToArray(draw_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新コンポーネント上書き関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::OverwriteComponent(GameObjectOrigin* game_object, DrawComponent* new_draw_component)
{
	// 新規コンポーネントがnullptrかどうか
	if (new_draw_component == nullptr)
	{
		// 古いオブジェクトの解放
		ReleaseComponent(game_object->GetDrawComponent());

		// 古いコンポーネントの消去
		DrawComponent* temp = game_object->GetDrawComponent();
		SafeRelease::Normal(&temp);

		// 新規コンポーネント(nullptr)の代入
		game_object->SetDrawComponent(new_draw_component);
	}
	else
	{
		// 配列の上書き
		all_draw_component_.OverwriteArray(game_object->GetDrawComponent(), new_draw_component);

		// 古いコンポーネントの消去
		DrawComponent* temp = game_object->GetDrawComponent();
		SafeRelease::Normal(&temp);

		// 新規コンポーネントの初期化
		game_object->SetDrawComponent(new_draw_component);
		new_draw_component->SetGameObjectOrigin(game_object);
		new_draw_component->Init();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画コンポーネント解放関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::ReleaseComponent(DrawComponent* draw_component)
{
	// 削除とソート
	all_draw_component_.DeleteFromArrayAndSortArray(draw_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトカメラ作成関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::CreateDefaultCamera(Camera::State* camera_state, Camera::Type camra_type)
{
	// デフォルトのカメラの作成
	if (all_camera_.GetEndPointer() > 0) return;
	all_camera_.AddToArray(new Camera(camera_state, camra_type));
	all_camera_.GetArrayObject(0)->CreateProjectionMatrix_PerspectiveFov();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ カメラ追加関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::AddCamera(Camera::State* camera_state, Camera::Type camra_type)
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



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ カメラ消去関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::DeleteCamera(unsigned index)
{
	// カメラの削除
	all_camera_.DeleteFromArray(all_camera_.GetArrayObject(index));
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ カメラステート変更関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::ChangeCameraState(unsigned index, Camera::State* camera_state_)
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



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ フェード初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::InitFade(Fade::Type type, Fade::State state, Vec2 size, 
									XColor4 fade_color, float fade_speed)
{
	// フェードの初期化
	fade_->Init(type, state, size, fade_color, fade_speed);

	// フェードフラグON
	is_fade_ = true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ フェード終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DrawComponentManager::UninitFade()
{
	// フェードの終了処理
	fade_->Uninit();

	// フェードフラグOFF
	is_fade_ = false;
}



//--------------------------------------------------------------------------------
//
// [ 更新関数 ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::Update(unsigned index)
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



//--------------------------------------------------------------------------------
//
// [ 描画コンポーネント配列のリセット関数 ]
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
// [ 描画コンポーネント振り分け関数 ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::DistributeDrawComponent(unsigned index)
{
	for (unsigned i = 0; i < all_draw_component_.GetEndPointer(); i++)
	{
		if (all_draw_component_.GetArrayObject(i) == nullptr) continue;

		switch (all_draw_component_.GetArrayObject(i)->GetState())
		{
			// 不透明
			case DrawComponent::State::FIXED				 :
			case DrawComponent::State::FIXED_BILLBOARD	     :
			case DrawComponent::State::TEST_SHADER           :
			case DrawComponent::State::TEST_SHADER_BILLBOARD :
			{
				all_opacity_draw_component_.AddToArray(all_draw_component_.GetArrayObject(i));
				break;
			}
			// 透明
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
// [ 透明描画コンポーネントのソート関数 ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::SortTransparent(unsigned index)
{
	// 透明オブジェクトがあるかどうか
	if (all_transparent_draw_component_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparent_draw_component_.GetEndPointer() - 1; i++)
	{
		// 深度値を算出
		Vector3D temp_vector0 = *all_transparent_draw_component_.GetArrayObject(i)->GetGameObjectOrigin()->GetTransform()->GetPosition()
			                    - *all_camera_.GetArrayObject(index)->GetPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparent_draw_component_.GetEndPointer(); j++)
		{
			// 深度値を算出
			Vector3D temp_vector1 = *all_transparent_draw_component_.GetArrayObject(j)->GetGameObjectOrigin()->GetTransform()->GetPosition()
			                        - *all_camera_.GetArrayObject(index)->GetPositon();
			
			float depth_value1 = temp_vector1.GetLengthSquare();

			// 深度値を比較
			if (depth_value0 < depth_value1)
			{
				// 並び替え
				all_transparent_draw_component_.SortTheTwoObject(i, j);
			}
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ ビルボード用行列変更関数 ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::SetBillboardMatrix(DrawComponent* draw_component, unsigned index)
{
	// ビュー行列の転置行列をセット
	draw_component->GetGameObjectOrigin()->GetTransform()->UpdateTransposeMatrix(all_camera_.GetArrayObject(index)->GetViewMatrix());
	
	// 平行成分をカット
	draw_component->GetGameObjectOrigin()->GetTransform()->TransposeMatrixTranslationOff();
	
	// ワールド行列の更新
	draw_component->GetGameObjectOrigin()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
}



//--------------------------------------------------------------------------------
//
// [ 各パイプライン描画関数 ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::DrawEachPipeline(LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM>* draw_components, unsigned index)
{
	for (unsigned i = 0; i < draw_components->GetEndPointer(); i++)
	{
		switch (draw_components->GetArrayObject(i)->GetState())
		{
			// 固定パイプライン
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
			// テストシェーダー
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
// [ ノーマルカメラパイプライン関数 ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::NormalCameraPipeline(unsigned index)
{
	// 共通更新
	Update(index);

	// 不透明オブジェクト
	DrawEachPipeline(&all_opacity_draw_component_, index);

	// 透明オブジェクト
	DrawEachPipeline(&all_transparent_draw_component_, index);

	// エフェクシアの描画
	EffekseerManager::Draw();

	// 2Dオブジェクト
	DrawEachPipeline(&all_2D_draw_component_, index);

	// フェードの処理
	FadeUpdate_Draw();
}



//--------------------------------------------------------------------------------
//
// [ フェードの更新及び描画関数 ]
//
//--------------------------------------------------------------------------------

void DrawComponentManager::FadeUpdate_Draw()
{
	if (!is_fade_) return;

	// 更新
	fade_->Update();

	// 描画
	switch(*fade_->GetType())
	{
		case Fade::Type::TYPE_NORMAL :
		{
			// デバイスの取得
			LPDIRECT3DDEVICE9 device = nullptr;
			Renderer::GetInstance()->GetDevice(&device);
			assert(device != nullptr && "Deviceの取得に失敗(DrawComponentManager.cpp)");

			FixedPipelineObject::SetDraw2D();
			device->SetTransform(D3DTS_WORLD, fade_->GetTransform()->GetWorldMatrix());
			device->SetTexture(0, NULL);
			fade_->Draw();
			break;
		}
		case Fade::Type::TYPE_TRANSITION_01 :
		{
			fade_->GetTransition01Object();		// テクスチャセット用にテクスオブジェクトの取得可能
			fade_->Draw();
			break;
		}
	}
}