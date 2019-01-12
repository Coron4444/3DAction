//================================================================================
//
//    スコア描画クラス
//    Author : Araki Kai                                作成日 : 2018/06/20
//
//================================================================================

#ifndef	_SCORE_DRAW_H_
#define _SCORE_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Score.h"



/*********************************************************//**
* @brief
* スコア描画クラス
*
* スコアの描画クラス
*************************************************************/
class ScoreDraw : public DrawNull
{
//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init() override;

	/**
	* @brief
	* 終了関数
	*/
	void Uninit() override;

	/**
	* @brief
	* 描画関数
	* @param
	* object_index : オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override;

	// プロパティ
	MATRIX* getpMatrix(unsigned object_index) override;
};



#endif