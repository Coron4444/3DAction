//================================================================================
//
//    空白描画クラス
//    Author : Araki Kai                                作成日 : 2018/03/22
//
//================================================================================

#ifndef	_DRAW_NULL_H_
#define _DRAW_NULL_H_



//****************************************
// インクルード文
//****************************************
#include <assert.h>
#include "../../Base/DrawBase/DrawBase.h"



/*********************************************************//**
* @brief
* 空白描画クラス
*
* 描画の空白クラス
*************************************************************/
class DrawNull : public DrawBase
{
//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~DrawNull() {}

	/**
	* @brief
	* 初期化関数
	*/
	virtual void Init() override {}

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit() override {}

	/**
	* @brief
	* 更新関数
	*/
	virtual void Update() {}

	/**
	* @brief
	* 描画関数
	* @param
	* object_index : オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	virtual void Draw(unsigned object_index, unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;

		assert("描画関数が未実装です");
	}

	/**
	* @brief
	* デバッグ表示関数
	*/
	virtual void DebugDisplay() override {}

	/**
	* @brief
	* 描画前設定関数
	* @param
	* camera : カメラ
	* object_index : オブジェクトインデックス
	*/
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) override
	{
		camera = camera;
		object_index = object_index;
	}

	/**
	* @brief
	* 描画後設定関数
	* @param
	* camera : カメラ
	* object_index : オブジェクトインデックス
	*/
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) override
	{
		camera = camera;
		object_index = object_index;
	}

	// プロパティ
	virtual unsigned GetObjectNum() override { return 1; }
	virtual unsigned GetMeshNum(unsigned object_index) override
	{
		object_index = object_index;
		return 1;
	}
	virtual const MATRIX* GetMatrix(unsigned object_index) override
	{
		object_index = object_index;
		assert("行列取得プロパティが未実装です");
		return nullptr;
	}
	virtual D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index)
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
	virtual LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index)
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
	virtual LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned object_index, unsigned mesh_index)
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
};



#endif