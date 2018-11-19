//================================================================================
//
//    シェーダーマネージャークラス
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_



//****************************************
// インクルード文
//****************************************




//****************************************
// クラス宣言
//****************************************
class DrawBase;
class Camera;
class VertexShaderBase;
class PixelShaderBase;



/*********************************************************//**
* @brief
* シェーダーマネージャークラス
*
* シェーダーを管理するクラス
*************************************************************/
class ShaderManager
{
//==============================
// 列挙型定義
//==============================
public:
	// 頂点シェーダータイプ
	enum VertexShaderType
	{
		VERTEX_NONE = -1,
		VERTEX_FIXED,
		VERTEX_BUMP_MAPPING,
		VERTEX_MAX
	};

	// ピクセルシェーダータイプ
	enum PixelShaderType
	{
		PIXEL_NONE = -1,
		PIXEL_FIXED,
		PIXEL_BUMP_MAPPING,
		PIXEL_MAX
	};


//==============================
// 非静的メンバ変数
//==============================
private:
	// 各種シェーダー
	VertexShaderBase* vertex_shaders_[VERTEX_MAX] = {nullptr};
	PixelShaderBase* pixel_shaders_[PIXEL_MAX] = {nullptr};


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init();

	/**
	* @brief
	* 終了関数
	*/
	void Uninit();

	/**
	* @brief
	* シェーダー設定関数
	* @param
	* draw : 描画基底クラス
	* forced_vertex_type : 強制頂点シェーダータイプ
	* forced_pixel_type : 強制ピクセルシェーダータイプ
	*/
	void SetShader(DrawBase* draw, VertexShaderType forced_vertex_type,
				   PixelShaderType forced_pixel_type);
	/**
	* @brief
	* 共通設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* forced_vertex_type : 強制頂点シェーダータイプ
	* forced_pixel_type : 強制ピクセルシェーダータイプ
	* object_index : 描画オブジェクトインデックス
	*/
	void CommonSetting(DrawBase* draw, Camera* camera,
					   VertexShaderType forced_vertex_type,
					   PixelShaderType forced_pixel_type, unsigned object_index);

	/**
	* @brief
	* 固有設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* forced_vertex_type : 強制頂点シェーダータイプ
	* forced_pixel_type : 強制ピクセルシェーダータイプ
	* object_index : 描画オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	void SpecificSetting(DrawBase* draw, Camera* camera,
						 VertexShaderType forced_vertex_type,
						 PixelShaderType forced_pixel_type,
						 unsigned object_index, unsigned mesh_index);

private:
	/**
	* @brief
	* 頂点シェーダー初期化関数
	*/
	void InitVertexShaders();

	/**
	* @brief
	* ピクセルシェーダー初期化関数
	*/
	void InitPixelShaders();


	/**
	* @brief
	* 頂点シェーダー終了関数
	*/
	void UninitVertexShaders();

	/**
	* @brief
	* ピクセルシェーダー終了関数
	*/
	void UninitPixelShaders();

	/**
	* @brief
	* 頂点シェーダー設定関数
	* @param
	* draw : 描画基底クラス
	* forced_vertex_type : 強制頂点シェーダータイプ
	*/
	void SetVertexShader(DrawBase* draw, VertexShaderType forced_vertex_type);

	/**
	* @brief
	* ピクセルシェーダー設定関数
	* @param
	* draw : 描画基底クラス
	* forced_pixel_type : 強制ピクセルシェーダータイプ
	*/
	void SetPixelShader(DrawBase* draw, PixelShaderType forced_pixel_type);

	/**
	* @brief
	* 頂点シェーダー共通設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* forced_vertex_type : 強制頂点シェーダータイプ
	* object_index : 描画オブジェクトインデックス
	*/
	void CommonSettingVertexShader(DrawBase* draw, Camera* camera,
								   VertexShaderType forced_vertex_type,
								   unsigned object_index);

	/**
	* @brief
	* ピクセルシェーダー共通設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* forced_pixel_type : 強制ピクセルシェーダータイプ
	* object_index : 描画オブジェクトインデックス
	*/
	void CommonSettingPixelShader(DrawBase* draw, Camera* camera,
								  PixelShaderType forced_pixel_type,
								  unsigned object_index);

	/**
	* @brief
	* 頂点シェーダー固有設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* forced_vertex_type : 強制頂点シェーダータイプ
	* forced_pixel_type : 強制ピクセルシェーダータイプ
	* object_index : 描画オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	void SpecificSettingVertexShader(DrawBase* draw, Camera* camera,
									 VertexShaderType forced_vertex_type,
									 unsigned object_index, unsigned mesh_index);

	/**
	* @brief
	* ピクセルシェーダー固有設定関数
	* @param
	* draw : 描画基底クラス
	* camera : カメラ
	* forced_vertex_type : 強制頂点シェーダータイプ
	* forced_pixel_type : 強制ピクセルシェーダータイプ
	* object_index : 描画オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	void SpecificSettingPixelShader(DrawBase* draw, Camera* camera,
									PixelShaderType forced_pixel_type,
									unsigned object_index, unsigned mesh_index);
};



#endif
