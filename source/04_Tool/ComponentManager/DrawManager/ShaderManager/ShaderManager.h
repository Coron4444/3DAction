//================================================================================
//!	@file	 ShaderManager.h
//!	@brief	 シェーダーマネージャClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_



//****************************************
// クラス宣言
//****************************************
class DrawBase;
class Camera;
class VertexShaderBase;
class PixelShaderBase;



//************************************************************														   
//! @brief   シェーダーマネージャClass
//!
//! @details シェーダーのマネージャClass
//************************************************************
class ShaderManager
{
//==============================
// 列挙型定義
//==============================
public:
	enum class VertexShaderType
	{
		NONE = -1,
		FIXED,
		ANIMATED_DEFAULT,
		BUMP_MAPPING,
		MAX
	};

	enum class PixelShaderType
	{
		NONE = -1,
		FIXED,
		DEFAULT,
		BUMP_MAPPING,
		MAX
	};


//====================
// 変数
//====================
private:
	VertexShaderBase* vertex_shader_[(int)VertexShaderType::MAX] = {nullptr};	//!< 頂点シェーダー
	PixelShaderBase* pixel_shader_[(int)PixelShaderType::MAX] = {nullptr};		//!< ピクセルシェーダー
	VertexShaderType forced_vertex_;	//!< 強制頂点シェーダータイプ
	PixelShaderType forced_pixel_;		//!< 強制ピクセルシェーダータイプ


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief デバイスにシェーダー設定関数
	//! @details
	//! @param *draw          描画基底クラス
	//! @param forced_vertex_ 強制頂点シェーダータイプ
	//! @param forced_pixel_  強制ピクセルシェーダータイプ
	//! @retval void なし
	//----------------------------------------
	void ShaderSetToDevice(DrawBase* draw,
						   VertexShaderType forced_vertex,
						   PixelShaderType forced_pixel);

	//----------------------------------------
	//! @brief オブジェクト設定関数
	//! @details
	//! @param *draw		描画基底クラス
	//! @param *camera		カメラ
	//! @param object_index	描画オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	void ObjectSetting(DrawBase* draw, Camera* camera, unsigned object_index);

	//----------------------------------------
	//! @brief メッシュ設定関数
	//! @details
	//! @param *draw		描画基底クラス
	//! @param *camera		カメラ
	//! @param object_index	描画オブジェクトインデックス
	//! @param mesh_index	メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void MeshSetting(DrawBase* draw, Camera* camera, 
					 unsigned object_index, unsigned mesh_index);

private:
	//----------------------------------------
	//! @brief 頂点シェーダー初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InitVertexShader();

	//----------------------------------------
	//! @brief ピクセルシェーダー初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InitPixelShader();

	//----------------------------------------
	//! @brief 頂点シェーダー終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitVertexShader();

	//----------------------------------------
	//! @brief ピクセルシェーダー終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitPixelShader();

	//----------------------------------------
	//! @brief デバイスに頂点シェーダー設定関数
	//! @details
	//! @param *draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void VertexShaderSetToDevice(DrawBase* draw);

	//----------------------------------------
	//! @brief デバイスにピクセルシェーダー設定関数
	//! @details
	//! @param *draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void PixelShaderSetToDevice(DrawBase* draw);

	//----------------------------------------
	//! @brief 頂点シェーダーのオブジェクト設定関数
	//! @details
	//! @param *draw		描画基底クラス
	//! @param *camera		カメラ
	//! @param object_index	描画オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	void ObjectSettingVertexShader(DrawBase* draw, Camera* camera,
								   unsigned object_index);

	//----------------------------------------
	//! @brief ピクセルシェーダーのオブジェクト設定関数
	//! @details
	//! @param *draw		描画基底クラス
	//! @param *camera		カメラ
	//! @param object_index	描画オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	void ObjectSettingPixelShader(DrawBase* draw, Camera* camera,
								  unsigned object_index);

	//----------------------------------------
	//! @brief 頂点シェーダーのメッシュ設定関数
	//! @details
	//! @param *draw		描画基底クラス
	//! @param *camera		カメラ
	//! @param object_index	描画オブジェクトインデックス
	//! @param mesh_index	メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void MeshSettingVertexShader(DrawBase* draw, Camera* camera,
								 unsigned object_index, unsigned mesh_index);

	//----------------------------------------
	//! @brief ピクセルシェーダーのメッシュ設定関数
	//! @details
	//! @param *draw		描画基底クラス
	//! @param *camera		カメラ
	//! @param object_index	描画オブジェクトインデックス
	//! @param mesh_index	メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void MeshSettingPixelShader(DrawBase* draw, Camera* camera,
								unsigned object_index, unsigned mesh_index);
};



#endif
