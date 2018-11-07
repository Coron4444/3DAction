//================================================================================
//
//    コインクラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================

#ifndef	_COIN_H_
#define _COIN_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Coin : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(DrawComponent*      draw_component,
			  CollisionComponent* collision_component);
	void Uninit() override;
	void Reset()  override;

	PlanePolygon* GetPolygon(){return polygon_;}


//------------------------------------------------------------
private :
	// 公開メンバ変数
	PlanePolygon* polygon_;
};



#endif