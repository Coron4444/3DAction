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

#include <GameObjectManager/GameObjectManager.h>
#include <ComponentManager/UpdateManager/UpdateManager.h>
#include <ComponentManager/DrawManager/DrawManager.h>
#include <ComponentManager/CollisionManager/CollisionManager.h>



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +コンストラクタ
//--------------------------------------------------
GameObjectBase::GameObjectBase(bool is_registration)
	: is_registration_(is_registration),
	physics_(nullptr),
	update_(nullptr),
	draw_(nullptr),
	collision_(nullptr)
{
}



//--------------------------------------------------
// +デストラクタ
//--------------------------------------------------
GameObjectBase::~GameObjectBase()
{
	// 各種開放
	SafeRelease::Normal(&update_);
	SafeRelease::Normal(&draw_);
	SafeRelease::Normal(&collision_);
	SafeRelease::Normal(&physics_);
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void GameObjectBase::Uninit()
{
	// コンポーネントの終了処理
	UninitComponent();
}



//--------------------------------------------------
// +剛体生成関数
//--------------------------------------------------
void GameObjectBase::CreatePhysics()
{
	if (physics_ != nullptr) return;
	physics_ = new Physics(this);
}



//--------------------------------------------------
// #基底クラス初期化関数
//--------------------------------------------------
void GameObjectBase::Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision)
{
	// コンポーネントをセット
	SetAllComponent(update, draw, collision);

	// コンポーネントの初期化
	InitComponent();

	// オブジェクトマネージャーに登録
	if (!is_registration_) return;
	GameObjectManager::AddGameObjectBaseToArray(this);
}



//--------------------------------------------------
// -コンポーネント初期化関数
//--------------------------------------------------
void GameObjectBase::InitComponent()
{
	if (update_ != nullptr)
	{
		update_->setGameObject(this);
		update_->Init();
	}

	if (draw_ != nullptr)
	{
		draw_->setGameObject(this);
		draw_->Init();
	}

	if (collision_ != nullptr)
	{
		collision_->setGameObject(this);
		collision_->Init();
	}
}



//--------------------------------------------------
// -コンポーネント終了関数
//--------------------------------------------------
void GameObjectBase::UninitComponent()
{
	if (update_ != nullptr)
	{
		update_->Uninit();
	}

	if (draw_ != nullptr)
	{
		draw_->Uninit();
	}

	if (collision_ != nullptr)
	{
		collision_->Uninit();
	}
}