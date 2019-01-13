//================================================================================
//!	@file	 EffekseerManager.h
//!	@brief	 エフェクシアマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_EFFEKSEER_MANAGER_H_
#define _EFFEKSEER_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <string>
#include <list>
#include <unordered_map>

#include "../EffekseerObject/EffekseerObject.h"



//************************************************************														   
//! @brief   エフェクシアマネージャClass
//!
//! @details エフェクシアのマネージャClass(Singleton)
//************************************************************
class EffekseerManager
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
	static EffekseerManager* instance_;	//!< インスタンス


//====================
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval EffekseerManager* インスタンス
	//----------------------------------------
	static EffekseerManager* getpInstance();


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
	std::unordered_map<std::string, EffekseerObject*> object_map_;	//!< オブジェクトマップ
	std::list<EffekseerObject*> disposable_object_;					//!< 使い捨てオブジェクトリスト
	Effekseer::Matrix44 view_matrix_;								//!< ビュー行列
	Effekseer::Matrix44 projection_matrix_;							//!< プロジェクション行列


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval TextureObject* オブジェクト取得
	//----------------------------------------
	EffekseerObject* getpObject(const std::string* key_name,
								const std::string* file_path = nullptr);

	//----------------------------------------
	//! @brief 使い捨てオブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval TextureObject* オブジェクト取得
	//----------------------------------------
	EffekseerObject* getpDisposableObject(const std::string* key_name,
										  const std::string* file_path = nullptr);


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	EffekseerManager();


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
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief マップから解放関数
	//! @details
	//! @param *key_name  キー名
	//! @param *file_path ファイルパス
	//! @retval void なし
	//----------------------------------------
	void ReleaseFromTheMap(std::string* key_name);

	//----------------------------------------
	//! @brief ビュー行列生成関数
	//! @details
	//! @param camera_position カメラ座標
	//! @param look_at_point   注視点
	//! @param camera_up       カメラの上ベクトル
	//! @retval void なし
	//----------------------------------------
	void CreateViewMatrix(Vec3 camera_position, Vec3 look_at_point, Vec3 camera_up);

	//----------------------------------------
	//! @brief プロジェクション行列生成関数
	//! @details
	//! @param angle_of_view_ 画角
	//! @retval void なし
	//----------------------------------------
	void CreateProjectionMatrix(int angle_of_view_);

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
};



#endif