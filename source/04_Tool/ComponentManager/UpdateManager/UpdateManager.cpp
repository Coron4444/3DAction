//================================================================================
//!	@file	 UpdateManager.cpp
//!	@brief	 更新マネージャーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "UpdateManager.h"

#include <Component/Update/UpdateBase/UpdateBase.h>
#include <GameObjectBase/GameObjectBase.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// 関数定義
//****************************************
void UpdateManager::Init()
{
}



void UpdateManager::Uninit()
{
	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全更新配列のリセット
	all_update_.ResetArray();
}



void UpdateManager::UninitWhenChangeScene()
{
	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全更新配列のリセット
	all_update_.ResetArray();
}



void UpdateManager::Update()
{
	// 追加待ち配列の中身を追加
	AddContentsOfAwaitAddArray();

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 更新
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i) == nullptr) continue;
		all_update_.GetArrayObject(i)->Update();
	}

	// 後更新
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i) == nullptr) continue;
		all_update_.GetArrayObject(i)->LateUpdate();
	}

	// 物理更新
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i)->getpGameObject()->GetPhysics() == nullptr) continue;
		all_update_.GetArrayObject(i)->getpGameObject()->GetPhysics()->Update();
	}


	// デバッグ
#ifdef _DEBUG
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i) == nullptr) continue;
		all_update_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



void UpdateManager::AddUpdateBaseToArray(UpdateBase* update)
{
	// 追加待ち配列に追加
	await_add_.AddToArray(update);
}



void UpdateManager::OverwriteArrayUpdateBase(GameObjectBase* game_object,
											 UpdateBase* new_update)
{
	// 新規がnullptrの場合
	if (new_update == nullptr)
	{
		// 古い更新基底クラスの解放
		ReleaseUpdateBaseFromArray(game_object->GetUpdate());

		// 古い更新基底クラスの消去
		UpdateBase* temp = game_object->GetUpdate();
		SafeRelease::Normal(&temp);

		// nullptrの代入
		game_object->SetUpdate(new_update);
	}
	else
	{
		// 配列の上書き
		all_update_.OverwriteArray(game_object->GetUpdate(), new_update);

		// 古い更新基底クラスの消去
		UpdateBase* temp = game_object->GetUpdate();
		SafeRelease::Normal(&temp);

		// 新規更新基底クラスの初期化
		game_object->SetUpdate(new_update);
		*new_update->getpGameObject() = *game_object;
		new_update->Init();
	}
}



void UpdateManager::ReleaseUpdateBaseFromArray(UpdateBase* update)
{
	// 解放待ち配列に追加
	await_release_.AddToArray(update);
}



void UpdateManager::AddContentsOfAwaitAddArray()
{
	// 追加待ちがあるかどうか
	if(await_add_.GetEndPointer() <= 0) return;

	// 追加
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_update_.AddToArray(await_add_.GetArrayObject(i));
	}

	// 追加待ち配列をリセット
	await_add_.ResetArray();
}



void UpdateManager::ReleaseContentsOfAwaitReleaseArray()
{
	// 解放待ちがあるかどうか
	if(await_release_.GetEndPointer() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		all_update_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// 解放待ち配列をリセット
	await_release_.ResetArray();
}