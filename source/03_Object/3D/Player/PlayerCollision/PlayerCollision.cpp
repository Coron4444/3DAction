//================================================================================
//
//    プレイヤー衝突クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "PlayerCollision.h"
#include "../Player.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <GameObjectManager\GameObjectManager.h>
#include <3D\Coin\CoinCollision\CoinCollision.h>
#include <3D\Enemy\EnemyCollision\EnemyCollision.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const float PlayerCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float PlayerCollision::SUBSTANCE_RADIUS = 1.0f;



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Init()
{
	// タイプ
	CollisionBase::setType(CollisionBase::Type::PLAYER);

	// 複数衝突オブジェクト
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()
		->Init(*getpGameObject()->GetTransform()->GetPosition(),
			   Vec3(3.0f, 3.0f, 3.0f));
	CollisionBase::AddCollisionObjectsToArray(collision_objects_);

	// バウンディングスフィアの作成
	Sphere* temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->GetTransform()->GetPosition(),
					  BOUNDING_SPHERE_RADIUS);

	bounding_sphere_ = new CollisionObject(temp_sphere, ObjectTag::BOUNDING_SPHERE);

	// バウンディングスフィアを追加
	collision_objects_->AddCollisionObjectToArray(bounding_sphere_);


	// 本体スフィアの作成
	temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->GetTransform()->GetPosition(),
					  SUBSTANCE_RADIUS);

	substance_ = new CollisionObject(temp_sphere, ObjectTag::SUBSTANCE);

	// 本体スフィアを追加
	collision_objects_->AddCollisionObjectToArray(substance_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Uninit()
{
	// スーパークラスの終了処理
	CollisionNull::Uninit();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Update()
{
	// 複数衝突オブジェクトの更新
	*collision_objects_->getOctreeAABB()->getpPositon() = *getpGameObject()
		->GetTransform()->GetPosition();
	collision_objects_->getOctreeAABB()->Update();

	// バウンディングスフィアの更新
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->GetTransform()->GetPosition();

	//// 本体スフィアの更新
	temp_sphere = (Sphere*)substance_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->GetTransform()->GetPosition();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突応答関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::HitCollision(CollisionBase* hit_collision,
								   CollisionObject*  hit_object,
								   CollisionObject*  hit_my_object)
{
	// 自分の衝突オブジェクトで振り分ける
	switch (hit_my_object->getTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE:
		{
			HitBoundingSphere(hit_collision, hit_object, hit_my_object);
			break;
		}
		case PlayerCollision::ObjectTag::SUBSTANCE:
		{
			HitSubstance(hit_collision, hit_object, hit_my_object);
			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 非衝突応答関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::NotHitCollision(CollisionBase* hit_collision,
									  CollisionObject*  hit_object,
									  CollisionObject*  hit_my_object)
{
	// 自分の衝突オブジェクトで振り分ける
	switch (hit_my_object->getTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE:
		{
			NotHitBoundingSphere(hit_collision, hit_object, hit_my_object);
			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 地面との衝突応答関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::HitGround(float position_y)
{
	// ダウンキャスト
	Player* player = (Player*)getpGameObject();

	// 地面の上に立つ
	player->GetTransform()->GetPosition()->y = position_y;
	player->GetTransform()->UpdateWorldMatrixSRT();

	if (player->GetPhysics() == nullptr) return;
	player->GetPhysics()->SetOnTheGround();
}



//--------------------------------------------------------------------------------
//
// [ バウンディングスフィア衝突処理関数 ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::HitBoundingSphere(CollisionBase* hit_collision,
										CollisionObject*  hit_object,
										CollisionObject*  hit_my_object)
{
	hit_my_object = hit_my_object;

	// 衝突コンポーネントで振り分け
	switch(hit_collision->getType())
	{
		case CollisionBase::Type::COIN :
		{
			//TestCubeCollisionBase* temp_component = (TestCubeCollisionBase*)hit_collision;
	
			// 相手の衝突オブジェクトで振り分け
			switch(hit_object->getTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB :
				{
					//game_object_origin_->translation_->position_ += hit_my_object->hit_vector_;
					//game_object_origin_->matrix_->UpdateTranslationMatrix(game_object_origin_->translation_->position_);
					//game_object_origin_->matrix_->UpdateWorldMatrix();
					break;
				}
			
			}
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ バウンディングスフィア非衝突処理関数 ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::NotHitBoundingSphere(CollisionBase* hit_collision,
										   CollisionObject*  hit_object,
										   CollisionObject*  hit_my_object)
{
	hit_my_object = hit_my_object;

	// 衝突コンポーネントで振り分け
	switch(hit_collision->getType())
	{
		case CollisionBase::Type::COIN :
		{
			// 使わなかった引数
			hit_object = hit_object;

			// バウンディングスフィアより内側の衝突オブジェクトをOFF
			substance_->setIsJudgment(false);

			break;
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ サブスタンス衝突処理関数 ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::HitSubstance(CollisionBase* hit_collision,
								   CollisionObject*  hit_object,
								   CollisionObject*  hit_my_object)
{
	// 衝突コンポーネントで振り分け
	switch(hit_collision->getType())
	{
		case CollisionBase::Type::COIN:
		{
			// 相手の衝突オブジェクトで振り分け
			switch(hit_object->getTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB :
				{
					// ダウンキャスト
					Player* player = (Player*)getpGameObject();
					Coin* coin = (Coin*)hit_collision->getpGameObject();
					if (coin->getCount() <= 0)
					{
						coin->setCount(120);
						// スコアアップ
						player->game_scene_->setScore(player->game_scene_->getScore() + 10);
					}

					// めり込み解消
					//EliminationOfNesting(player->GetTransform(), hit_my_object->getpHitVector());

					// 相手のオブジェクトを消去
					//GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					
					break;
				}
			}
			break;
		}
		case CollisionBase::Type::ENEMY :
		{
			// 相手の衝突オブジェクトで振り分け
			switch(hit_object->getTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE :
				{
					// ダウンキャスト
					Player* player = (Player*)getpGameObject();
					
					// めり込み解消
					EliminationOfNesting(player->GetTransform(), hit_my_object->getpHitVector());

					// スコアダウン
					player->game_scene_->setGameOver(1);

					// 相手のオブジェクトを消去
					GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					
					break;
				}
			}
			break;
		}
		case CollisionBase::Type::GOAL:
		{
			// 相手の衝突オブジェクトで振り分け
			switch (hit_object->getTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE:
				{
					// ダウンキャスト
					Player* player = (Player*)getpGameObject();

					// めり込み解消
					EliminationOfNesting(player->GetTransform(), hit_my_object->getpHitVector());

					// スコアダウン
					player->game_scene_->setGameOver(0);

					// 相手のオブジェクトを消去
					GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());

					break;
				}
			}
			break;
		}
	}
}