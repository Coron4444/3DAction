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
class FixedVertexShader;
class FixedPixelShader;



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
		VERTEX_MAX
	};

	// ピクセルシェーダータイプ
	enum PixelShaderType
	{
		PIXEL_NONE = -1,
		PIXEL_FIXED,
		PIXEL_MAX
	};


//==============================
// 非静的メンバ変数
//==============================
private:
	// 各種シェーダーが入る(本当は配列を作る)
	FixedVertexShader* fixed_vertex_shader_ = nullptr;
	FixedPixelShader* fixed_pixel_shader_ = nullptr;


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
};



#endif
