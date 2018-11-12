//================================================================================
//
//    敵クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================

#ifndef	_ENEMY_H_
#define _ENEMY_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <GameObjectBase/GameObjectBase.h>

#include <Polygon\CubePolygon\CubePolygon.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Enemy : public GameObjectBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(UpdateBase*    update,
			  DrawBase*      draw,
			  CollisionBase* collision);
	void Uninit() override;
	void Reset()  override;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ変数
	CubePolygon* cube_polygon_;
};



#endif