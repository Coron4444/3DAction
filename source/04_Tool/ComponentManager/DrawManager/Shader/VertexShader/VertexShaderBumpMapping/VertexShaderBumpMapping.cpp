//================================================================================
//
//    バンプマッピング頂点シェーダークラス
//    Author : Araki Kai                                作成日 : 2018/11/17
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "VertexShaderBumpMapping.h"

#include <GameObjectManager/GameObjectManager.h>



//****************************************
// 定数定義
//****************************************
const char* VertexShaderBumpMapping::PATH = "resource/HLSL/Effect/VertexShader/BumpMapping.vsh";
const D3DVERTEXELEMENT9 VertexShaderBumpMapping::DECLARATION[]
= {{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
   {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
   {0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
   {0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
   D3DDECL_END()
};



//****************************************
// 静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +頂点宣言用メッシュ更新関数
//--------------------------------------------------
void VertexShaderBumpMapping::UpdateMeshDeclaration(ModelXObject* model_x)
{
	model_x->UpdateMeshDeclaration(DECLARATION);					// メッシュの変更
	D3DXComputeNormals(model_x->GetMesh(), nullptr);				// 法線を算出
	D3DXComputeTangent(model_x->GetMesh(), 0, 0, 0, TRUE, nullptr);	//接ベクトルを算出
}



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void VertexShaderBumpMapping::Init()
{
	// デバイス初期化
	InitDevice();

	// 頂点宣言オブジェクトの生成
	HRESULT hr = GetDevice()->CreateVertexDeclaration(DECLARATION,
													  &declaration_object_);

#ifdef _DEBUG
	assert(SUCCEEDED(hr) && "頂点宣言オブジェクトの生成に失敗(FixedPipelineObject.cpp)");
#else
	hr = hr;
#endif

	// シェーダーのコンパイル
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void VertexShaderBumpMapping::Uninit()
{
	// シェーダーの解放
	ReleaseVertexShader();
}



//--------------------------------------------------
// +共通設定関数
//--------------------------------------------------
void VertexShaderBumpMapping::CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index)
{
	// 行列のセット
	GetConstantTable()->SetMatrix(ShaderBase::GetDevice(),
								  "MATRIX_WORLD",
								  draw->getpMatrix(object_index));
	GetConstantTable()->SetMatrix(ShaderBase::GetDevice(),
								  "MATRIX_VIEW",
								  camera->getpViewMatrix());
	GetConstantTable()->SetMatrix(ShaderBase::GetDevice(),
								  "MATRIX_PROJECTION",
								  camera->getpProjectionMatrix());

	// ライト方向をセット
	Vec4 light_position = (Vec4)*GameObjectManager::GetDrawManager()
		->GetDirectionalLightVector();
	light_position.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->getpMatrix(object_index));
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vec3*)&light_position, (Vec3*)&light_position);
	light_position.w = -0.7f;		// 環境光の比率
	GetConstantTable()->SetVector(GetDevice(),
								  "LAMBERT_DIFFUSE_LIGHT_VECTOR",
								  &light_position);

	// 視点の設定(オブジェクトごとのローカル座標でのカメラの座標を取得する)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw->getpMatrix(object_index),
					   camera->getpViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	GetConstantTable()->SetVector(GetDevice(),
								  "CAMERA_POSITION",
								  &object_local_camera_position);

	// 頂点宣言
	GetDevice()->SetVertexDeclaration(declaration_object_);
}



//--------------------------------------------------
// +固有設定関数
//--------------------------------------------------
void VertexShaderBumpMapping::SpecificSetting(DrawBase* draw, Camera* camera,
											  unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	// ディヒューズ色の設定
	Vec4 lambert_diffuse_light_color_;
	lambert_diffuse_light_color_.x = draw->getpMaterial(object_index, mesh_index)->Diffuse.r;
	lambert_diffuse_light_color_.y = draw->getpMaterial(object_index, mesh_index)->Diffuse.g;
	lambert_diffuse_light_color_.z = draw->getpMaterial(object_index, mesh_index)->Diffuse.b;
	lambert_diffuse_light_color_.w = draw->getpMaterial(object_index, mesh_index)->Diffuse.a;
	GetConstantTable()->SetVector(GetDevice(),
								  "LAMBERT_DIFFUSE_LIGHT_COLOR",
								  &lambert_diffuse_light_color_);
}
