//================================================================================
//
//    ゲームオブジェクトの参照マネージャクラス
//    Author : Araki Kai                                作成日 : 2018/07/15
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "GameObjectReferenceManager.h"
#include "../../GameObjectBase/GameObjectBase.h"
#include <SafeRelease/SafeRelease.h>



//**********************************************************************
//
// 非静的メンバ関数定義
//
//**********************************************************************

//================================================================================
//
// [ デフォルトコンストラクタ ]
//
//================================================================================

GameObjectReferenceManager::GameObjectReferenceManager()
{
}



//================================================================================
//
// [ デストラクタ ]
//
//================================================================================

GameObjectReferenceManager::~GameObjectReferenceManager()
{
	// 全て解放
	AllReleaseReference();
}



//================================================================================
//
// [ 参照データ登録関数 ]
//
//================================================================================

void GameObjectReferenceManager::RegistrationReference(GameObjectBase* source, void* pointer, 
													   GameObjectBase* destination)
{
	// 参照元マップへの登録の確認
	RegistrationReference_Source(source, pointer, destination);

	// 参照先マップへの登録
	RegistrationReference_Source(source, pointer, destination);
}



//================================================================================
//
// [ 参照先データ解放関数 ]
//
//================================================================================

void GameObjectReferenceManager::ReleaseReference(GameObjectBase* object)
{
	// 参照元マップから消去
	ReleaseReference_Source(object);

	// 参照先マップから消去及びnullptrを代入
	ReleaseReference_Destination(object);
}



//================================================================================
//
// [ 全ての参照データ解放関数 ]
//
//================================================================================

void GameObjectReferenceManager::AllReleaseReference()
{
	// 参照元マップの解放
	for(auto& contents : reference_map_.source_map_)
	{
		if (contents.second == nullptr) return;
		
		for (unsigned i = 0; i < contents.second->GetEndPointer(); i++)
		{
			ReferenceData* temp = contents.second->GetArrayObject(i);
			SafeRelease::Normal(&temp);
		}

		SafeRelease::Normal(&contents.second);
	}

	// 参照先マップの解放
	for(auto& contents : reference_map_.destination_map_)
	{
		if (contents.second == nullptr) return;
		
		for (unsigned i = 0; i < contents.second->GetEndPointer(); i++)
		{
			ReferenceData* temp = contents.second->GetArrayObject(i);
			SafeRelease::Normal(&temp);
		}

		SafeRelease::Normal(&contents.second);
	}
}



//================================================================================
//
// [ 参照元登録関数 ]
//
//================================================================================

void GameObjectReferenceManager::RegistrationReference_Source(GameObjectBase* source, void* pointer, 
															  GameObjectBase* destination)
{
	// 参照元の検索
	auto iterator = reference_map_.source_map_.find(source);

	// 登録されていない場合
	if (iterator == reference_map_.source_map_.end())
	{
		// 参照データ配列を作成
		LimitedPointerArray<ReferenceData*, ARRAY_NUM>* temp_array = new LimitedPointerArray<ReferenceData*, ARRAY_NUM>;
		temp_array->AddToArray(new ReferenceData(source, pointer, destination));
		
		// 参照元マップに参照データ配列を登録
		reference_map_.source_map_.insert(std::make_pair(source, temp_array));
	}
	else
	{
		// 登録されている場合
		unsigned index;
		for (index = 0; index < iterator->second->GetEndPointer(); index++)
		{
			// 同じ参照先があるかどうか
			if (iterator->second->GetArrayObject(index)->reference_destination_ != destination) continue;
			
			break;
		}

		// 同じ参照先がないので登録
		if (index != iterator->second->GetEndPointer())
		{
			// 追加
			iterator->second->AddToArray(new ReferenceData(source, pointer, destination));
		}
	}
}



//================================================================================
//
// [ 参照先登録関数 ]
//
//================================================================================

void GameObjectReferenceManager::RegistrationReference_Destination(GameObjectBase* source, void* pointer, 
																   GameObjectBase* destination)
{
	// 参照先の検索
	auto iterator = reference_map_.destination_map_.find(destination);

	// 登録されていない場合
	if (iterator == reference_map_.destination_map_.end())
	{
		// 参照データ配列を作成
		LimitedPointerArray<ReferenceData*, ARRAY_NUM>* temp_array = new LimitedPointerArray<ReferenceData*, ARRAY_NUM>;
		temp_array->AddToArray(new ReferenceData(source, pointer, destination));
		
		// 参照元マップに参照データ配列を登録
		reference_map_.destination_map_.insert(std::make_pair(destination, temp_array));
	}
	else
	{
		// 登録されている場合
		unsigned index;
		for (index = 0; index < iterator->second->GetEndPointer(); index++)
		{
			// 同じ参照先があるかどうか
			if (iterator->second->GetArrayObject(index)->reference_source_ != source) continue;
			
			break;
		}

		// 同じ参照先がないので登録
		if (index != iterator->second->GetEndPointer())
		{
			// 追加
			iterator->second->AddToArray(new ReferenceData(source, pointer, destination));
		}
	}
}



//================================================================================
//
// [ 参照元データ解放関数 ]
//
//================================================================================

void GameObjectReferenceManager::ReleaseReference_Source(GameObjectBase* object)
{
	auto iterator = reference_map_.source_map_.find(object);

	// 登録されている場合
	if (iterator != reference_map_.source_map_.end())
	{
		for (unsigned i = 0; i < iterator->second->GetEndPointer(); i++)
		{
			// 解放
			ReferenceData* temp = iterator->second->GetArrayObject(i);
			SafeRelease::Normal(&temp);
		}

		// 配列の解放
		SafeRelease::Normal(&iterator->second);

		// 参照元マップから消去
		reference_map_.source_map_.erase(object);
	}
}



//================================================================================
//
// [ 参照先データ解放関数 ]
//
//================================================================================

void GameObjectReferenceManager::ReleaseReference_Destination(GameObjectBase* object)
{
	auto iterator = reference_map_.destination_map_.find(object);

	// 登録されている場合
	if (iterator != reference_map_.destination_map_.end())
	{
		for (unsigned i = 0; i < iterator->second->GetEndPointer(); i++)
		{
			// nullptrの挿入
			iterator->second->GetArrayObject(i)->reference_pointer_ = nullptr;

			// 解放
			ReferenceData* temp = iterator->second->GetArrayObject(i);
			SafeRelease::Normal(&temp);
		}

		// 配列の解放
		SafeRelease::Normal(&iterator->second);

		// 参照元マップから消去
		reference_map_.destination_map_.erase(object);
	}
}