//================================================================================
//
//    ゲームオブジェクトのマネージャクラス(static)
//    Author : Araki Kai                                作成日 : 2018/07/13
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "GameObjectManager.h"
#include "../GameObjectOrigin/GameObjectOrigin.h"
#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

LimitedPointerArray<GameObjectOrigin*, GameObjectManager::ARRAY_NUM> GameObjectManager::all_game_object_;
LimitedPointerArray<GameObjectOrigin*, GameObjectManager::ARRAY_NUM> GameObjectManager::all_release_game_object_;

GameObjectReferenceManager GameObjectManager::reference_manager_;




//======================================================================
//
// 静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 配列に登録関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::Registration(GameObjectOrigin* game_object)
{
	all_game_object_.AddToArray(game_object);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 解放待ちを解放関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::ReleaseAllWaitingObjects()
{
	// 登録されているオブジェクトを全て解放
	all_release_game_object_.ReleaseObjectAndResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 解放関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::Release(GameObjectOrigin* game_object)
{
	// 参照データ解放
	reference_manager_.ReleaseReference(game_object);

	// 全体配列からの消去
	all_game_object_.DeleteFromArrayAndSortArray(game_object);

	// リリース配列に登録
	all_release_game_object_.AddToArray(game_object);

	// ゲームオブジェクトの解放
	game_object->ReleaseObject();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 全て解放関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::ReleaseAll()
{
	// 参照データを全て消去
	reference_manager_.AllReleaseReference();

	// 登録されているオブジェクトを全て解放
	for (unsigned i = 0; i < all_game_object_.GetEndPointer(); i++)
	{
		all_game_object_.GetArrayObject(i)->ReleaseObject();
		GameObjectOrigin* temp = all_game_object_.GetArrayObject(i);
		SafeRelease::Normal(&temp);
	}

	// オブジェクト配列をリセット
	all_game_object_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 全てリセット関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectManager::ResetAll()
{
	// 登録されているオブジェクトを全てリセット
	for (unsigned i = 0; i < all_game_object_.GetEndPointer(); i++)
	{
		all_game_object_.GetArrayObject(i)->Reset();
	}
}