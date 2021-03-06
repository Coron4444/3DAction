//================================================================================
//
//    スコア更新クラス
//    Author : Araki Kai                                作成日 : 2018/06/20
//
//================================================================================

#ifndef	_SCORE_UPDATE_H_
#define _SCORE_UPDATE_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <Component\UpdateComponent\UpdateComponent.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class ScoreUpdate : public UpdateComponent
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 定数
	static const Vec2 SCORE_POSITION;
	static const Vec2 SCORE_SCALE;
	static const XColor4 SCORE_COLOR;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()		  override;
	void Uninit()	  override;
	void Update()	  override;
	void LateUpdate() override;
};



#endif