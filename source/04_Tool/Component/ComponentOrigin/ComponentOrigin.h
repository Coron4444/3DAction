//================================================================================
//
//    コンポーネントの原点クラス
//    Author : Araki Kai                                作成日 : 2018/03/30
//
//================================================================================

#ifndef	_COMPONENT_ORIGIN_H_
#define _COMPONENT_ORIGIN_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <Vector3D.h>
#include <Renderer\RendererDirectX9\RendererDirectX9.h>



//======================================================================
//
// クラス宣言
//
//======================================================================

class GameObjectOrigin;



//======================================================================
//
// クラス定義
//
//======================================================================

class ComponentOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 仮想デストラクタ
	virtual ~ComponentOrigin(){}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	virtual void Init()	  = 0;
	virtual void Uninit() = 0;

	// アクセッサ
	void SetGameObjectOrigin(GameObjectOrigin* game_object_origin){game_object_origin_ = game_object_origin;}
	GameObjectOrigin* GetGameObjectOrigin(){return game_object_origin_;}


//------------------------------------------------------------
private :
	// メンバ変数
	GameObjectOrigin* game_object_origin_;
};



#endif