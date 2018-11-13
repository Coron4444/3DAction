//================================================================================
//
//    スコア描画クラス
//    Author : Araki Kai                                作成日 : 2018/06/20
//
//================================================================================

#ifndef	_SCORE_DRAW_H_
#define _SCORE_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../Score.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class ScoreDraw : public DrawBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()   override;
	void Uninit() override;
	void Draw(unsigned object_index, unsigned mesh_index) override;

	const MATRIX* GetMatrix(unsigned object_index) override;
};



#endif