//================================================================================
//
//    ゲームオブジェクト基底クラス
//    Author : Araki Kai                                作成日 : 2018/03/22
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "GameObjectBase.h"

#include "../GameObjectManager/GameObjectManager.h"
#include "../ComponentManager/UpdateComponentManager/UpdateComponentManager.h"
#include "../ComponentManager/DrawComponentManager/DrawComponentManager.h"
#include "../ComponentManager/CollisionComponentManager/CollisionComponentManager.h"



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +コンストラクタ
//--------------------------------------------------
GameObjectBase::GameObjectBase(bool is_registration)
	: is_registration_(is_registration),
	physics_(nullptr),
	update_component_(nullptr),
	draw_component_(nullptr),
	collision_component_(nullptr)
{
	// オブジェクトマネージャーに登録
	if (!is_registration_) return;
	GameObjectManager::Registration(this);
}



//--------------------------------------------------
// +デストラクタ
//--------------------------------------------------
GameObjectBase::~GameObjectBase()
{
	// 各種開放
	SafeRelease::Normal(&update_component_);
	SafeRelease::Normal(&draw_component_);
	SafeRelease::Normal(&collision_component_);
	SafeRelease::Normal(&physics_);
}


//--------------------------------------------------
// +オブジェクト解放関数
//--------------------------------------------------
void GameObjectBase::ReleaseObject()
{
	// 派生先の終了処理
	Uninit();
}



//--------------------------------------------------
// +オブジェクト解放関数
//--------------------------------------------------
void GameObjectBase::CreatePhysics()
{
	if (physics_ != nullptr) return;
	physics_ = new Physics(this);
}



//--------------------------------------------------
// #基底クラス初期化関数
//--------------------------------------------------
void GameObjectBase::BaseClassInit(UpdateComponent* update_component, 
								   DrawComponent* draw_component, 
								   CollisionComponent* collision_component)
{
	// コンポーネントをセット
	SetAllComponent(update_component, draw_component, collision_component);
	
	// コンポーネントをマネージャへ設定
	SetComponentToManager();

	// ゲームオブジェクトをコンポーネントに設定
	SetGameObjectToComponent();

	// コンポーネントの初期化
	InitComponent();
}



//--------------------------------------------------
// #基底クラス終了関数
//--------------------------------------------------
void GameObjectBase::BaseClassUninit()
{
	// コンポーネントをマネージャから解放
	ReleaseComponentFromManager();

	// コンポーネントの終了処理
	UninitComponent();

}



//--------------------------------------------------
// -コンポーネント初期化関数
//--------------------------------------------------
void GameObjectBase::InitComponent()
{
	if (update_component_ != nullptr)
	{
		update_component_->Init();
	}

	if (draw_component_ != nullptr)
	{
		draw_component_->Init();
	}

	if (collision_component_ != nullptr)
	{
		collision_component_->Init();
	}
}



//--------------------------------------------------
// -コンポーネント終了関数
//--------------------------------------------------
void GameObjectBase::UninitComponent()
{
	if (update_component_ != nullptr)
	{
		update_component_->Uninit();
	}

	if (draw_component_ != nullptr)
	{
		draw_component_->Uninit();
	}

	if (collision_component_ != nullptr)
	{
		collision_component_->Uninit();
	}
}


//--------------------------------------------------
// -コンポーネントをマネージャーへ設定関数
//--------------------------------------------------
void GameObjectBase::SetComponentToManager()
{
	if (update_component_ != nullptr)
	{
		UpdateComponentManager::RegistrationComponent(update_component_);
	}

	if (draw_component_ != nullptr)
	{
		DrawComponentManager::RegistrationComponent(draw_component_);
	}

	if (collision_component_ != nullptr)
	{
		CollisionComponentManager::RegistrationComponent(collision_component_);
	}
}


//--------------------------------------------------
// -コンポーネントをマネージャーから解放関数
//--------------------------------------------------
void GameObjectBase::ReleaseComponentFromManager()
{
	if (update_component_ != nullptr)
	{
		UpdateComponentManager::ReleaseComponent(update_component_);
	}

	if (draw_component_ != nullptr)
	{
		DrawComponentManager::ReleaseComponent(draw_component_);
	}

	if (collision_component_ != nullptr)
	{
		CollisionComponentManager::ReleaseComponent(collision_component_);
	}
}



//--------------------------------------------------
// -ゲームオブジェクトをコンポーネントに設定関数
//--------------------------------------------------
void GameObjectBase::SetGameObjectToComponent()
{
	if (update_component_ != nullptr)
	{
		update_component_->SetGameObjectOrigin(this);
	}

	if (draw_component_ != nullptr)
	{
		draw_component_->SetGameObjectOrigin(this);
	}

	if (collision_component_ != nullptr)
	{
		collision_component_->SetGameObjectOrigin(this);
	}
}