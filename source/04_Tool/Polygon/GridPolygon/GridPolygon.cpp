//================================================================================
//
//    グリッドポリゴンクラス
//    Author : Araki Kai                                作成日 : 2017/10/16
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "GridPolygon.h"

#include <Vector3D.h>
#include <SafeRelease/SafeRelease.h>



//**********************************************************************
//
// 非静的メンバ関数定義
//
//**********************************************************************

//================================================================================
//
// [ デフォルトコンストラクタ ]
//
//================================================================================

GridPolygon::GridPolygon()
	: device_(nullptr)
{
	CreateVertex();
	CreateMaterial();

	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(GridPolygon.cpp)", "Error", MB_OK);
		return;
	}
}



//================================================================================
//
// [ デストラクタ ]
//
//================================================================================

GridPolygon::~GridPolygon()
{
}



//================================================================================
//
// [ 描画関数 ]
//
//================================================================================

void GridPolygon::Draw()
{
	// FVFの設定(デバイスの方に頂点の属性を教える)
	device_->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// テクスチャをOFF
	device_->SetTexture(0, NULL);

	// マテリアルをデバイスにセット
	device_->SetMaterial(&material_);

	// ライティングをOFFにする
	device_->SetRenderState(D3DRS_LIGHTING, FALSE);

	// グリッド
	device_->DrawPrimitiveUP(D3DPT_LINELIST, vertex_.size() / 2, &vertex_[0], sizeof(RendererDirectX9::VERTEX_3D));

	// ライティングをONにする
	device_->SetRenderState(D3DRS_LIGHTING, TRUE);
}



//================================================================================
//
// [ 頂点作成関数 ]
//
//================================================================================

void GridPolygon::CreateVertex()
{
	// 頂点データ作成
	constexpr int   vertexMax = 44;
	constexpr float endPos = 5.0f;
	constexpr float interval_grid = 1.0f;

	vertex_.resize(vertexMax);

	int tempAdd = 0;

	// 横線
	for (int i = 0; i < vertexMax / 2 - 1; i += 2)
	{
		float posX = -endPos + tempAdd * interval_grid;

		vertex_[i].posisiont_ = Vec3(posX, -endPos, 0.0f);
		vertex_[i + 1].posisiont_ = Vec3(posX, endPos, 0.0f);

		vertex_[i].color_ = 0xff00ff00;
		vertex_[i + 1].color_ = 0xff00ff00;

		tempAdd++;
	}

	tempAdd = 0;

	// 縦線
	for (int i = vertexMax / 2; i < vertexMax - 1; i += 2)
	{
		float posY = -endPos + tempAdd * interval_grid;
		vertex_[i].posisiont_ = Vec3(-endPos, posY, 0.0f);
		vertex_[i + 1].posisiont_ = Vec3(endPos, posY, 0.0f);

		vertex_[i].color_ = 0xffff0000;
		vertex_[i + 1].color_ = 0xffff0000;

		tempAdd++;
	}
}


//================================================================================
//
// [ マテリアル作成関数 ]
//
//================================================================================

void GridPolygon::CreateMaterial()
{
	// マテリアルの設定
	ZeroMemory(&material_, sizeof(material_));	// 第一引数のアドレスからsizeof()分を0で埋める(クラスには使わない)

	// マテリアルカラーを白にする
	material_.Diffuse.r = 1.0f;
	material_.Diffuse.g = 1.0f;
	material_.Diffuse.b = 1.0f;
	material_.Diffuse.a = 1.0f;

	// アンビエントマテリアルの設定
	material_.Ambient.r = 1.0f;
	material_.Ambient.g = 1.0f;
	material_.Ambient.b = 1.0f;
	material_.Ambient.a = 1.0f;
}