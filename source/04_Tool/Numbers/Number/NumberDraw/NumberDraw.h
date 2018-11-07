//================================================================================
//
//    数字描画クラス
//    Author : Araki Kai                                作成日 : 2018/06/19
//
//================================================================================

#ifndef	_NUMBER_DRAW_H_
#define _NUMBER_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../Number.h"
#include <Component\DrawComponent\DrawComponent.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class NumberDraw : public DrawComponent
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()   override;
	void Uninit() override;
	void Draw(unsigned mesh_index) override;

	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// メンバ変数
	Number* number_;
};



#endif