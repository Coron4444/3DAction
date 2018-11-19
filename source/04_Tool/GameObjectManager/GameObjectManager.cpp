//================================================================================
//
//    ゲームオブジェクトのマネージャクラス(static)
//    Author : Araki Kai                                作成日 : 2018/07/13
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "GameObjectManager.h"
#include "../GameObjectBase/GameObjectBase.h"
#include <SafeRelease/SafeRelease.h>



//****************************************
// 静的メンバ変数定義
//****************************************
LimitedPointerArray<GameObjectBase*, GameObjectManager::ARRAY_NUM> GameObjectManager::all_game_object_;
LimitedPointerArray<GameObjectBase*, GameObjectManager::ARRAY_NUM> GameObjectManager::await_add_;
LimitedPointerArray<GameObjectBase*, GameObjectManager::ARRAY_NUM> GameObjectManager::await_release_;

GameObjectReferenceManager GameObjectManager::reference_manager_;
UpdateManager GameObjectManager::update_manager_;
DrawManager GameObjectManager::draw_manager_;
CollisionManager GameObjectManager::collision_manager_;



//****************************************
// 静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void GameObjectManager::Init()
{
	// 各種マネージャの初期化
	update_manager_.Init();
	draw_manager_.Init();
	collision_manager_.Init();
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void GameObjectManager::Uninit()
{
	// 全ゲームオブジェクトの解放
	AllRelease();

	// 各種マネージャの終了処理
	collision_manager_.Uninit();
	draw_manager_.Uninit();
	update_manager_.Uninit();

}



//--------------------------------------------------
// +シーン変更時の終了関数
//--------------------------------------------------
void GameObjectManager::UninitWhenChangeScene()
{
	// 全ゲームオブジェクトの解放
	AllRelease();

	// 各種マネージャのシーン変更時の終了処理
	collision_manager_.UninitWhenChangeScene();
	draw_manager_.UninitWhenChangeScene();
	update_manager_.UninitWhenChangeScene();
	
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void GameObjectManager::Update()
{
	// 追加待ち配列の中身を追加
	AddContentsOfAwaitAddArray();

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 更新
	update_manager_.Update();
	collision_manager_.Update();
	draw_manager_.Update();
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void GameObjectManager::Draw()
{
	draw_manager_.Draw();
}



//--------------------------------------------------
// +全ゲームオブジェクトリセット関数
//--------------------------------------------------
void GameObjectManager::AllReset()
{
	// 登録されているオブジェクトを全てリセット
	for (unsigned i = 0; i < all_game_object_.GetEndPointer(); i++)
	{
		all_game_object_.GetArrayObject(i)->Reset();
	}
}



//--------------------------------------------------
// +ゲームオブジェクト基底クラスの追加関数
//--------------------------------------------------
void GameObjectManager::AddGameObjectBaseToArray(GameObjectBase* game_object)
{
	await_add_.AddToArray(game_object);
}



//--------------------------------------------------
// +ゲームオブジェクト基底クラスの解放関数
//--------------------------------------------------
void GameObjectManager::ReleaseGameObjectBaseFromArray(GameObjectBase* game_object)
{
	// ゲームオブジェクト終了処理
	game_object->Uninit();

	// コンポーネントをマネージャから解放
	ReleaseComponentFromManager(game_object);

	// 参照データ解放
	reference_manager_.ReleaseReference(game_object);

	// 解放待ち配列に追加
	await_release_.AddToArray(game_object);
}



//--------------------------------------------------
// -追加待ち配列の中身を追加関数
//--------------------------------------------------
void GameObjectManager::AddContentsOfAwaitAddArray()
{
	// 追加待ちがあるかどうか
	if (await_add_.GetEndPointer() <= 0) return;

	// 追加
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		// 全体配列へ追加
		all_game_object_.AddToArray(await_add_.GetArrayObject(i));

		// コンポーネントをマネージャにセット
		SetComponentToManager(await_add_.GetArrayObject(i));
	}

	// 追加待ち配列をリセット
	await_add_.ResetArray();
}



//--------------------------------------------------
// -解放待ち配列の中身を解放関数
//--------------------------------------------------
void GameObjectManager::ReleaseContentsOfAwaitReleaseArray()
{
	// 解放待ちがあるかどうか
	if (await_release_.GetEndPointer() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		// 全体配列からの消去
		all_game_object_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));

		// オブジェクトの消去
		GameObjectBase* temp = await_release_.GetArrayObject(i);
		SafeRelease::Normal(&temp);
	}

	// 解放待ち配列をリセット
	await_release_.ResetArray();
}



//--------------------------------------------------
// -コンポーネントをマネージャーへ設定関数
//--------------------------------------------------
void GameObjectManager::SetComponentToManager(GameObjectBase* game_object)
{
	if (game_object->GetUpdate() != nullptr)
	{
		update_manager_.AddUpdateBaseToArray(game_object->GetUpdate());
	}

	if (game_object->GetDraw() != nullptr)
	{
		draw_manager_.AddDrawBaseToArray(game_object->GetDraw());
	}

	if (game_object->GetCollision() != nullptr)
	{
		collision_manager_.AddCollisionBaseToArray(game_object->GetCollision());
	}
}



//--------------------------------------------------
// -コンポーネントをマネージャーから解放関数
//--------------------------------------------------
void GameObjectManager::ReleaseComponentFromManager(GameObjectBase* game_object)
{
	if (game_object->GetUpdate() != nullptr)
	{
		update_manager_.ReleaseUpdateBaseFromArray(game_object->GetUpdate());
	}

	if (game_object->GetDraw() != nullptr)
	{
		draw_manager_.ReleaseDrawBaseFromArray(game_object->GetDraw());
	}

	if (game_object->GetCollision() != nullptr)
	{
		collision_manager_.ReleaseCollisionBaseFromArray(game_object->GetCollision());
	}
}



//--------------------------------------------------
// -全ゲームオブジェクトの解放関数
//--------------------------------------------------
void GameObjectManager::AllRelease()
{
	// 参照データを全て消去
	reference_manager_.AllReleaseReference();

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 残りのオブジェクトを全て解放待ちに登録
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		ReleaseGameObjectBaseFromArray(await_add_.GetArrayObject(i));
	}

	for (unsigned i = 0; i < all_game_object_.GetEndPointer(); i++)
	{
		ReleaseGameObjectBaseFromArray(all_game_object_.GetArrayObject(i));
	}

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();
	
	// オブジェクト配列をリセット
	all_game_object_.ResetArray();
}