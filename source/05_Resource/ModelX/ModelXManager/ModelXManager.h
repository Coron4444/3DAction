//================================================================================
//!	@file	 ModelXManager.h
//!	@brief	 XモデルマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_MODEL_X_MANAGER_H_
#define _MODEL_X_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <string>
#include <vector>
#include <unordered_map>

#include <ModelX\ModelXObject\ModelXObject.h>
#include <Texture/TextureManager/TextureManager.h>



//************************************************************														   
//! @brief   XモデルマネージャClass
//!
//! @details XモデルのマネージャClass(Singleton)
//************************************************************
class ModelXManager
{
//====================
// 定数
//====================
private:
	static const std::string DEFAULT_PATH;		//!< 既定パス


//====================
// static変数
//====================
private:
	static ModelXManager* instance_;	//!< インスタンス


//====================
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval ModelXManager* インスタンス
	//----------------------------------------
	static ModelXManager* getpInstance();


//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief インスタンス解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	static void ReleaseInstance();


//====================
// 変数
//====================
private:
	std::unordered_map<std::string, ModelXObject*> object_map_;		//!< オブジェクトマップ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval ModelXObject* オブジェクト
	//----------------------------------------
	ModelXObject* getpObject(const std::string* key_name,
							 const std::string* file_path = nullptr);


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	ModelXManager();

public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief マップから解放関数
	//! @details
	//! @param *key_name  キー名
	//! @param *file_path ファイルパス
	//! @retval void なし
	//----------------------------------------
	void ReleaseFromTheMap(std::string* key_name);

private:
	//----------------------------------------
	//! @brief フルパス生成関数
	//! @details
	//! @param *key_name  キー名
	//! @param *file_path ファイルパス
	//! @retval std::string フルパス
	//----------------------------------------
	std::string CreateFilePath(const std::string* key_name, 
							   const std::string* file_path);


//====================
// 消去済み関数
//====================
private:
	ModelXManager(const ModelXManager& class_name) = delete;
	ModelXManager& operator = (const ModelXManager& class_name) = delete;
};



#endif