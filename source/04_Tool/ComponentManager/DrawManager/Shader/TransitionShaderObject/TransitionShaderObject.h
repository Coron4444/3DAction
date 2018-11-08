//================================================================================
//
//    トランジションシェーダーオブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/08/21
//
//================================================================================

#ifndef	_TRANSITION_SHADER_OBJECT_H_
#define _TRANSITION_SHADER_OBJECT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../ShaderObjectCommonMethod/ShaderObjectCommonMethod.h"



//**********************************************************************
//
// クラス定義
//
//**********************************************************************

class TransitionShaderObject
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 定数
	static const char* EFFECT_PATH;


//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	TransitionShaderObject() = delete;

	// コピーコンストラクタ
	TransitionShaderObject(const TransitionShaderObject& class_name) = delete;

	// 代入演算子のオーバーロード
	TransitionShaderObject& operator = (const TransitionShaderObject& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ関数
	static void Init();
	static void Uninit();
	static void Draw(Camera* camera);
	static void ResetArray();
	static void DistributeDrawComponent(DrawComponent* draw_component, Camera* camera);
	static void SortTransparent(Camera* camera);



//------------------------------------------------------------
private :
	// メンバ変数
	static LimitedPointerArray<DrawComponent*, DrawComponentManager::DRAW_ARRAY_NUM> shader_;
	
	static LPDIRECT3DDEVICE9 device_;

	// 計算用
	static D3DXMATRIX math_matrix_;

	// エフェクトファイルハンドル群
	static LPD3DXEFFECT effect_;
	static D3DXHANDLE   technique_;
	static D3DXHANDLE   matrix_W_;
	static D3DXHANDLE   diffuse_light_vector_;
};



#endif
