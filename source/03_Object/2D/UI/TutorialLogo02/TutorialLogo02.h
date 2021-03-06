//================================================================================
//
//    チュートリアルロゴ02クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_02_H_
#define _TUTORIAL_LOGO_02_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>



//======================================================================
//
// クラス宣言
//
//======================================================================

class PlanePolygon;



//======================================================================
//
// クラス定義
//
//======================================================================

class TutorialLogo02 : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(DrawComponent* draw_component);
	void Uninit() override;
	void Reset()  override;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ変数
	PlanePolygon*    plane_polygon_;
};



#endif