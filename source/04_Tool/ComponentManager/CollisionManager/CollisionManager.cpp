//================================================================================
//
//    �Փ˃}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/04/17
//
//================================================================================



//****************************************
// �C���N���[�h��
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
// �ÓI�����o�ϐ���`
//****************************************
LimitedPointerArray<CollisionBase*, CollisionManager::ARRAY_NUM> CollisionManager::all_collision_;
LimitedPointerArray<CollisionBase*, CollisionManager::ARRAY_NUM> CollisionManager::await_add_;
LimitedPointerArray<CollisionBase*, CollisionManager::ARRAY_NUM> CollisionManager::await_release_;

MeshPlanePolygon* CollisionManager::ground_polygon_;



//****************************************
// �ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void CollisionManager::Init()
{
	// �n�ʂ̏�����
	ground_polygon_ = nullptr;
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void CollisionManager::Uninit()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�Փ˔z��̃��Z�b�g
	all_collision_.ResetArray();
}



//--------------------------------------------------
// +�V�[���ύX���̏I���֐�
//--------------------------------------------------
void CollisionManager::UninitWhenChangeScene()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�Փ˔z��̃��Z�b�g
	all_collision_.ResetArray();
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void CollisionManager::Update()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �Փ˃N���X�̍X�V
	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		all_collision_.GetArrayObject(i)->Update();
	}

	// �Փ˔���
	CollisionDetermination();

	// �n�ʂƂ̏Փ˔���
	CollisionGround();

	// �f�o�b�O
#ifdef _DEBUG
	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		if (all_collision_.GetArrayObject(i) == nullptr) continue;
		all_collision_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



//--------------------------------------------------
// +�Փˊ��N���X�̒ǉ��֐�
//--------------------------------------------------
void CollisionManager::AddCollisionBaseToArray(CollisionBase* collision)
{
	// �ǉ��҂��z��ɒǉ�
	await_add_.AddToArray(collision);
}



//--------------------------------------------------
// +�X�V���N���X�̏㏑���֐�
//--------------------------------------------------
void CollisionManager::OverwriteArrayCollisionBase(GameObjectBase* game_object,
												   CollisionBase* new_collision)
{
	// �V�K��nullptr�̏ꍇ
	if (new_collision == nullptr)
	{
		// �Â��X�V���N���X�̉��
		ReleaseCollisionBaseFromArray(game_object->GetCollision());

		// �Â��X�V���N���X�̏���
		CollisionBase* temp = game_object->GetCollision();
		SafeRelease::Normal(&temp);

		// nullptr�̑��
		game_object->SetCollision(new_collision);
	}
	else
	{
		// �z��̏㏑��
		all_collision_.OverwriteArray(game_object->GetCollision(), new_collision);

		// �Â��X�V���N���X�̏���
		CollisionBase* temp = game_object->GetCollision();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g�̏�����
		game_object->SetCollision(new_collision);
		new_collision->SetGameObject(game_object);
		new_collision->Init();
	}
}



//--------------------------------------------------
// +�Փˊ��N���X�̉���֐�
//--------------------------------------------------
void CollisionManager::ReleaseCollisionBaseFromArray(CollisionBase* collision)
{
	// �ǉ��҂��z��ɒǉ�
	await_release_.AddToArray(collision);
}



//--------------------------------------------------
// +�n�ʐݒ�֐�
//--------------------------------------------------
void CollisionManager::SetGround(MeshPlanePolygon* ground_polygon)
{
	ground_polygon_ = ground_polygon;
}



//--------------------------------------------------
// -�ǉ��҂��z��̒��g��ǉ��֐�
//--------------------------------------------------
void CollisionManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if (await_add_.GetEndPointer() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_collision_.AddToArray(await_add_.GetArrayObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.ResetArray();
}



//--------------------------------------------------
// -����҂��z��̒��g������֐�
//--------------------------------------------------
void CollisionManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if (await_release_.GetEndPointer() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		all_collision_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.ResetArray();
}



//--------------------------------------------------
// -�Փ˔���֐�
//--------------------------------------------------
void CollisionManager::CollisionDetermination()
{
	if (all_collision_.GetEndPointer() < 2) return;
	for (unsigned i = 0; i < all_collision_.GetEndPointer() - 1; i++)
	{
		if (all_collision_.GetArrayObject(i) == nullptr) continue;

		// �R���|�[�l���g���̂����肷�邩�ǂ���
		if (!all_collision_.GetArrayObject(i)->GetIsJudgment()) continue;

		// ��������
		for (unsigned j = i + 1; j < all_collision_.GetEndPointer(); j++)
		{
			if (all_collision_.GetArrayObject(j) == nullptr) continue;

			// �R���|�[�l���g���̂����肷�邩�ǂ���
			if (!all_collision_.GetArrayObject(j)->GetIsJudgment()) continue;

			// ���������g�ݍ��킹���H
			if (!CollisionPairCheck::IsCheck(all_collision_.GetArrayObject(i),
											 all_collision_.GetArrayObject(j))) continue;

			// ���ۂ̔��菈��
			ActualCalculation(all_collision_.GetArrayObject(i),
							  all_collision_.GetArrayObject(j));

			// �e�R���|�[�l���g�̏Փ˃I�u�W�F�N�g�̔�������Z�b�g
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
// -�n�ʂƂ̏Փ˔���֐�
//--------------------------------------------------
void CollisionManager::CollisionGround()
{
	if (ground_polygon_ == nullptr) return;

	for (unsigned i = 0; i < all_collision_.GetEndPointer(); i++)
	{
		// �n�ʂƂ̔�������邩�ǂ���
		if (!all_collision_.GetArrayObject(i)->GetIsJudgmentGround()) continue;

		// �n�ʍ����擾
		float position_y = ground_polygon_->GetHeight(*all_collision_.GetArrayObject(i)
													  ->GetGameObject()->GetTransform()
													  ->GetPosition());

		// �Փ˂��Ă邩
		if (position_y >= all_collision_.GetArrayObject(i)
			->GetGameObject()->GetTransform()->GetPosition()->y)
		{
			// �n�ʂƂ̏Փˏ���
			all_collision_.GetArrayObject(i)->HitGround(position_y);
		}
		else
		{
			// �n�ʂƂ̔�Փˏ���
			all_collision_.GetArrayObject(i)->NotHitGround(position_y);
		}
	}
}



//--------------------------------------------------
// -���ۂ̌v�Z�֐�
//--------------------------------------------------
void CollisionManager::ActualCalculation(CollisionBase* collision0,
										 CollisionBase* collision1)
{
	for (unsigned i = 0; i < collision0->GetEndIndexOfArray(); i++)
	{
		// �Փ˃I�u�W�F�N�g�����肷�邩�ǂ���
		if (!collision0->GetCollisionObject(i)->GetIsJudgment()) continue;

		// ��������
		for (unsigned j = 0; j < collision1->GetEndIndexOfArray(); j++)
		{
			// �Փ˃I�u�W�F�N�g�����肷�邩�ǂ���
			if (!collision1->GetCollisionObject(j)->GetIsJudgment()) continue;

			// �Փˌv�Z
			if (SortCollisionCalculation(collision0->GetCollisionObject(i),
										 collision1->GetCollisionObject(j)))
			{
				// �R���|�[�l���g1�ڂ̏Փˉ���
				collision0->HitCollision(collision1,
										 collision1->GetCollisionObject(j),
										 collision0->GetCollisionObject(i));

				// �R���|�[�l���g2�ڂ̏Փˉ���
				collision1->HitCollision(collision0,
										 collision0->GetCollisionObject(i),
										 collision1->GetCollisionObject(j));
			}
			else
			{
				// �R���|�[�l���g1�ڂ̔�Փˉ���
				collision0->NotHitCollision(collision1,
											collision1->GetCollisionObject(j),
											collision0->GetCollisionObject(i));

				// �R���|�[�l���g2�ڂ̔�Փˉ���
				collision1->NotHitCollision(collision0,
											collision0->GetCollisionObject(i),
											collision1->GetCollisionObject(j));
			}

			// �R���|�[�l���g������\���ǂ���
			if (!collision0->GetIsJudgment()) return;
			if (!collision1->GetIsJudgment()) return;
		}
	}
}



//--------------------------------------------------
// -�Փˌv�Z�U�蕪���֐�
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
