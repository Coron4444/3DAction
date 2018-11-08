//================================================================================
//
//    描画コンポーネントマネージャークラス(static)
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_DRAW_COMPONENT_MANAGER_H_
#define _DRAW_COMPONENT_MANAGER_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <LimitedPointerArray\LimitedPointerArray.h>

#include "Camera\Camera.h"
#include "Camera\CameraState_CrawlUp\CameraState_CrawlUp.h"
#include "Camera\CameraState_HomingTarget\CameraState_HomingTarget.h"

#include "Fade\Fade.h"



//======================================================================
//
// クラス宣言
//
//======================================================================

class DrawComponent;
class GameObjectOrigin;



//======================================================================
//
// クラス定義
//
//======================================================================

class DrawComponentManager
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 定数
	static const unsigned DRAW_ARRAY_NUM   = 1000;
	static const unsigned CAMERA_ARRAY_NUM = 4;


//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	DrawComponentManager() = delete;

	// コピーコンストラクタ
	DrawComponentManager(const DrawComponentManager& class_name) = delete;

	// 代入演算子のオーバーロード
	DrawComponentManager& operator = (const DrawComponentManager& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メイン
	static void Init();
	static void Uninit();
	static void Uninit_ChangeScene();
	static void Draw();

	// コンポーネント
	static void RegistrationComponent(DrawComponent* draw_component);
	static void OverwriteComponent	 (GameObjectOrigin* game_object, DrawComponent* new_draw_component);
	static void ReleaseComponent	 (DrawComponent* draw_component);


	// カメラ
	static void CreateDefaultCamera(Camera::State* camera_state = nullptr, Camera::Type camra_type = Camera::Type::NORMAL);
	static void AddCamera		   (Camera::State* camera_state = nullptr, Camera::Type camra_type = Camera::Type::NORMAL);
	static void DeleteCamera	   (unsigned index);
	static void ChangeCameraState  (unsigned index, Camera::State* camera_state);
	
	static Camera* GetCamera(unsigned index){return all_camera_.GetArrayObject(index);}


	// フェード
	static void InitFade(Fade::Type type, Fade::State state, Vec2 size, XColor4 fade_color, float fade_speed);
	static void UninitFade();
	
	static bool IsFadeEnd()						  {return fade_->GetEndFlag();}
	static bool IsFadeStateName(Fade::State state){return *fade_->GetState() == state;}


//------------------------------------------------------------
private :
	// メイン
	static void Update(unsigned index);
	static void ResetDrawComponentArray();
	static void DistributeDrawComponent(unsigned index);
	static void SortTransparent		   (unsigned index);
	static void SetBillboardMatrix     (DrawComponent* draw_component, unsigned index);
	static void DrawEachPipeline	   (LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM>* draw_components, unsigned index);

	// カメラ
	static void NormalCameraPipeline(unsigned index);

	// フェード
	static void FadeUpdate_Draw();


//------------------------------------------------------------
private :
	// コンポーネント
	static LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM> all_draw_component_;
	static LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM> all_opacity_draw_component_;
	static LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM> all_transparent_draw_component_;
	static LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM> all_2D_draw_component_;

	// カメラ
	static LimitedPointerArray<Camera*, CAMERA_ARRAY_NUM> all_camera_;

	// フェード
	static Fade* fade_;
	static bool  is_fade_;
};



#endif
