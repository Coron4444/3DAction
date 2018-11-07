//================================================================================
//
//    衝突コンポーネントマネージャークラス(static)
//    Author : Araki Kai                                作成日 : 2018/04/17
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "CollisionComponentManager.h"
#include "CollisionComponentPairCheck\CollisionComponentPairCheck.h"
#include "CollisionJudgment\CollisionJudgment.h"

#include <GameObjectOrigin\GameObjectOrigin.h>
#include <Component\CollisionComponent\CollisionComponent.h>
#include <Component\CollisionComponent\CollisionObject\CollisionObject.h>

#include <SafeRelease/SafeRelease.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>



//======================================================================
//
// 静的メンバ変数定義
//
//======================================================================

LimitedPointerArray<CollisionComponent*, CollisionComponentManager::ARRAY_NUM> CollisionComponentManager::all_collision_component_;
LimitedPointerArray<CollisionComponent*, CollisionComponentManager::ARRAY_NUM> CollisionComponentManager::release_;

MeshPlanePolygon* CollisionComponentManager::ground_polygon_;



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

void CollisionComponentManager::Init()
{
	// 地面の初期化
	ground_polygon_ = nullptr;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::Uninit()
{
	// 解放用配列のリセット
	release_.ResetArray();

	// コンポーネント配列のリセット
	all_collision_component_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ シーン変更時の終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::Uninit_ChangeScene()
{
	// 解放用配列のリセット
	release_.ResetArray();

	// コンポーネント配列のリセット
	all_collision_component_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::Update()
{
	// 解放待ちの解放
	ReleaseUpdateComponentALL();

	// コンポーネントの更新
	for (unsigned i = 0; i < all_collision_component_.GetEndPointer(); i++)
	{
		all_collision_component_.GetArrayObject(i)->Update();
	}

	// 衝突判定
	CollisionDetermination();

	// 地面との衝突判定
	CollisionGround();

#ifdef _DEBUG
	// デバッグ
	for (unsigned i = 0; i < all_collision_component_.GetEndPointer(); i++)
	{
		if (all_collision_component_.GetArrayObject(i) == nullptr) continue;
		all_collision_component_.GetArrayObject(i)->Debug();
	}
#endif
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突コンポーネント登録関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::RegistrationComponent(CollisionComponent* collision_component)
{
	// 登録
	all_collision_component_.AddToArray(collision_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突コンポーネント上書き関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::OverwriteComponent(GameObjectOrigin* game_object, CollisionComponent* new_collision_component)
{
	// 新規コンポーネントがnullptrかどうか
	if (new_collision_component == nullptr)
	{
		// 古いオブジェクトの解放
		ReleaseComponent(game_object->GetCollisionComponent());

		// 古いコンポーネントの消去
		CollisionComponent* temp = game_object->GetCollisionComponent();
		SafeRelease::Normal(&temp);

		// 新規コンポーネント(nullptr)の代入
		game_object->SetCollisionComponent(new_collision_component);
	}
	else
	{
		// 配列の上書き
		all_collision_component_.OverwriteArray(game_object->GetCollisionComponent(), new_collision_component);

		// 古いコンポーネントの消去
		CollisionComponent* temp = game_object->GetCollisionComponent();
		SafeRelease::Normal(&temp);

		// 新規コンポーネントの初期化
		game_object->SetCollisionComponent(new_collision_component);
		new_collision_component->SetGameObjectOrigin(game_object);
		new_collision_component->Init();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突コンポーネント解放関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::ReleaseComponent(CollisionComponent* collision_component)
{
	// 解放配列登録
	release_.AddToArray(collision_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 地面設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::SetGround(MeshPlanePolygon* ground_polygon)
{
	ground_polygon_ = ground_polygon; 
}



//--------------------------------------------------------------------------------
//
// [ 全ての解放待ち衝突コンポーネントの解放関数 ]
//
//--------------------------------------------------------------------------------

void CollisionComponentManager::ReleaseUpdateComponentALL()
{
	// 解放待ちがあるかどうか
	if(release_.GetEndPointer() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < release_.GetEndPointer(); i++)
	{
		// 解放と並べ替え
		all_collision_component_.DeleteFromArrayAndSortArray(release_.GetArrayObject(i));
	}

	// 解放待ち配列をリセット
	release_.ResetArray();
}



//--------------------------------------------------------------------------------
//
// [ 衝突判定関数 ]
//
//--------------------------------------------------------------------------------

void CollisionComponentManager::CollisionDetermination()
{
	if (all_collision_component_.GetEndPointer() < 2) return;
	for (unsigned i = 0; i < all_collision_component_.GetEndPointer() - 1; i++)
	{
		if (all_collision_component_.GetArrayObject(i) == nullptr) continue;

		// コンポーネント自体が判定するかどうか
		if (!all_collision_component_.GetArrayObject(i)->GetIsJudgment()) continue;

		// 総当たり
		for (unsigned j = i + 1; j < all_collision_component_.GetEndPointer(); j++)
		{
			if (all_collision_component_.GetArrayObject(j) == nullptr) continue;	

			// コンポーネント自体が判定するかどうか
			if (!all_collision_component_.GetArrayObject(j)->GetIsJudgment()) continue;

			// 判定をする組み合わせか？
			if (!CollisionComponentPairCheck::IsCheck(all_collision_component_.GetArrayObject(i), all_collision_component_.GetArrayObject(j))) continue;

			// 実際の判定処理
			ActualCalculation(all_collision_component_.GetArrayObject(i), all_collision_component_.GetArrayObject(j));

			// 各コンポーネントの衝突オブジェクトの判定をリセット
			if (all_collision_component_.GetArrayObject(i)->GetIsJudgment())
			{
				all_collision_component_.GetArrayObject(i)->ResetHitData_AllCollisionObject();
			}
			if (all_collision_component_.GetArrayObject(j)->GetIsJudgment())
			{
				all_collision_component_.GetArrayObject(j)->ResetHitData_AllCollisionObject();
			}
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ 地面との衝突判定関数 ]
//
//--------------------------------------------------------------------------------

void CollisionComponentManager::CollisionGround()
{
	if (ground_polygon_ == nullptr) return;

	for (unsigned i = 0; i < all_collision_component_.GetEndPointer(); i++)
	{
		// 地面との判定をするかどうか
		if (!all_collision_component_.GetArrayObject(i)->GetIsJudgmentGround()) continue;

		// 地面高さ取得
		float position_y = ground_polygon_->GetHeight(*all_collision_component_.GetArrayObject(i)->
													   GetGameObjectOrigin()->GetTransform()->GetPosition());

		// 衝突してるか
		if (position_y >= all_collision_component_.GetArrayObject(i)->
						  GetGameObjectOrigin()->GetTransform()->GetPosition()->y)
		{
			// 地面との衝突処理
			all_collision_component_.GetArrayObject(i)->HitGround(position_y);
		}
		else
		{
			// 地面との非衝突処理
			all_collision_component_.GetArrayObject(i)->NotHitGround(position_y);
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ 実際の計算関数 ]
//
//--------------------------------------------------------------------------------

void CollisionComponentManager::ActualCalculation(CollisionComponent* collision_component_0, CollisionComponent* collision_component_1)
{
	for (unsigned i = 0; i < collision_component_0->GetEndIndexCollisionObjectArray(); i++)
	{
		// 衝突オブジェクトが判定するかどうか
		if (!collision_component_0->GetCollisionObject(i)->GetIsJudgment()) continue;

		// 総当たり
		for (unsigned j = 0; j < collision_component_1->GetEndIndexCollisionObjectArray(); j++)
		{
			// 衝突オブジェクトが判定するかどうか
			if (!collision_component_1->GetCollisionObject(j)->GetIsJudgment()) continue;

			// 衝突計算
			if (SortCollisionCalculation(collision_component_0->GetCollisionObject(i),
				                         collision_component_1->GetCollisionObject(j)))
			{
				// コンポーネント1つ目の衝突応答
				collision_component_0->HitCollision(collision_component_1, 
													collision_component_1->GetCollisionObject(j),
													collision_component_0->GetCollisionObject(i));
				
				// コンポーネント2つ目の衝突応答
				collision_component_1->HitCollision(collision_component_0, 
													collision_component_0->GetCollisionObject(i),
													collision_component_1->GetCollisionObject(j));
			}
			else
			{
				// コンポーネント1つ目の非衝突応答
				collision_component_0->NotHitCollision(collision_component_1, 
													   collision_component_1->GetCollisionObject(j),
													   collision_component_0->GetCollisionObject(i));
				
				// コンポーネント2つ目の非衝突応答
				collision_component_1->NotHitCollision(collision_component_0, 
													   collision_component_0->GetCollisionObject(i),
													   collision_component_1->GetCollisionObject(j));
			}

			// コンポーネントが判定可能かどうか
			if (!collision_component_0->GetIsJudgment()) return;
			if (!collision_component_1->GetIsJudgment()) return;
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ 衝突計算振り分け関数 ]
//
//--------------------------------------------------------------------------------

bool CollisionComponentManager::SortCollisionCalculation(CollisionObject* collision_object_0, CollisionObject* collision_object_1)
{
	bool is_hit = false;

	switch(collision_object_0->GetCollisionShape()->GetType())
	{
		case CollisionShapeOrigin::Type::TYPE_AABB :
		{
			/*switch(collision_object_1->GetCollisionShape()->GetType())
			{
				default :
					break;
			}*/
			break;
		}
		case CollisionShapeOrigin::Type::TYPE_CAPSULE :
		{
			switch(collision_object_1->GetCollisionShape()->GetType())
			{
				case CollisionShapeOrigin::Type::TYPE_CAPSULE :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Capsule_Capsule(&temp_vector, 
																		 (Capsule*)collision_object_0->GetCollisionShape(), 
																		 (Capsule*)collision_object_1->GetCollisionShape());

					collision_object_0->SetHitVector(temp_vector);
					collision_object_1->SetHitVector(-temp_vector);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SEGMENT :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Capsule(&temp_position,
													                       (Segment*)collision_object_1->GetCollisionShape(), 
													                       (Capsule*)collision_object_0->GetCollisionShape());

					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SPHERE :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Capsule(&temp_vector, 
						                                                (Sphere*)collision_object_1->GetCollisionShape(), 
											                            (Capsule*)collision_object_0->GetCollisionShape());
					
					collision_object_0->SetHitVector(-temp_vector);
					collision_object_1->SetHitVector(temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeOrigin::Type::TYPE_CYLINDER :
		{
			switch(collision_object_1->GetCollisionShape()->GetType())
			{
				case CollisionShapeOrigin::Type::TYPE_SEGMENT :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Cylinder(&temp_position, 
						                                                    (Segment*)collision_object_1->GetCollisionShape(), 
											                                (Cylinder*)collision_object_0->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeOrigin::Type::TYPE_OBB :
		{
			switch(collision_object_1->GetCollisionShape()->GetType())
			{
				case CollisionShapeOrigin::Type::TYPE_OBB :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_OBB_OBB(&temp_vector, 
						                                         (OBB*)collision_object_0->GetCollisionShape(), 
									                             (OBB*)collision_object_1->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_vector); 
					collision_object_1->SetHitVector(-temp_vector);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SPHERE :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_OBB(&temp_vector, 
						                                            (Sphere*)collision_object_1->GetCollisionShape(), 
									                                (OBB*)collision_object_0->GetCollisionShape());
					
					collision_object_0->SetHitVector(-temp_vector);
					collision_object_1->SetHitVector(temp_vector); 

					break;
				}
			}
			break;
		}
		case CollisionShapeOrigin::Type::TYPE_PLANE :
		{
			switch(collision_object_1->GetCollisionShape()->GetType())
			{
				case CollisionShapeOrigin::Type::TYPE_PLANE :
				{
					is_hit =  CollisionJudgment::HitCheck_Plane_Plane(nullptr, 
						                                              (Plane*)collision_object_0->GetCollisionShape(), 
									                                  (Plane*)collision_object_1->GetCollisionShape());
					
					collision_object_0->GetHitVector()->ResetVector();
					collision_object_1->GetHitVector()->ResetVector();

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SEGMENT :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Plane(&temp_position, 
						                                                 (Segment*)collision_object_1->GetCollisionShape(), 
											                             (Plane*)collision_object_0->GetCollisionShape());
				
					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SPHERE :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Plane(&temp_vector, 
						                                              (Sphere*)collision_object_1->GetCollisionShape(), 
											                          (Plane*)collision_object_0->GetCollisionShape());
					
					collision_object_0->SetHitVector(-temp_vector);
					collision_object_1->SetHitVector(temp_vector); 
				
					break;
				}
				case CollisionShapeOrigin::Type::TYPE_TRIANGLE :
				{
					is_hit = CollisionJudgment::HitCheck_Plane_Triangle((Plane*)collision_object_0->GetCollisionShape(), 
													                    (Triangle*)collision_object_1->GetCollisionShape());
				
					collision_object_0->GetHitVector()->ResetVector();
					collision_object_1->GetHitVector()->ResetVector();

					break;
				}
			}
			break;
		}
		case CollisionShapeOrigin::Type::TYPE_SEGMENT :
		{
			switch(collision_object_1->GetCollisionShape()->GetType())
			{
				case CollisionShapeOrigin::Type::TYPE_CAPSULE :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Capsule(&temp_position, 
						                                                   (Segment*)collision_object_0->GetCollisionShape(), 
											                               (Capsule*)collision_object_1->GetCollisionShape());
				
					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);
				
				}
				case CollisionShapeOrigin::Type::TYPE_CYLINDER :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Cylinder(&temp_position, 
						                                                    (Segment*)collision_object_0->GetCollisionShape(), 
											                                (Cylinder*)collision_object_1->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);
				
					break;
				}
				case CollisionShapeOrigin::Type::TYPE_PLANE :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Plane(&temp_position, 
						                                                 (Segment*)collision_object_0->GetCollisionShape(), 
											                             (Plane*)collision_object_1->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SEGMENT :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment2D_Segment2D(&temp_position, 
						                                                     (Segment*)collision_object_0->GetCollisionShape(), 
											                                 (Segment*)collision_object_1->GetCollisionShape());
				
					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SPHERE :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Sphere(&temp_position, 
						                                                  (Segment*)collision_object_0->GetCollisionShape(), 
											                              (Sphere*)collision_object_1->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_TRIANGLE :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Triangle(&temp_position, 
						                                                    (Segment*)collision_object_0->GetCollisionShape(), 
											                                (Triangle*)collision_object_1->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeOrigin::Type::TYPE_SPHERE :
		{
			switch(collision_object_1->GetCollisionShape()->GetType())
			{
				case CollisionShapeOrigin::Type::TYPE_CAPSULE :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Capsule(&temp_vector, 
						                                                (Sphere*)collision_object_0->GetCollisionShape(), 
											                            (Capsule*)collision_object_1->GetCollisionShape());
				
					collision_object_0->SetHitVector(temp_vector); 
					collision_object_1->SetHitVector(-temp_vector);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_OBB :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_OBB(&temp_vector, 
						                                            (Sphere*)collision_object_0->GetCollisionShape(), 
											                        (OBB*)collision_object_1->GetCollisionShape());
				
					collision_object_0->SetHitVector(temp_vector); 
					collision_object_1->SetHitVector(-temp_vector);

					break;

				}
				case CollisionShapeOrigin::Type::TYPE_PLANE :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Plane(&temp_vector, 
						                                              (Sphere*)collision_object_0->GetCollisionShape(), 
											                          (Plane*)collision_object_1->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_vector); 
					collision_object_1->SetHitVector(-temp_vector);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SEGMENT :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Sphere(&temp_position, 
						                                                  (Segment*)collision_object_0->GetCollisionShape(), 
											                              (Sphere*)collision_object_1->GetCollisionShape());

					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);

					break;

				}
				case CollisionShapeOrigin::Type::TYPE_SPHERE :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Sphere(&temp_vector, 
						                                               (Sphere*)collision_object_0->GetCollisionShape(), 
											                           (Sphere*)collision_object_1->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_vector); 
					collision_object_1->SetHitVector(-temp_vector);

					break;

				}
				case CollisionShapeOrigin::Type::TYPE_TRIANGLE :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Triangle(&temp_vector, 
						                                                 (Sphere*)collision_object_0->GetCollisionShape(), 
											                             (Triangle*)collision_object_1->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_vector); 
					collision_object_1->SetHitVector(-temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeOrigin::Type::TYPE_TRIANGLE :
		{
			switch(collision_object_1->GetCollisionShape()->GetType())
			{
				case CollisionShapeOrigin::Type::TYPE_PLANE :
				{
					is_hit = CollisionJudgment::HitCheck_Plane_Triangle((Plane*)collision_object_1->GetCollisionShape(), 
											                            (Triangle*)collision_object_0->GetCollisionShape());
					
					collision_object_0->GetHitVector()->ResetVector();
					collision_object_1->GetHitVector()->ResetVector();
					
					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SEGMENT :
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Triangle(&temp_position, 
						                                                    (Segment*)collision_object_1->GetCollisionShape(), 
											                                (Triangle*)collision_object_0->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_position);
					collision_object_1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeOrigin::Type::TYPE_SPHERE :
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Triangle(&temp_vector, 
						                                                 (Sphere*)collision_object_1->GetCollisionShape(), 
											                             (Triangle*)collision_object_0->GetCollisionShape());
					
					collision_object_0->SetHitVector(temp_vector); 
					collision_object_1->SetHitVector(-temp_vector);
					
					break;
				}
				case CollisionShapeOrigin::Type::TYPE_TRIANGLE :
				{
					is_hit = CollisionJudgment::HitCheck_Triangle_Triangle((Triangle*)collision_object_0->GetCollisionShape(), 
																		   (Triangle*)collision_object_1->GetCollisionShape());
					
					collision_object_0->GetHitVector()->ResetVector();
					collision_object_1->GetHitVector()->ResetVector();
					
					break;
				}
			}
			break;
		}
	}

	return is_hit;
}
