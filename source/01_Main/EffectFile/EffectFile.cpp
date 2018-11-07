//================================================================================
//
//    エフェクトファイルヘッダ
//    Author : Araki Kai                                作成日 : 2018/01/04
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "EffectFile.h"

#include <stdio.h>




//**********************************************************************
//
// 静的メンバ変数定義
//
//**********************************************************************

EffectFile* EffectFile::effect_file_ = nullptr;



//**********************************************************************
//
// 静的メンバ関数定義
//
//**********************************************************************

EffectFile* EffectFile::GetPointer()
{
	return effect_file_;
}



void EffectFile::Create()
{
	effect_file_ = new EffectFile;
}



void EffectFile::Delete()
{
	delete effect_file_;
}



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

EffectFile::EffectFile()
	: effect_(nullptr)
{
	InputEffectFile();
}



//================================================================================
//
// [ デストラクタ ]
//
//================================================================================

EffectFile::~EffectFile()
{
	// 各種開放
	SafeRelease(&effect_);
}



//================================================================================
//
// [ エフェクトファイルの読み込み関数 ]
//
//================================================================================

void EffectFile::InputEffectFile()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = RendererDirectX9::GetDevice();
	assert(device != nullptr && "Deviceの取得に失敗(EffectFile.cpp)");

	// シェーダーの読み込み
	FILE* fp;
	fp = fopen("resource/HLSL/AnimationFBX.obj", "rb");
	
	if (fp == nullptr) return;
	
	// ファイルサイズ取得
	fseek(fp, 0, SEEK_END);
	unsigned size = (unsigned)ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// ファイルデータ取得
	char* src_data = new char[size];
	fread(src_data, size, sizeof(char), fp);
	fclose(fp);

	LPD3DXBUFFER error = nullptr;
	// エフェクトファイルのコンパイル
	HRESULT hr = D3DXCreateEffect(device,		// デバイス
		                          src_data,		// コンパイル済みfxデータ
		                          size,			// コンパイル済みfxデータのサイズ
		                          NULL,			// プリプロセッサ定義へのポインタ
		                          NULL,			// オプションのインタフェースへのポインタ
		                          0,			// D3DXSHADERで識別されるコンパイルオプション
		                          NULL,			// 共有引数で使うID3DXEffectPoolオブジェクトへのポインタ
		                          &effect_,		// コンパイルされたエフェクトの格納先
		                          &error);		// コンパイルエラー一覧の格納先

	if (FAILED(hr))
	{
		MessageBox( NULL, (LPCTSTR)error->GetBufferPointer(), "エラー", MB_OK );
		return;
	}

	// 各種開放
	SafeRelease(&error);
	delete[] src_data;
}