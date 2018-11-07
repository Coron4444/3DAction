//================================================================================
//
//    �Փ˃I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/04/25
//
//================================================================================

#ifndef	_COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "CollisionShapeOrigin\CollisionShapeOrigin.h"

#include "CollisionShapeOrigin\AABB\AABB.h"
#include "CollisionShapeOrigin\Capsule\Capsule.h"
#include "CollisionShapeOrigin\Cylinder\Cylinder.h"
#include "CollisionShapeOrigin\OBB\OBB.h"
#include "CollisionShapeOrigin\Plane\Plane.h"
#include "CollisionShapeOrigin\Segment\Segment.h"
#include "CollisionShapeOrigin\Sphere\Sphere.h"
#include "CollisionShapeOrigin\Triangle\Triangle.h"



//======================================================================
//
// �N���X��`
//
//======================================================================

class CollisionObject
{
//------------------------------------------------------------
private :
	static const int TAG_NONE = -1;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	CollisionObject(CollisionShapeOrigin* collision_shape, 
		            int tag = TAG_NONE);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	~CollisionObject();
	

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void ResetHitData();

	// �Z�b�^
	void SetHitVector(Vector3D hit_vector) {hit_vector_ = hit_vector;}
	void SetIsJudgment(bool is_judgment)   {is_judgment_ = is_judgment;}
	
	// �Q�b�^
	CollisionShapeOrigin* GetCollisionShape() const {return collision_shape_;}
	int	 GetTag()		 const {return tag_;}
	bool GetIsJudgment() const {return is_judgment_;}
	Vector3D* GetHitVector() {return &hit_vector_;}


//------------------------------------------------------------
private :
	// �`��
	CollisionShapeOrigin* collision_shape_;
	
	// �߂荞��
	Vector3D hit_vector_;
	
	// ���
	int		 tag_;
	bool     is_judgment_;
	bool     is_trigger_;
	
};



#endif
