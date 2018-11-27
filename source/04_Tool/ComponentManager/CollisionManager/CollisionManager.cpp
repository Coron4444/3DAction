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
#include <Component/Base/CollisionBase/CollisionBase.h>
#include <Component/Base/CollisionBase/CollisionObject/CollisionObject.h>

#include <GameObjectBase/GameObjectBase.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>

#include <SafeRelease/SafeRelease.h>



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
void CollisionManager::Init()
{
	// 地面の初期化
	ground_polygon_ = nullptr;

	// 8分木の初期化
	if (liner_octree_ == nullptr)
	{
		liner_octree_ = new LinerOctree<CollisionObjects*>();
		liner_octree_->Init(2, Vec3(-30.0f, 0.0f, -30.0f), Vec3(30.0f, 60.0f, 30.0f));
	}
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

	// 8分木
	SafeRelease::PlusUninit(&liner_octree_);
	for (unsigned i = 0; i < object_of_tree_.size(); i++)
	{
		SafeRelease::Normal(&object_of_tree_[i]);
	}

	object_of_tree_.clear();
	collision_list_.clear();
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
	time_ = timeGetTime();

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
	for (unsigned i = 0; i < object_of_tree_.size(); i++)
	{
		// 移動オブジェクトはリストから一時的に離脱する
		object_of_tree_[i]->DeleteFromList();

		// 再登録
		liner_octree_->Add(object_of_tree_[i],
						   object_of_tree_[i]->getObject()->getOctreeAABB()->getMin(),
						   object_of_tree_[i]->getObject()->getOctreeAABB()->getMax());
	}
	liner_octree_->UpdateCollisionList(&collision_list_);

	// 古い衝突判定
	OldCollisionDetermination();

	// 地面との衝突判定
	CollisionGround();

	time_ = timeGetTime() - time_;

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



//--------------------------------------------------
// +衝突基底クラスの追加関数
//--------------------------------------------------
void CollisionManager::AddCollisionBaseToArray(CollisionBase* collision)
{
	// 追加待ち配列に追加
	await_add_.AddToArray(collision);
}



//--------------------------------------------------
// +衝突基底クラスの上書き関数
//--------------------------------------------------
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
		new_collision->SetGameObject(game_object);
		new_collision->Init();
	}
}



//--------------------------------------------------
// +衝突基底クラスの解放関数
//--------------------------------------------------
void CollisionManager::ReleaseCollisionBaseFromArray(CollisionBase* collision)
{
	// 解放待ち配列に追加
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

		// 8分木への追加
		for (unsigned j = 0; j < await_add_.GetArrayObject(i)->getEndIndexOfArray(); j++)
		{
			ObjectOfTree<CollisionObjects*>* temp = new ObjectOfTree<CollisionObjects*>;
			CollisionObjects* temp_objects = await_add_.GetArrayObject(i)->getCollisionObjects(j);
			object_of_tree_.push_back(temp);
			temp->setObject(temp_objects);
			liner_octree_->Add(temp, temp_objects->getOctreeAABB()->getMin(),
							   temp_objects->getOctreeAABB()->getMax());
		}
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
// -古い衝突判定関数
//--------------------------------------------------
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
			if (!CollisionPairCheck::IsCheck(all_collision_.GetArrayObject(i),
											 all_collision_.GetArrayObject(j))) continue;

			for (unsigned a = 0; a < all_collision_.GetArrayObject(i)->getEndIndexOfArray(); a++)
			{
				// 複数衝突オブジェクトが判定するかどうか
				if (!all_collision_.GetArrayObject(i)->getCollisionObjects(a)
					->getIsJudgment()) continue;

				for (unsigned b = 0; b < all_collision_.GetArrayObject(i)->getEndIndexOfArray(); b++)
				{
					// 複数衝突オブジェクトが判定するかどうか
					if (!all_collision_.GetArrayObject(j)->getCollisionObjects(b)
						->getIsJudgment()) continue;

					// 実際の判定処理
					ActualCalculation(all_collision_.GetArrayObject(i),
									  all_collision_.GetArrayObject(j),
									  all_collision_.GetArrayObject(i)->getCollisionObjects(a),
									  all_collision_.GetArrayObject(j)->getCollisionObjects(b));

					// 各コンポーネントの衝突オブジェクトの判定をリセット
					if (all_collision_.GetArrayObject(i)->getIsJudgment())
					{
						if (all_collision_.GetArrayObject(i)->getCollisionObjects(a)
							->getIsJudgment())
						{
							all_collision_.GetArrayObject(i)->getCollisionObjects(a)
								->ResetHitDataAllCollisionObject();
						}
					}
					else
					{
						a = all_collision_.GetArrayObject(i)->getEndIndexOfArray();
						break;
					}

					if (all_collision_.GetArrayObject(j)->getIsJudgment())
					{
						if (all_collision_.GetArrayObject(j)->getCollisionObjects(b)
							->getIsJudgment())
						{
							all_collision_.GetArrayObject(j)->getCollisionObjects(b)
								->ResetHitDataAllCollisionObject();
						}
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



//--------------------------------------------------
// -地面との衝突判定関数
//--------------------------------------------------
void CollisionManager::CollisionGround()
{
	if (ground_polygon_ == nullptr) return;

	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		// 地面との判定をするかどうか
		if (!all_collision_.GetArrayObject(i)->getIsJudgmentGround()) continue;

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
										 CollisionBase* collision1,
										 CollisionObjects* collision_objects0,
										 CollisionObjects* collision_objects1)
{
	for (unsigned i = 0; i < collision_objects0->getEndIndexOfArray(); i++)
	{
		// 衝突オブジェクトが判定するかどうか
		if (!collision_objects0->getCollisionObject(i)->getIsJudgment()) continue;

		// 総当たり
		for (unsigned j = 0; j < collision_objects1->getEndIndexOfArray(); j++)
		{
			// 衝突オブジェクトが判定するかどうか
			if (!collision_objects1->getCollisionObject(j)->getIsJudgment()) continue;

			// 衝突計算
			if (SortCollisionCalculation(collision_objects0->getCollisionObject(i),
										 collision_objects1->getCollisionObject(j)))
			{
				// コンポーネント1つ目の衝突応答
				collision_objects0->getCollisionBase()
					->HitCollision(collision_objects1->getCollisionBase(),
								   collision_objects1->getCollisionObject(j),
								   collision_objects0->getCollisionObject(i));

				// コンポーネント2つ目の衝突応答
				if (!collision1->getIsJudgment()) return;
				collision_objects1->getCollisionBase()
					->HitCollision(collision_objects0->getCollisionBase(),
								   collision_objects0->getCollisionObject(i),
								   collision_objects1->getCollisionObject(j));
			}
			else
			{
				// コンポーネント1つ目の非衝突応答
				collision_objects0->getCollisionBase()
					->NotHitCollision(collision_objects1->getCollisionBase(),
									  collision_objects1->getCollisionObject(j),
									  collision_objects0->getCollisionObject(i));

				// コンポーネント2つ目の非衝突応答
				if (!collision1->getIsJudgment()) return;
				collision_objects1->getCollisionBase()
					->NotHitCollision(collision_objects0->getCollisionBase(),
									  collision_objects0->getCollisionObject(i),
									  collision_objects1->getCollisionObject(j));
			}

			// コンポーネントが判定可能かどうか
			if (!collision0->getIsJudgment()) return;
			if (!collision1->getIsJudgment()) return;
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

	switch (collision_object0->getCollisionShape()->getType())
	{
		case CollisionShapeBase::Type::AABB:
		{
			/*switch(collision_object1->getCollisionShape()->getType())
			{
				default :
					break;
			}*/
			break;
		}
		case CollisionShapeBase::Type::CAPSULE:
		{
			switch (collision_object1->getCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Capsule_Capsule(&temp_vector,
						(Capsule*)collision_object0->getCollisionShape(),
																		 (Capsule*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Capsule(&temp_position,
						(Segment*)collision_object1->getCollisionShape(),
																		   (Capsule*)collision_object0->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Capsule(&temp_vector,
						(Sphere*)collision_object1->getCollisionShape(),
																		(Capsule*)collision_object0->getCollisionShape());

					collision_object0->setHitVector(-temp_vector);
					collision_object1->setHitVector(temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::CYLINDER:
		{
			switch (collision_object1->getCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Cylinder(&temp_position,
						(Segment*)collision_object1->getCollisionShape(),
																			(Cylinder*)collision_object0->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::OBB:
		{
			switch (collision_object1->getCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::OBB:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_OBB_OBB(&temp_vector,
						(OBB*)collision_object0->getCollisionShape(),
																 (OBB*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_OBB(&temp_vector,
						(Sphere*)collision_object1->getCollisionShape(),
																	(OBB*)collision_object0->getCollisionShape());

					collision_object0->setHitVector(-temp_vector);
					collision_object1->setHitVector(temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::PLANE:
		{
			switch (collision_object1->getCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionJudgment::HitCheck_Plane_Plane(nullptr,
						(Plane*)collision_object0->getCollisionShape(),
																	 (Plane*)collision_object1->getCollisionShape());

					collision_object0->getHitVector()->ResetVector();
					collision_object1->getHitVector()->ResetVector();

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Plane(&temp_position,
						(Segment*)collision_object1->getCollisionShape(),
																		 (Plane*)collision_object0->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Plane(&temp_vector,
						(Sphere*)collision_object1->getCollisionShape(),
																	  (Plane*)collision_object0->getCollisionShape());

					collision_object0->setHitVector(-temp_vector);
					collision_object1->setHitVector(temp_vector);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionJudgment::HitCheck_Plane_Triangle((Plane*)collision_object0->getCollisionShape(),
						(Triangle*)collision_object1->getCollisionShape());

					collision_object0->getHitVector()->ResetVector();
					collision_object1->getHitVector()->ResetVector();

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::SEGMENT:
		{
			switch (collision_object1->getCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Capsule(&temp_position,
						(Segment*)collision_object0->getCollisionShape(),
																		   (Capsule*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

				}
				case CollisionShapeBase::Type::CYLINDER:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Cylinder(&temp_position,
						(Segment*)collision_object0->getCollisionShape(),
																			(Cylinder*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::PLANE:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Plane(&temp_position,
						(Segment*)collision_object0->getCollisionShape(),
																		 (Plane*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment2D_Segment2D(&temp_position,
						(Segment*)collision_object0->getCollisionShape(),
																			 (Segment*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Sphere(&temp_position,
						(Segment*)collision_object0->getCollisionShape(),
																		  (Sphere*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Triangle(&temp_position,
						(Segment*)collision_object0->getCollisionShape(),
																			(Triangle*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::SPHERE:
		{
			switch (collision_object1->getCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Capsule(&temp_vector,
						(Sphere*)collision_object0->getCollisionShape(),
																		(Capsule*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::OBB:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_OBB(&temp_vector,
						(Sphere*)collision_object0->getCollisionShape(),
																	(OBB*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;

				}
				case CollisionShapeBase::Type::PLANE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Plane(&temp_vector,
						(Sphere*)collision_object0->getCollisionShape(),
																	  (Plane*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Sphere(&temp_position,
						(Segment*)collision_object0->getCollisionShape(),
																		  (Sphere*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;

				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Sphere(&temp_vector,
						(Sphere*)collision_object0->getCollisionShape(),
																	   (Sphere*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;

				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Triangle(&temp_vector,
						(Sphere*)collision_object0->getCollisionShape(),
																		 (Triangle*)collision_object1->getCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::TRIANGLE:
		{
			switch (collision_object1->getCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionJudgment::HitCheck_Plane_Triangle((Plane*)collision_object1->getCollisionShape(),
						(Triangle*)collision_object0->getCollisionShape());

					collision_object0->getHitVector()->ResetVector();
					collision_object1->getHitVector()->ResetVector();

					break;
				}
				case CollisionShapeBase::Type::SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionJudgment::HitCheck_Segment3D_Triangle(&temp_position,
						(Segment*)collision_object1->getCollisionShape(),
																			(Triangle*)collision_object0->getCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionJudgment::HitCheck_Sphere_Triangle(&temp_vector,
						(Sphere*)collision_object1->getCollisionShape(),
																		 (Triangle*)collision_object0->getCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionJudgment::HitCheck_Triangle_Triangle((Triangle*)collision_object0->getCollisionShape(),
						(Triangle*)collision_object1->getCollisionShape());

					collision_object0->getHitVector()->ResetVector();
					collision_object1->getHitVector()->ResetVector();

					break;
				}
			}
			break;
		}

	}
	return is_hit;
}



//--------------------------------------------------
// -衝突計算振り分け関数
//--------------------------------------------------
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

	// 終了
	ImGui::End();

	// 色の解放(設定でプッシュした分だけ)
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}