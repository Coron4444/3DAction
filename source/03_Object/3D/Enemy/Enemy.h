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

#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Polygon\CubePolygon\CubePolygon.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Enemy : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(UpdateComponent*    update_component,
			  DrawComponent*      draw_component,
			  CollisionComponent* collision_component);
	void Uninit() override;
	void Reset()  override;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ変数
	CubePolygon* cube_polygon_;
};



#endif