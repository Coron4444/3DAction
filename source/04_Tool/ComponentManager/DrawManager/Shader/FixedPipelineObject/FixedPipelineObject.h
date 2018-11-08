//================================================================================
//
//    固定パイプラインオブジェクトクラス(static)
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_FIXED_PIPELINE_OBJECT_H_
#define _FIXED_PIPELINE_OBJECT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <Renderer/Renderer.h>



//======================================================================
//
// クラス宣言
//
//======================================================================

class Camera;
class DrawComponent;



//======================================================================
//
// クラス定義
//
//======================================================================

class FixedPipelineObject 
{
//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	FixedPipelineObject() = delete;

	// コピーコンストラクタ
	FixedPipelineObject(const FixedPipelineObject& class_name) = delete;

	// 代入演算子のオーバーロード
	FixedPipelineObject& operator = (const FixedPipelineObject& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 静的公開メンバ関数
	static void Init();
	static void Uninit();
	static void Draw3D(DrawComponent* draw_component, Camera* camera);
	static void Draw2D(DrawComponent* draw_component, Camera* camera);
	
	static void SetDraw3D(Camera* camera);
	static void SetDraw2D();

	// アルファブレンド
	static void UseAlphaBlending(bool flag);
	static void SetAlphaBlending_Linear();
	static void SetAlphaBlending_Add();
	static void SetAlphaBlending_Sub();
	static void SetAlphaBlending_Mul();
	static void SetAlphaBlending_Baking();
	static void SetAlphaBlending_Nega();
	static void SetAlphaBlending_Opacity();

	// サンプラーステート
	static void SetDefaultSamplerState();

//------------------------------------------------------------
private :
	// 固定パイプライン統一設定
	static void UnifiedSetting();

	// ワールド行列設定
	static void SetWorldMatrix(DrawComponent* draw_component);

	// テクスチャ設定
	static void SetTexture(DrawComponent* draw_component, unsigned mesh_index);

	// マテリアル設定
	static void SetMaterial(DrawComponent* draw_component, unsigned mesh_index);

	// ライト
	static void Init_DirectionalLignt();

//------------------------------------------------------------
private :
	// 静的メンバ変数
	static D3DLIGHT9 directional_light_;

	static LPDIRECT3DDEVICE9 device_;
};



#endif
