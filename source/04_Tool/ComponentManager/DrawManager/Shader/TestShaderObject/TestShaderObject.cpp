//================================================================================
//
//    テストシェーダーオブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/07/09
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include <assert.h>

#include "TestShaderObject.h"
#include <ComponentManager/DrawManager/Camera/Camera.h>
#include <Component/DrawBase/DrawBase.h>
#include <GameObjectBase/GameObjectBase.h>

#include <Renderer/Renderer.h>
#include <Transform\Transform.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const char* TestShaderObject::EFFECT_PATH = "resource/HLSL/Effect/obj/BumpMapping.obj";
const D3DVERTEXELEMENT9 TestShaderObject::DECLARATION[] 
	= {{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	   {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
       {0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
       {0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	   D3DDECL_END()
      };


//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

LPDIRECT3DDEVICE9 TestShaderObject::device_;

D3DXMATRIX TestShaderObject::math_matrix_;

IDirect3DVertexDeclaration9* TestShaderObject::declaration_object_;

LPD3DXEFFECT TestShaderObject::effect_;
D3DXHANDLE   TestShaderObject::technique_;
D3DXHANDLE   TestShaderObject::matrix_WVP_;
D3DXHANDLE   TestShaderObject::lambert_diffuse_light_vector_;
D3DXHANDLE   TestShaderObject::lambert_diffuse_light_color_;
D3DXHANDLE   TestShaderObject::camera_position_;
D3DXHANDLE   TestShaderObject::decale_texture_;
D3DXHANDLE   TestShaderObject::normal_texture_;




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
	Renderer::GetInstance()->GetDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(TestShaderObject.cpp)", "Error", MB_OK);
		return;
	}

	// 頂点宣言オブジェクトの生成
	HRESULT hr = device_->CreateVertexDeclaration(DECLARATION, &declaration_object_);
	

#ifdef _DEBUG
	assert(SUCCEEDED(hr) && "頂点宣言オブジェクトの生成に失敗(FixedPipelineObject.cpp)");
#else
	hr = hr;
#endif

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
	matrix_WVP_					  = effect_->GetParameterByName(NULL, "MATRIX_WVP");
	lambert_diffuse_light_vector_ = effect_->GetParameterByName(NULL, "LAMBERT_DIFFUSE_LIGHT_VECTOR");
	lambert_diffuse_light_color_  = effect_->GetParameterByName(NULL, "LAMBERT_DIFFUSE_LIGHT_COLOR");
	camera_position_			  = effect_->GetParameterByName(NULL, "CAMERA_POSITION");
	decale_texture_			      = effect_->GetParameterByName(NULL, "DECALE_TEXTURE");
	normal_texture_			      = effect_->GetParameterByName(NULL, "NORMAL_TEXTURE");

	// 各種開放
	SafeRelease::PlusRelease(&error_message);
	delete[] file_data;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Uninit()
{
	// 各種開放
	SafeRelease::PlusRelease(&effect_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::Draw(DrawBase* draw, Camera* camera)
{
	// テクニック設定
	effect_->SetTechnique(technique_);
	
	// シェーダーでのレンダリング開始
	effect_->Begin(nullptr, 0);
	
	// パスを設定
	effect_->BeginPass(0);
	
	// 描画

	// ワールド変換行列(WVP)をセット
	D3DXMatrixMultiply(&math_matrix_, draw->GetGameObject()->GetTransform()->GetWorldMatrix(), camera->GetViewMatrix());
	D3DXMatrixMultiply(&math_matrix_, &math_matrix_, camera->GetProjectionMatrix());
	effect_->SetMatrix(matrix_WVP_, &math_matrix_);

	// ライト方向をセット
	D3DXMatrixIdentity(&math_matrix_);
	Vec4 light_position(0.5f, -1.0f, 0.8f, 0.0f);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->GetGameObject()->GetTransform()->GetWorldMatrix());
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vec3*)&light_position, (Vec3*)&light_position);
	light_position.w = -0.7f;		// 環境光の比率
	effect_->SetVector(lambert_diffuse_light_vector_, &light_position);
	
	// 視点の設定(オブジェクトごとのローカル座標でのカメラの座標を取得する)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw->GetGameObject()->GetTransform()->GetWorldMatrix(), camera->GetViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	effect_->SetVector(camera_position_, &object_local_camera_position);

	// 頂点宣言
	device_->SetVertexDeclaration(declaration_object_);

	// メッシュ数分描画
	Vec4 temp_vector;
	for (unsigned i = 0; i < draw->GetMeshNum(); i++)
	{
		// ディヒューズ色の設定
		temp_vector.x = draw->GetMaterial(i)->Diffuse.r;
		temp_vector.y = draw->GetMaterial(i)->Diffuse.g;
		temp_vector.z = draw->GetMaterial(i)->Diffuse.b;
		temp_vector.w = draw->GetMaterial(i)->Diffuse.a;
		effect_->SetVector(lambert_diffuse_light_color_, &temp_vector);
		
		// デカールテクスチャの設定
		LPDIRECT3DTEXTURE9 temp = draw->GetDecaleTexture(i);
		temp = temp;
		effect_->SetTexture(decale_texture_, temp);

		// 法線マップの設定
		effect_->SetTexture(normal_texture_, draw->GetNormalTexture(i));

		// シェーダーの設定確定
		effect_->CommitChanges();
		
		// 描画
		draw->Draw(i);
	}
	
	
	// パスを解除
	effect_->EndPass();

	// シェーダーでのレンダリング終了
	effect_->End();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 頂点宣言用メッシュ更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TestShaderObject::UpdateMeshDeclaration(ModelXObject* model_x)
{
	model_x->UpdateMeshDeclaration(DECLARATION);					// メッシュの変更
	D3DXComputeNormals(model_x->GetMesh(), nullptr);				// 法線を算出
	D3DXComputeTangent(model_x->GetMesh(), 0, 0, 0, TRUE,nullptr);	//接ベクトルを算出
}