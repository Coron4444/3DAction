//================================================================================
//!	@file	 ModelXManager.cpp
//!	@brief	 XモデルマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "ModelXManager.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string ModelXManager::DEFAULT_PATH = "resource/ModelX/";



//****************************************
// static変数定義
//****************************************
ModelXManager* ModelXManager::instance_ = nullptr;



//****************************************
// staticプロパティ定義
//****************************************
ModelXManager* ModelXManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new ModelXManager();
	}
	return instance_;
}



//****************************************
// static関数定義
//****************************************
void ModelXManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// プロパティ定義
//****************************************
ModelXObject* ModelXManager::getpObject(const std::string* key_name,
										const std::string* file_path)
{
	// マップにあるかの確認
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		// 参照カウンタをUP
		iterator->second->AddReferenceCounter();

		return iterator->second;
	}

	// 新規作成
	std::string path = CreateFilePath(key_name, file_path);
	ModelXObject* object = new ModelXObject();
	object->Init(&path, key_name);
	object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, object));
	return object;
}



//****************************************
// 関数定義
//****************************************
ModelXManager::ModelXManager()
{
}



void ModelXManager::Init()
{
	// マップの初期化
	object_map_.clear();
}



void ModelXManager::Uninit()
{
	// 各オブジェクトの強制解放
	auto iterator = object_map_.begin();
	while (iterator != object_map_.end())
	{
		iterator->second->ForcedRelease();
		iterator = object_map_.begin();
	}
	object_map_.clear();
}



void ModelXManager::ReleaseFromTheMap(std::string* key_name)
{
	// マップから解放
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		object_map_.erase(iterator);
	}
}



std::string ModelXManager::CreateFilePath(const std::string* key_name,
										  const std::string* file_path)
{
	// デフォルトのパスを使用
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// 任意のパスを使用
	return *file_path + *key_name;
}