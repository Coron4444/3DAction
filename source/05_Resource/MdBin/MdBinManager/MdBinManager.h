//================================================================================
//!	@file	 MdBinManager.h
//!	@brief	 バイナリーモデルマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_MD_BIN_MANAGER_H_
#define _MD_BIN_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <string>
#include <vector>
#include <unordered_map>

#include <MdBin/MdBinObject/MdBinObject.h>
#include <Texture/TextureManager/TextureManager.h>



//************************************************************														   
//! @brief   バイナリーモデルマネージャClass
//!
//! @details バイナリーモデルのマネージャClass(Singleton)
//************************************************************
class MdBinManager
{
//====================
// 定数
//====================
private:
	static const std::string DEFAULT_PATH;					//!< 既定パス


//====================
// static変数
//====================
private:
	static MdBinManager* instance_;	//!< インスタンス


//====================
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval MdBinManager* インスタンス
	//----------------------------------------
	static MdBinManager* getpInstance();


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
	std::unordered_map<std::string, MdBinObject*> object_map_;		//!< オブジェクトマップ
	

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval MdBinObject* オブジェクト
	//----------------------------------------
	MdBinObject* getpObject(const std::string* key_name,
							const std::string* file_path = nullptr);


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	MdBinManager();

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
	MdBinManager(const MdBinManager& class_name) = delete;
	MdBinManager& operator = (const MdBinManager& class_name) = delete;
};



#endif