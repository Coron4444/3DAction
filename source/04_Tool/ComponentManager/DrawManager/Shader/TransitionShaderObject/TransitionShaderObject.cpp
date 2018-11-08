//================================================================================
//
//    トランジションシェーダーオブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/08/21
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "TransitionShaderObject.h"
#include <Component/DrawComponent/DrawComponent.h>
#include <GameObjectOrigin/GameObjectOrigin.h>

#include <assert.h>

#include <Translation\Translation3D.h>
#include <Matrix\MatrixSRT_Axis.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const char* TestShaderObject::EFFECT_PATH = "resource/HLSL/Effect/obj/LambertLightingModel.obj";



//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

LimitedPointerArray<DrawComponent*, DrawComponentManager::DRAW_ARRAY_NUM> TestShaderObject::shader_;
	
LPDIRECT3DDEVICE9 TestShaderObject::device_;

D3DXMATRIX TestShaderObject::math_matrix_;

LPD3DXEFFECT TestShaderObject::effect_;
D3DXHANDLE   TestShaderObject::technique_;
D3DXHANDLE   TestShaderObject::matrix_WVP_;
D3DXHANDLE   TestShaderObject::matrix_WIT_;
D3DXHANDLE   TestShaderObject::diffuse_light_vector_;
D3DXHANDLE   TestShaderObject::diffuse_light_intensity_;
D3DXHANDLE   TestShaderObject::ambient_light_intensity_;
D3DXHANDLE   TestShaderObject::object_color_diffuse_;
D3DXHANDLE   TestShaderObject::object_color_ambient_;



//======================================================================
//
// 静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Init()
{
	// デバイスの取得
	device_ = RendererDirectX9::GetDevice();
	assert(device_ != nullptr && "デバイスの取得に失敗(FixedPipelineObject.cpp)");

	// エフェクトファイルの読み込み
	FILE* file_pointer = nullptr;
	file_pointer = fopen(EFFECT_PATH, "rb");
	if (file_pointer == nullptr)
	{
		MessageBox(nullptr, "エフェクトファイルの読み込みに失敗", "Error(TestShaderObject.cpp)", MB_OK);
	}

	// ファイルポインターの位置からファイルサイズを取得する(バイナリ―ファイルであるため有効)
	fseek(file_pointer, 0, SEEK_END);
	long file_size = ftell(file_pointer);
	fseek(file_pointer, 0, SEEK_SET);
	
	// ファイルの読み込み
	char* file_data = new char[file_size];
	fread(file_data, file_size, sizeof(char), file_pointer);
	fclose(file_pointer);

	// エフェクトファイルハンドラの取得
	LPD3DXBUFFER error_message = nullptr;
	HRESULT h_result = D3DXCreateEffect(device_,			// デバイス
										file_data,			// コンパイル済みfxデータ
										file_size,			// コンパイル済みfxデータのサイズ
										nullptr,			// プリプロセッサ定義へのポインタ
										nullptr,			// オプションのインタフェースへのポインタ
										0,					// D3DXSHADERで識別されるコンパイルオプション
										nullptr,			// 共有引数で使うID3DXEffectPoolオブジェクトへのポインタ
										&effect_,			// コンパイルされたエフェクトの格納先
										&error_message);	// コンパイルエラー一覧の格納先
	if (FAILED(h_result))
	{
		MessageBox(nullptr, "エフェクトファイルハンドラの取得に失敗", "Error(TestShaderObject.cpp)", MB_OK);
	}

	// テクニックハンドラの取得
	technique_  = effect_->GetTechniqueByName("Techique01");
	
	// 定数ハンドラの取得
	matrix_WVP_				 = effect_->GetParameterByName(NULL, "MATRIX_WVP");
	matrix_WIT_				 = effect_->GetParameterByName(NULL, "MATRIX_WIT");
	diffuse_light_vector_    = effect_->GetParameterByName(NULL, "DIFFUSE_LIGHT_VECTOR");
	diffuse_light_intensity_ = effect_->GetParameterByName(NULL, "DIFFUSE_LIGHT_INTENSITY");
	ambient_light_intensity_ = effect_->GetParameterByName(NULL, "AMBIENT_LIGHT_INTENSITY");
	object_color_diffuse_    = effect_->GetParameterByName(NULL, "OBJECT_COLOR_DIFFUSE");
	object_color_ambient_    = effect_->GetParameterByName(NULL, "OBJECT_COLOR_AMBIENT");

	// 各種開放
	SafeReleaseDirectX9(&error_message);
	delete[] file_data;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Uninit()
{
	// 配列のリセット
	ResetArray();

	// 各種開放
	SafeReleaseDirectX9(&effect_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Draw(Camera* camera)
{
	// テクニック設定
	effect_->SetTechnique(technique_);
	
	// シェーダーでのレンダリング開始
	effect_->Begin(nullptr, 0);
	
	// パスを設定
	effect_->BeginPass(0);

	// 頂点宣言
	LPDIRECT3DDEVICE9 device = RendererDirectX9::GetDevice();
	if (device == nullptr)
	{
		MessageBox(nullptr, "D3DDeviceの取得に失敗", "Error(TestShaderObject.cpp)", MB_OK);
	}
	//device->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	device->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// 描画
	for(unsigned i = 0; i < shader_.GetEndPointer(); i++)
	{
		// ワールド変換行列(WVP)をセット
		D3DXMatrixMultiply(&math_matrix_, shader_.GetArrayObject(i)->GetGameObjectOrigin()->matrix_->GetWorldMatrixPointer(), camera->GetViewMatrix());
		D3DXMatrixMultiply(&math_matrix_, &math_matrix_, camera->GetProjectionMatrix());
		effect_->SetMatrix(matrix_WVP_, &math_matrix_);

		// 法線用ワールド変換行列(WVP)をセット
		D3DXMatrixInverse(&math_matrix_, NULL, shader_.GetArrayObject(i)->GetGameObjectOrigin()->matrix_->GetWorldMatrixPointer());
		D3DXMatrixTranspose(&math_matrix_, &math_matrix_);
		effect_->SetMatrix(matrix_WIT_, &math_matrix_);

		// ライト方向をセット
		Vec4 light_position(-0.577f, -0.577f, -0.577f, 0.0f);
		effect_->SetVector(diffuse_light_vector_, &light_position);

		// マテリアルの設定
		Vec4 temp_vector;
		for (unsigned j = 0; j < shader_.GetArrayObject(i)->GetMeshNum(); j++)
		{
			// ディヒューズ色の設定
			temp_vector.x = shader_.GetArrayObject(i)->GetMaterial(j)->Diffuse.r;
			temp_vector.y = shader_.GetArrayObject(i)->GetMaterial(j)->Diffuse.g;
			temp_vector.z = shader_.GetArrayObject(i)->GetMaterial(j)->Diffuse.b;
			temp_vector.w = shader_.GetArrayObject(i)->GetMaterial(j)->Diffuse.a;
			effect_->SetVector(object_color_diffuse_, &temp_vector);
			
			// アンビエント色の設定
			temp_vector.x = shader_.GetArrayObject(i)->GetMaterial(j)->Ambient.r;
			temp_vector.y = shader_.GetArrayObject(i)->GetMaterial(j)->Ambient.g;
			temp_vector.z = shader_.GetArrayObject(i)->GetMaterial(j)->Ambient.b;
			temp_vector.w = shader_.GetArrayObject(i)->GetMaterial(j)->Ambient.a;
			effect_->SetVector(object_color_ambient_, &temp_vector);

			// 設定確定
			effect_->CommitChanges();

			// 描画
			shader_.GetArrayObject(i)->Draw();
		}
	}
	
	// パスを解除
	effect_->EndPass();

	// シェーダーでのレンダリング終了
	effect_->End();
}



//================================================================================
//
// [ 描画コンポーネント配列のリセット関数 ]
//
//================================================================================

void TestShaderObject::ResetArray()
{
	// 配列リセット
	shader_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画コンポーネント振り分け関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::DistributeDrawComponent(DrawComponent* draw_component, Camera* camera)
{
	switch (draw_component->GetState())
	{
		case DrawComponent::State::TEST_SHADER :
		{
			shader_.AddToArray(draw_component);
			break;
		}

		case DrawComponent::State::FIXED_BILLBOARD :
		{
			ShaderObjectCommonMethod::SetBillboardMatrix(draw_component, camera);
			shader_.AddToArray(draw_component);
			break;
		}
		default :
		{
			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 透明描画コンポーネントのソート関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::SortTransparent(Camera* camera)
{
	ShaderObjectCommonMethod::SortTransparent(&shader_, camera);
}