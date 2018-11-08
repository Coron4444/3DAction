//================================================================================
//
//    描画基底クラス
//    Author : Araki Kai                                作成日 : 2018/03/22
//
//================================================================================

#ifndef	_DRAW_BASE_H_
#define _DRAW_BASE_H_



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
* 描画基底クラス
*
* 描画の基底クラス
*************************************************************/
class DrawComponent : public ComponentBase
{
//==============================
// 列挙型定義
//==============================
public:
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


//==============================
// 非静的メンバ変数
//==============================
private:
	DrawComponent::State state_ = NONE;		//!< ステート


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~DrawComponent() {}

	/**
	* @brief
	* 描画関数
	*/
	virtual void Draw(unsigned mesh_index) = 0;

	/**
	* @brief
	* デバッグ表示関数
	*/
	virtual void Debug() {}

	// プロパティ
	virtual unsigned GetMeshNum() { return 1; }
	virtual D3DMATERIAL9* GetMaterial(unsigned mesh_index) { mesh_index = mesh_index; return nullptr; }
	virtual LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index) { mesh_index = mesh_index; return nullptr; }
	virtual LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned mesh_index) { mesh_index = mesh_index; return nullptr; }
	DrawComponent::State GetState() { return state_; }
	void SetState(DrawComponent::State state) { state_ = state; }
};



#endif