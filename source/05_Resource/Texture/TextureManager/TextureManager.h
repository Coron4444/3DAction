//================================================================================
//
//    テクスチャマネージャクラス(static)
//    Author : Araki Kai                                作成日 : 2017/12/19
//
//================================================================================

#ifndef	_TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>
#include <vector>
#include <unordered_map>

#include <Texture\TextureObject\TextureObject.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class TextureManager
{
//------------------------------------------------------------
private :
	static const std::string DEFAULT_PATH;


//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	TextureManager() = delete;

	// コピーコンストラクタ
	TextureManager(const TextureManager& class_name) = delete;

	// 代入演算子のオーバーロード
	TextureManager& operator = (const TextureManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 初期化関数
	static void InitAllData();
	static void InitShareData();
	static void InitUniqueData();

	// 終了処理関数
	static void UninitAllData();
	static void UninitShareData();
	static void UninitUniqueData();

	// 追加関数
	static TextureObject* AddShareData (const std::string* key_name, const std::string* file_path = nullptr, int pattern_num_all = 1, int pattern_num_width = 1, int pattern_num_height = 1);
	static TextureObject* AddUniqueData(const std::string* key_name, const std::string* file_path = nullptr, int pattern_num_all = 1, int pattern_num_width = 1, int pattern_num_height = 1);

	// ゲッタ―
	static TextureObject* GetTextureObject(const std::string* key_name);


//------------------------------------------------------------
private :
	static std::string MakeFilePath(const std::string* key_name, const std::string* file_path);


//------------------------------------------------------------
private :
	// メンバ変数
	static std::unordered_map<std::string, TextureObject*> share_texture_map_;
	static std::unordered_map<std::string, TextureObject*> unique_texture_map_;
};



#endif