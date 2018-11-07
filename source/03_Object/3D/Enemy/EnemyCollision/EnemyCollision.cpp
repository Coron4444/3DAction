//================================================================================
//
//    敵衝突クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "EnemyCollision.h"
#include "../Enemy.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <GameObjectManager\GameObjectManager.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const float EnemyCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float EnemyCollision::SUBSTANCE_RADIUS	   = 1.0f;



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

EnemyCollision::EnemyCollision()
		: CollisionComponent(CollisionComponent::State::ENEMY)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EnemyCollision::Init()
{
	// バウンディングスフィアの作成
	Sphere* temp_sphere = new Sphere(*GetGameObjectOrigin()->GetTransform()->GetPosition(), 
									 BOUNDING_SPHERE_RADIUS);
	
	bounding_sphere_ = new CollisionObject(temp_sphere, ObjectTag::BOUNDING_SPHERE);

	// バウンディングスフィアの登録
	AddCollisionObject(bounding_sphere_);


	// 本体スフィアの作成
	temp_sphere = new Sphere(*GetGameObjectOrigin()->GetTransform()->GetPosition(),
							 SUBSTANCE_RADIUS);

	substance_ = new CollisionObject(temp_sphere, ObjectTag::SUBSTANCE);

	// 本体スフィアの登録
	AddCollisionObject(substance_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EnemyCollision::Uninit()
{
	// スーパークラスの終了処理
	CollisionComponent::Uninit();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EnemyCollision::Update()
{
	// バウンディングスフィアの更新
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->GetCollisionShape();
	temp_sphere->position_ = *GetGameObjectOrigin()->GetTransform()->GetPosition();

	// 本体スフィアの更新
	temp_sphere = (Sphere*)substance_->GetCollisionShape();
	temp_sphere->position_ = *GetGameObjectOrigin()->GetTransform()->GetPosition();
}