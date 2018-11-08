//================================================================================
//
//    衝突マネージャークラス(static)
//    Author : Araki Kai                                作成日 : 2018/04/17
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "CollisionManager.h"
#include "CollisionPairCheck/CollisionPairCheck.h"
#include "CollisionJudgment\CollisionJudgment.h"
#include <Component/CollisionBase/CollisionBase.h>
#include <Component/CollisionBase/CollisionObject/CollisionObject.h>

#include <GameObjectBase/GameObjectBase.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>

#include <SafeRelease/SafeRelease.h>



//****************************************
// 静的メンバ変数定義
//****************************************
LimitedPointerArray<CollisionBase*, CollisionManager::ARRAY_NUM> CollisionManager::all_collision_;
LimitedPointerArray<CollisionBase*, CollisionManager::ARRAY_NUM> CollisionManager::await_add_;
LimitedPointerArray<CollisionBase*, CollisionManager::ARRAY_NUM> CollisionManager::await_release_;

MeshPlanePolygon* CollisionManager::ground_polygon_;



//****************************************
// 静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void CollisionManager::Init()
{
	// 地面の初期化
	ground_polygon_ = nullptr;
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void CollisionManager::Uninit()
{
	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全衝突配列のリセット
	all_collision_.ResetArray();
}



//--------------------------------------------------
// +シーン変更時の終了関数
//--------------------------------------------------
void CollisionManager::UninitWhenChangeScene()
{
	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全衝突配列のリセット
	all_collision_.ResetArray();
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void CollisionManager::Update()
{
	// 追加待ち配列の中身を追加
	AddContentsOfAwaitAddArray();

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 衝突クラスの更新
	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		all_collision_.GetArrayObject(i)->Update();
	}

	// 衝突判定
	CollisionDetermination();

	// 地面との衝突判定
	CollisionGround();

	// デバッグ
#ifdef _DEBUG
	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		if (all_collision_.GetArrayObject(i) == nullptr) continue;
		all_collision_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



//--------------------------------------------------
// +衝突基底クラスの追加関数
//--------------------------------------------------
void CollisionManager::AddCollisionBaseToArray(CollisionBase* collision)
{
	// 追加待ち配列に追加
	await_add_.AddToArray(collision);
}



//--------------------------------------------------
// +更新基底クラスの上書き関数
//--------------------------------------------------
void CollisionManager::OverwriteArrayCollisionBase(GameObjectBase* game_object,
												   CollisionBase* new_collision)
{
	// 新規がnullptrの場合
	if (new_collision == nullptr)
	{
		// 古い更新基底クラスの解放
		ReleaseCollisionBaseFromArray(game_object->GetCollision());

		// 古い更新基底クラスの消去
		CollisionBase* temp = game_object->GetCollision();
		SafeRelease::Normal(&temp);

		// nullptrの代入
		game_object->SetCollision(new_collision);
	}
	else
	{
		// 配列の上書き
		all_collision_.OverwriteArray(game_object->GetCollision(), new_collision);

		// 古い更新基底クラスの消去
		CollisionBase* temp = game_object->GetCollision();
		SafeRelease::Normal(&temp);

		// 新規コンポーネントの初期化
		game_object->SetCollision(new_collision);
		new_collision->SetGameObject(game_object);
		new_collision->Init();
	}
}



//--------------------------------------------------
// +衝突基底クラスの解放関数
//--------------------------------------------------
void CollisionManager::ReleaseCollisionBaseFromArray(CollisionBase* collision)
{
	// 追加待ち配列に追加
	await_release_.AddToArray(collision);
}



//--------------------------------------------------
// +地面設定関数
//--------------------------------------------------
void CollisionManager::SetGround(MeshPlanePolygon* ground_polygon)
{
	ground_polygon_ = ground_polygon;
}



//--------------------------------------------------
// -追加待ち配列の中身を追加関数
//--------------------------------------------------
void CollisionManager::AddContentsOfAwaitAddArray()
{
	// 追加待ちがあるかどうか
	if (await_add_.GetEndPointer() <= 0) return;

	// 追加
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_collision_.AddToArray(await_add_.GetArrayObject(i));
	}

	// 追加待ち配列をリセット
	await_add_.ResetArray();
}



//--------------------------------------------------
// -解放待ち配列の中身を解放関数
//--------------------------------------------------
void CollisionManager::ReleaseContentsOfAwaitReleaseArray()
{
	// 解放待ちがあるかどうか
	if (await_release_.GetEndPointer() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		all_collision_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// 解放待ち配列をリセット
	await_release_.ResetArray();
}



//--------------------------------------------------
// -衝突判定関数
//--------------------------------------------------
void CollisionManager::CollisionDetermination()
{
	if (all_collision_.GetEndPointer() < 2) return;
	for (unsigned i = 0; i < all_collision_.GetEndPointer() - 1; i++)
	{
		if (all_collision_.GetArrayObject(i) == nullptr) continue;

		// コンポーネント自体が判定するかどうか
		if (!all_collision_.GetArrayObject(i)->GetIsJudgment()) continue;

		// 総当たり
		for (unsigned j = i + 1; j < all_collision_.GetEndPointer(); j++)
		{
			if (all_collision_.GetArrayObject(j) == nullptr) continue;

			// コンポーネント自体が判定するかどうか
			if (!all_collision_.GetArrayObject(j)->GetIsJudgment()) continue;

			// 判定をする組み合わせか？
			if (!CollisionPairCheck::IsCheck(all_collision_.GetArrayObject(i),
											 all_collision_.GetArrayObject(j))) continue;

			// 実際の判定処理
			ActualCalculation(all_collision_.GetArrayObject(i),
							  all_collision_.GetArrayObject(j));

			// 各コンポーネントの衝突オブジェクトの判定をリセット
			if (all_collision_.GetArrayObject(i)->GetIsJudgment())
			{
				all_collision_.GetArrayObject(i)->ResetHitDataAllCollisionObject();
			}
			if (all_collision_.GetArrayObject(j)->GetIsJudgment())
			{
				all_collision_.GetArrayObject(j)->ResetHitDataAllCollisionObject();
			}
		}
	}
}



//--------------------------------------------------
// -地面との衝突判定関数
//--------------------------------------------------
void CollisionManager::CollisionGround()
{
	if (ground_polygon_ == nullptr) return;

	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		// 地面との判定をするかどうか
		if (!all_collision_.GetArrayObject(i)->GetIsJudgmentGround()) continue;

		// 地面高さ取得
		float position_y = ground_polygon_->GetHeight(*all_collision_.GetArrayObject(i)
													  ->GetGameObject()->GetTransform()
													  ->GetPosition());

		// 衝突してるか
		if (position_y >= all_collision_.GetArrayObject(i)
			->GetGameObject()->GetTransform()->GetPosition()->y)
		{
			// 地面との衝突処理
			all_collision_.GetArrayObject(i)->HitGround(position_y);
		}
		else
		{
			// 地面との非衝突処理
			all_collision_.GetArrayObject(i)->NotHitGround(position_y);
		}
	}
}



//--------------------------------------------------
// -実際の計算関数
//--------------------------------------------------
void CollisionManager::ActualCalculation(CollisionBase* collision0,
										 CollisionBase* collision1)
{
	for (unsigned i = 0; i < collision0->GetEndIndexOfArray(); i++)
	{
		// 衝突オブジェクトが判定するかどうか
		if (!collision0->GetCollisionObject(i)->GetIsJudgment()) continue;

		// 総当たり
		for (unsigned j = 0; j < collision1->GetEndIndexOfArray(); j++)
		{
			// 衝突オブジェクトが判定するかどうか
			if (!collision1->GetCollisionObject(j)->GetIsJudgment()) continue;

			// 衝突計算
			if (SortCollisionCalculation(collision0->GetCollisionObject(i),
										 collision1->GetCollisionObject(j)))
			{
				// コンポーネント1つ目の衝突応答
				collision0->HitCollision(collision1,
										 collision1->GetCollisionObject(j),
										 collision0->GetCollisionObject(i));

				// コンポーネント2つ目の衝突応答
				collision1->HitCollision(collision0,
										 collision0->GetCollisionObject(i),
										 collision1->GetCollisionObject(j));
			}
			else
			{
				// コンポーネント1つ目の非衝突応答
				collision0->NotHitCollision(collision1,
											collision1->GetCollisionObject(j),
											collision0->GetCollisionObject(i));

				// コンポーネント2つ目の非衝突応答
				collision1->NotHitCollision(collision0,
											collision0->GetCollisionObject(i),
											collision1->GetCollisionObject(j));
			}

			// コンポーネントが判定可能かどうか
			if (!collision0->GetIsJudgment()) return;
			if (!collision1->GetIsJudgment()) return;
		}
	}
}



//--------------------------------------------------
// -衝突計算振り分け関数
//--------------------------------------------------
bool CollisionManager::SortCollisionCalculation(CollisionObject* collision_object0,
												CollisionObject* collision_object1)
{
	bool is_hit = false;

	switch (collision_object0->GetCollisionShape()->GetType())
	{
		case CollisionShapeBase::Type::AABB:
		{
			/*switch(collision_object1->GetCollisionShape()->GetType())
			{
				default :
					break;
			}*/
			break;
		}
		case CollisionShapeBase::Type::CAPSULE:
		{
			switch (collision_object1->GetCollisionShape()->GetType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Capsule_Capsule(&temp_vector,
						(Capsule*)collision_object0->GetCollisionShape(),
																		 (Capsule*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_vector);
					collision_object1->SetHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Capsule(&temp_position,
						(Segment*)collision_object1->GetCollisionShape(),
																		   (Capsule*)collision_object0->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Capsule(&temp_vector,
						(Sphere*)collision_object1->GetCollisionShape(),
																		(Capsule*)collision_object0->GetCollisionShape());

					collision_object0->SetHitVector(-temp_vector);
					collision_object1->SetHitVector(temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::CYLINDER:
		{
			switch (collision_object1->GetCollisionShape()->GetType())
			{
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Cylinder(&temp_position,
						(Segment*)collision_object1->GetCollisionShape(),
																			(Cylinder*)collision_object0->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::OBB:
		{
			switch (collision_object1->GetCollisionShape()->GetType())
			{
				case CollisionShapeBase::Type::OBB:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_OBB_OBB(&temp_vector,
						(OBB*)collision_object0->GetCollisionShape(),
																 (OBB*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_vector);
					collision_object1->SetHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_OBB(&temp_vector,
						(Sphere*)collision_object1->GetCollisionShape(),
																	(OBB*)collision_object0->GetCollisionShape());

					collision_object0->SetHitVector(-temp_vector);
					collision_object1->SetHitVector(temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::PLANE:
		{
			switch (collision_object1->GetCollisionShape()->GetType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionJudgment::HitCheck_Plane_Plane(nullptr,
						(Plane*)collision_object0->GetCollisionShape(),
																	 (Plane*)collision_object1->GetCollisionShape());

					collision_object0->GetHitVector()->ResetVector();
					collision_object1->GetHitVector()->ResetVector();

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Plane(&temp_position,
						(Segment*)collision_object1->GetCollisionShape(),
																		 (Plane*)collision_object0->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Plane(&temp_vector,
						(Sphere*)collision_object1->GetCollisionShape(),
																	  (Plane*)collision_object0->GetCollisionShape());

					collision_object0->SetHitVector(-temp_vector);
					collision_object1->SetHitVector(temp_vector);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionJudgment::HitCheck_Plane_Triangle((Plane*)collision_object0->GetCollisionShape(),
						(Triangle*)collision_object1->GetCollisionShape());

					collision_object0->GetHitVector()->ResetVector();
					collision_object1->GetHitVector()->ResetVector();

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::SEGMENT:
		{
			switch (collision_object1->GetCollisionShape()->GetType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Capsule(&temp_position,
						(Segment*)collision_object0->GetCollisionShape(),
																		   (Capsule*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

				}
				case CollisionShapeBase::Type::CYLINDER:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Cylinder(&temp_position,
						(Segment*)collision_object0->GetCollisionShape(),
																			(Cylinder*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::PLANE:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Plane(&temp_position,
						(Segment*)collision_object0->GetCollisionShape(),
																		 (Plane*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment2D_Segment2D(&temp_position,
						(Segment*)collision_object0->GetCollisionShape(),
																			 (Segment*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Sphere(&temp_position,
						(Segment*)collision_object0->GetCollisionShape(),
																		  (Sphere*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Triangle(&temp_position,
						(Segment*)collision_object0->GetCollisionShape(),
																			(Triangle*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::SPHERE:
		{
			switch (collision_object1->GetCollisionShape()->GetType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Capsule(&temp_vector,
						(Sphere*)collision_object0->GetCollisionShape(),
																		(Capsule*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_vector);
					collision_object1->SetHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::OBB:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_OBB(&temp_vector,
						(Sphere*)collision_object0->GetCollisionShape(),
																	(OBB*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_vector);
					collision_object1->SetHitVector(-temp_vector);

					break;

				}
				case CollisionShapeBase::Type::PLANE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Plane(&temp_vector,
						(Sphere*)collision_object0->GetCollisionShape(),
																	  (Plane*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_vector);
					collision_object1->SetHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Sphere(&temp_position,
						(Segment*)collision_object0->GetCollisionShape(),
																		  (Sphere*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;

				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Sphere(&temp_vector,
						(Sphere*)collision_object0->GetCollisionShape(),
																	   (Sphere*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_vector);
					collision_object1->SetHitVector(-temp_vector);

					break;

				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Triangle(&temp_vector,
						(Sphere*)collision_object0->GetCollisionShape(),
																		 (Triangle*)collision_object1->GetCollisionShape());

					collision_object0->SetHitVector(temp_vector);
					collision_object1->SetHitVector(-temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::TRIANGLE:
		{
			switch (collision_object1->GetCollisionShape()->GetType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionJudgment::HitCheck_Plane_Triangle((Plane*)collision_object1->GetCollisionShape(),
						(Triangle*)collision_object0->GetCollisionShape());

					collision_object0->GetHitVector()->ResetVector();
					collision_object1->GetHitVector()->ResetVector();

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Triangle(&temp_position,
						(Segment*)collision_object1->GetCollisionShape(),
																			(Triangle*)collision_object0->GetCollisionShape());

					collision_object0->SetHitVector(temp_position);
					collision_object1->SetHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Triangle(&temp_vector,
						(Sphere*)collision_object1->GetCollisionShape(),
																		 (Triangle*)collision_object0->GetCollisionShape());

					collision_object0->SetHitVector(temp_vector);
					collision_object1->SetHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionJudgment::HitCheck_Triangle_Triangle((Triangle*)collision_object0->GetCollisionShape(),
						(Triangle*)collision_object1->GetCollisionShape());

					collision_object0->GetHitVector()->ResetVector();
					collision_object1->GetHitVector()->ResetVector();

					break;
				}
			}
			break;
		}
	}
	return is_hit;
}
