//================================================================================
//
//    ゴール描画クラス
//    Author : Araki Kai                                作成日 : 2018/11/28
//
//================================================================================

#ifndef	_GOAL_DRAW_H_
#define _GOAL_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include <string>

#include "../Goal.h"

#include <Polygon\CubePolygon\CubePolygon.h>



//****************************************
// クラス宣言
//****************************************
class EffekseerObject;


/*********************************************************//**
* @brief
* ゴール描画クラス
*
* ゴールの描画クラス
*************************************************************/
class GoalDraw : public DrawNull
{
//==============================
// 定数
//==============================
private:
	static const std::string EFFECT;			//!< エフェクト名


//==============================
// 非静的メンバ変数
//==============================
private:
	Goal* goal_;	//!< ゴール
	CubePolygon* cube_polygon_;		//!< キューブポリゴン
	EffekseerObject* effekseer_object_;	//!< エフェクシアオブジェクト

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
	* 更新関数
	*/
	virtual void Update() override;

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