//================================================================================
//
//    �Փˌ`��x�[�X�̌��_�N���X
//    Author : Araki Kai                                �쐬�� : 2018/04/25
//
//================================================================================

#ifndef	_COLLISION_SHAPE_ORIGIN_H_
#define _COLLISION_SHAPE_ORIGIN_H_



//======================================================================
//
// �N���X��`
//
//======================================================================

class CollisionShapeOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	enum Type
	{
		TYPE_NONE = -1,
		TYPE_AABB,
		TYPE_CAPSULE,
		TYPE_CYLINDER,
		TYPE_OBB,
		TYPE_PLANE,
		TYPE_SEGMENT,
		TYPE_SPHERE,
		TYPE_TRIANGLE,
		TYPE_MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	CollisionShapeOrigin(Type type) : type_(type){}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~CollisionShapeOrigin(){}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	Type GetType() {return type_;}


//------------------------------------------------------------
private :
	// �����o�ϐ�
	Type type_;

};



#endif