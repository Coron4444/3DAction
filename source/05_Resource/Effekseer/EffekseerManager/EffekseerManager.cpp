//================================================================================
//
//    エフェクシアマネージャクラス(static)
//    Author : Araki Kai                                作成日 : 2018/08/30
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "EffekseerManager.h"
#include <main.h>
#include <Renderer/Renderer.h>
#include <ComponentManager/DrawManager/Camera/Camera.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const std::string EffekseerManager::DEFAULT_PATH = "resource/Effekseer/";
const int MAX_SPRITE_NUM = 2000;


//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

std::unordered_map<std::string, EffekseerArray*> EffekseerManager::share_effekseer_map_;
std::unordered_map<std::string, EffekseerArray*> EffekseerManager::unique_effekseer_map_;

Effekseer::Matrix44 EffekseerManager::projection_matrix_;
Effekseer::Matrix44 EffekseerManager::view_matrix_;



//======================================================================
//
// 静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数(全データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::InitAllData()
{
	// 各種初期化
	InitUniqueData();
	InitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数(共有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::InitShareData()
{
	// マップの初期化
	share_effekseer_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数(固有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::InitUniqueData()
{
	// マップの初期化
	unique_effekseer_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(全データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::UninitAllData()
{
	// 各種終了処理
	UninitUniqueData();
	UninitShareData();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(共有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::UninitShareData()
{
	// 各エフェクシアオブジェクト配列の解放
	for(auto& contents : share_effekseer_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// マップの全消去
	share_effekseer_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数(固有データ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::UninitUniqueData()
{
	// 各エフェクシアオブジェクト配列の解放
	for(auto& contents : unique_effekseer_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// マップの全消去
	unique_effekseer_map_.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::Update()
{
	for (auto contents : share_effekseer_map_)
	{
		contents.second->Update(&projection_matrix_, &view_matrix_);
	}

	for (auto contents : unique_effekseer_map_)
	{
		contents.second->Update(&projection_matrix_, &view_matrix_);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::Draw()
{
	bool is_draw = false;

	for (auto contents : share_effekseer_map_)
	{
		contents.second->Draw();
		is_draw = true;
	}

	for (auto contents : unique_effekseer_map_)
	{
		contents.second->Draw();
		is_draw = true;
	}

	if (!is_draw) return;

	// サンプラーステートを元に戻す
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->SetDefaultSamplerState();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 共有データの追加関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::AddShareData(const std::string* key_name, const std::string* file_path)
{
	// 共有データマップにあるかの確認
	auto itr_share = share_effekseer_map_.find(*key_name);
	if (itr_share != share_effekseer_map_.end()) return;
	
	// 固有データマップにあるかの確認
	auto itr_unique = unique_effekseer_map_.find(*key_name);
	if (itr_unique != unique_effekseer_map_.end()) return;

	// 存在しない場合
	std::string temp_path = MakeFilePath(key_name, file_path);
	EffekseerArray* temp_array = new EffekseerArray(&temp_path);
	share_effekseer_map_.insert(std::make_pair(*key_name, temp_array));
	return;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 固有データの追加関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::AddUniqueData(const std::string* key_name, const std::string* file_path)
{
	// 共有データマップにあるかの確認
	auto itr_share = share_effekseer_map_.find(*key_name);
	if (itr_share != share_effekseer_map_.end()) return;
	
	// 固有データマップにあるかの確認
	auto itr_unique = unique_effekseer_map_.find(*key_name);
	if (itr_unique != unique_effekseer_map_.end()) return;

	// 存在しない場合
	std::string temp_path = MakeFilePath(key_name, file_path);
	EffekseerArray* temp_array = new EffekseerArray(&temp_path);
	unique_effekseer_map_.insert(std::make_pair(*key_name, temp_array));
	return;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ エフェクシアオブジェクト取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::CreateDisposableEffekseerObject(const std::string* key_name, Vec3 position, 
													   Vec3 scale)
{
	// 共有データマップにあるかの確認
	auto itr_share = share_effekseer_map_.find(*key_name);
	if (itr_share != share_effekseer_map_.end())
	{
		CreateDisposableEffekseerObjectFromArray(itr_share->second, position, scale);
		return;
	}
	
	// 固有データマップにあるかの確認
	auto itr_unique = unique_effekseer_map_.find(*key_name);
	if (itr_unique != unique_effekseer_map_.end())
	{
		CreateDisposableEffekseerObjectFromArray(itr_unique->second, position, scale);
		return;
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ エフェクシアオブジェクト取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerObject* EffekseerManager::GetReferenceEffekseerObject(const std::string* key_name)
{
	// 共有データマップにあるかの確認
	auto itr_share = share_effekseer_map_.find(*key_name);
	if (itr_share != share_effekseer_map_.end()) return GetReferenceEffekseerObjectFromArray(itr_share->second);
	
	// 固有データマップにあるかの確認
	auto itr_unique = unique_effekseer_map_.find(*key_name);
	if (itr_unique != unique_effekseer_map_.end()) return GetReferenceEffekseerObjectFromArray(itr_unique->second);

	return nullptr;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ プロジェクション行列作成関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::CreateProjectionMatrix(int angle_of_view_)
{
	projection_matrix_ = Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(angle_of_view_), 
																(float)SCREEN_WIDTH / SCREEN_HEIGHT,  
																Camera::NEAR_CLIPPING_PLANE, 
																Camera::FAR_CLIPPING_PLANE);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ビュー行列作成関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerManager::CreateViewMatrix(Vec3 position, Vec3 look_at_point, Vec3 camera_up)
{
	view_matrix_ = Effekseer::Matrix44().LookAtLH(Effekseer::Vector3D(position.x, position.y, position.z),
												  Effekseer::Vector3D(look_at_point.x, look_at_point.y, look_at_point.z),
												  Effekseer::Vector3D(camera_up.x, camera_up.y, camera_up.z));
}



//--------------------------------------------------------------------------------
//
// [ ファイルパス作成関数 ]
//
//--------------------------------------------------------------------------------

std::string EffekseerManager::MakeFilePath(const std::string* key_name, const std::string* file_path)
{
	// デフォルトのパスを使用
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;
	
	// 任意のパスを使用
	return *file_path + *key_name;
}



//--------------------------------------------------------------------------------
//
// [ 参照エフェクシアオブジェクト取得関数 ]
//
//--------------------------------------------------------------------------------

EffekseerObject* EffekseerManager::GetReferenceEffekseerObjectFromArray(EffekseerArray* effekseer_array)
{
	return effekseer_array->GetReferenceEffekseerObject();
}



//--------------------------------------------------------------------------------
//
// [ 使い捨てエフェクシアオブジェクト取得関数 ]
//
//--------------------------------------------------------------------------------

void EffekseerManager::CreateDisposableEffekseerObjectFromArray(EffekseerArray* effekseer_array,
																Vec3 position, Vec3 scale)
{
	return effekseer_array->CreateDisposableEffekseerObject(position, scale);
}