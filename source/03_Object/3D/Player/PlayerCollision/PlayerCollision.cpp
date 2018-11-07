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
const float PlayerCollision::SUBSTANCE_RADIUS		= 1.0f;



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

PlayerCollision::PlayerCollision()
	: CollisionComponent(CollisionComponent::State::PLAYER)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Init()
{
	// バウンディングスフィアの作成
	Sphere* temp_sphere = new Sphere(*GetGameObjectOrigin()->GetTransform()->GetPosition(), 
									 BOUNDING_SPHERE_RADIUS);
	
	bounding_sphere_ = new CollisionObject(temp_sphere, ObjectTag::BOUNDING_SPHERE);

	// バウンディングスフィアを追加
	AddCollisionObject(bounding_sphere_);


	// 本体スフィアの作成
	temp_sphere = new Sphere(*GetGameObjectOrigin()->GetTransform()->GetPosition(),
							 SUBSTANCE_RADIUS);

	substance_ = new CollisionObject(temp_sphere, ObjectTag::SUBSTANCE);

	// 本体スフィアを追加
	AddCollisionObject(substance_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Uninit()
{
	// スーパークラスの終了処理
	CollisionComponent::Uninit();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Update()
{
	// バウンディングスフィアの更新
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->GetCollisionShape();
	temp_sphere->position_ = *GetGameObjectOrigin()->GetTransform()->GetPosition();

	// 本体スフィアの更新
	temp_sphere = (Sphere*)substance_->GetCollisionShape();
	temp_sphere->position_ = *GetGameObjectOrigin()->GetTransform()->GetPosition();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突応答関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::HitCollision(CollisionComponent* hit_component, 
								   CollisionObject*    hit_opponent_object,
								   CollisionObject*    hit_myself_object)
{
	// 自分の衝突オブジェクトで振り分ける
	switch (hit_myself_object->GetTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE :
		{
			HitBoundingSphere(hit_component, hit_opponent_object, hit_myself_object);
			break;
		}
		case PlayerCollision::ObjectTag::SUBSTANCE :
		{
			HitSubstance(hit_component, hit_opponent_object, hit_myself_object);
			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 非衝突応答関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::NotHitCollision(CollisionComponent* hit_component, 
								      CollisionObject*    hit_opponent_object,
								      CollisionObject*    hit_myself_object)
{
	// 自分の衝突オブジェクトで振り分ける
	switch (hit_myself_object->GetTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE :
		{
			NotHitBoundingSphere(hit_component, hit_opponent_object, hit_myself_object);
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
	Player* player = (Player*)GetGameObjectOrigin();

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

void PlayerCollision::HitBoundingSphere(CollisionComponent* hit_component, 
								        CollisionObject*    hit_opponent_object,
								        CollisionObject*    hit_myself_object)
{
	hit_myself_object = hit_myself_object;

	// 衝突コンポーネントで振り分け
	switch(hit_component->GetState())
	{
		case CollisionComponent::State::COIN :
		{
			//TestCubeCollisionComponent* temp_component = (TestCubeCollisionComponent*)hit_component;
	
			// 相手の衝突オブジェクトで振り分け
			switch(hit_opponent_object->GetTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB :
				{
					//game_object_origin_->translation_->position_ += hit_myself_object->hit_vector_;
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

void PlayerCollision::NotHitBoundingSphere(CollisionComponent* hit_component, 
								           CollisionObject*    hit_opponent_object,
								           CollisionObject*    hit_myself_object)
{
	hit_myself_object = hit_myself_object;

	// 衝突コンポーネントで振り分け
	switch(hit_component->GetState())
	{
		case CollisionComponent::State::COIN :
		{
			// 使わなかった引数
			hit_opponent_object = hit_opponent_object;

			// バウンディングスフィアより内側の衝突オブジェクトをOFF
			substance_->SetIsJudgment(false);

			break;
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ サブスタンス衝突処理関数 ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::HitSubstance(CollisionComponent* hit_component, 
								   CollisionObject*    hit_opponent_object,
								   CollisionObject*    hit_myself_object)
{
	// 衝突コンポーネントで振り分け
	switch(hit_component->GetState())
	{
		case CollisionComponent::State::COIN:
		{
			// 相手の衝突オブジェクトで振り分け
			switch(hit_opponent_object->GetTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB :
				{
					// ダウンキャスト
					Player* player = (Player*)GetGameObjectOrigin();
					
					// めり込み解消
					EliminationOfNesting(player->GetTransform(), hit_myself_object->GetHitVector());

					// スコアアップ
					player->game_scene_->SetScore(player->game_scene_->GetScore() + 30);

					// 相手のオブジェクトを消去
					GameObjectManager::Release(hit_component->GetGameObjectOrigin());
					
					break;
				}
			
			}
			break;
		}
		case CollisionComponent::State::ENEMY :
		{
			// 相手の衝突オブジェクトで振り分け
			switch(hit_opponent_object->GetTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE :
				{
					// ダウンキャスト
					Player* player = (Player*)GetGameObjectOrigin();
					
					// めり込み解消
					EliminationOfNesting(player->GetTransform(), hit_myself_object->GetHitVector());

					// スコアダウン
					player->game_scene_->SetScore(player->game_scene_->GetScore() - 9999);

					// 相手のオブジェクトを消去
					GameObjectManager::Release(hit_component->GetGameObjectOrigin());
					
					break;
				}
			}
			break;
		}
	}
}