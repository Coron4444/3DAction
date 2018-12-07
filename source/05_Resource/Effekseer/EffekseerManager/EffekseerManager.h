//================================================================================
//
//    エフェクシアマネージャクラス(static)
//    Author : Araki Kai                                作成日 : 2018/08/30
//
//================================================================================

#ifndef	_EFFEKSEER_MANAGER_H_
#define _EFFEKSEER_MANAGER_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>
#include <vector>
#include <unordered_map>

#include "../EffekseerArray/EffekseerArray.h"
#include "../EffekseerObject/EffekseerObject.h"



//======================================================================
//
// クラス定義
//
//======================================================================

class EffekseerManager
{
//------------------------------------------------------------
private :
	static const std::string DEFAULT_PATH;
	static const int MAX_SPRITE_NUM;


//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	EffekseerManager() = delete;

	// コピーコンストラクタ
	EffekseerManager(const EffekseerManager& class_name) = delete;

	// 代入演算子のオーバーロード
	EffekseerManager& operator = (const EffekseerManager& class_name) = delete;


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

	// 更新
	static void Update();

	// 描画
	static void Draw();

	// 追加関数
	static void AddShareData (const std::string* key_name, const std::string* file_path = nullptr);
	static void AddUniqueData(const std::string* key_name, const std::string* file_path = nullptr);

	// プロジェクション行列
	static void CreateProjectionMatrix(int angle_of_view_);

	// ビュー行列
	static void CreateViewMatrix(Vec3 position, Vec3 look_at_point, Vec3 camera_up);

	// 使い捨てエフェクシアオブジェクトの作成
	static void CreateDisposableEffekseerObject(const std::string* key_name, Vec3 position, Vec3 scale = Vec3(1.0f, 1.0f, 1.0f));

	// 参照エフェクシアオブジェクトの取得
	static EffekseerObject* GetReferenceEffekseerObject(const std::string* key_name);


//------------------------------------------------------------
private :
	static std::string MakeFilePath(const std::string* key_name, const std::string* file_path);
	static EffekseerObject* GetReferenceEffekseerObjectFromArray(EffekseerArray* effekseer_array);
	static void CreateDisposableEffekseerObjectFromArray(EffekseerArray* effekseer_array, Vec3 position, Vec3 scale);

//------------------------------------------------------------
private :
	// メンバ変数
	static std::unordered_map<std::string, EffekseerArray*> share_effekseer_map_;
	static std::unordered_map<std::string, EffekseerArray*> unique_effekseer_map_;

	// エフェクシア用行列
	static Effekseer::Matrix44 projection_matrix_;
	static Effekseer::Matrix44 view_matrix_;
};



#endif