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
#include "Camera\Camera.h"
#include "Camera\CameraState_CrawlUp\CameraState_CrawlUp.h"
#include "Camera\CameraState_HomingTarget\CameraState_HomingTarget.h"

#include "Fade\Fade.h"

#include <LimitedPointerArray\LimitedPointerArray.h>



//****************************************
// クラス宣言
//****************************************
class DrawBase;
class GameObjectBase;



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
	static const unsigned CAMERA_ARRAY_NUM = 4;		//!< カメラ配列数



//==============================
// 非静的メンバ変数
//==============================
private:
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_draw_;		//!< 全描画配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_add_;		//!< 追加待ち配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_release_;	//!< 解放待ち配列

	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_opacity_draw_;		//!< 不透明配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_transparent_draw_;	//!< 透明配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_2D_draw_;			//!< 2D配列

	LimitedPointerArray<Camera*, CAMERA_ARRAY_NUM> all_camera_;	//!< カメラ配列

	Fade* fade_;		//!< フェード
	bool  is_fade_;	//!< フェード中フラグ


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

	/**
	* @brief
	* デフォルトカメラの作成関数
	*/
	void CreateDefaultCamera(Camera::State* camera_state = nullptr,
							 Camera::Type camra_type = Camera::Type::NORMAL);

	/**
	* @brief
	* カメラの追加関数
	*/
	void AddCamera(Camera::State* camera_state = nullptr,
				   Camera::Type camra_type = Camera::Type::NORMAL);

	/**
	* @brief
	* カメラの解放関数
	*/
	void ReleaseCamera(unsigned index);

	/**
	* @brief
	* カメラのステート変更関数
	*/
	void ChangeCameraState(unsigned index, Camera::State* camera_state);

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
	Camera* GetCamera(unsigned index) { return all_camera_.GetArrayObject(index); }

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
	* 更新関数
	*/
	void Update(unsigned index);

	/**
	* @brief
	* 描画コンポーネント配列のリセット関数
	*/
	void ResetDrawComponentArray();

	/**
	* @brief
	* 描画コンポーネント振り分け関数
	*/
	void DistributeDrawComponent(unsigned index);

	/**
	* @brief
	* 透明描画コンポーネントのソート関数
	*/
	void SortTransparent(unsigned index);

	/**
	* @brief
	* ビルボード用行列変更関数
	*/
	void SetBillboardMatrix(DrawBase* draw, unsigned index);

	/**
	* @brief
	* 各パイプライン描画関数
	*/
	void DrawEachPipeline(LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM>* draw,
						  unsigned index);

	/**
	* @brief
	* ノーマルカメラパイプライン関数
	*/
	void NormalCameraPipeline(unsigned index);

	/**
	* @brief
	* フェードの更新及び描画関数
	*/
	void FadeUpdate_Draw();
};



#endif
