//================================================================================
//!	@file	 ComponentBase.h
//!	@brief	 コンポーネントBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COMPONENT_BASE_H_
#define _COMPONENT_BASE_H_



//****************************************
// インクルード文
//****************************************
#ifdef _DEBUG
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_dx9.h>
#endif



//****************************************
// クラス宣言
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   コンポーネントBaseClass
//!
//! @details コンポーネントのBaseClass
//************************************************************
class ComponentBase
{
//====================
// 変数
//====================
private:
	GameObjectBase* game_object_;		//!< ゲームオブジェクト


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @param void なし
	//----------------------------------------
	virtual ~ComponentBase() {}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Init() = 0;

	//----------------------------------------
	//! @brief 終了関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Update() = 0;

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void DebugDisplay() = 0;

	// プロパティ
	GameObjectBase* getpGameObject() { return game_object_; }
	void setGameObject(GameObjectBase* value) { game_object_ = value; }
};



#endif