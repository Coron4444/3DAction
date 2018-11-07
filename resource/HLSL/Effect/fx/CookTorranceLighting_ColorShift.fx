//================================================================================
//
//    クック・トランス金属反射モデルシェーダー(カラーシフト有)
//    Author : Araki Kai                                作成日 : 2018/08/07
//
//================================================================================



//**********************************************************************
//
// グローバル変数
//
//**********************************************************************

// 変換行列
float4x4 MATRIX_WVP;

// ランバート拡散照明(ライトベクトルはプログラムで正規化)
float4 LAMBERT_DIFFUSE_LIGHT_VECTOR = {1.0f, 0.0f, 0.0f, 1.0f};
float4 LAMBERT_DIFFUSE_LIGHT_COLOR 	= {1.0f, 1.0f, 1.0f, 1.0f};

// カメラ座標
float3 CAMERA_POSITION = {0.0f, 0.0f, 0.0f};



//**********************************************************************
//
// 構造体宣言
//
//**********************************************************************

// 頂点シェーダへの入力
struct Input_VS
{
	float4 position_ : POSITION;
	float4 normal_   : NORMAL;
};


// 頂点シェーダからの出力(ピクセルシェーダの入力)
struct Output_VS
{
	float4 position_  : POSITION;
	float4 color_	  : COLOR0;
	float3 normal_	  : TEXCOORD0;
	float3 position3_ : TEXCOORD1;
};



//**********************************************************************
//
// 頂点シェーダ定義
//
//**********************************************************************

//================================================================================
//
// [ メイン頂点シェーダ関数 ]
//
//================================================================================

Output_VS mainVS(Input_VS input)
{
//------------------------------------------------------------
// 初期化

	// 出力データの作成
	Output_VS output = (Output_VS)0;


//------------------------------------------------------------
// 座標変換

	// 座標をWVP行列で変換
	output.position_ = mul(input.position_, MATRIX_WVP);


//------------------------------------------------------------
// ランバート拡散照明

	// 環境光の比率を保存
	float ambient_ratio = LAMBERT_DIFFUSE_LIGHT_VECTOR.w;

	// ライトベクトルを反転
	float4 inverse_light_vector4 = -LAMBERT_DIFFUSE_LIGHT_VECTOR;

	// 色の計算(α値も環境比率が掛かってしまうため、α値は別途代入)
	output.color_ = LAMBERT_DIFFUSE_LIGHT_COLOR * max(ambient_ratio, dot(input.normal_, inverse_light_vector4));
	output.color_.w = LAMBERT_DIFFUSE_LIGHT_COLOR.w;

	
//------------------------------------------------------------
// ピクセルシェーダーに渡す値計算

	// 座標
	output.position3_ = input.position_.xyz;

	// 法線
	output.normal_ = input.normal_.xyz;

	return output;
}



//**********************************************************************
//
// ピクセルシェーダ定義
//
//**********************************************************************

//================================================================================
//
// [ メインピクセルシェーダ関数 ]
//
//================================================================================

float4 mainPS(Output_VS input) : COLOR
{
//------------------------------------------------------------
// クック・トランス金属反射

	// 法線を正規化
	input.normal_ = normalize(input.normal_);

	// ライトベクトルを反転
	float3 inverse_light_vector3 = -LAMBERT_DIFFUSE_LIGHT_VECTOR;

	// 視線ベクトルの作成
	float3 eye_vector = normalize(CAMERA_POSITION - input.position3_);

	// ハーフベクトルの作成
	float3 half_vector = normalize(inverse_light_vector3 + eye_vector);

	// 各種角度(cosΘ)の算出
	float dot_normal_eye   = dot(input.normal_, eye_vector);
	float dot_normal_half  = dot(input.normal_, half_vector);
	float dot_normal_light = dot(input.normal_, inverse_light_vector3);
	float dot_eye_half     = dot(eye_vector, half_vector);
	float dot_light_half   = dot(inverse_light_vector3, half_vector);

	// Beckmann分布関数(マイクロファセット分布関数の一つ)の算出
	const float roughness = 0.3f;		// 荒さ
	float squaring_dot_normal_half = dot_normal_half * dot_normal_half;
	float beckmann_distribution_function = exp(-(1 - squaring_dot_normal_half) / (squaring_dot_normal_half * roughness * roughness))
												/ (4 * roughness * roughness * squaring_dot_normal_half * squaring_dot_normal_half);

	// 幾何減衰率の算出
	float geometric_decay_rate = min(1, min((2 * dot_normal_half * dot_normal_eye) / dot_eye_half, (2 * dot_normal_half * dot_normal_light) / dot_eye_half));

	// フレネル反射係数
	const float refraction = 5.0f;		// 屈折率(これを上げると中心からの色の領域が広くなる)
	float g = (refraction * refraction) + (dot_light_half * dot_light_half) - 1;
	float g_plus_c  = g + dot_light_half;
	float g_minus_c = g - dot_light_half;
	float cg_plus_cc_minus_1 = dot_light_half * g_plus_c - 1;
	float cg_minus_cc_plus_1 = dot_light_half * g_minus_c + 1;
	float fresnel = 0.5f * ((g_minus_c * g_minus_c) * (1 + (cg_plus_cc_minus_1 * cg_plus_cc_minus_1) / (cg_minus_cc_plus_1 * cg_minus_cc_plus_1))
						/ (g_plus_c * g_plus_c));
	
	// 視点とほぼ同じ向きからライトを当てた時のフレネル反射係数
	float fresnel0 = ((refraction - 1) * (refraction - 1)) / ((refraction + 1) * (refraction + 1));

	// 金属の色
	float4 light_color = {0.3f, 0.3f, 1.0f, 1.0f};		// 入射光の色
	float4 color0      = {0.9f * light_color.x,			// 正面からlight_colorの色の光が当たったときの鏡面反射色
						  0.8f * light_color.y, 
						  0.3f * light_color.z, 
						  1.0f};

	// カラーシフトを考慮した色の算出
	float color_Shift = color0 + (light_color - color0) * max(0, fresnel - fresnel0) / (1 - fresnel0);

	input.color_ += color_Shift * max(0, (beckmann_distribution_function * geometric_decay_rate * fresnel) / dot_normal_eye);

	return input.color_;
}



//**********************************************************************
//
// テクニック定義
//
//**********************************************************************

//================================================================================
//
// [ テクニック(レンダリング方法をまとめたもの) ]
//
//================================================================================

technique Techique01
{
	pass P0
	{
		VertexShader = compile vs_2_0 mainVS();
		PixelShader  = compile ps_2_0 mainPS();
	}
}