//================================================================================
//
//    �Փˌ`����N���X
//    Author : Araki Kai                                �쐬�� : 2018/04/25
//
//================================================================================

#ifndef	_COLLISION_SHAPE_BASE_H_
#define _COLLISION_SHAPE_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Vector3D.h>



/*********************************************************//**
* @brief
* �Փˌ`����N���X
*
* �Փˌ`��̊��N���X
*************************************************************/
class CollisionShapeBase
{
//==============================
// �񋓌^��`
//==============================
public:
	// �`��^�C�v
	enum Type
	{
		NONE = -1,
		AABB,
		CAPSULE,
		CYLINDER,
		OBB,
		PLANE,
		SEGMENT,
		SPHERE,
		TRIANGLE,
		MAX
	};


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	Type type_;				//!< �`��^�C�v
	Vector3D position_;		//!< ���W


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �R���X�g���N�^
	*/
	CollisionShapeBase(Type type) : type_(type) {}

	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~CollisionShapeBase() {}

	// �v���p�e�B
	Type getType() { return type_; }
	const Vector3D* getPositon() const { return &position_; }
	void setPosition(Vector3D value) { position_ = value; }
};



#endif