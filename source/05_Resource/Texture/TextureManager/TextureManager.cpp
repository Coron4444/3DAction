//================================================================================
//
//    テクスチャマネージャクラス(static)
//    Author : Araki Kai                                作成日 : 2017/12/19
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "TextureManager.h"



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string TextureManager::DEFAULT_PATH = "resource/Texture/";



//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

std::unordered_map<std::string, TextureObject*> TextureManager::share_texture_map_;
std::unordered_map<std::string, TextureObject*> TextureManager::unique_texture_map_;



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

void TextureManager::InitAllData()
{
	// 各種初期化
	InitUniqueData();
	InitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数(共有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TextureManager::InitShareData()
{
	// マップの初期化
	share_texture_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数(固有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TextureManager::InitUniqueData()
{
	// マップの初期化
	unique_texture_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(全データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TextureManager::UninitAllData()
{
	// 各種終了処理
	UninitUniqueData();
	UninitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(共有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TextureManager::UninitShareData()
{
	// 各テクスチャの解放
	for(auto& contents : share_texture_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// マップの全消去
	share_texture_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(固有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TextureManager::UninitUniqueData()
{
	// 各テクスチャの解放
	for(auto& contents : unique_texture_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// マップの全消去
	unique_texture_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 共有データの追加関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject* TextureManager::AddShareData(const std::string* key_name, const std::string* file_path, 
											int pattern_num_all, int pattern_num_width, int pattern_num_height)
{
	TextureObject* temp_object = GetTextureObject(key_name);

	// 存在する場合
	if (temp_object != nullptr) return temp_object;

	// 存在しない場合
	std::string temp_path = MakeFilePath(key_name, file_path);
	temp_object = new TextureObject(&temp_path, pattern_num_all, pattern_num_width, pattern_num_height);
	share_texture_map_.insert(std::make_pair(*key_name, temp_object));
	return temp_object;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 固有データの追加関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject* TextureManager::AddUniqueData(const std::string* key_name, const std::string* file_path, 
											 int pattern_num_all, int pattern_num_width, int pattern_num_height)
{
	TextureObject* temp_object = GetTextureObject(key_name);

	// 存在する場合
	if (temp_object != nullptr) return temp_object;

	// 存在しない場合
	std::string temp_path = MakeFilePath(key_name, file_path);
	temp_object = new TextureObject(&temp_path, pattern_num_all, pattern_num_width, pattern_num_height);
	unique_texture_map_.insert(std::make_pair(*key_name, temp_object));
	return temp_object;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ テクスチャオブジェクト取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject* TextureManager::GetTextureObject(const std::string* key_name)
{
	// 共有データマップにあるかの確認
	auto itr_share = share_texture_map_.find(*key_name);
	if (itr_share != share_texture_map_.end()) return itr_share->second;
	
	// 固有データマップにあるかの確認
	auto itr_unique = unique_texture_map_.find(*key_name);
	if (itr_unique != unique_texture_map_.end()) return itr_unique->second;

	return nullptr;
}



//--------------------------------------------------------------------------------
//
// [ ファイルパス作成関数 ]
//
//--------------------------------------------------------------------------------

std::string TextureManager::MakeFilePath(const std::string* key_name, const std::string* file_path)
{
	// デフォルトのパスを使用
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;
	
	// 任意のパスを使用
	return *file_path + *key_name;
}