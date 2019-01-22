//================================================================================
//!	@file	 DrawManager.h
//!	@brief	 描画マネージャーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_DRAW_MANAGER_H_
#define _DRAW_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include "RenderTarget/BackBuffer/BackBuffer.h"

#include <LimitedPointerArray\LimitedPointerArray.h>



//****************************************
// クラス宣言
//****************************************
class DrawBase;
class GameObjectBase;
class ShaderManager;



//************************************************************														   
//! @brief   描画マネージャーlass
//!
//! @details 登録されている描画基底クラスを管理するClass
//************************************************************
class DrawManager
{
//====================
// 定数
//====================
public:
	static const unsigned DRAW_ARRAY_NUM = 10000;	//!< 配列数


//====================
// 変数
//====================
private:
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_draw_;		//!< 全描画配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_add_;		//!< 追加待ち配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_release_;	//!< 解放待ち配列

	ShaderManager* shader_manager_ = nullptr;	//!< シェーダーマネージャ
	BackBuffer* back_buffer_ = nullptr;			//!< バックバッファ

	Vec3 directional_light_vector_ = {0.5f, -1.0f, 0.8f};	//!< ディレクショナルライト方向

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief バックバッファ取得関数
	//! @details
	//! @param void なし
	//! @retval BackBuffer* バックバッファ
	//----------------------------------------
	BackBuffer* getpBackBuffer();

	const Vec3* GetDirectionalLightVector() { return &directional_light_vector_; }

//====================
// 関数
//====================
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
	//! @brief シーン変更時の終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitWhenChangeScene();

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
	//! @brief 描画基底クラスの追加関数
	//! @details
	//! @param *draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void AddDrawBaseToArray(DrawBase* draw);

	//----------------------------------------
	//! @brief 描画基底クラスの上書き関数
	//! @details
	//! @param *game_object ゲームオブジェクト
	//! @param *new_draw    新規描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void OverwriteArrayDrawBase(GameObjectBase* game_object,
								DrawBase* new_draw);

	//----------------------------------------
	//! @brief 描画基底クラスの解放関数
	//! @details
	//! @param *draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void ReleaseDrawBaseFromArray(DrawBase* draw);
	
private:
	//----------------------------------------
	//! @brief 追加待ち配列の中身を追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddContentsOfAwaitAddArray();

	//----------------------------------------
	//! @brief 解放待ち配列の中身を解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseContentsOfAwaitReleaseArray();

	//----------------------------------------
	//! @brief 全描画基底クラス更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateAllDrawBase();

	//----------------------------------------
	//! @brief 全レンダーターゲット更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateAllRenderTarget();

	//----------------------------------------
	//! @brief 全レンダーターゲットリセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetAllRenderTarget();

	//----------------------------------------
	//! @brief 描画基底クラス振り分け関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DistributeDrawBase();
};



#endif
