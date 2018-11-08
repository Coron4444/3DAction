//================================================================================
//
//    コンポーネント基底クラス
//    Author : Araki Kai                                作成日 : 2018/03/30
//
//================================================================================

#ifndef	_COMPONENT_BASE_H_
#define _COMPONENT_BASE_H_



//****************************************
// インクルード文
//****************************************
#include <Vector3D.h>
#include <Renderer\RendererDirectX9\RendererDirectX9.h>



//****************************************
// クラス宣言
//****************************************
class GameObjectBase;



/*********************************************************//**
* @brief
* コンポーネント基底クラス
*
* コンポーネントの基底クラス
*************************************************************/
class ComponentBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	GameObjectBase* game_object_;		//!< ゲームオブジェクト

//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~ComponentBase(){}

	/**
	* @brief
	* 初期化関数
	*/
	virtual void Init()	  = 0;

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit() = 0;

	// プロパティ
	void SetGameObject(GameObjectBase* value){game_object_ = value;}
	GameObjectBase* GetGameObject(){return game_object_;}
};



#endif