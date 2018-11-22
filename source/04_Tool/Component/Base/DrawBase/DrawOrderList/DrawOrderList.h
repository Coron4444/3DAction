//================================================================================
//
//    描画注文リストクラス
//    Author : Araki Kai                                作成日 : 2018/03/22
//
//================================================================================

#ifndef	_DRAW_ORDER_LIST_H_
#define _DRAW_ORDER_LIST_H_



//****************************************
// インクルード文
//****************************************
#include <ComponentManager/DrawManager/ShaderManager/ShaderManager.h>
#include <Flag/Flag.h>




/*********************************************************//**
* @brief
* 描画注文リストクラス
*
* 描画に関する注文リストクラス
*************************************************************/
class DrawOrderList
{
//==============================
// 定数定義
//==============================
public:
	static const unsigned RENDER_TARGET_BACK_BUFFER = 1 << 0;


//==============================
// 列挙型定義
//==============================
public:
	// 描画タイプ
	enum DrawType
	{
		NONE = -1,
		OPACITY,
		TRANSPARENCY,
		TWO_DIMENSIONAL,
		MAX
	};


//==============================
// 非静的メンバ変数
//==============================
private:
	ShaderManager::VertexShaderType vertex_shader_type_ = ShaderManager::VertexShaderType::VERTEX_FIXED;	//!< 頂点シェーダーの種類
	ShaderManager::PixelShaderType pixel_shader_type_ = ShaderManager::PixelShaderType::PIXEL_FIXED;		//!< ピクセルシェーダーの種類

	DrawType draw_type_ = DrawType::OPACITY;	//!< 描画の種類

	Flag render_target_flag_;			//!< レンダーターゲットフラグ
	bool is_billboard_ = false;			//!< ビルボード化フラグ
	bool is_lighting_ = true;			//!< ラインティングフラグ
	int layer_num_ = 0;					//!< レイヤー数


//==============================
// 非静的メンバ関数
//==============================
public:
	// プロパティ
	ShaderManager::VertexShaderType GetVertexShaderType() { return vertex_shader_type_; }
	void SetVertexShaderType(ShaderManager::VertexShaderType value) { vertex_shader_type_ = value; }
	ShaderManager::PixelShaderType GetPixelShaderType() { return pixel_shader_type_; }
	void SetPixelShaderType(ShaderManager::PixelShaderType value) { pixel_shader_type_ = value; }
	DrawType GetDrawType() { return draw_type_; }
	void SetDrawType(DrawType value) { draw_type_ = value; }
	Flag* GetRenderTargetFlag() { return &render_target_flag_; }
	bool GetIsBillboard() { return is_billboard_; }
	void SetIsBillboard(bool value) { is_billboard_ = value; }
	bool GetIsLighting() { return is_lighting_; }
	void SetIsLighting(bool value) { is_lighting_ = value; }
	int GetLayerNum() { return layer_num_; }
	void SetLayerNum(int value) { layer_num_ = value; }
};



#endif