//================================================================================
//
//    シェーダー基底クラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_SHADER_BASE_H_
#define _SHADER_BASE_H_



//****************************************
// インクルード文
//****************************************
#include <Renderer/Renderer.h>
#include <Component/Base/DrawBase/DrawBase.h>
#include <ComponentManager/DrawManager/Camera/Camera.h>

#include <SafeRelease/SafeRelease.h>



/*********************************************************//**
* @brief
* シェーダー基底クラス
*
* シェーダー基底クラス
*************************************************************/
class ShaderBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	LPDIRECT3DDEVICE9 device_ = nullptr;			//!< デバイス
	LPD3DXCONSTANTTABLE	constant_table_ = nullptr;	//!< 定数テーブル


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	virtual void Init() = 0;

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit() = 0;

	/**
	* @brief
	* シェーダー設定関数
	*/
	virtual void SetShader() = 0;

	/**
	* @brief
	* 共通設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* object_index : 描画オブジェクトインデックス
	*/
	virtual void CommonSetting(DrawBase* draw, Camera* camera,
							   unsigned object_index) = 0;

	/**
	* @brief
	* 固有設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* object_index : 描画オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	virtual void SpecificSetting(DrawBase* draw, Camera* camera,
								 unsigned object_index, unsigned mesh_index) = 0;

	/**
	* @brief
	* シェーダーコンパイル関数
	* @param
	* file_name : ファイル名
	* entry_function : エントリ関数名
	* version : シェーダーバージョン
	* compiled_code : コンパイル済みコード
	* @return コンパイル成功ならtrue
	*/
	bool ShaderCompile(const char* file_name, const char* entry_function,
					   const char* version, LPD3DXBUFFER* compiled_code)
	{
		LPD3DXBUFFER compil_error = nullptr;
		HRESULT hr = D3DXCompileShaderFromFile(file_name,			// ファイル名
											   nullptr,				// プリプロセッサ定義へのポインタ
											   nullptr,				// ID3DXInclude(#include疑似命令)
											   entry_function,		// エントリ関数名
											   version,				// シェーダーバージョン
											   0,					// コンパイルオプション
											   compiled_code,		// コンパイル済みコード
											   &compil_error,		// エラー情報
											   &constant_table_);	// コンスタントテーブル
		// 成功したか
		if (SUCCEEDED(hr)) return true;
		
		// エラーメッセージ
		if (compil_error) 
		{
			// コンパイルエラーあり
			MessageBox(NULL, (LPSTR)compil_error->GetBufferPointer(), "Error", MB_OK);
		}
		else 
		{
			// その他のエラー
			MessageBox(NULL, "シェーダーファイルが読み込めません", "Error", MB_OK);
		}
		return false;
}

	/**
	* @brief
	* デバイスの初期化関数
	*/
	void InitDevice()
	{ 
		// デバイスの取得
		Renderer::GetInstance()->GetDevice(&device_);
		if (device_ == nullptr)
		{
			MessageBox(nullptr, "NotGetDevice!(VertexShaderBase.cpp)", "Error", MB_OK);
			return;
		}
	}

	// プロパティ
	LPDIRECT3DDEVICE9 GetDevice() { return device_; }
	LPD3DXCONSTANTTABLE GetConstantTable() { return constant_table_; }
};

#endif
