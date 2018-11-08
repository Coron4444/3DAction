//================================================================================
//
//    深度バッファシャドウオブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/09/24
//
//================================================================================

#ifndef	_DEPTH_BUFFER_SHADOW_OBJECT_H_
#define _DEPTH_BUFFER_SHADOW_OBJECT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// クラス宣言
//
//======================================================================

class Camera;
class DrawComponent;



/*****************************************************************************//**
* @brief
* 深度バッファシャドウオブジェクトクラス
*
* シャドウマップを用いた影をつける
* レンダリング回数：2回
* 1回目 : シャドウマップの作成
* 2回目 : シャドウマップの深度値とオブジェクトの深度値を比較しながらレンダリング
*********************************************************************************/

class DepthBufferShadowObject
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 定数
	static const char* EFFECT_PATH;
	static const D3DVERTEXELEMENT9 DECLARATION[];
	static const Vec2 SHADOW_MAP_SIZE;

//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	DepthBufferShadowObject() = delete;

	// コピーコンストラクタ
	DepthBufferShadowObject(const DepthBufferShadowObject& class_name) = delete;

	// 代入演算子のオーバーロード
	DepthBufferShadowObject& operator = (const DepthBufferShadowObject& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ関数
	static void Init();
	static void Uninit();

	static void SetRenderTarget();
	static void SetOldRenderTarget();
	static void Draw_Pass0(DrawComponent* draw_component, Camera* camera);
	static void Draw_Pass1(DrawComponent* draw_component, Camera* camera);


//------------------------------------------------------------
private :
	// メンバ変数	
	static LPDIRECT3DDEVICE9 device_;

	// 計算用
	static D3DXMATRIX math_matrix_;

	// 頂点宣言オブジェクト
	static IDirect3DVertexDeclaration9* declaration_object_;

	// シャドウマップ
	static LPDIRECT3DTEXTURE9 shadow_map_;
	static LPDIRECT3DSURFACE9 shadow_map_render_target_surface_;
	static LPDIRECT3DSURFACE9 shadow_map_depth_buffer_surface_;
	static D3DVIEWPORT9       shadow_map_view_port_;
	static Camera             shadow_map_camera_;


	// 元のレンダリングターゲット
	static LPDIRECT3DSURFACE9 old_render_target_surface_;
	static LPDIRECT3DSURFACE9 old_depth_buffer_surface_;
	static D3DVIEWPORT9       old_view_port_;



	// エフェクトファイルハンドル群
	static LPD3DXEFFECT effect_;
	static D3DXHANDLE   technique_;
	static D3DXHANDLE   matrix_WVP_;
	static D3DXHANDLE   lambert_diffuse_light_vector_;
	static D3DXHANDLE   lambert_diffuse_light_color_;
	static D3DXHANDLE   camera_position_;
	static D3DXHANDLE   decale_texture_;
	static D3DXHANDLE   normal_texture_;

};



#endif
