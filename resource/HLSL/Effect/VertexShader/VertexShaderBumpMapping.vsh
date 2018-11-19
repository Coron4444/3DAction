//================================================================================
//
//    バンプマッピング頂点シェーダー
//    Author : Araki Kai                                作成日 : 2018/08/07
//
//================================================================================



//****************************************
// グローバル変数
//****************************************
// 変換行列
float4x4 MATRIX_WORLD;
float4x4 MATRIX_VIEW;
float4x4 MATRIX_PROJECTION;

// ランバート拡散照明(ライトベクトルはプログラムで正規化)
float4 LAMBERT_DIFFUSE_LIGHT_VECTOR = { 1.0f, 0.0f, 0.0f, 1.0f };
float4 LAMBERT_DIFFUSE_LIGHT_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };

// カメラ座標
float3 CAMERA_POSITION = { 0.0f, 0.0f, 0.0f };



//****************************************
// 構造体定義
//****************************************
struct InputVertexShader
{
    float4 position_ : POSITION; // ローカル座標
    float3 normal_ : NORMAL; // 法線ベクトル
    float3 tangent_ : TANGENT0; // 接ベクトル
    float2 texcoord_ : TEXCOORD0; // 法線ベクトル
};


struct OutputVertexShader
{
    float4 position_ : POSITION;
    float4 color_ : COLOR0;
    float2 texcoord_ : TEXCOORD0; // 法線ベクトル
    float3 eye_vector_ : TEXCOORD1; // 視線ベクトル
    float3 light_vector_ : TEXCOORD2; // ライトベクトル
};



//****************************************
// 頂点シェーダー
//****************************************
//--------------------------------------------------
// +エントリ関数
//--------------------------------------------------
OutputVertexShader MainVertexShader(InputVertexShader input)
{
//------------------------------------------------------------
// 初期化

	// 出力データの作成
    OutputVertexShader output = (OutputVertexShader) 0;


//------------------------------------------------------------
// 座標変換
    
    output.position_ = mul(input.position_, MATRIX_WORLD);
    output.position_ = mul(output.position_, MATRIX_VIEW);
    output.position_ = mul(output.position_, MATRIX_PROJECTION);



//------------------------------------------------------------
// メッシュの色

    output.color_ = LAMBERT_DIFFUSE_LIGHT_COLOR;

	
//------------------------------------------------------------
// デカール用テクスチャ座標

    output.texcoord_ = input.texcoord_;


//------------------------------------------------------------
// 頂点空間座標系の基底ベクトルの計算

	// 従法線の算出
    float3 binormal = cross(input.normal_, input.tangent_);


//------------------------------------------------------------
// 視線ベクトルとライトベクトルを頂点空間座標系に変換

	// 視線ベクトル
    float3 eye_vector = CAMERA_POSITION - input.position_.xyz;
    output.eye_vector_.x = dot(eye_vector, input.tangent_);
    output.eye_vector_.y = dot(eye_vector, binormal);
    output.eye_vector_.z = dot(eye_vector, input.normal_);

	// ライトベクトル
    float3 light_vector = -LAMBERT_DIFFUSE_LIGHT_VECTOR.xyz;
    output.light_vector_.x = dot(light_vector, input.tangent_);
    output.light_vector_.y = dot(light_vector, binormal);
    output.light_vector_.z = dot(light_vector, input.normal_);

    return output;
}