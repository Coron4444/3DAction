//================================================================================
//
//    敵描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================

#ifndef	_ENEMY_DRAW_H_
#define _ENEMY_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Enemy.h"



/*********************************************************//**
* @brief
* 敵描画クラス
*
* 敵の描画クラス
*************************************************************/
class EnemyDraw : public DrawNull
{
//==============================
// 非静的メンバ関数
//==============================
private:
	Enemy* enemy_;				//!< 敵


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
	unsigned getMeshNum(unsigned object_index) override;
	MATRIX* getpMatrix(unsigned object_index) override;
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;
};



#endif