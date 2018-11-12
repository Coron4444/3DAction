//================================================================================
//
//    チュートリアルロゴ02クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "TutorialLogo02.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo02::Init(DrawBase* draw)
{
	// プレーンポリゴン作成
	plane_polygon_ = new PlanePolygon();

	// 基底クラスの初期化
	GameObjectBase::Init(nullptr, draw, nullptr);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo02::Uninit()
{
	// 基底クラスの終了処理
	GameObjectBase::Uninit();

	// 各種開放
	SafeRelease::Normal(&plane_polygon_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Reset処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo02::Reset()
{

}