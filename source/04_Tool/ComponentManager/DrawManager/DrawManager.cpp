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
#include "ShaderManager/ShaderManager.h"

#include <Component/Base/DrawBase/DrawBase.h>
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
	// シェーダーマネージャー初期化
	shader_manager_ = new ShaderManager();
	shader_manager_->Init();

	// バックバッファ初期化
	back_buffer_ = new BackBuffer();
	back_buffer_->Init();
	back_buffer_->SetShaderManager(shader_manager_);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void DrawManager::Uninit()
{
	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全描画配列のリセット
	all_draw_.ResetArray();

	// バックバッファ終了処理
	SafeRelease::PlusUninit(&back_buffer_);
	SafeRelease::PlusUninit(&shader_manager_);
}



//--------------------------------------------------
// +シーン変更時の終了関数
//--------------------------------------------------
void DrawManager::UninitWhenChangeScene()
{
	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全描画配列のリセット
	all_draw_.ResetArray();

	// バックバッファ終了処理
	back_buffer_->UninitWhenChangeScene();
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void DrawManager::Update()
{
	// 追加待ち配列の中身を追加
	AddContentsOfAwaitAddArray();

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 全レンダーターゲットのリセット
	ResetAllRenderTarget();

	// レンダーターゲットごとの振り分け
	DistributeDrawBase();

	// 全レンダーターゲット更新関数
	UpdateAllRenderTarget();

	// デバッグ表示
#ifdef _DEBUG
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		if (all_draw_.GetArrayObject(i) == nullptr) continue;
		all_draw_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void DrawManager::Draw()
{
	// バックバッファ
	back_buffer_->Draw();
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
// -全レンダーターゲット更新関数
//--------------------------------------------------
void DrawManager::UpdateAllRenderTarget()
{
	// バックバッファ
	back_buffer_->Update();
}



//--------------------------------------------------
// -全レンダーターゲットリセット関数
//--------------------------------------------------
void DrawManager::ResetAllRenderTarget()
{
	// バックバッファ
	back_buffer_->ResetAllArray();
}



//--------------------------------------------------
// -描画基底クラス振り分け関数
//--------------------------------------------------
void DrawManager::DistributeDrawBase()
{
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		// バックバッファ
		if (all_draw_.GetArrayObject(i)->GetDrawOrderList()->GetRenderTargetFlag()
			->CheckAny(DrawOrderList::RENDER_TARGET_BACK_BUFFER))
		{
			back_buffer_->AddDrawBaseToArray(all_draw_.GetArrayObject(i));
		}
	}
}