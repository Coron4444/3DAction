//================================================================================
//
//    Xモデルマネージャクラスヘッダ
//    Author : Araki Kai                                作成日 : 2018/01/21
//
//================================================================================

#ifndef	_MODEL_X_MANAGER_H_
#define _MODEL_X_MANAGER_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>
#include <vector>
#include <unordered_map>

#include <ModelX\ModelXObject\ModelXObject.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class ModelXManager
{
//------------------------------------------------------------
private :
	static const std::string DEFAULT_PATH;


//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	ModelXManager() = delete;

	// コピーコンストラクタ
	ModelXManager(const ModelXManager& class_name) = delete;

	// 代入演算子のオーバーロード
	ModelXManager& operator = (const ModelXManager& class_name) = delete;


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
	static ModelXObject* AddShareData (const std::string* key_name, const std::string* file_path = nullptr);
	static ModelXObject* AddUniqueData(const std::string* key_name, const std::string* file_path = nullptr);

	// ゲッタ―
	static ModelXObject* GetModelXObject(const std::string* key_name);


//------------------------------------------------------------
private :
	static std::string MakeFilePath(const std::string* key_name, const std::string* file_path);


//------------------------------------------------------------
private :
	// メンバ変数
	static std::unordered_map<std::string, ModelXObject*> share_model_map_;
	static std::unordered_map<std::string, ModelXObject*> unique_model_map_;
};



#endif