//================================================================================
//
//    更新コンポーネントマネージャークラス(static)
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "UpdateComponentManager.h"
#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Component\UpdateComponent\UpdateComponent.h>
#include <SafeRelease/SafeRelease.h>


//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

LimitedPointerArray<UpdateComponent*, UpdateComponentManager::ARRAY_NUM> UpdateComponentManager::all_update_component_;
LimitedPointerArray<UpdateComponent*, UpdateComponentManager::ARRAY_NUM> UpdateComponentManager::registration_;
LimitedPointerArray<UpdateComponent*, UpdateComponentManager::ARRAY_NUM> UpdateComponentManager::release_;



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

void UpdateComponentManager::Init()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::Uninit()
{
	// 解放用配列のリセット
	release_.ResetArray();

	// 登録用配列のリセット
	registration_.ResetArray();

	// コンポーネント配列のリセット
	all_update_component_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ シーン変更時の終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::Uninit_ChangeScene()
{
	// 解放用配列のリセット
	release_.ResetArray();

	// 登録用配列のリセット
	registration_.ResetArray();

	// コンポーネント配列のリセット
	all_update_component_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::Update()
{
	// 解放待ちの解放
	ReleaseUpdateComponentALL();

	// 登録待ちの登録
	RegistrationUpdateComponentALL();

	// 更新
	for (unsigned i = 0; i < all_update_component_.GetEndPointer(); i++)
	{
		if (all_update_component_.GetArrayObject(i) == nullptr) continue;
		all_update_component_.GetArrayObject(i)->Update();
	}

	// 後更新
	for (unsigned i = 0; i < all_update_component_.GetEndPointer(); i++)
	{
		if (all_update_component_.GetArrayObject(i) == nullptr) continue;
		all_update_component_.GetArrayObject(i)->LateUpdate();
	}

	// 物理更新
	for (unsigned i = 0; i < all_update_component_.GetEndPointer(); i++)
	{
		if (all_update_component_.GetArrayObject(i)->GetGameObjectOrigin()->GetPhysics() == nullptr) continue;

		// 物理更新
		all_update_component_.GetArrayObject(i)->GetGameObjectOrigin()->GetPhysics()->Update();
	}


#ifdef _DEBUG
	// デバッグ
	for (unsigned i = 0; i < all_update_component_.GetEndPointer(); i++)
	{
		if (all_update_component_.GetArrayObject(i) == nullptr) continue;
		all_update_component_.GetArrayObject(i)->Debug();
	}
#endif

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新コンポーネント登録予約関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::RegistrationComponent(UpdateComponent* update_component)
{
	// 登録
	registration_.AddToArray(update_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新コンポーネント上書き関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::OverwriteComponent(GameObjectOrigin* game_object, UpdateComponent* new_update_component)
{
	// 新規コンポーネントがnullptrかどうか
	if (new_update_component == nullptr)
	{
		// 古いオブジェクトの解放予約
		ReleaseComponent(game_object->GetUpdateComponent());

		// 古いコンポーネントの消去
		UpdateComponent* temp = game_object->GetUpdateComponent();
		SafeRelease::Normal(&temp);

		// 新規コンポーネント(nullptr)の代入
		game_object->SetUpdateComponent(new_update_component);
	}
	else
	{
		// 配列の上書き
		all_update_component_.OverwriteArray(game_object->GetUpdateComponent(), new_update_component);

		// 古いコンポーネントの消去
		UpdateComponent* temp = game_object->GetUpdateComponent();
		SafeRelease::Normal(&temp);

		// 新規コンポーネントの初期化
		game_object->SetUpdateComponent(new_update_component);
		new_update_component->SetGameObjectOrigin(game_object);
		new_update_component->Init();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新コンポーネント解放予約関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UpdateComponentManager::ReleaseComponent(UpdateComponent* update_component)
{
	// 解放配列登録
	release_.AddToArray(update_component);
}



//--------------------------------------------------------------------------------
//
// [ 全ての登録待ち更新コンポーネントの登録関数 ]
//
//--------------------------------------------------------------------------------

void UpdateComponentManager::RegistrationUpdateComponentALL()
{
	// 登録待ちがあるかどうか
	if(registration_.GetEndPointer() <= 0) return;

	// 登録
	for (unsigned i = 0; i < registration_.GetEndPointer(); i++)
	{
		all_update_component_.AddToArray(registration_.GetArrayObject(i));
	}

	// 登録待ち配列をリセット
	registration_.ResetArray();
}



//--------------------------------------------------------------------------------
//
// [ 全ての解放待ち更新コンポーネントの解放関数 ]
//
//--------------------------------------------------------------------------------

void UpdateComponentManager::ReleaseUpdateComponentALL()
{
	// 解放待ちがあるかどうか
	if(release_.GetEndPointer() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < release_.GetEndPointer(); i++)
	{
		all_update_component_.DeleteFromArrayAndSortArray(release_.GetArrayObject(i));
	}

	// 解放待ち配列をリセット
	release_.ResetArray();
}