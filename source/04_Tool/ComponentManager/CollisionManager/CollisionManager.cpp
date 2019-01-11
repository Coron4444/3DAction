//================================================================================
//!	@file	 CollisionManager.cpp
//!	@brief	 衝突マネージャーClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "CollisionManager.h"
#include "CollisionPairCheck/CollisionPairCheck.h"
#include "CollisionCalculation/CollisionCalculation.h"
#include <Component/Collision/CollisionBase/CollisionBase.h>
#include <Component/Collision/CollisionBase/CollisionObject/CollisionObject.h>

#include <GameObjectBase/GameObjectBase.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>

#include <SafeRelease/SafeRelease.h>

#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>



//****************************************
// プロパティ定義
//****************************************
void CollisionManager::setGround(MeshPlanePolygon* ground_polygon)
{
	ground_polygon_ = ground_polygon;
}



//****************************************
// 関数定義
//****************************************
void CollisionManager::Init()
{
	// 地面の初期化
	ground_polygon_ = nullptr;

	// 8分木の初期化
	if (liner_octree_ == nullptr)
	{
		liner_octree_ = new LinerOctree<CollisionObjects*>();
		liner_octree_->Init(7, Vec3(-50.0f, -10.0f, -50.0f), Vec3(50.0f, 90.0f, 50.0f));
	}
}



void CollisionManager::Uninit()
{
	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 8分木
	SafeRelease::PlusUninit(&liner_octree_);
	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		for (unsigned j = 0; j < all_collision_.GetArrayObject(i)->getEndIndexOfArray(); j++)
		{
			// 移動オブジェクトはリストから一時的に離脱する
			ObjectOfTree<CollisionObjects*>* temp = all_collision_.GetArrayObject(i)
				->getpCollisionObjects(j)->getpObjectOfTree();
			temp->DeleteFromList();
			SafeRelease::Normal(&temp);
		}
	}
	collision_objects_list_.clear();

	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全衝突配列のリセット
	all_collision_.ResetArray();
}



void CollisionManager::UninitWhenChangeScene()
{
	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 8分木
	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		for (unsigned j = 0; j < all_collision_.GetArrayObject(i)->getEndIndexOfArray(); j++)
		{
			// 移動オブジェクトはリストから一時的に離脱する
			ObjectOfTree<CollisionObjects*>* temp = all_collision_.GetArrayObject(i)
				->getpCollisionObjects(j)->getpObjectOfTree();
			temp->DeleteFromList();
			SafeRelease::Normal(&temp);
		}
	}
	collision_objects_list_.clear();

	// 追加待ち配列のリセット
	await_add_.ResetArray();

	// 解放待ち配列のリセット
	await_release_.ResetArray();

	// 全衝突配列のリセット
	all_collision_.ResetArray();
}



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

	// 8分木の処理
	if (is_octree_)
	{
		for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
		{
			for (unsigned j = 0; j < all_collision_.GetArrayObject(i)->getEndIndexOfArray(); j++)
			{
				// 移動オブジェクトはリストから一時的に離脱する
				ObjectOfTree<CollisionObjects*>* temp = all_collision_.GetArrayObject(i)
					->getpCollisionObjects(j)->getpObjectOfTree();
				temp->DeleteFromList();

				// 再登録
				liner_octree_->Add(temp,
								   temp->getObject()->getOctreeAABB()->getpMin(),
								   temp->getObject()->getOctreeAABB()->getpMax());
			}
		}
		liner_octree_->UpdateCollisionList(&collision_objects_list_);

		time_ = timeGetTime();

		// 衝突判定
		CollisionDetermination();
	}
	else
	{
		time_ = timeGetTime();

		// 古い衝突判定
		OldCollisionDetermination();
	}

	time_ = timeGetTime() - time_;

	// 地面との衝突判定
	CollisionGround();

	// デバッグ表示
	DebugDisplay();

	// デバッグ
#ifdef _DEBUG
	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		if (all_collision_.GetArrayObject(i) == nullptr) continue;
		all_collision_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



void CollisionManager::AddCollisionBaseToArray(CollisionBase* collision)
{
	// 追加待ち配列に追加
	await_add_.AddToArray(collision);
}



void CollisionManager::OverwriteArrayCollisionBase(GameObjectBase* game_object,
												   CollisionBase* new_collision)
{
	// 新規がnullptrの場合
	if (new_collision == nullptr)
	{
		// 古い衝突基底クラスの解放
		ReleaseCollisionBaseFromArray(game_object->GetCollision());

		// 古い衝突基底クラスの消去
		CollisionBase* temp = game_object->GetCollision();
		SafeRelease::Normal(&temp);

		// nullptrの代入
		game_object->SetCollision(new_collision);
	}
	else
	{
		// 配列の上書き
		all_collision_.OverwriteArray(game_object->GetCollision(), new_collision);

		// 古い衝突基底クラスの消去
		CollisionBase* temp = game_object->GetCollision();
		SafeRelease::Normal(&temp);

		// 新規コンポーネントの初期化
		game_object->SetCollision(new_collision);
		*new_collision->getpGameObject() = *game_object;
		new_collision->Init();
	}
}



void CollisionManager::ReleaseCollisionBaseFromArray(CollisionBase* collision)
{
	// 8分木から消去
	for (unsigned i = 0; i < collision->getEndIndexOfArray(); i++)
	{
		ObjectOfTree<CollisionObjects*>* temp = collision->getpCollisionObjects(i)->getpObjectOfTree();
		temp->DeleteFromList();
		SafeRelease::Normal(&temp);
	}

	// 解放待ち配列に追加
	await_release_.AddToArray(collision);
}



void CollisionManager::AddContentsOfAwaitAddArray()
{
	// 追加待ちがあるかどうか
	if (await_add_.GetEndPointer() <= 0) return;

	// 追加
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_collision_.AddToArray(await_add_.GetArrayObject(i));

		// 8分木への追加
		for (unsigned j = 0; j < await_add_.GetArrayObject(i)->getEndIndexOfArray(); j++)
		{
			ObjectOfTree<CollisionObjects*>* temp = new ObjectOfTree<CollisionObjects*>;
			CollisionObjects* temp_objects = await_add_.GetArrayObject(i)->getpCollisionObjects(j);
			temp->setObject(temp_objects);
			temp_objects->setObjectOfTree(temp);
			liner_octree_->Add(temp, temp_objects->getOctreeAABB()->getpMin(),
							   temp_objects->getOctreeAABB()->getpMax());
		}
	}

	// 追加待ち配列をリセット
	await_add_.ResetArray();
}



void CollisionManager::ReleaseContentsOfAwaitReleaseArray()
{
	// 解放待ちがあるかどうか
	if (await_release_.GetEndPointer() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		// 全体配列から解放
		all_collision_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// 解放待ち配列をリセット
	await_release_.ResetArray();
}



void CollisionManager::CollisionDetermination()
{
	// ペアになっているため
	unsigned max_index = collision_objects_list_.size() / 2;

	for (unsigned i = 0; i < max_index; i++)
	{
		// 複数衝突オブジェクトが判定するかどうか
		if (!collision_objects_list_[i * 2]->getIsJudgment()) continue;
		if (!collision_objects_list_[i * 2 + 1]->getIsJudgment()) continue;

		// 判定をする組み合わせか？
		if (is_pair_check_)
		{
			if (!CollisionPairCheck::IsCheck(collision_objects_list_[i * 2]->getpCollisionBase(),
											 collision_objects_list_[i * 2 + 1]->getpCollisionBase())) continue;
		}

		// 実際の判定処理
		ActualCalculation(collision_objects_list_[i * 2],
						  collision_objects_list_[i * 2 + 1]);

		// 各コンポーネントの衝突オブジェクトの判定をリセット
		if (collision_objects_list_[i * 2]->getIsJudgment())
		{
			collision_objects_list_[i * 2]->ResetHitDataAllCollisionObject();
		}
		if (collision_objects_list_[i * 2 + 1]->getIsJudgment())
		{
			collision_objects_list_[i * 2 + 1]->ResetHitDataAllCollisionObject();
		}
	}

}



void CollisionManager::OldCollisionDetermination()
{
	// 衝突基底クラスが2つ以上かどうか
	if (all_collision_.GetEndPointer() < 2) return;

	// 衝突判定
	for (unsigned i = 0; i < all_collision_.GetEndPointer() - 1; i++)
	{
		// 衝突基底クラスがあるかどうか
		if (all_collision_.GetArrayObject(i) == nullptr) continue;

		// 総当たり
		for (unsigned j = i + 1; j < all_collision_.GetEndPointer(); j++)
		{
			// 衝突基底クラスがあるかどうか
			if (all_collision_.GetArrayObject(j) == nullptr) continue;

			// 判定をする組み合わせか？
			if (is_pair_check_)
			{
				if (!CollisionPairCheck::IsCheck(all_collision_.GetArrayObject(i),
												 all_collision_.GetArrayObject(j))) continue;
			}

			for (unsigned a = 0; a < all_collision_.GetArrayObject(i)->getEndIndexOfArray(); a++)
			{
				// 複数衝突オブジェクトが判定するかどうか
				if (!all_collision_.GetArrayObject(i)->getpCollisionObjects(a)
					->getIsJudgment()) continue;

				for (unsigned b = 0; b < all_collision_.GetArrayObject(i)->getEndIndexOfArray(); b++)
				{
					// 複数衝突オブジェクトが判定するかどうか
					if (!all_collision_.GetArrayObject(j)->getpCollisionObjects(b)
						->getIsJudgment()) continue;

					// 実際の判定処理
					ActualCalculation(all_collision_.GetArrayObject(i)->getpCollisionObjects(a),
									  all_collision_.GetArrayObject(j)->getpCollisionObjects(b));

					// 各コンポーネントの衝突オブジェクトの判定をリセット
					if (all_collision_.GetArrayObject(i)->getpCollisionObjects(a)
						->getIsJudgment())
					{
						all_collision_.GetArrayObject(i)->getpCollisionObjects(a)
							->ResetHitDataAllCollisionObject();
					}
					else
					{
						a = all_collision_.GetArrayObject(i)->getEndIndexOfArray();
						break;
					}

					if (all_collision_.GetArrayObject(j)->getpCollisionObjects(b)
						->getIsJudgment())
					{
						all_collision_.GetArrayObject(j)->getpCollisionObjects(b)
							->ResetHitDataAllCollisionObject();
					}
					else
					{
						a = all_collision_.GetArrayObject(i)->getEndIndexOfArray();
						break;
					}

				}
			}
		}
	}
}



void CollisionManager::CollisionGround()
{
	if (ground_polygon_ == nullptr) return;

	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		// 地面との判定をするかどうか
		if (!all_collision_.GetArrayObject(i)->getIsJudgmentGround()) continue;

		// 地面高さ取得
		float position_y = ground_polygon_->GetHeight(*all_collision_.GetArrayObject(i)
													  ->getpGameObject()->GetTransform()
													  ->GetPosition());

		// 衝突してるか
		if (position_y >= all_collision_.GetArrayObject(i)
			->getpGameObject()->GetTransform()->GetPosition()->y)
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



void CollisionManager::ActualCalculation(CollisionObjects* collision_objects0,
										 CollisionObjects* collision_objects1)
{
	for (unsigned i = 0; i < collision_objects0->getEndIndexOfArray(); i++)
	{
		// 衝突オブジェクトが判定するかどうか
		if (!collision_objects0->getpCollisionObject(i)->getIsJudgment()) continue;

		// 総当たり
		for (unsigned j = 0; j < collision_objects1->getEndIndexOfArray(); j++)
		{
			// 衝突オブジェクトが判定するかどうか
			if (!collision_objects1->getpCollisionObject(j)->getIsJudgment()) continue;

			// 衝突計算
			if (SortCollisionCalculation(collision_objects0->getpCollisionObject(i),
										 collision_objects1->getpCollisionObject(j)))
			{
				// コンポーネント1つ目の衝突応答
				collision_objects0->getpCollisionBase()
					->HitCollision(collision_objects1->getpCollisionBase(),
								   collision_objects1->getpCollisionObject(j),
								   collision_objects0->getpCollisionObject(i));

				// コンポーネント2つ目の衝突応答
				collision_objects1->getpCollisionBase()
					->HitCollision(collision_objects0->getpCollisionBase(),
								   collision_objects0->getpCollisionObject(i),
								   collision_objects1->getpCollisionObject(j));
			}
			else
			{
				// コンポーネント1つ目の非衝突応答
				collision_objects0->getpCollisionBase()
					->NotHitCollision(collision_objects1->getpCollisionBase(),
									  collision_objects1->getpCollisionObject(j),
									  collision_objects0->getpCollisionObject(i));

				// コンポーネント2つ目の非衝突応答
				collision_objects1->getpCollisionBase()
					->NotHitCollision(collision_objects0->getpCollisionBase(),
									  collision_objects0->getpCollisionObject(i),
									  collision_objects1->getpCollisionObject(j));
			}

			// コンポーネントが判定可能かどうか
			if (!collision_objects0->getIsJudgment()) return;
			if (!collision_objects1->getIsJudgment()) return;
		}
	}
}



bool CollisionManager::SortCollisionCalculation(CollisionObject* collision_object0,
												CollisionObject* collision_object1)
{
	bool is_hit = false;

	switch (collision_object0->getpCollisionShape()->getType())
	{
		case CollisionShapeBase::Type::AABB:
		{
			/*switch(collision_object1->getpCollisionShape()->getType())
			{
				default :
					break;
			}*/
			break;
		}
		case CollisionShapeBase::Type::CAPSULE:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfCapsuleAndCapsule(&temp_vector,
						(Capsule*)collision_object0->getpCollisionShape(),
																						(Capsule*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndCapsule(&temp_position,
						(LineSegment*)collision_object1->getpCollisionShape(),
																							(Capsule*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndCapsule(&temp_vector,
						(Sphere*)collision_object1->getpCollisionShape(),
																					   (Capsule*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(-temp_vector);
					collision_object1->setHitVector(temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::CYLINDER:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndCylinder(&temp_position,
						(LineSegment*)collision_object1->getpCollisionShape(),
																							 (Cylinder*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::OBB:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::OBB:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfOBBAndOBB(&temp_vector,
						(OBB*)collision_object0->getpCollisionShape(),
																				(OBB*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndOBB(&temp_vector,
						(Sphere*)collision_object1->getpCollisionShape(),
																				   (OBB*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(-temp_vector);
					collision_object1->setHitVector(temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::PLANE:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionCalculation::CollisionJudgmentOfPlaneAndPlane(nullptr,
						(Plane*)collision_object0->getpCollisionShape(),
																					(Plane*)collision_object1->getpCollisionShape());

					collision_object0->getpHitVector()->ResetVector();
					collision_object1->getpHitVector()->ResetVector();

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndPlane(&temp_position,
						(LineSegment*)collision_object1->getpCollisionShape(),
																						  (Plane*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndPlane(&temp_vector,
						(Sphere*)collision_object1->getpCollisionShape(),
																					 (Plane*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(-temp_vector);
					collision_object1->setHitVector(temp_vector);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionCalculation::CollisionJudgmentOfPlaneAndTriangle((Plane*)collision_object0->getpCollisionShape(),
						(Triangle*)collision_object1->getpCollisionShape());

					collision_object0->getpHitVector()->ResetVector();
					collision_object1->getpHitVector()->ResetVector();

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::LINE_SEGMENT:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndCapsule(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																							(Capsule*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

				}
				case CollisionShapeBase::Type::CYLINDER:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndCylinder(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																							 (Cylinder*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::PLANE:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndPlane(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																						  (Plane*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOf2DLineSegmentAnd2DLineSegment(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																									(LineSegment*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndSphere(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																						   (Sphere*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndTriangle(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																							 (Triangle*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::SPHERE:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndCapsule(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																					   (Capsule*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::OBB:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndOBB(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																				   (OBB*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;

				}
				case CollisionShapeBase::Type::PLANE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndPlane(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																					 (Plane*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndSphere(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																						   (Sphere*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;

				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndSphere(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																					  (Sphere*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;

				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndTriangle(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																						(Triangle*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::TRIANGLE:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionCalculation::CollisionJudgmentOfPlaneAndTriangle((Plane*)collision_object1->getpCollisionShape(),
						(Triangle*)collision_object0->getpCollisionShape());

					collision_object0->getpHitVector()->ResetVector();
					collision_object1->getpHitVector()->ResetVector();

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndTriangle(&temp_position,
						(LineSegment*)collision_object1->getpCollisionShape(),
																							 (Triangle*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndTriangle(&temp_vector,
						(Sphere*)collision_object1->getpCollisionShape(),
																						(Triangle*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionCalculation::CollisionJudgmentOfTriangleAndTriangle((Triangle*)collision_object0->getpCollisionShape(),
						(Triangle*)collision_object1->getpCollisionShape());

					collision_object0->getpHitVector()->ResetVector();
					collision_object1->getpHitVector()->ResetVector();

					break;
				}
			}
			break;
		}

	}
	return is_hit;
}



void CollisionManager::DebugDisplay()
{
	// ウィンドウの設定
	ImGui::SetNextWindowPos(ImVec2(1100, 30), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(150, 500), ImGuiSetCond_Once);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.5f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.5f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f, 0.5f, 0.5f, 1.0f));

	// 開始
	ImGui::Begin("CollisionManager", nullptr);

	// 処理時間
	ImGui::Text("Time : %05lu ms", time_);

	// コンビ数
	if (is_octree_)
	{
		ImGui::Text("CombiNum : %06d", collision_objects_list_.size() / 2);
	}
	else
	{
		ImGui::Text("CombiNum : %06d", (all_collision_.GetEndPointer()) * (all_collision_.GetEndPointer() - 1) / 2);
	}

	// 8分木の有無
	ImGui::Text("PairCheck : %s", is_pair_check_ ? "true" : "false");
	if (ImGui::Button("PairCheckButton"))
	{
		is_pair_check_ ^= 1;
	}

	// 8分木の有無
	ImGui::Text("Octree : %s", is_octree_ ? "true" : "false");
	if (ImGui::Button("OctreeButton"))
	{
		is_octree_ ^= 1;
	}

	// 終了
	ImGui::End();

	// 色の解放(設定でプッシュした分だけ)
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}