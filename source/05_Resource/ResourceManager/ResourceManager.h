//================================================================================
//!	@file	 ResourceManager.h
//!	@brief	 リソースマネージャClass
//! @details static
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <Texture\TextureManager\TextureManager.h>
#include <ModelX\ModelXManager\ModelXManager.h>
#include <Effekseer\EffekseerManager\EffekseerManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================
//************************************************************														   
//! @brief   リソースマネージャClass
//!
//! @details リソース全体のマネージャClass
//************************************************************
class ResourceManager
{
//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	ResourceManager() = delete;

	// コピーコンストラクタ
	ResourceManager(const ResourceManager& class_name) = delete;

	// 代入演算子のオーバーロード
	ResourceManager& operator = (const ResourceManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	static void InitAllData();
	static void InitShareData();
	static void InitUniqueData();

	static void UninitAllData();
	static void UninitShareData();
	static void UninitUniqueData();
};



#endif