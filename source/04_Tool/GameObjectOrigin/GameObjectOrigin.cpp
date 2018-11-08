//================================================================================
//
//    ゲームオブジェクトの原点クラス
//    Author : Araki Kai                                作成日 : 2018/03/22
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "GameObjectOrigin.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../ComponentManager/UpdateComponentManager/UpdateComponentManager.h"
#include "../ComponentManager/DrawComponentManager/DrawComponentManager.h"
#include "../ComponentManager/CollisionComponentManager/CollisionComponentManager.h"



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトコンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GameObjectOrigin::GameObjectOrigin(bool is_registration)
	: is_registration_    (is_registration),
	  update_component_   (nullptr),
	  draw_component_     (nullptr),
	  collision_component_(nullptr),
	  physics_            (nullptr)
{
	// オブジェクトマネージャーに登録
	if (!is_registration_) return;
	GameObjectManager::Registration(this);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GameObjectOrigin::~GameObjectOrigin()
{
	// 各種開放
	SafeRelease::Normal(&update_component_);
	SafeRelease::Normal(&draw_component_);
	SafeRelease::Normal(&collision_component_);
	SafeRelease::Normal(&physics_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ オブジェクト解放処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameObjectOrigin::ReleaseObject()
{
	// 派生先の終了処理
	Uninit();
}



//################################################################################
//
// [ スーパークラス初期化関数 ]
//
//################################################################################

void GameObjectOrigin::Init_SuperClass(UpdateComponent* update_component, DrawComponent* draw_component, CollisionComponent* collision_component)
{
	// コンポーネントをセット
	SetComponentAll(update_component, draw_component, collision_component);

	// ゲームオブジェクトの登録
	SetGameObject();

	// コンポーネントの初期化
	InitComponent();

	// コンポーネントの登録
	RegistrationComponentManager();
}



//################################################################################
//
// [ スーパークラス終了関数 ]
//
//################################################################################

void GameObjectOrigin::Uninit_SuperClass()
{
	// コンポーネントの終了処理
	UninitComponent();

	// コンポーネントの解放
	ReleaseComponentManager();
}



//################################################################################
//
// [ ゲームオブジェクトをセットする関数 ]
//
//################################################################################

void GameObjectOrigin::SetGameObject()
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



//################################################################################
//
// [ コンポーネント初期化関数 ]
//
//################################################################################

void GameObjectOrigin::InitComponent()
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



//################################################################################
//
// [ コンポーネント終了処理関数 ]
//
//################################################################################

void GameObjectOrigin::UninitComponent()
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



//################################################################################
//
// [ コンポーネントマネージャーへの登録関数 ]
//
//################################################################################

void GameObjectOrigin::RegistrationComponentManager()
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



//################################################################################
//
// [ コンポーネントマネージャーからの解放関数 ]
//
//################################################################################

void GameObjectOrigin::ReleaseComponentManager()
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