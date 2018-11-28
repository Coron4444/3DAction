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

#include <GameObjectBase/GameObjectBase.h>

#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Coin : public GameObjectBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(DrawBase*      draw,
			  CollisionBase* collision);
	void Uninit() override;
	void Reset()  override;

	PlanePolygon* GetPolygon(){return polygon_;}

	int getCount() { return count_; }
	void setCount(int value) { count_ = value; }

//------------------------------------------------------------
private :
	// 公開メンバ変数
	PlanePolygon* polygon_;
	int count_ = 0;
};



#endif