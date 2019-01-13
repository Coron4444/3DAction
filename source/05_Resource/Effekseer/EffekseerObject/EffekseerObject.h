//================================================================================
//!	@file	 EffekseerObject.h
//!	@brief	 エフェクシアオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_EFFEKSEER_OBJECT_H_
#define _EFFEKSEER_OBJECT_H_



//****************************************
// インクルード文
//****************************************
#include <string>
#include <vector>
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4099)
#include <Effekseer/Effekseer.h>
#include <Effekseer/EffekseerRendererDX9.h>
#pragma warning(pop)

#include <Vector3D.h>
#include <Transform\Transform.h>



//************************************************************														   
//! @brief   エフェクシアオブジェクトClass
//!
//! @details エフェクシアのオブジェクトClass
//************************************************************
class EffekseerObject
{
//====================
// 定数
//====================
private:
	static const int MAX_SPRITE_NUM;	//!< 最大スプライト数


//====================
// 変数
//====================
private:
	EffekseerRendererDX9::Renderer* effekseer_renderer_ = nullptr;	//!< レンダラー
	Effekseer::Manager*	effekseer_manager_ = nullptr;				//!< マネージャ
	Effekseer::Effect* effekseer_effect_ = nullptr;					//!< エフェクト
	Effekseer::Handle effekseer_handle_;							//!< ハンドル
	Effekseer::Matrix43	world_matrix_;								//!< 行列
	bool is_disposable_ = false;	//!< 使い捨てフラグ
	bool is_playing_ = false;		//!< 再生フラグ
	bool is_pause_ = false;			//!< 停止フラグ
	bool is_repeat_ = false;		//!< リピートフラグ
	Transform transform_;			//!< 変形
	std::string map_key_name_;		//!< マップ用キー名
	int reference_counter_ = 0;		//!< 参照カウンタ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 使い捨てフラグ設定関数
	//! @details
	//! @param value 使い捨てフラグの値 
	//! @retval void なし
	//----------------------------------------
	void setDisposable(bool value);

	//----------------------------------------
	//! @brief 再生中フラグ取得関数
	//! @details
	//! @param void なし 
	//! @retval bool 再生中の有無
	//----------------------------------------
	bool getpIsPlaying();

	//----------------------------------------
	//! @brief リピートフラグ設定関数
	//! @details
	//! @param value リピートフラグの値
	//! @retval void なし
	//----------------------------------------
	void setIsRepeat(bool value);

	//----------------------------------------
	//! @brief 変形取得関数
	//! @details
	//! @param void なし 
	//! @retval Transform* 変形
	//----------------------------------------
	Transform* getpTransform();

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *file_path    ファイルパス
	//! @param *map_key_name マップ用キー名
	//! @retval void なし
	//----------------------------------------
	void Init(std::string* file_path, const std::string* map_key_name);

	//----------------------------------------
	//! @brief 解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Release();

	//----------------------------------------
	//! @brief 強制解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ForcedRelease();

	//----------------------------------------
	//! @brief 参照カウンタ追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddReferenceCounter();

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
	//! @brief 再生関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Play();

	//----------------------------------------
	//! @brief 停止関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Stop();

	//----------------------------------------
	//! @brief 一時停止関数
	//! @details
	//! @param is_pause 一時停止フラグ
	//! @retval void なし
	//----------------------------------------
	void Pause(bool is_pause);

	//----------------------------------------
	//! @brief 速度変更関数
	//! @details
	//! @param velocity 速度
	//! @retval void なし
	//----------------------------------------
	void ChangeVelocity(float velocity);

	//----------------------------------------
	//! @brief 色変更関数
	//! @details
	//! @param r 赤
	//! @param g 緑
	//! @param b 青
	//! @param a 透過度
	//! @retval void なし
	//----------------------------------------
	void ChangeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	//----------------------------------------
	//! @brief ビュー行列変更関数
	//! @details
	//! @param velocity 速度
	//! @retval void なし
	//----------------------------------------
	void ChangeViewMatrix(Effekseer::Matrix44* view_matrix);

	//----------------------------------------
	//! @brief プロジェクション行列変更関数
	//! @details
	//! @param velocity 速度
	//! @retval void なし
	//----------------------------------------
	void ChangeProjectionMatrix(Effekseer::Matrix44* projection_matrix);
	
private:
	//----------------------------------------
	//! @brief レンダラー&マネージャ生成関数
	//! @details
	//! @param *file_path ファイルパス
	//! @retval void なし
	//----------------------------------------
	void CreateRendererAndManager();

	//----------------------------------------
	//! @brief エフェクト生成関数
	//! @details
	//! @param *file_path ファイルパス
	//! @retval void なし
	//----------------------------------------
	void CreateEffect(std::string* file_path);

	//----------------------------------------
	//! @brief ワールド行列変更関数
	//! @details
	//! @param *file_path ファイルパス
	//! @retval void なし
	//----------------------------------------
	void ChangeWorldMatrix(MATRIX* world_matrix);
};



#endif