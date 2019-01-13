//================================================================================
//!	@file	 EffekseerManager.cpp
//!	@brief	 エフェクシアマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// インクルード文
//****************************************
#include <algorithm>

#include "EffekseerManager.h"

#include <main.h>
#include <Renderer/Renderer.h>
#include <ComponentManager/DrawManager/Camera/Camera.h>



//****************************************
// 叙述関数クラス定義
//****************************************
class IsPlayingDisposableObject
{
public:
	bool operator()(EffekseerObject* object)
	{
		if (!object->getpIsPlaying())
		{
			object->Release();
			return true;
		}
		return false;
	};
};



//****************************************
// 定数定義
//****************************************
const std::string EffekseerManager::DEFAULT_PATH = "resource/Effekseer/";



//****************************************
// static変数定義
//****************************************
EffekseerManager* EffekseerManager::instance_ = nullptr;



//****************************************
// staticプロパティ定義
//****************************************
EffekseerManager* EffekseerManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new EffekseerManager();
	}
	return instance_;
}



//****************************************
// static関数定義
//****************************************
void EffekseerManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// プロパティ定義
//****************************************
EffekseerObject* EffekseerManager::getpObject(const std::string* key_name,
											  const std::string* file_path)
{
	// マップにあるかの確認
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		// 参照カウンタをUP
		iterator->second->AddReferenceCounter();

		return iterator->second;
	}

	// 新規作成
	std::string path = CreateFilePath(key_name, file_path);
	EffekseerObject* object = new EffekseerObject();
	object->Init(&path, key_name);
	object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, object));
	return object;
}



EffekseerObject* EffekseerManager::getpDisposableObject(const std::string* key_name,
														const std::string* file_path)
{
	// 新規作成
	std::string path = CreateFilePath(key_name, file_path);
	EffekseerObject* object = new EffekseerObject();
	object->Init(&path, key_name);
	object->AddReferenceCounter();
	object->setDisposable(true);
	disposable_object_.push_back(object);
	return object;
}



//****************************************
// 関数定義
//****************************************
EffekseerManager::EffekseerManager()
{
}



void EffekseerManager::Init()
{
	// マップの初期化
	object_map_.clear();

	// リストの初期化
	disposable_object_.clear();
}



void EffekseerManager::Uninit()
{
	// 各オブジェクトの強制解放
	auto iterator = object_map_.begin();
	while (iterator != object_map_.end())
	{
		iterator->second->ForcedRelease();
		iterator = object_map_.begin();
	}
	object_map_.clear();

	for (auto& contents : disposable_object_)
	{
		contents->ForcedRelease();
	}
	disposable_object_.clear();
}



void EffekseerManager::ReleaseFromTheMap(std::string* key_name)
{
	// マップから解放
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		object_map_.erase(iterator);
	}
}



void EffekseerManager::Update()
{
	// 各種更新
	for (auto contents : object_map_)
	{
		contents.second->ChangeViewMatrix(&view_matrix_);
		contents.second->ChangeProjectionMatrix(&projection_matrix_);
		contents.second->Update();
	}
	for (auto contents : disposable_object_)
	{
		contents->ChangeViewMatrix(&view_matrix_);
		contents->ChangeProjectionMatrix(&projection_matrix_);
		contents->Update();
	}

	// 使い捨てオブジェクト解放
	disposable_object_.erase(remove_if(disposable_object_.begin(),
									   disposable_object_.end(),
									   IsPlayingDisposableObject()),
							 disposable_object_.end());
}



void EffekseerManager::Draw()
{
	// 各種描画
	bool is_draw = false;
	for (auto contents : object_map_)
	{
		contents.second->Draw();
		is_draw = true;
	}
	for (auto contents : disposable_object_)
	{
		contents->Draw();
		is_draw = true;
	}
	if (!is_draw) return;

	// サンプラーステートを元に戻す
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())
		->SetDefaultSamplerState();
}



std::string EffekseerManager::CreateFilePath(const std::string* key_name,
											 const std::string* file_path)
{
	// デフォルトのパスを使用
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// 任意のパスを使用
	return *file_path + *key_name;
}



void EffekseerManager::CreateViewMatrix(Vec3 camera_position, Vec3 look_at_point, Vec3 camera_up)
{
	view_matrix_ = Effekseer::Matrix44().LookAtLH(Effekseer::Vector3D(camera_position.x, camera_position.y, camera_position.z),
												  Effekseer::Vector3D(look_at_point.x, look_at_point.y, look_at_point.z),
												  Effekseer::Vector3D(camera_up.x, camera_up.y, camera_up.z));
}



void EffekseerManager::CreateProjectionMatrix(int angle_of_view_)
{
	projection_matrix_ = Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(angle_of_view_),
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,
																Camera::NEAR_CLIPPING_PLANE,
																Camera::FAR_CLIPPING_PLANE);
}