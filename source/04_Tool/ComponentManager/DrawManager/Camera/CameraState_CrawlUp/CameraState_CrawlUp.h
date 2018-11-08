//================================================================================
//
//    這いつくばりカメラステート
//    Author : Araki Kai                                作成日 : 2018/03/21
//
//================================================================================

#ifndef	_CAMERA_STATE_CRAWL_UP_H_
#define _CAMERA_STATE_CRAWL_UP_H_



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "../Camera.h"





//**********************************************************************
//
// クラス定義
//
//**********************************************************************

class CameraState_CrawlUp : public Camera::State
{
// ============================================================
private :
	// 定数
	const float TRANSLATION_SPEED;
	const float ROTATION_SPEED;
	const float POSITION_Y;
	const float LOOK_AT_POSITION_Y;

// ============================================================
public :
	// コンストラクタ
	CameraState_CrawlUp();


// ============================================================
public :
	// デストラクタ
	~CameraState_CrawlUp();


// ============================================================
public :
	// メンバ関数
	void Init  (Camera* camera) override;
	void Uninit(Camera* camera) override {camera = camera;}
	void Update(Camera* camera) override;
};



#endif