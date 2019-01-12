//================================================================================
//!	@file	 BackBuffer.h
//!	@brief	 バックバッファーClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_BACK_BUFFER_H_
#define _BACK_BUFFER_H_



//****************************************
// インクルード文
//****************************************
#include "../../Fade/Fade.h"
#include <LimitedPointerArray\LimitedPointerArray.h>
#include <ComponentManager/DrawManager/RenderTexture/RenderTexture.h>



//****************************************
// クラス宣言
//****************************************
class Camera;
class DrawBase;
class Fade;
class ShaderManager;



//************************************************************														   
//! @brief   バックバッファーClass
//!
//! @details バックバッファーへ描画する描画基底クラスを管理するClass
//************************************************************
class BackBuffer
{
//====================
// 定数
//====================
public:
	static const unsigned ARRAY_NUM = 10000;	//!< 配列数


//====================
// 変数
//====================
private:
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_opacity_draw_;		//!< 不透明配列
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_transparency_draw_;	//!< 透明配列
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_2D_draw_;				//!< 2D配列

	Camera* camera_ = false;	//!< カメラ

	Fade* fade_ = false;		//!< フェード
	bool  is_fade_ = false;		//!< フェード中フラグ

	ShaderManager* shader_manager_ = nullptr;	//!< シェーダーマネージャ

	LPDIRECT3DTEXTURE9 main_screen_texture_;
	LPDIRECT3DSURFACE9 main_screen_surface_;

	LPDIRECT3DTEXTURE9 post_effect_texture_;
	LPDIRECT3DSURFACE9 post_effect_surface_;

	LPDIRECT3DSURFACE9 back_buffer_surface_;

	RenderTexture render_texture_;


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief カメラ取得関数
	//! @details
	//! @param void なし
	//! @retval Camera* カメラ
	//----------------------------------------
	Camera* getpCamera();
	
	//----------------------------------------
	//! @brief シェーダーマネージャ設定関数
	//! @details
	//! @param value シェーダーマネージャ
	//! @retval void なし
	//----------------------------------------
	void setShaderManager(ShaderManager* value);


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
	//! @brief シーン変更時の終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitWhenChangeScene();

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
	//! @brief 描画基底クラスの追加関数
	//! @details
	//! @param draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void AddDrawBaseToArray(DrawBase* draw);

	//----------------------------------------
	//! @brief 全配列のリセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetAllArray();

	//----------------------------------------
	//! @brief フェード初期化関数
	//! @details
	//! @param type  タイプ
	//! @param state ステート
	//! @param size  拡縮
	//! @param color 色
	//! @param speed フェード速度
	//! @retval void なし
	//----------------------------------------
	void InitFade(Fade::Type type, Fade::State state, Vec2 size,
				  XColor4 fade_color, float fade_speed);

	//----------------------------------------
	//! @brief フェード終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitFade();

	//----------------------------------------
	//! @brief フェード終了かの確認関数
	//! @details
	//! @param void なし
	//! @retval bool フェード終了かの有無
	//----------------------------------------
	bool IsFadeEnd();

	//----------------------------------------
	//! @brief フェードステートの名前判定関数
	//! @details
	//! @param state ステート
	//! @retval bool ステートと合っていればtrue
	//----------------------------------------
	bool IsFadeStateName(Fade::State state);

private:
	//----------------------------------------
	//! @brief 透明描画基底クラスのソート関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SortTransparent();

	//----------------------------------------
	//! @brief 2D描画基底クラスのソート関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Sort2D();

	//----------------------------------------
	//! @brief ビルボード用行列変更関数
	//! @details
	//! @param draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void SetBillboardMatrix(DrawBase* draw);
	
	//----------------------------------------
	//! @brief 全ビルボード更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AllBillboardUpdate();

	//----------------------------------------
	//! @brief フェード描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void FadeDraw();
};



#endif
