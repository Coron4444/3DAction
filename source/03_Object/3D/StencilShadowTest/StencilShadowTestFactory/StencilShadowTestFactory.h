//================================================================================
//
//    プレイヤーファクトリークラス
//    Author : Araki Kai                                作成日 : 2018/07/23
//
//================================================================================

#ifndef	_STENCIL_SHADOW_TEST_FACTORY_H_
#define _STENCIL_SHADOW_TEST_FACTORY_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../StencilShadowTest.h"
#include "../StencilShadowTestDraw/StencilShadowTestDraw.h"



//======================================================================
//
// クラス定義
//
//======================================================================

class StencilShadowTestFactory
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	StencilShadowTest* Create()
	{
		StencilShadowTest* temp = new StencilShadowTest();

		// 初期化
		temp->Init(new StencilShadowTestDraw());

		return temp;
	}
};



#endif