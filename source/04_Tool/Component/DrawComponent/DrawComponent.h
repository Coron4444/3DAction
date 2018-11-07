//================================================================================
//
//    描画コンポーネントクラス
//    Author : Araki Kai                                作成日 : 2018/03/22
//
//================================================================================

#ifndef	_DRAW_COMPONENT_H_
#define _DRAW_COMPONENT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../ComponentOrigin/ComponentOrigin.h"

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



//======================================================================
//
// クラス定義
//
//======================================================================

class DrawComponent : public ComponentOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ステート
	enum State
	{
		NONE = -1,
		FIXED,
		FIXED_ALPHA,
		FIXED_BILLBOARD,
		FIXED_BILLBOARD_ALPHA,
		FIXED_2D,
		TEST_SHADER,
		TEST_SHADER_BILLBOARD,
		MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 仮想デストラクタ
	virtual ~DrawComponent(){}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	virtual void Draw(unsigned mesh_index) = 0;

	// デバッグ
	virtual void Debug(){}

	virtual unsigned		   GetMeshNum()							{return 1;}
	virtual D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		{mesh_index = mesh_index; return nullptr;}
	virtual LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index){mesh_index = mesh_index; return nullptr;}
	virtual LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned mesh_index){mesh_index = mesh_index; return nullptr;}


	// 状態
	DrawComponent::State GetState(){return state_;}
	void SetState(DrawComponent::State state){state_ = state;}


//------------------------------------------------------------
private :
	// メンバ変数
	DrawComponent::State state_ = NONE;
};



#endif