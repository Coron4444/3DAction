//================================================================================
//
//    FBXモデルマネージャクラスヘッダ
//    Author : Araki Kai                                作成日 : 2018/01/21
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "ModelFBXManager.h"

#include <ModelFBX\ModelFBXObject\ModelFBXObject.h>

#include <Texture\TextureManager\TextureManager.h>


//**********************************************************************
//
// 非静的メンバ関数定義
//
//**********************************************************************

//================================================================================
//
// [ コンストラクタ ]
//
//================================================================================

ModelFBXManager::ModelFBXManager(TextureManager* texture_manager)
	: texture_manager_(texture_manager)
{
}



//================================================================================
//
// [ デストラクタ ]
//
//================================================================================

ModelFBXManager::~ModelFBXManager()
{
	// 各FBXモデルの解放
	for(auto& contents : model_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// マップの全消去
	model_map_.clear();
}



//================================================================================
//
// [ FBXモデルオブジェクト登録関数 ]
//
//================================================================================

void ModelFBXManager::RegistrationModelFBXObject(const std::string* key_name, const std::string* file_path)
{
	// 登録の確認
	auto itr = model_map_.find(*key_name);

	if(itr != model_map_.end())
	{
		// 設定されている場合
		return;
	}
	else
	{
		// 設定されていない場合
		model_map_.insert(std::make_pair(*key_name, new ModelFBXObject(texture_manager_, key_name, file_path)));
	}
}



//================================================================================
//
// [ FBXモデル取得関数 ]
//
//================================================================================

ModelFBXObject* ModelFBXManager::GetModelFBXObject(const std::string* key_name)
{
	// 登録の確認
	auto itr = model_map_.find(*key_name);

	if(itr != model_map_.end())
	{
		// 設定されている場合
		return itr->second;
	}
	else
	{
		// 設定されていない場合
		return nullptr;
	}
}



//================================================================================
//
// [ FBXモデルセット関数 ]
//
//================================================================================

void ModelFBXManager::SetModelFBXObject(const std::string* key_name)
{
	// 登録の確認
	auto itr = model_map_.find(*key_name);

	if(itr != model_map_.end())
	{
		// 設定されている場合
		itr->second->SetModelFBXObject();
		return;
	}
}