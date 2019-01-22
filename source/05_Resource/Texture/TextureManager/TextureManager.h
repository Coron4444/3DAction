//================================================================================
//!	@file	 TextureManager.h
//!	@brief	 テクスチャマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <string>
#include <vector>
#include <unordered_map>

#include <Texture\TextureObject\TextureObject.h>



//************************************************************														   
//! @brief   テクスチャマネージャClass
//!
//! @details テクスチャのマネージャClass(Singleton)
//************************************************************
class TextureManager
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
	static TextureManager* instance_;	//!< インスタンス


//====================
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval TextureManager* インスタンス
	//----------------------------------------
	static TextureManager* getpInstance();


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
	std::unordered_map<std::string, TextureObject*> object_map_;	//!< オブジェクトマップ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval TextureObject* オブジェクト
	//----------------------------------------
	TextureObject* getpObject(const std::string* key_name, 
							  const std::string* file_path = nullptr);


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	TextureManager();

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
	//! @param *key_name キー名
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
	TextureManager(const TextureManager& class_name) = delete;
	TextureManager& operator = (const TextureManager& class_name) = delete;
};



#endif