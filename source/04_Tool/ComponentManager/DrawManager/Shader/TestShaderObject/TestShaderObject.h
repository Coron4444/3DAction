//================================================================================
//
//    テストシェーダーオブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/07/09
//
//================================================================================

#ifndef	_TEST_SHADER_OBJECT_H_
#define _TEST_SHADER_OBJECT_H_



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
class DrawBase;



//======================================================================
//
// クラス定義
//
//======================================================================

class TestShaderObject
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 定数
	static const char* EFFECT_PATH;
	static const D3DVERTEXELEMENT9 DECLARATION[];


//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	TestShaderObject() = delete;

	// コピーコンストラクタ
	TestShaderObject(const TestShaderObject& class_name) = delete;

	// 代入演算子のオーバーロード
	TestShaderObject& operator = (const TestShaderObject& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ関数
	static void Init();
	static void Uninit();
	static void Draw(DrawBase* draw, Camera* camera);

	static void UpdateMeshDeclaration(ModelXObject* model_x);


//------------------------------------------------------------
private :
	// メンバ変数	
	static LPDIRECT3DDEVICE9 device_;

	// 計算用
	static D3DXMATRIX math_matrix_;

	// 頂点宣言オブジェクト
	static IDirect3DVertexDeclaration9* declaration_object_;

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
