//================================================================================
//
//    固定機能ピクセルシェーダークラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include <assert.h>

#include "FixedPixelShader.h"
#include "../../../Camera/Camera.h"

#include <Component/DrawBase/DrawBase.h>
#include <Renderer/Renderer.h>
#include <GameObjectManager/GameObjectManager.h>


//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void FixedPixelShader::Init()
{
	// デバイスの取得
	Renderer::GetInstance()->GetDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(FixedPipeline.cpp)", "Error", MB_OK);
		return;
	}
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void FixedPixelShader::Uninit()
{

}



//--------------------------------------------------
// +シェーダー設定関数
//--------------------------------------------------
void FixedPixelShader::SetShader()
{
	device_->SetPixelShader(nullptr);
}



//--------------------------------------------------
// +共通設定関数
//--------------------------------------------------
void FixedPixelShader::CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



//--------------------------------------------------
// +固有設定関数
//--------------------------------------------------
void FixedPixelShader::SpecificSetting(DrawBase* draw, Camera* camera,
									   unsigned object_index, unsigned mesh_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
	mesh_index = mesh_index;
}