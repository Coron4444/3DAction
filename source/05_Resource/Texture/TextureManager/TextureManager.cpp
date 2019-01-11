//================================================================================
//!	@file	 TextureManager.cpp
//!	@brief	 テクスチャマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "TextureManager.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string TextureManager::DEFAULT_PATH = "resource/Texture/";



//****************************************
// static変数定義
//****************************************
TextureManager* TextureManager::instance_ = nullptr;



//****************************************
// staticプロパティ定義
//****************************************
TextureManager* TextureManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new TextureManager();
	}
	return instance_;
}



//****************************************
// static関数定義
//****************************************
void TextureManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// プロパティ定義
//****************************************
TextureObject* TextureManager::getpObject(std::string* key_name,
									std::string* file_path,
									int pattern_num_all,
									int pattern_num_width,
									int pattern_num_height)
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
	TextureObject* texture_object = new TextureObject();
	texture_object->Init(&path);
	texture_object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, texture_object));
	return texture_object;
}



//****************************************
// 関数定義
//****************************************
TextureManager::TextureManager()
{
}



void TextureManager::Init()
{
	// マップの初期化
	object_map_.clear();
}



void TextureManager::Uninit()
{
	// 各テクスチャの解放
	for (auto& contents : object_map_)
	{
		contents.second->ResetReferenceCounter();
		SafeRelease::PlusRelease(&contents.second);
	}
}



std::string TextureManager::CreateFilePath(std::string* key_name,
										   std::string* file_path)
{
	// デフォルトのパスを使用
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// 任意のパスを使用
	return *file_path + *key_name;
}