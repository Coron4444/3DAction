//================================================================================
//
//    バックバッファークラス
//    Author : Araki Kai                                作成日 : 2018/11/12
//
//================================================================================

#ifndef	_BACK_BUFFER_H_
#define _BACK_BUFFER_H_



//****************************************
// インクルード文
//****************************************
#include "../../Camera/Camera.h"
#include "../../Camera/CameraState_CrawlUp/CameraState_CrawlUp.h"
#include "../../Camera/CameraState_HomingTarget/CameraState_HomingTarget.h"

#include "../../Fade/Fade.h"

#include <LimitedPointerArray\LimitedPointerArray.h>



//****************************************
// クラス宣言
//****************************************
class DrawBase;
class ShaderManager;



/*********************************************************//**
* @brief
* バックバッファークラス
*
* バックバッファーへ描画する描画基底クラスを管理するクラス
*************************************************************/
class BackBuffer
{
//==============================
// 定数
//==============================
public:
	static const unsigned ARRAY_NUM = 1000;	//!< 配列数



//==============================
// 非静的メンバ変数
//==============================
private:
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_opacity_draw_;		//!< 不透明配列
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_transparency_draw_;	//!< 透明配列
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_2D_draw_;				//!< 2D配列

	Camera* camera_ = false;	//!< カメラ

	Fade* fade_ = false;		//!< フェード
	bool  is_fade_ = false;		//!< フェード中フラグ

	ShaderManager* shader_manager_ = nullptr;	//!< シェーダーマネージャ


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init();

	/**
	* @brief
	* シーン変更時の終了関数
	*/
	void UninitWhenChangeScene();

	/**
	* @brief
	* 終了関数
	*/
	void Uninit();

	/**
	* @brief
	* 更新関数
	*/
	void Update();

	/**
	* @brief
	* 描画関数
	*/
	void Draw();

	/**
	* @brief
	* 描画基底クラスの追加関数
	*/
	void AddDrawBaseToArray(DrawBase* draw);

	/**
	* @brief
	* 全配列のリセット関数
	*/
	void ResetAllArray();

	/**
	* @brief
	* フェード初期化関数
	*/
	void InitFade(Fade::Type type, Fade::State state, Vec2 size, XColor4 fade_color,
				  float fade_speed);

	/**
	* @brief
	* フェード終了関数
	*/
	void UninitFade();

	/**
	* @brief
	* フェード終了かの確認関数
	*/
	bool IsFadeEnd() { return fade_->GetEndFlag(); }

	/**
	* @brief
	* フェードステートの名前判定関数
	*/
	bool IsFadeStateName(Fade::State state) { return *fade_->GetState() == state; }

	// プロパティ
	Camera* GetCamera() { return camera_; }
	void SetShaderManager(ShaderManager* value) { shader_manager_ = value; }

private:
	/**
	* @brief
	* 透明描画コンポーネントのソート関数
	*/
	void SortTransparent();

	/**
	* @brief
	* ビルボード用行列変更関数
	*/
	void SetBillboardMatrix(DrawBase* draw);
	
	/**
	* @brief
	* 全ビルボード更新関数
	*/
	void AllBillboardUpdate();

	/**
	* @brief
	* フェード描画関数
	*/
	void FadeDraw();
};



#endif
