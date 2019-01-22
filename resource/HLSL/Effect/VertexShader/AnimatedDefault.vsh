//================================================================================
//!	@file	 AnimatedDefault.vsh
//!	@brief	 アニメーション付きデフォルト頂点シェーダ
//! @details 
//!	@author  Kai Araki									@date 2019/1/19
//================================================================================



//****************************************
// グローバル変数
//****************************************
// 変換行列
float4x4 MATRIX_WORLD;
float4x4 MATRIX_VIEW;
float4x4 MATRIX_PROJECTION;
float4x4 MATRIX_BONE[55];
int BONE_NUM = {4};



//****************************************
// 構造体定義
//****************************************
//************************************************************														   
//! @brief   インプットStruct
//!
//! @details インプットのStruct
//************************************************************
struct Input
{
    float4 position_    : POSITION;         //!< ローカル座標
    float3 normal_      : NORMAL;           //!< 法線ベクトル
    float4 color_       : COLOR0;           //!< 色
    float2 uv_          : TEXCOORD0;        //!< UV
    float4 bone_weight_ : BLENDWEIGHT;      //!< ボーンの重み
    int4 bone_index_    : BLENDINDICES;     //!< ボーンインデックス
};



//************************************************************														   
//! @brief   アウトプットStruct
//!
//! @details アウトプットのStruct
//************************************************************
struct Output
{
    float4 position_     : POSITION;    //!< 変換済み座標
    float4 color_        : COLOR0;      //!< 色
    float2 uv_           : TEXCOORD0;   //!< uv
};



//****************************************
// 関数宣言
//****************************************
void CalculateWorldPosition(Input input, inout Output output);
void CalculateBoneMatrix(Input input, inout float4x4 bone_matrix);



//****************************************
// 関数定義
//****************************************
//--------------------------------------------------
//! @brief エントリー関数
//! @details
//! @param input 入力データ 
//! @retval Output 出力データ
//--------------------------------------------------
Output MainVertexShader(Input input)
{
	// 出力データの初期化
    Output output = (Output)0;

    // ワールド座標算出
    CalculateWorldPosition(input, output);

    // 頂点色
    output.color_ = input.color_;

    // UV
    output.uv_ = input.uv_;

    return output;
}



//--------------------------------------------------
//! @brief ワールド座標算出関数
//! @details
//! @param input  入力データ
//! @param output 出力データ
//! @retval void なし
//--------------------------------------------------
void CalculateWorldPosition(Input input, inout Output output)
{
    // ボーン行列算出
    float4x4 bone_matrix = (float4x4)0;              
    CalculateBoneMatrix(input, bone_matrix);

    // ワールド座標算出
    input.position_.w = 1.0f;
    output.position_ = mul(input.position_, bone_matrix);
    output.position_ = mul(output.position_, MATRIX_WORLD);
    output.position_ = mul(output.position_, MATRIX_VIEW);
    output.position_ = mul(output.position_, MATRIX_PROJECTION);
}



//--------------------------------------------------
//! @brief ボーン行列算出関数
//! @details
//! @param input  入力データ
//! @param bone_matrix ボーン行列
//! @retval void なし
//--------------------------------------------------
void CalculateBoneMatrix(Input input, inout float4x4 bone_matrix)
{
    float weight[4] = (float[4])input.bone_weight_;     // 重みを配列に分解
    float total_bone_weight = 0.0f;                     // 重みの合計
    int bone_index;                                     // ボーンインデックス
    int blend_num = 4;                                  // ブレンド数
    int blend_num_minus_one = blend_num - 1;            // ブレンド数ｰ1

    // ボーン行列(ボーン数ｰ1)ブレンド
    for (int i = 0; i < blend_num_minus_one; i++)
    {
        total_bone_weight += weight[i];
        bone_index = input.bone_index_[i];
        bone_matrix += MATRIX_BONE[bone_index] * weight[i];
    }

    // 最後のボーン行列をブレンド
    float last_weight = 1.0f - total_bone_weight;
    bone_index = input.bone_index_[blend_num_minus_one];
    bone_matrix += MATRIX_BONE[bone_index] * last_weight;
}