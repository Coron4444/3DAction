//================================================================================
//
//    テクスチャオブジェクトクラスヘッダ
//    Author : Araki Kai                                作成日 : 2017/12/18
//
//================================================================================




//======================================================================
//
// インクルード文
//
//======================================================================

#include "TextureObject.h"

#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトコンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject::TextureObject(const std::string* file_path, int pattern_num_all, 
							 int pattern_num_width, int pattern_num_height)
	: pattern_num_all_(pattern_num_all)
{
	// テクスチャの読み込み
	InputTexture(file_path);

	// テクスチャの情報設定
	SetTextureInformation(file_path, &pattern_num_width, &pattern_num_height);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject::~TextureObject()
{
	SafeRelease::PlusRelease(&texture_handler_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ テクスチャーパターン取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int TextureObject::GetTexturePatternNum(const int animation_count, int animation_speed)
{
	if (animation_speed <= 0) animation_speed = 1;

	return animation_count / animation_speed % pattern_num_all_;
}



//--------------------------------------------------------------------------------
//
// [ テクスチャの読み込み関数 ]
//
//--------------------------------------------------------------------------------

void TextureObject::InputTexture(const std::string* file_path)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(EffekseerObject.cpp)", "Error", MB_OK);
		return;
	}

	// テクスチャファイルの読み込み
	HRESULT hr = D3DXCreateTextureFromFile(device, file_path->c_str(), &texture_handler_);

#ifdef _DEBUG
	assert(!FAILED(hr) && "Textureの読み込みに失敗(TextureObject.cpp)");
#else
	hr = hr;
#endif
	
}



//--------------------------------------------------------------------------------
//
// [ テクスチャの情報設定関数 ]
//
//--------------------------------------------------------------------------------

void TextureObject::SetTextureInformation(const std::string* file_path, const int* pattern_num_width, const int* pattern_num_height)
{
	// テクスチャファイルから情報を取り出す
	D3DXIMAGE_INFO image_info;
	D3DXGetImageInfoFromFile(file_path->c_str(), &image_info);

	width_  = (int)image_info.Width;
	height_ = (int)image_info.Height;

	// UV値の算出
	float tcw = ((float)width_  / *pattern_num_width ) / (float)width_;
	float tch = ((float)height_ / *pattern_num_height) / (float)height_;

	for ( int i = 0; i < pattern_num_all_; i++)
	{
		int pattern_width  = i % *pattern_num_width;
		int pattern_height = i / *pattern_num_width;

		TextureUV temp_uv;
		temp_uv.u0 = pattern_width  * tcw;
		temp_uv.v0 = pattern_height * tch;
		temp_uv.u1 = temp_uv.u0 + tcw;
		temp_uv.v1 = temp_uv.v0 + tch;

		texture_uv.push_back(temp_uv);
	}
}