//================================================================================
//
//    敵描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================

#ifndef	_ENEMY_DRAW_H_
#define _ENEMY_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../Enemy.h"

#include <Component\DrawComponent\DrawComponent.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class EnemyDraw : public DrawComponent
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()					   override;
	void Uninit()				   override;
	void Draw(unsigned mesh_index) override;

	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		 override;
};



#endif