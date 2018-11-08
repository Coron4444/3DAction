//================================================================================
//
//    �Փ˃y�A����N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/04/20
//
//================================================================================

#ifndef	_COLLISION_PAIR_CHECK_H_
#define _COLLISION_PAIR_CHECK_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <vector>

#include <Component/CollisionBase/CollisionBase.h>

#include <Vector3D.h>



/*********************************************************//**
* @brief
* �Փ˃y�A����N���X
*
* �Փˊ��N���X�̃y�A�𔻒肷��N���X
*************************************************************/
class CollisionPairCheck
{
//==============================
// �ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �Փˊ��N���X�y�A����֐�
	*/
	static bool IsCheck(CollisionBase* collision0, CollisionBase* collision1);


private:
	/**
	* @brief
	* �y�A����֐�
	*/
	static bool IsPair(CollisionBase* collision0, CollisionBase* collision1);

	/**
	* @brief
	* �w�肵���Փ˃X�e�[�g�̌����֐�
	*/
	static CollisionBase* IsState(CollisionBase::State state,
								  CollisionBase* collision0,
								  CollisionBase* collision1);

	/**
	* @brief
	* �w�肵���R���|�[�l���g�̋t��Ԃ��֐�
	*/
	static CollisionBase* OtherSideComponent(CollisionBase* age_component,
											 CollisionBase* collision0,
											 CollisionBase* collision1);

	/**
	* @brief
	* �v���C���[�̃y�A���X�g�֐�
	*/
	static bool PairList_Player(CollisionBase* collision);


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	/**
	* @brief
	* �R���X�g���N�^(�폜)
	*/
	CollisionPairCheck() = delete;

	/**
	* @brief
	* �R�s�[�R���X�g���N�^(�폜)
	*/
	CollisionPairCheck(const CollisionPairCheck& value) = delete;

	/**
	* @brief
	* ������Z�q�̃I�[�o�[���[�h(�폜)
	*/
	CollisionPairCheck& operator = (const CollisionPairCheck& value) = delete;
};



#endif