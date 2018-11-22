//================================================================================
//
//    フェードクラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================

#ifndef	_RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include <Transform\Transform.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <Texture\TextureManager\TextureManager.h>



/*********************************************************//**
* @brief
* フェードクラス
*
* フェードのクラス
*************************************************************/
class RenderTexture : public DrawNull
{
//==============================
// 非静的メンバ変数
//==============================
private:
	PlanePolygon* plane_polygon_;		//!< 板ポリゴン
	Transform transform_;				//!< 状態

//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init()
	{		
		plane_polygon_ = new PlanePolygon();
	}

	/**
	* @brief
	* 終了関数
	*/
	void Uninit() override
	{
		SafeRelease::Normal(&plane_polygon_);
	}

	void Update(float x, float y, XColor4 color)
	{
		transform_.GetPosition()->x = -0.5f;
		transform_.GetPosition()->y = -0.5f;
		transform_.GetScale()->x = x;
		transform_.GetScale()->y = y;
		transform_.UpdateWorldMatrixSRT();

		plane_polygon_->SetColor(color);
	}

	/**
	* @brief
	* 描画関数
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;

		// ポリゴン描画
		plane_polygon_->Draw();
	}

	// プロパティ
	const MATRIX* GetMatrix(unsigned object_index) override
	{
		object_index = object_index;
		return transform_.GetMatrixExtend()->GetWorldMatrix();
	}

	D3DMATERIAL9* GetMaterial()
	{
		return plane_polygon_->GetMaterial();
	}
};



#endif