//================================================================================
//!	@file	 VertexShaderBumpMapping.cpp
//!	@brief	 バンプマッピング頂点シェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "VertexShaderBumpMapping.h"

#include <GameObjectManager/GameObjectManager.h>
#include <ModelX/ModelXManager/ModelXManager.h>



//****************************************
// 定数定義
//****************************************
const D3DVERTEXELEMENT9 VertexShaderBumpMapping::DECLARATION[] =
{
	{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
	{0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
	{0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
};

const char* VertexShaderBumpMapping::PATH = "resource/HLSL/Effect/VertexShader/BumpMapping.vsh";



//****************************************
// static関数定義
//****************************************
void VertexShaderBumpMapping::UpdateMeshDeclaration(ModelXObject* model_x)
{
	model_x->UpdateMeshDeclaration(DECLARATION);						// メッシュの変更
	D3DXComputeNormals(model_x->getpMesh(), nullptr);					// 法線を算出
	D3DXComputeTangent(model_x->getpMesh(), 0, 0, 0, TRUE, nullptr);	//接ベクトルを算出
}



//****************************************
// 関数定義
//****************************************
void VertexShaderBumpMapping::Init()
{
	// デバイス初期化
	InitDevice();

	// 頂点宣言オブジェクトの生成
	getpDevice()->CreateVertexDeclaration(DECLARATION, &declaration_object_);

	// シェーダーのコンパイル
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");
}



void VertexShaderBumpMapping::Uninit()
{
	// シェーダーの解放
	ReleaseVertexShader();
}



void VertexShaderBumpMapping::ObjectSetting(DrawBase* draw, Camera* camera,
											unsigned object_index)
{
	// 行列のセット
	getpConstantTable()->SetMatrix(getpDevice(),
								   "MATRIX_WORLD",
								   draw->getpMatrix(object_index));
	getpConstantTable()->SetMatrix(getpDevice(),
								   "MATRIX_VIEW",
								   camera->getpViewMatrix());
	getpConstantTable()->SetMatrix(getpDevice(),
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
	getpConstantTable()->SetVector(getpDevice(),
								   "LAMBERT_DIFFUSE_LIGHT_VECTOR",
								   &light_position);

	// 視点の設定(オブジェクトごとのローカル座標でのカメラの座標を取得する)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw->getpMatrix(object_index),
					   camera->getpViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	getpConstantTable()->SetVector(getpDevice(),
								   "CAMERA_POSITION",
								   &object_local_camera_position);

	// 頂点宣言
	getpDevice()->SetVertexDeclaration(declaration_object_);
}



//--------------------------------------------------
// +固有設定関数
//--------------------------------------------------
void VertexShaderBumpMapping::MeshSetting(DrawBase* draw, Camera* camera,
										  unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	// ディヒューズ色の設定
	Vec4 lambert_diffuse_light_color_;
	lambert_diffuse_light_color_.x = draw->getpMaterial(object_index, mesh_index)->Diffuse.r;
	lambert_diffuse_light_color_.y = draw->getpMaterial(object_index, mesh_index)->Diffuse.g;
	lambert_diffuse_light_color_.z = draw->getpMaterial(object_index, mesh_index)->Diffuse.b;
	lambert_diffuse_light_color_.w = draw->getpMaterial(object_index, mesh_index)->Diffuse.a;
	getpConstantTable()->SetVector(getpDevice(),
								   "LAMBERT_DIFFUSE_LIGHT_COLOR",
								   &lambert_diffuse_light_color_);
}
