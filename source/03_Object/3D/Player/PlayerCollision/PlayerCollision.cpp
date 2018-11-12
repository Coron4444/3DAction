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
	: CollisionBase(CollisionBase::State::PLAYER)
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
	Sphere* temp_sphere = new Sphere(*GetGameObject()->GetTransform()->GetPosition(), 
									 BOUNDING_SPHERE_RADIUS);
	
	bounding_sphere_ = new CollisionObject(temp_sphere, ObjectTag::BOUNDING_SPHERE);

	// バウンディングスフィアを追加
	AddCollisionObjectToArray(bounding_sphere_);


	// 本体スフィアの作成
	temp_sphere = new Sphere(*GetGameObject()->GetTransform()->GetPosition(),
							 SUBSTANCE_RADIUS);

	substance_ = new CollisionObject(temp_sphere, ObjectTag::SUBSTANCE);

	// 本体スフィアを追加
	AddCollisionObjectToArray(substance_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Uninit()
{
	// スーパークラスの終了処理
	CollisionBase::Uninit();
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
	temp_sphere->position_ = *GetGameObject()->GetTransform()->GetPosition();

	// 本体スフィアの更新
	temp_sphere = (Sphere*)substance_->GetCollisionShape();
	temp_sphere->position_ = *GetGameObject()->GetTransform()->GetPosition();
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
	switch (hit_my_object->GetTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE :
		{
			HitBoundingSphere(hit_collision, hit_object, hit_my_object);
			break;
		}
		case PlayerCollision::ObjectTag::SUBSTANCE :
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
	switch (hit_my_object->GetTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE :
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
	Player* player = (Player*)GetGameObject();

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
	switch(hit_collision->GetState())
	{
		case CollisionBase::State::COIN :
		{
			//TestCubeCollisionBase* temp_component = (TestCubeCollisionBase*)hit_collision;
	
			// 相手の衝突オブジェクトで振り分け
			switch(hit_object->GetTag())
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
	switch(hit_collision->GetState())
	{
		case CollisionBase::State::COIN :
		{
			// 使わなかった引数
			hit_object = hit_object;

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

void PlayerCollision::HitSubstance(CollisionBase* hit_collision,
								   CollisionObject*  hit_object,
								   CollisionObject*  hit_my_object)
{
	// 衝突コンポーネントで振り分け
	switch(hit_collision->GetState())
	{
		case CollisionBase::State::COIN:
		{
			// 相手の衝突オブジェクトで振り分け
			switch(hit_object->GetTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB :
				{
					// ダウンキャスト
					Player* player = (Player*)GetGameObject();
					
					// めり込み解消
					EliminationOfNesting(player->GetTransform(), hit_my_object->GetHitVector());

					// スコアアップ
					player->game_scene_->SetScore(player->game_scene_->GetScore() + 30);

					// 相手のオブジェクトを消去
					GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->GetGameObject());
					
					break;
				}
			
			}
			break;
		}
		case CollisionBase::State::ENEMY :
		{
			// 相手の衝突オブジェクトで振り分け
			switch(hit_object->GetTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE :
				{
					// ダウンキャスト
					Player* player = (Player*)GetGameObject();
					
					// めり込み解消
					EliminationOfNesting(player->GetTransform(), hit_my_object->GetHitVector());

					// スコアダウン
					player->game_scene_->SetScore(player->game_scene_->GetScore() - 9999);

					// 相手のオブジェクトを消去
					GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->GetGameObject());
					
					break;
				}
			}
			break;
		}
	}
}