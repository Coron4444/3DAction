//================================================================================
//
//    Xモデルマネージャクラスヘッダ
//    Author : Araki Kai                                作成日 : 2018/01/21
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "ModelXManager.h"

#include <Texture\TextureManager\TextureManager.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string ModelXManager::DEFAULT_PATH = "resource/ModelX/";



//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

std::unordered_map<std::string, ModelXObject*> ModelXManager::share_model_map_;
std::unordered_map<std::string, ModelXObject*> ModelXManager::unique_model_map_;



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

void ModelXManager::InitAllData()
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

void ModelXManager::InitShareData()
{
	// マップの初期化
	share_model_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数(固有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXManager::InitUniqueData()
{
	// マップの初期化
	unique_model_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(全データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXManager::UninitAllData()
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

void ModelXManager::UninitShareData()
{
	// 各Xモデルの解放
	for(auto& contents : share_model_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// マップの全消去
	share_model_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(固有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXManager::UninitUniqueData()
{
	// 各Xモデルの解放
	for(auto& contents : unique_model_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// マップの全消去
	unique_model_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 共有データの追加関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject* ModelXManager::AddShareData(const std::string* key_name, const std::string* file_path)
{
	ModelXObject* temp_object = GetModelXObject(key_name);

	// 存在する場合
	if (temp_object != nullptr) return temp_object;

	// 存在しない場合
	std::string temp_path = MakeFilePath(key_name, file_path);
	temp_object = new ModelXObject(&temp_path, true);
	share_model_map_.insert(std::make_pair(*key_name, temp_object));
	return temp_object;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 固有データの追加関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject* ModelXManager::AddUniqueData(const std::string* key_name, const std::string* file_path)
{
	ModelXObject* temp_object = GetModelXObject(key_name);

	// 存在する場合
	if (temp_object != nullptr) return temp_object;

	// 存在しない場合
	std::string temp_path = MakeFilePath(key_name, file_path);
	temp_object = new ModelXObject(&temp_path, false);
	unique_model_map_.insert(std::make_pair(*key_name, temp_object));
	return temp_object;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ モデルXオブジェクト取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject* ModelXManager::GetModelXObject(const std::string* key_name)
{
	// 共有データマップにあるかの確認
	auto itr_share = share_model_map_.find(*key_name);
	if (itr_share != share_model_map_.end()) return itr_share->second;
	
	// 固有データマップにあるかの確認
	auto itr_unique = unique_model_map_.find(*key_name);
	if (itr_unique != unique_model_map_.end()) return itr_unique->second;

	return nullptr;
}



//--------------------------------------------------------------------------------
//
// [ ファイルパス作成関数 ]
//
//--------------------------------------------------------------------------------

std::string ModelXManager::MakeFilePath(const std::string* key_name, const std::string* file_path)
{
	// デフォルトのパスを使用
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;
	
	// 任意のパスを使用
	return *file_path + *key_name;
}