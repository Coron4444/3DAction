//================================================================================
//!	@file	 TextureObject.cpp
//!	@brief	 テクスチャオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "TextureObject.h"
#include "../TextureManager/TextureManager.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
float* TextureObject::UV::getpLeftUpU()
{
	return &left_up_uv_.x;
}



float* TextureObject::UV::getpLeftUpV()
{
	return &left_up_uv_.y;
}



float* TextureObject::UV::getpRightButtomU()
{
	return &right_bottom_uv_.x;
}



float* TextureObject::UV::getpRightButtomV()
{
	return &right_bottom_uv_.y;
}



int	TextureObject::getWidth()
{
	return width_;
}



int	TextureObject::getHeight()
{
	return height_;
}



void TextureObject::setDivisionNum(int division_num, int division_num_width,
								   int division_num_height)
{
	// 切り取り幅高さ算出
	float cut_width = ((float)width_ / division_num_width) / (float)width_;
	float cut_height = ((float)height_ / division_num_height) / (float)height_;

	// UVの作成
	uv_.clear();
	division_num_ = division_num;
	for (int i = 0; i < division_num; i++)
	{
		int animation_num_width = i % division_num_width;
		int animation_num_height = i / division_num_height;

		UV uv;
		*uv.getpLeftUpU() = animation_num_width * cut_width;
		*uv.getpLeftUpV() = animation_num_height * cut_height;
		*uv.getpRightButtomU() = *uv.getpLeftUpU() + cut_width;
		*uv.getpRightButtomV() = *uv.getpLeftUpV() + cut_height;

		uv_.push_back(uv);
	}
}



int TextureObject::getDivisionNum()
{
	return division_num_;
}



TextureObject::UV* TextureObject::getpUV(int index)
{
	return &uv_[index];
}



LPDIRECT3DTEXTURE9 TextureObject::getpHandler()
{
	return texture_handler_;
}



int TextureObject::getAnimationNum(int animation_count, int animation_speed)
{
	if (animation_speed <= 0) animation_speed = 1;

	return animation_count / animation_speed % division_num_;
}



//****************************************
// 関数定義
//****************************************
void TextureObject::Init(std::string* file_path, const std::string* map_key_name)
{
	// テクスチャハンドラ生成
	CreateTextureHandler(file_path);

	// テクスチャ情報生成
	CreateTextureInformation(file_path);

	// キー名保存
	map_key_name_ = *map_key_name;
}



void TextureObject::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	SafeRelease::PlusRelease(&texture_handler_);
	TextureManager::getpInstance()->ReleaseFromTheMap(&map_key_name_);
	delete this;
}



void TextureObject::ForcedRelease()
{
	reference_counter_ = 0;
	Release();
}



void TextureObject::AddReferenceCounter()
{
	reference_counter_++;
}



void TextureObject::CreateTextureHandler(std::string* file_path)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(TextureObject.cpp)", "Error", MB_OK);
		return;
	}

	// テクスチャハンドラの取得
	HRESULT hr = D3DXCreateTextureFromFile(device, file_path->c_str(), &texture_handler_);
	std::string error_message = *file_path + "のテクスチャハンドラの生成に失敗(TextureObject.cpp)";
	if (FAILED(hr))
	{
		MessageBox(nullptr, error_message.c_str(), "Error", MB_OK);
		return;
	}
}



void TextureObject::CreateTextureInformation(std::string* file_path)
{
	// テクスチャファイルから情報を取り出す
	D3DXIMAGE_INFO image_info;
	D3DXGetImageInfoFromFile(file_path->c_str(), &image_info);

	// 幅高さ
	width_ = (int)image_info.Width;
	height_ = (int)image_info.Height;

	// UV値
	division_num_ = 1;
	UV uv;
	*uv.getpLeftUpU() = 0.0f;
	*uv.getpLeftUpV() = 0.0f;
	*uv.getpRightButtomU() = 1.0f;
	*uv.getpRightButtomV() = 1.0f;
	uv_.push_back(uv);
}