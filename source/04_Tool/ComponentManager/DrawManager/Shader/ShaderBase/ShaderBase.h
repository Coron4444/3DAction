//================================================================================
//!	@file	 ShaderBase.h
//!	@brief	 シェーダーBaseClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_SHADER_BASE_H_
#define _SHADER_BASE_H_



//****************************************
// インクルード文
//****************************************
#include <Renderer/Renderer.h>



//****************************************
// クラス宣言
//****************************************
class DrawBase;
class Camera;



//************************************************************														   
//! @brief   シェーダーBaseClass
//!
//! @details シェーダーのBaseClass
//************************************************************
class ShaderBase
{
//====================
// 変数
//====================
private:
	LPD3DXCONSTANTTABLE	constant_table_ = nullptr;	//!< 定数テーブル
	LPDIRECT3DDEVICE9 device_ = nullptr;			//!< デバイス


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 定数テーブル取得関数
	//! @details
	//! @param void なし
	//! @retval LPD3DXCONSTANTTABLE 定数テーブル
	//----------------------------------------
	LPD3DXCONSTANTTABLE getpConstantTable();

protected:
	//----------------------------------------
	//! @brief デバイス取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3DDEVICE9 デバイス
	//----------------------------------------
	LPDIRECT3DDEVICE9 getpDevice();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デストラクタ関数
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~ShaderBase() = 0;

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Init() = 0;

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief オブジェクト設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param *camera      カメラ
	//! @param object_index 描画オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void ObjectSetting(DrawBase* draw, Camera* camera,
							   unsigned object_index) = 0;

	//----------------------------------------
	//! @brief メッシュ設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param *camera      カメラ
	//! @param object_index 描画オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void MeshSetting(DrawBase* draw, Camera* camera,
							 unsigned object_index, unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief デバイスにシェーダー設定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void ShaderSetToDevice() = 0;

protected:
	//----------------------------------------
	//! @brief シェーダーコンパイル関数
	//! @details
	//! @param *file_name : ファイル名
	//! @param *entry_function : エントリ関数名
	//! @param *version : シェーダーバージョン
	//! @param *compiled_code : コンパイル済みコード
	//! @retval bool コンパイル成功ならtrue
	//----------------------------------------
	bool ShaderCompile(const char* file_name, const char* entry_function,
					   const char* version, LPD3DXBUFFER* compiled_code);

	//----------------------------------------
	//! @brief デバイス初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InitDevice();
};

#endif
