//================================================================================
//
//    深度バッファシャドウオブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/09/24
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include <assert.h>

#include "DepthBufferShadowObject.h"

#include <main.h>
#include <ComponentManager\DrawComponentManager\Camera\Camera.h>
#include <Component/DrawComponent/DrawComponent.h>
#include <GameObjectOrigin/GameObjectOrigin.h>

#include <Transform\Transform.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const char* DepthBufferShadowObject::EFFECT_PATH = "resource/HLSL/Effect/obj/BumpMapping.obj";
const D3DVERTEXELEMENT9 DepthBufferShadowObject::DECLARATION[] 
	= {{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	   {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
	   D3DDECL_END()
      };

const Vec2 DepthBufferShadowObject::SHADOW_MAP_SIZE(SCREEN_WIDTH, SCREEN_HEIGHT);


//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

LPDIRECT3DDEVICE9 DepthBufferShadowObject::device_;

D3DXMATRIX DepthBufferShadowObject::math_matrix_;

IDirect3DVertexDeclaration9* DepthBufferShadowObject::declaration_object_;

LPDIRECT3DTEXTURE9 DepthBufferShadowObject::shadow_map_;
LPDIRECT3DSURFACE9 DepthBufferShadowObject::shadow_map_render_target_surface_;
LPDIRECT3DSURFACE9 DepthBufferShadowObject::shadow_map_depth_buffer_surface_;
D3DVIEWPORT9	   DepthBufferShadowObject::shadow_map_view_port_;
Camera			   DepthBufferShadowObject::shadow_map_camera_(nullptr, Camera::Type::NONE);

LPDIRECT3DSURFACE9 DepthBufferShadowObject::old_render_target_surface_;
LPDIRECT3DSURFACE9 DepthBufferShadowObject::old_depth_buffer_surface_;
D3DVIEWPORT9	   DepthBufferShadowObject::old_view_port_;

LPD3DXEFFECT DepthBufferShadowObject::effect_;
D3DXHANDLE   DepthBufferShadowObject::technique_;
D3DXHANDLE   DepthBufferShadowObject::matrix_WVP_;
D3DXHANDLE   DepthBufferShadowObject::lambert_diffuse_light_vector_;
D3DXHANDLE   DepthBufferShadowObject::lambert_diffuse_light_color_;
D3DXHANDLE   DepthBufferShadowObject::camera_position_;
D3DXHANDLE   DepthBufferShadowObject::decale_texture_;
D3DXHANDLE   DepthBufferShadowObject::normal_texture_;




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

void DepthBufferShadowObject::Init()
{
	// デバイスの取得
	device_ = RendererDirectX9::GetDevice();
	assert(device_ != nullptr && "デバイスの取得に失敗(FixedPipelineObject.cpp)");

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
		MessageBox(nullptr, "エフェクトファイルの読み込みに失敗", "Error(DepthBufferShadowObject.cpp)", MB_OK);
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
		MessageBox(nullptr, "エフェクトファイルハンドラの取得に失敗", "Error(DepthBufferShadowObject.cpp)", MB_OK);
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
	SafeReleaseDirectX9(&error_message);
	delete[] file_data;

	// シャドウマップの作成
	h_result = device_->CreateTexture(SHADOW_MAP_SIZE.x, SHADOW_MAP_SIZE.y,
									  1,
									  D3DUSAGE_RENDERTARGET,
									  D3DFMT_A8R8G8B8,
									  D3DPOOL_DEFAULT,
									  &shadow_map_,
									  NULL);

	if (FAILED(h_result))
	{
		MessageBox(nullptr, "シャドウマップの作成に失敗", "Error(DepthBufferShadowObject.cpp)", MB_OK);
	}

	// シャドウマップからレンダリングターゲットサーフェスを取得する
	h_result = shadow_map_->GetSurfaceLevel(0, &shadow_map_render_target_surface_);

	if (FAILED(h_result))
	{
		MessageBox(nullptr, "シャドウマップのサーフェス取得に失敗", "Error(DepthBufferShadowObject.cpp)", MB_OK);
	}
	
	// シャドウマップと同じ大きさを持つ深度バッファサーフェスの作成(深度バッファが小さいとZテストがキャンセルされるため)
	h_result = device_->CreateDepthStencilSurface(SHADOW_MAP_SIZE.x, SHADOW_MAP_SIZE.y,
												  D3DFMT_D16,								
												  D3DMULTISAMPLE_NONE,
												  0,
												  TRUE,
												  &shadow_map_depth_buffer_surface_,		
												  NULL);

	if (FAILED(h_result))
	{
		MessageBox(nullptr, "シャドウマップの深度バッファサーフェスの作成に失敗", "Error(DepthBufferShadowObject.cpp)", MB_OK);
	}

	// ビューポートの作成(画面の大きさと違う場合は必要)
	shadow_map_view_port_ = {0, 0,									// 左上座標
							 SHADOW_MAP_SIZE.x, SHADOW_MAP_SIZE.y,	// 幅高さ
							 0.0f, 1.0f};							// 前面、後面

	// 元のレンダーターゲットを取得
	device_->GetRenderTarget(0, &old_render_target_surface_);
	device_->GetDepthStencilSurface(&old_depth_buffer_surface_);
	device_->GetViewport(&old_view_port_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::Uninit()
{
	// 各種開放
	SafeReleaseDirectX9(&effect_);
	SafeReleaseDirectX9(&shadow_map_);
	SafeReleaseDirectX9(&shadow_map_render_target_surface_);
	SafeReleaseDirectX9(&shadow_map_render_target_surface_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ レンダーターゲット設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::SetRenderTarget()
{
	// レンダーターゲットの変更
	device_->SetRenderTarget(0, shadow_map_render_target_surface_);
	device_->SetDepthStencilSurface(shadow_map_depth_buffer_surface_);
	device_->SetViewport(&shadow_map_view_port_);

	// シャドウマップのクリア
	device_->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(1, 1, 1, 1),
		1.0f,
		0);

	// ライト方向から見た射影空間への行列
	*shadow_map_camera_.GetPositon() = {10.0f, 10.0f, 0.0f};
	shadow_map_camera_.CreateViewMatrix();
	shadow_map_camera_.CreateProjectionMatrix(0.25f * D3DX_PI, 1.0f, 5.0f, 12.0f);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 古いレンダーターゲット設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::SetOldRenderTarget()
{
	// レンダーターゲットの変更
	device_->SetRenderTarget(0, old_render_target_surface_);
	device_->SetDepthStencilSurface(old_depth_buffer_surface_);
	device_->SetViewport(&old_view_port_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::Draw_Pass0(DrawComponent* draw_component, Camera* camera)
{	
	// テクニック設定
	effect_->SetTechnique(technique_);
	
	// シェーダーでのレンダリング開始
	effect_->Begin(nullptr, 0);
	
	// パスを設定
	effect_->BeginPass(0);

	// 頂点宣言
	device_->SetVertexDeclaration(declaration_object_);
	
	// ワールド変換行列(WVP)をセット
	D3DXMatrixMultiply(&math_matrix_, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix(), shadow_map_camera_.GetViewMatrix());
	D3DXMatrixMultiply(&math_matrix_, &math_matrix_, shadow_map_camera_.GetProjectionMatrix());
	effect_->SetMatrix(matrix_WVP_, &math_matrix_);

	// メッシュ数分描画
	Vec4 temp_vector;
	for (unsigned i = 0; i < draw_component->GetMeshNum(); i++)
	{
		// シェーダーの設定確定
		effect_->CommitChanges();
		
		// 描画
		draw_component->Draw(i);
	}
	
	
	// パスを解除
	effect_->EndPass();

	// シェーダーでのレンダリング終了
	effect_->End();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::Draw_Pass0(DrawComponent* draw_component, Camera* camera)
{
	// テクニック設定
	effect_->SetTechnique(technique_);

	// シェーダーでのレンダリング開始
	effect_->Begin(nullptr, 0);

	// パスを設定
	effect_->BeginPass(0);

	// 描画

	// ワールド変換行列(WVP)をセット
	D3DXMatrixMultiply(&math_matrix_, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix(), camera->GetViewMatrix());
	D3DXMatrixMultiply(&math_matrix_, &math_matrix_, camera->GetProjectionMatrix());
	effect_->SetMatrix(matrix_WVP_, &math_matrix_);

	// ライト方向をセット
	D3DXMatrixIdentity(&math_matrix_);
	Vec4 light_position(0.5f, -1.0f, 0.8f, 0.0f);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix());
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vec3*)&light_position, (Vec3*)&light_position);
	light_position.w = -0.7f;		// 環境光の比率
	effect_->SetVector(lambert_diffuse_light_vector_, &light_position);

	// 視点の設定(オブジェクトごとのローカル座標でのカメラの座標を取得する)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix(), camera->GetViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	effect_->SetVector(camera_position_, &object_local_camera_position);

	// 頂点宣言
	device_->SetVertexDeclaration(declaration_object_);

	// メッシュ数分描画
	Vec4 temp_vector;
	for (unsigned i = 0; i < draw_component->GetMeshNum(); i++)
	{
		// ディヒューズ色の設定
		temp_vector.x = draw_component->GetMaterial(i)->Diffuse.r;
		temp_vector.y = draw_component->GetMaterial(i)->Diffuse.g;
		temp_vector.z = draw_component->GetMaterial(i)->Diffuse.b;
		temp_vector.w = draw_component->GetMaterial(i)->Diffuse.a;
		effect_->SetVector(lambert_diffuse_light_color_, &temp_vector);

		// デカールテクスチャの設定
		LPDIRECT3DTEXTURE9 temp = draw_component->GetDecaleTexture(i);
		temp = temp;
		effect_->SetTexture(decale_texture_, temp);

		// 法線マップの設定
		effect_->SetTexture(normal_texture_, draw_component->GetNormalTexture(i));

		// シェーダーの設定確定
		effect_->CommitChanges();

		// 描画
		draw_component->Draw(i);
	}

	// パスを解除
	effect_->EndPass();

	// シェーダーでのレンダリング終了
	effect_->End();
}