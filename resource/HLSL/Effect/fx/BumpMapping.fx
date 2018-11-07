//================================================================================
//
//    バンプマッピング
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

// デカールテクスチャ
texture DECALE_TEXTURE;

// サンプラ( テクスチャを読み込むときの設定、使用するテクスチャやサンプラステートの設定をする)
sampler DECALE_SAMPLER = sampler_state{Texture = <DECALE_TEXTURE>;
							     	   MinFilter = LINEAR;
							           MagFilter = LINEAR;
							           MipFilter = NONE;
							     	   AddressU = Clamp;
							     	   AddressV = Clamp;};

// 法線マップ
texture NORMAL_TEXTURE;
// サンプラ( テクスチャを読み込むときの設定、使用するテクスチャやサンプラステートの設定をする)
sampler NORMAL_SAMPLER = sampler_state{Texture = <NORMAL_TEXTURE>;
							     	   MinFilter = LINEAR;
							    	   MagFilter = LINEAR;
							     	   MipFilter = NONE;
							     	   AddressU = Clamp;
							     	   AddressV = Clamp;};


//**********************************************************************
//
// 構造体宣言
//
//**********************************************************************

// 頂点シェーダへの入力
struct Input_VS
{
	float4 position_ : POSITION;	// ローカル座標
	float3 normal_   : NORMAL;		// 法線ベクトル
	float3 tangent_  : TANGENT0;	// 接ベクトル
	float2 texcoord_ : TEXCOORD0;	// 法線ベクトル
};


// 頂点シェーダからの出力(ピクセルシェーダの入力)
struct Output_VS
{
	float4 position_     : POSITION;
	float4 color_	     : COLOR0;
	float2 texcoord_     : TEXCOORD0;	// 法線ベクトル
	float3 eye_vector_   : TEXCOORD1;
	float3 light_vector_ : TEXCOORD2;
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
// メッシュの色

	output.color_ = LAMBERT_DIFFUSE_LIGHT_COLOR;

	
//------------------------------------------------------------
// デカール用テクスチャ座標

	output.texcoord_ = input.texcoord_;


//------------------------------------------------------------
// 頂点空間座標系の基底ベクトルの計算

	// 法線ベクトル
	float3 normal = input.normal_;
	
	// 接ベクトル
	float3 tangent = input.tangent_;

	// 従法線の算出
	float3 binormal = cross(normal, tangent);


//------------------------------------------------------------
// 視線ベクトルとライトベクトルを頂点空間座標系に変換

	// 視線ベクトル
	float3 eye_vector = CAMERA_POSITION - input.position_.xyz;
	output.eye_vector_.x = dot(eye_vector, tangent);
	output.eye_vector_.y = dot(eye_vector, binormal);
	output.eye_vector_.z = dot(eye_vector, normal);

	// ライトベクトル
	float3 light_vector = -LAMBERT_DIFFUSE_LIGHT_VECTOR.xyz;
	output.light_vector_.x = dot(light_vector, tangent);
	output.light_vector_.y = dot(light_vector, binormal);
	output.light_vector_.z = dot(light_vector, normal);

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
// バンプマッピング

	// 法線マップからの法線(テクスチャは0~1の為、2倍して-1.0fすることで-1~1の範囲にする)
	float normal = 2.0f * tex2D(NORMAL_SAMPLER, input.texcoord_).xyz - 1.0f;

	// ライトベクトル
	float3 light_vector = normalize(input.light_vector_);

	// 反射ベクトル
	float3 refraction_vector = reflect(-normalize(input.eye_vector_), normal);

	// 環境光の強さ
	float ambient = -LAMBERT_DIFFUSE_LIGHT_VECTOR.w;

	//return input.color_;//tex2D(DECALE_SAMPLER, input.texcoord_);

	input.color_ = input.color_ * tex2D(DECALE_SAMPLER, input.texcoord_)			// ランバート照明には頂点色とテクスチャの色を合成する
			* (max(0, dot(normal, light_vector)) + ambient)					
			+ 0.3f * pow(max(0, dot(refraction_vector, light_vector)), 8);

	input.color_.w = 1.0f;
	return input.color_;
//	return input.color_ * tex2D(DECALE_SAMPLER, input.texcoord_)			// ランバート照明には頂点色とテクスチャの色を合成する
//			* (max(0, dot(normal, light_vector)) + ambient)					
//			+ 0.3f * pow(max(0, dot(refraction_vector, light_vector)), 8);	// Phong鏡面反射光
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