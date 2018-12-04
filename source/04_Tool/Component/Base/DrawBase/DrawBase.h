//================================================================================
//!	@file	 DrawBase.h
//!	@brief	 描画BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
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



//************************************************************														   
//! @brief   描画BaseClass
//!
//! @details 描画のBaseClass
//************************************************************
class DrawBase : public ComponentBase
{
//====================
// 変数
//====================
private:
	DrawOrderList draw_order_list_;							//!< 描画注文リスト
	Camera::Type save_camera_type_ = Camera::Type::NONE;	//!< カメラタイプ保存用


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @param void なし
	//----------------------------------------
	virtual ~DrawBase() {}

	//----------------------------------------
	//! @brief 描画関数
	//! @param[in] object_index オブジェクトインデックス
	//! @param[in] mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void Draw(unsigned object_index, unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief 描画前設定関数
	//! @param[in, out] camera       カメラ
	//! @param[in]      object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) = 0;

	//----------------------------------------
	//! @brief 描画後設定関数
	//! @param[in, out] camera       カメラ
	//! @param[in]      object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) = 0;

	//----------------------------------------
	//! @brief 限定カメラタイプ変更関数
	//! @param[in, out] camera  カメラ
	//! @param[in]      type 　 カメラタイプ
	//! @retval void なし
	//----------------------------------------
	void LimitedChangeCameraType(Camera* camera, Camera::Type type)
	{
		save_camera_type_ = camera->GetType();
		camera->SetType(type);
	}

	//----------------------------------------
	//! @brief カメラタイプ復活関数
	//! @param[in, out] camera カメラ
	//! @retval void なし
	//----------------------------------------
	void RevivalCameraType(Camera* camera)
	{
		if (save_camera_type_ == Camera::Type::NONE) return;
		camera->SetType(save_camera_type_);
	}

	// プロパティ
	virtual unsigned getObjectNum() = 0;
	virtual unsigned getMeshNum(unsigned object_index) = 0;
	virtual MATRIX* getpMatrix(unsigned object_index) = 0;
	virtual D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) = 0;
	virtual LPDIRECT3DTEXTURE9 getpDecaleTexture(unsigned object_index, unsigned mesh_index) = 0;
	virtual LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index, unsigned mesh_index) = 0;
	DrawOrderList* getpDrawOrderList() { return &draw_order_list_; }
};



#endif