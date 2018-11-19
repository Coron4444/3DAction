//================================================================================
//
//    更新基底クラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_UPDATE_BASE_H_
#define _UPDATE_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "../ComponentBase/ComponentBase.h"

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



/*********************************************************//**
* @brief
* 更新基底クラス
*
* 更新の基底クラス
*************************************************************/
class UpdateBase : public ComponentBase
{
//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~UpdateBase() {}

	/**
	* @brief
	* 更新関数
	*/
	virtual void Update() = 0;

	/**
	* @brief
	* 後更新関数
	*/
	virtual void LateUpdate() = 0;

	/**
	* @brief
	* デバッグ表示関数
	*/
	virtual void DebugDisplay() = 0;
};



#endif