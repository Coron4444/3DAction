//================================================================================
//
//    �e�N�X�`���I�u�W�F�N�g�N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2017/12/18
//
//================================================================================




//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "TextureObject.h"

#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject::TextureObject(const std::string* file_path, int pattern_num_all, 
							 int pattern_num_width, int pattern_num_height)
	: pattern_num_all_(pattern_num_all)
{
	// �e�N�X�`���̓ǂݍ���
	InputTexture(file_path);

	// �e�N�X�`���̏��ݒ�
	SetTextureInformation(file_path, &pattern_num_width, &pattern_num_height);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TextureObject::~TextureObject()
{
	SafeRelease::PlusRelease(&texture_handler_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �e�N�X�`���[�p�^�[���擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int TextureObject::GetTexturePatternNum(const int animation_count, int animation_speed)
{
	if (animation_speed <= 0) animation_speed = 1;

	return animation_count / animation_speed % pattern_num_all_;
}



//--------------------------------------------------------------------------------
//
// [ �e�N�X�`���̓ǂݍ��݊֐� ]
//
//--------------------------------------------------------------------------------

void TextureObject::InputTexture(const std::string* file_path)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(EffekseerObject.cpp)", "Error", MB_OK);
		return;
	}

	// �e�N�X�`���t�@�C���̓ǂݍ���
	HRESULT hr = D3DXCreateTextureFromFile(device, file_path->c_str(), &texture_handler_);

#ifdef _DEBUG
	assert(!FAILED(hr) && "Texture�̓ǂݍ��݂Ɏ��s(TextureObject.cpp)");
#else
	hr = hr;
#endif
	
}



//--------------------------------------------------------------------------------
//
// [ �e�N�X�`���̏��ݒ�֐� ]
//
//--------------------------------------------------------------------------------

void TextureObject::SetTextureInformation(const std::string* file_path, const int* pattern_num_width, const int* pattern_num_height)
{
	// �e�N�X�`���t�@�C������������o��
	D3DXIMAGE_INFO image_info;
	D3DXGetImageInfoFromFile(file_path->c_str(), &image_info);

	width_  = (int)image_info.Width;
	height_ = (int)image_info.Height;

	// UV�l�̎Z�o
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