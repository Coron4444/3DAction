//================================================================================
//!	@file	 ResourceManager.cpp
//!	@brief	 リソースマネージャClass
//! @details static
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "ResourceManager.h"



//======================================================================
//
// 静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数(全データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::InitAllData()
{
	// 各種リソースの初期化
	TextureManager::InitAllData();
	ModelXManager::InitAllData();
	EffekseerManager::InitAllData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数(共有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::InitShareData()
{
	// 各種リソースの初期化
	TextureManager::InitShareData();
	ModelXManager::InitShareData();
	EffekseerManager::InitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数(固有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::InitUniqueData()
{
	// 各種リソースの初期化
	TextureManager::InitUniqueData();
	ModelXManager::InitUniqueData();
	EffekseerManager::InitUniqueData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(全データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::UninitAllData()
{
	// 各種リソースの終了処理
	ModelXManager::UninitAllData();
	TextureManager::UninitAllData();
	EffekseerManager::UninitAllData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(共有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::UninitShareData()
{
	// 各種リソースの終了処理
	ModelXManager::UninitShareData();
	TextureManager::UninitShareData();
	EffekseerManager::UninitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(固有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ResourceManager::UninitUniqueData()
{
	// 各種リソースの終了処理
	ModelXManager::UninitUniqueData();
	TextureManager::UninitUniqueData();
	EffekseerManager::UninitUniqueData();
}