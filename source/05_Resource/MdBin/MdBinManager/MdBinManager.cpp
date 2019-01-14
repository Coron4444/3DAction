//================================================================================
//!	@file	 MdBinManager.cpp
//!	@brief	 バイナリーモデルマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "MdBinManager.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string MdBinManager::DEFAULT_PATH = "resource/MdBin/";



//****************************************
// static変数定義
//****************************************
MdBinManager* MdBinManager::instance_ = nullptr;



//****************************************
// staticプロパティ定義
//****************************************
MdBinManager* MdBinManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new MdBinManager();
	}
	return instance_;
}



//****************************************
// static関数定義
//****************************************
void MdBinManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// プロパティ定義
//****************************************
MdBinObject* MdBinManager::getpObject(const std::string* key_name,
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
	MdBinObject* object = new MdBinObject();
	object->Init(&path, key_name);
	object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, object));
	return object;
}



//****************************************
// 関数定義
//****************************************
MdBinManager::MdBinManager()
{
}



void MdBinManager::Init()
{
	// マップの初期化
	object_map_.clear();
}



void MdBinManager::Uninit()
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



void MdBinManager::ReleaseFromTheMap(std::string* key_name)
{
	// マップから解放
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		object_map_.erase(iterator);
	}
}



std::string MdBinManager::CreateFilePath(const std::string* key_name,
										 const std::string* file_path)
{
	// デフォルトのパスを使用
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// 任意のパスを使用
	return *file_path + *key_name;
}