//================================================================================
//
//    �Փ˃I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/04/25
//
//================================================================================

#ifndef	_COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionShapeBase/AABB/AABB.h"
#include "CollisionShapeBase/Capsule/Capsule.h"
#include "CollisionShapeBase/Cylinder/Cylinder.h"
#include "CollisionShapeBase/OBB/OBB.h"
#include "CollisionShapeBase/Plane/Plane.h"
#include "CollisionShapeBase/Segment/Segment.h"
#include "CollisionShapeBase/Sphere/Sphere.h"
#include "CollisionShapeBase/Triangle/Triangle.h"



//======================================================================
//
// �N���X��`
//
//======================================================================

class CollisionObject
{
//==============================
// �萔
//==============================
private:
	static const int TAG_NONE = -1;			//!< �^�O�Ȃ����̒l


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	
	CollisionShapeBase* collision_shape_;		//!< �`��
	Vector3D hit_vector_;						//!< �߂荞�݃x�N�g��

	int		 tag_;			//!< �^�O
	bool     is_judgment_;	//!< ���肷�邩�t���O
	bool     is_trigger_;	//!< �������Z�����邩�̃t���O


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �R���X�g���N�^
	* @param
	* collision_shape : �Փ˃I�u�W�F�N�g�̌`��
	* tag : �R���W�����I�u�W�F�N�g�����ʂ���^�O
	*/
	CollisionObject(CollisionShapeBase* collision_shape, int tag = TAG_NONE);

	/**
	* @brief
	* �f�X�g���N�^
	*/
	~CollisionObject();

	/**
	* @brief
	* �Փ˗p�f�[�^�̃��Z�b�g�֐�
	*/
	void ResetHitData();

	// �v���p�e�B
	int	 GetTag() const { return tag_; }
	CollisionShapeBase* GetCollisionShape() const { return collision_shape_; }
	Vector3D* GetHitVector() { return &hit_vector_; }
	void SetHitVector(Vector3D value) { hit_vector_ = value; }
	bool GetIsJudgment() const { return is_judgment_; }
	void SetIsJudgment(bool value) { is_judgment_ = value; }
};



#endif
