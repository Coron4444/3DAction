//================================================================================
//
//    �Փ˃R���|�[�l���g�}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/04/17
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
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
// �ÓI�����o�ϐ���`
//
//======================================================================

LimitedPointerArray<CollisionComponent*, CollisionComponentManager::ARRAY_NUM> CollisionComponentManager::all_collision_component_;
LimitedPointerArray<CollisionComponent*, CollisionComponentManager::ARRAY_NUM> CollisionComponentManager::release_;

MeshPlanePolygon* CollisionComponentManager::ground_polygon_;



//======================================================================
//
// �ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::Init()
{
	// �n�ʂ̏�����
	ground_polygon_ = nullptr;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::Uninit()
{
	// ����p�z��̃��Z�b�g
	release_.ResetArray();

	// �R���|�[�l���g�z��̃��Z�b�g
	all_collision_component_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �V�[���ύX���̏I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::Uninit_ChangeScene()
{
	// ����p�z��̃��Z�b�g
	release_.ResetArray();

	// �R���|�[�l���g�z��̃��Z�b�g
	all_collision_component_.ResetArray();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::Update()
{
	// ����҂��̉��
	ReleaseUpdateComponentALL();

	// �R���|�[�l���g�̍X�V
	for (unsigned i = 0; i < all_collision_component_.GetEndPointer(); i++)
	{
		all_collision_component_.GetArrayObject(i)->Update();
	}

	// �Փ˔���
	CollisionDetermination();

	// �n�ʂƂ̏Փ˔���
	CollisionGround();

#ifdef _DEBUG
	// �f�o�b�O
	for (unsigned i = 0; i < all_collision_component_.GetEndPointer(); i++)
	{
		if (all_collision_component_.GetArrayObject(i) == nullptr) continue;
		all_collision_component_.GetArrayObject(i)->Debug();
	}
#endif
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˃R���|�[�l���g�o�^�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::RegistrationComponent(CollisionComponent* collision_component)
{
	// �o�^
	all_collision_component_.AddToArray(collision_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˃R���|�[�l���g�㏑���֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::OverwriteComponent(GameObjectOrigin* game_object, CollisionComponent* new_collision_component)
{
	// �V�K�R���|�[�l���g��nullptr���ǂ���
	if (new_collision_component == nullptr)
	{
		// �Â��I�u�W�F�N�g�̉��
		ReleaseComponent(game_object->GetCollisionComponent());

		// �Â��R���|�[�l���g�̏���
		CollisionComponent* temp = game_object->GetCollisionComponent();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g(nullptr)�̑��
		game_object->SetCollisionComponent(new_collision_component);
	}
	else
	{
		// �z��̏㏑��
		all_collision_component_.OverwriteArray(game_object->GetCollisionComponent(), new_collision_component);

		// �Â��R���|�[�l���g�̏���
		CollisionComponent* temp = game_object->GetCollisionComponent();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g�̏�����
		game_object->SetCollisionComponent(new_collision_component);
		new_collision_component->SetGameObjectOrigin(game_object);
		new_collision_component->Init();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փ˃R���|�[�l���g����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::ReleaseComponent(CollisionComponent* collision_component)
{
	// ����z��o�^
	release_.AddToArray(collision_component);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �n�ʐݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CollisionComponentManager::SetGround(MeshPlanePolygon* ground_polygon)
{
	ground_polygon_ = ground_polygon; 
}



//--------------------------------------------------------------------------------
//
// [ �S�Ẳ���҂��Փ˃R���|�[�l���g�̉���֐� ]
//
//--------------------------------------------------------------------------------

void CollisionComponentManager::ReleaseUpdateComponentALL()
{
	// ����҂������邩�ǂ���
	if(release_.GetEndPointer() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < release_.GetEndPointer(); i++)
	{
		// ����ƕ��בւ�
		all_collision_component_.DeleteFromArrayAndSortArray(release_.GetArrayObject(i));
	}

	// ����҂��z������Z�b�g
	release_.ResetArray();
}



//--------------------------------------------------------------------------------
//
// [ �Փ˔���֐� ]
//
//--------------------------------------------------------------------------------

void CollisionComponentManager::CollisionDetermination()
{
	if (all_collision_component_.GetEndPointer() < 2) return;
	for (unsigned i = 0; i < all_collision_component_.GetEndPointer() - 1; i++)
	{
		if (all_collision_component_.GetArrayObject(i) == nullptr) continue;

		// �R���|�[�l���g���̂����肷�邩�ǂ���
		if (!all_collision_component_.GetArrayObject(i)->GetIsJudgment()) continue;

		// ��������
		for (unsigned j = i + 1; j < all_collision_component_.GetEndPointer(); j++)
		{
			if (all_collision_component_.GetArrayObject(j) == nullptr) continue;	

			// �R���|�[�l���g���̂����肷�邩�ǂ���
			if (!all_collision_component_.GetArrayObject(j)->GetIsJudgment()) continue;

			// ���������g�ݍ��킹���H
			if (!CollisionComponentPairCheck::IsCheck(all_collision_component_.GetArrayObject(i), all_collision_component_.GetArrayObject(j))) continue;

			// ���ۂ̔��菈��
			ActualCalculation(all_collision_component_.GetArrayObject(i), all_collision_component_.GetArrayObject(j));

			// �e�R���|�[�l���g�̏Փ˃I�u�W�F�N�g�̔�������Z�b�g
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
// [ �n�ʂƂ̏Փ˔���֐� ]
//
//--------------------------------------------------------------------------------

void CollisionComponentManager::CollisionGround()
{
	if (ground_polygon_ == nullptr) return;

	for (unsigned i = 0; i < all_collision_component_.GetEndPointer(); i++)
	{
		// �n�ʂƂ̔�������邩�ǂ���
		if (!all_collision_component_.GetArrayObject(i)->GetIsJudgmentGround()) continue;

		// �n�ʍ����擾
		float position_y = ground_polygon_->GetHeight(*all_collision_component_.GetArrayObject(i)->
													   GetGameObjectOrigin()->GetTransform()->GetPosition());

		// �Փ˂��Ă邩
		if (position_y >= all_collision_component_.GetArrayObject(i)->
						  GetGameObjectOrigin()->GetTransform()->GetPosition()->y)
		{
			// �n�ʂƂ̏Փˏ���
			all_collision_component_.GetArrayObject(i)->HitGround(position_y);
		}
		else
		{
			// �n�ʂƂ̔�Փˏ���
			all_collision_component_.GetArrayObject(i)->NotHitGround(position_y);
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ ���ۂ̌v�Z�֐� ]
//
//--------------------------------------------------------------------------------

void CollisionComponentManager::ActualCalculation(CollisionComponent* collision_component_0, CollisionComponent* collision_component_1)
{
	for (unsigned i = 0; i < collision_component_0->GetEndIndexCollisionObjectArray(); i++)
	{
		// �Փ˃I�u�W�F�N�g�����肷�邩�ǂ���
		if (!collision_component_0->GetCollisionObject(i)->GetIsJudgment()) continue;

		// ��������
		for (unsigned j = 0; j < collision_component_1->GetEndIndexCollisionObjectArray(); j++)
		{
			// �Փ˃I�u�W�F�N�g�����肷�邩�ǂ���
			if (!collision_component_1->GetCollisionObject(j)->GetIsJudgment()) continue;

			// �Փˌv�Z
			if (SortCollisionCalculation(collision_component_0->GetCollisionObject(i),
				                         collision_component_1->GetCollisionObject(j)))
			{
				// �R���|�[�l���g1�ڂ̏Փˉ���
				collision_component_0->HitCollision(collision_component_1, 
													collision_component_1->GetCollisionObject(j),
													collision_component_0->GetCollisionObject(i));
				
				// �R���|�[�l���g2�ڂ̏Փˉ���
				collision_component_1->HitCollision(collision_component_0, 
													collision_component_0->GetCollisionObject(i),
													collision_component_1->GetCollisionObject(j));
			}
			else
			{
				// �R���|�[�l���g1�ڂ̔�Փˉ���
				collision_component_0->NotHitCollision(collision_component_1, 
													   collision_component_1->GetCollisionObject(j),
													   collision_component_0->GetCollisionObject(i));
				
				// �R���|�[�l���g2�ڂ̔�Փˉ���
				collision_component_1->NotHitCollision(collision_component_0, 
													   collision_component_0->GetCollisionObject(i),
													   collision_component_1->GetCollisionObject(j));
			}

			// �R���|�[�l���g������\���ǂ���
			if (!collision_component_0->GetIsJudgment()) return;
			if (!collision_component_1->GetIsJudgment()) return;
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ �Փˌv�Z�U�蕪���֐� ]
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
