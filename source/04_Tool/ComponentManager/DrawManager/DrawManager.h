//================================================================================
//
//    描画マネージャークラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
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
class BackBuffer;
class ShaderManager;


/*********************************************************//**
* @brief
* 描画マネージャークラス
*
* 登録されている描画基底クラスを管理するクラス
*************************************************************/
class DrawManager
{
//==============================
// 定数
//==============================
public:
	static const unsigned DRAW_ARRAY_NUM = 1000;	//!< 描画配列数


//==============================
// 非静的メンバ変数
//==============================
private:
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_draw_;		//!< 全描画配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_add_;		//!< 追加待ち配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_release_;	//!< 解放待ち配列

	ShaderManager* shader_manager_ = nullptr;	//!< シェーダーマネージャ
	BackBuffer* back_buffer_ = nullptr;			//!< バックバッファ

	Vec3 directional_light_vector_ = {0.5f, -1.0f, 0.8f};		//!< 拡散反射光ベクトル


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
	* 終了関数
	*/
	void Uninit();

	/**
	* @brief
	* シーン変更時の終了関数
	*/
	void UninitWhenChangeScene();

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
	* 描画基底クラスの上書き関数
	*/
	void OverwriteArrayDrawBase(GameObjectBase* game_object,
								DrawBase* new_draw);

	/**
	* @brief
	* 描画基底クラスの解放関数
	*/
	void ReleaseDrawBaseFromArray(DrawBase* draw);

	// プロパティ
	const Vec3* GetDirectionalLightVector() { return &directional_light_vector_; }
	void SetDirectionalLightVector(Vec3 value) { directional_light_vector_ = value; }
	BackBuffer* GetBackBuffer() { return back_buffer_; }


private:
	/**
	* @brief
	* 追加待ち配列の中身を追加関数
	*/
	void AddContentsOfAwaitAddArray();

	/**
	* @brief
	* 解放待ち配列の中身を解放関数
	*/
	void ReleaseContentsOfAwaitReleaseArray();

	/**
	* @brief
	* 全レンダーターゲット更新関数
	*/
	void UpdateAllRenderTarget();

	/**
	* @brief
	* 全レンダーターゲットリセット関数
	*/
	void ResetAllRenderTarget();

	/**
	* @brief
	* 描画基底クラス振り分け関数
	*/
	void DistributeDrawBase();
};



#endif
