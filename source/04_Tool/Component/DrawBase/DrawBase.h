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
#include "DrawOrderList/DrawOrderList.h"
#include <ComponentManager/DrawManager/Camera/Camera.h>

#include <Vector3D.h>

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
class DrawBase : public ComponentBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	DrawOrderList draw_order_list_;	//!< 描画注文リスト

protected:
	Camera::Type save_camera_type_ = Camera::Type::NONE;	//!< カメラタイプ保存用


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~DrawBase() {}

	/**
	* @brief
	* 描画関数
	*/
	virtual void Draw(unsigned object_index, unsigned mesh_index) = 0;

	/**
	* @brief
	* デバッグ表示関数
	*/
	virtual void DebugDisplay() {}

	/**
	* @brief
	* 限定カメラタイプ変更関数
	*/
	virtual void LimitedChangeCameraType(Camera* camera, unsigned object_index) { camera = camera; object_index = object_index; }

	/**
	* @brief
	* カメラタイプ復活関数
	*/
	void RevivalCameraType(Camera* camera)
	{
		if (save_camera_type_ == Camera::Type::NONE) return;
		camera->SetType(save_camera_type_);
	}

	// プロパティ
	virtual unsigned GetDrawObjectNum() { return 1; }
	virtual unsigned GetMeshNum(unsigned object_index) { object_index = object_index; return 1; }
	virtual const MATRIX* GetMatrix(unsigned object_index) = 0;
	virtual D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index) { object_index = object_index; mesh_index = mesh_index; return nullptr; }
	virtual LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) { object_index = object_index; mesh_index = mesh_index; return nullptr; }
	virtual LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned object_index, unsigned mesh_index) { object_index = object_index; mesh_index = mesh_index; return nullptr; }
	DrawOrderList* GetDrawOrderList() { return &draw_order_list_; }
};



#endif