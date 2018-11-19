//================================================================================
//
//    深度バッファシャドウ
//    Author : Araki Kai                                作成日 : 2018/09/24
//
//================================================================================



//======================================================================
//
// グローバル変数
//
//======================================================================

// 変換行列
float4x4 MATRIX_WVP;
float4x4 MATRIX_WLP;
float4x4 MATRIX_WLPB;

// ランバート拡散反射照明
float4 LAMBERT_DIFFUSE_LIGHT_VECTOR = {1.0f, 0.0f, 0.0f, 1.0f};
float4 LAMBERT_DIFFUSE_LIGHT_COLOR 	= {1.0f, 1.0f, 1.0f, 1.0f};

// デカールテクスチャ
texture DECALE_TEXTURE;

// サンプラ( テクスチャを読み込むときの設定、使用するテクスチャやサンプラステートの設定をする)
sampler DECALE_SAMPLER = sampler_state{Texture = <DECALE_TEXTURE>;
							     	   MinFilter = LINEAR;
							           MagFilter = LINEAR;
							           MipFilter = NONE;
							     	   AddressU = Clamp;
							     	   AddressV = Clamp;};


// シャドウマップ
texture SHADOW_MAP;

// サンプラ( テクスチャを読み込むときの設定、使用するテクスチャやサンプラステートの設定をする)
sampler SHADOW_MAP_SAMPLER = sampler_state{Texture = <SHADOW_MAP>;
							     	       MinFilter = LINEAR;
							               MagFilter = LINEAR;
							               MipFilter = NONE;
							     	       AddressU = Clamp;
							     	       AddressV = Clamp;};


//======================================================================
//
// 構造体宣言
//
//======================================================================

// 頂点シェーダへの入力
struct VsIn_Pass0
{
	float4 position_ : POSITION;
	float3 normal_   : NORMAL;
};

struct VsIn_Pass1
{
	float4 position_ : POSITION;
	float3 normal_	 : NORMAL;
	float2 decal_texture_  : TEXCOORD0;
}


// 頂点シェーダからの出力(ピクセルシェーダの入力)
struct VsOut_Pass0
{
	float4 position_      : POSITION; 
	float4 shadow_map_uv_ : TEXCOORD0;
};

struct VsOut_Pass1
{
	float4 position_       : POSITION;
	float4 diffuse_        : COLOR0;
	float4 ambient_		   : COLOR1;
	float4 decale_texture_ : TEXCOORD0;
	float4 shadow_map_uv_  : TEXCOORD1;
	float4 depth_          : TEXCOORD2;
};



//======================================================================
//
// 頂点シェーダ定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 頂点シェーダ関数(パス0) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

VsOut_Pass0 Vs_Pass0(VsInput_Pass0 input)
{
//------------------------------------------------------------
// 初期化

	// 出力データの作成
	VsOut_Pass0 output = (VsOut_Pass0)0;


//------------------------------------------------------------
// 座標変換

	// 位置座標をWVP行列で変換
	float4 temp_position = mul(input.position_, MATRIX_WVP);


//------------------------------------------------------------
// 出力データ作成

	// 位置座標
	output.position_ = temp_position;

	// ライト位置からの距離を出力する為に射影空間座標をテクスチャ座標として
	// そのまま出力する
	output.shadow_map_uv_ = temp_position;

	return output;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 頂点シェーダ関数(パス1) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

VsOut_Pass1 Vs_Pass1(VsInput_Pass1 input)
{
//------------------------------------------------------------
// 初期化

	// 出力データの作成
	VsOut_Pass1 output = (VsOut_Pass1)0;


//------------------------------------------------------------
// 座標変換

	// 位置座標をWVP行列で変換
	float4 temp_position = mul(input.position_, MATRIX_WVP);


//------------------------------------------------------------
// 出力データ作成

	// 位置座標
	output.position_ = temp_position;

	// 色
	// 環境光の比率を保存
	float ambient_ratio = LAMBERT_DIFFUSE_LIGHT_VECTOR.w;

	// ライトベクトルを反転
	float4 inverse_light_vector4 = -LAMBERT_DIFFUSE_LIGHT_VECTOR;

	// 色の計算(α値も環境比率が掛かってしまうため、α値は別途代入)
	output.diffuse_   = LAMBERT_DIFFUSE_LIGHT_COLOR * max(dot(input.normal_, inverse_light_vector4), 0);
	output.diffuse_.w = LAMBERT_DIFFUSE_LIGHT_COLOR.w;
	output.ambient_   = LAMBERT_DIFFUSE_LIGHT_COLOR * ambient_ratio;
	output.ambient_.w = LAMBERT_DIFFUSE_LIGHT_COLOR.w;

	// シャドウマップ
	output.shadow_map_uv_ = mul(input.position_, MATRIX_WLPB);

	// 比較のための深度値
	output.depth_ = mul(input.positon_, MATRIX_WLP);

	// デカールテクスチャ
	output_.decale_texture_ = input_.decal_texture_;

	return output;
}



//======================================================================
//
// ピクセルシェーダ定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ピクセルシェーダ関数(パス0) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float4 Ps_Pass0(VsOut_Pass0 vs_output) : COLOR
{
	// 描画する色はライト座標からの距離とする
	float4 ps_output;

	// Z座標をW値で割ると、0~1の範囲の深度値となる
	ps_output = vs_output.shadow_map_uv.z / vs_output.shadow_map_uv.w;

	return ps_output;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ピクセルシェーダ関数(パス1) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float4 Ps_Pass1(VsOut_Pass1 vs_output) : COLOR
{
	// tex2Dprojは、該当オブジェクトにテクスチャを投影するような形でテクセルをフェッチします
	//つまり、同次座標系で見た場合に、該当のテクセルがどうなるか、を計算しているわけです
	float  shadow = tex2Dproj(SHADOW_MAP_SAMPLER, vs_output.shadow_map_uv_).x;
	float4 decale = tex2D(DECALE_SAMPLER, vs_output.decale_texture_)

	float4 color = vs_output.ambient_ + (shadow * vs_output);
	

	return ps_output;
}

//======================================================================
//
// テクニック定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ テクニック(レンダリング方法をまとめたもの) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

technique Techique01
{
	pass Pass0
	{
		VertexShader = compile vs_3_0 Vs_Pass0();
		PixelShader  = compile ps_3_0 Ps_Pass0();
	}
}