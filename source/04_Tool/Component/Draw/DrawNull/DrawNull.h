//================================================================================
//!	@file	 DrawNull.h
//!	@brief	 空白描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_DRAW_NULL_H_
#define _DRAW_NULL_H_



//****************************************
// インクルード文
//****************************************
#include <assert.h>

#include "../../Base/DrawBase/DrawBase.h"



//************************************************************														   
//! @brief   空白描画Class
//!
//! @details 描画の空白Class
//************************************************************
class DrawNull : public DrawBase
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @param void なし
	//----------------------------------------
	virtual ~DrawNull() {}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Init() override {}

	//----------------------------------------
	//! @brief 終了関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() override {}

	//----------------------------------------
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Update() {}

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void DebugDisplay() {}

	//----------------------------------------
	//! @brief 描画関数
	//! @param[in] object_index オブジェクトインデックス
	//! @param[in] mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void Draw(unsigned object_index, unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;

		assert("描画関数が未実装です");
	}

	//----------------------------------------
	//! @brief 描画前設定関数
	//! @param[in, out] camera       カメラ
	//! @param[in]      object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) override
	{
		camera = camera;
		object_index = object_index;
	}

	//----------------------------------------
	//! @brief 描画後設定関数
	//! @param[in, out] camera       カメラ
	//! @param[in]      object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) override
	{
		camera = camera;
		object_index = object_index;
	}

	// プロパティ
	virtual unsigned getObjectNum() override { return 1; }
	virtual unsigned getMeshNum(unsigned object_index) override
	{
		object_index = object_index;
		return 1;
	}
	virtual MATRIX* getpMatrix(unsigned object_index) override
	{
		object_index = object_index;
		assert("行列取得プロパティが未実装です");
		return nullptr;
	}
	virtual D3DMATERIAL9* getpMaterial(unsigned object_index, 
									   unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
	virtual LPDIRECT3DTEXTURE9 getpDecaleTexture(unsigned object_index, 
												 unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
	virtual LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index, 
												unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
};



#endif