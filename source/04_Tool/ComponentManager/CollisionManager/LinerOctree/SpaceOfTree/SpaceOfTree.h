//================================================================================
//
//    ���؋�ԃN���X
//    Author : Araki Kai                                �쐬�� : 2018/11/26
//
//================================================================================

#ifndef	_SPACE_OF_TREE_H_
#define _SPACE_OF_TREE_H_



//****************************************
// �C���N���[�h��
//****************************************

#include "../ObjectOfTree/ObjectOfTree.h"



/*********************************************************//**
* @brief
* ���؋�ԃN���X
*
* ���؂̋�ԃN���X
*************************************************************/
template <class Type>
class SpaceOfTree
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	ObjectOfTree<Type>* first_pointer_ = nullptr;	//!< �ŏ��̃I�u�W�F�N�g�|�C���^


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �I���֐�
	*/
	void Uninit()
	{
		if (first_pointer_ == nullptr) return;

		ResetLink(&first_pointer_);
	}

	/**
	* @brief
	* �����N�̃��Z�b�g�֐�
	* @param
	* object : �����N�����Z�b�g�������I�u�W�F�N�g�̃|�C���^�̃|�C���^
	*/
	void ResetLink(ObjectOfTree<Type>** object)
	{
		if ((*object)->getNextPointer() != nullptr)
		{
			ResetLink((*object)->getNextPointer2());
		}

		*object = nullptr;
	}

	/**
	* @brief
	* �I�u�W�F�N�g�̒ǉ��֐�
	* @param
	* object : �ǉ��������I�u�W�F�N�g�|�C���^
	*/
	void AddObject(ObjectOfTree<Type>* object)
	{
		// NULL&2�d�o�^�`�F�b�N
		if (object == nullptr) return;
		if (object->getBelongingSpace() == this) return;

		// �ŏ��̃I�u�W�F�N�g�|�C���^���o�^����Ă��邩�ǂ���
		if (first_pointer_ == nullptr)
		{
			// �ŏ��̃I�u�W�F�N�g�|�C���^�ɓo�^
			first_pointer_ = object;
		}
		else
		{
			// �ŏ��̃I�u�W�F�N�g�|�C���^���X�V
			object->setNextPointer(first_pointer_);
			first_pointer_->setPreviousPointer(object);
			first_pointer_ = object;
		}

		// ��Ԃ�o�^
		object->setBelongingSpace(this);
	}

	/**
	* @brief
	* �����I�u�W�F�N�g�̃`�F�b�N�֐�
	* @param
	* object : �`�F�b�N�����������I�u�W�F�N�g�|�C���^
	*/
	void CheckDeleteObject(ObjectOfTree<Type>* object)
	{
		if (first_pointer_ != object) return;
		if (first_pointer_ == nullptr) return;

		// ���̃|�C���^�֑}���ւ���
		first_pointer_ = first_pointer_->getNextPointer();
	}

	// �v���p�e�B
	ObjectOfTree<Type>* getFirstObject() { return first_pointer_; }
	void setFirstObject(ObjectOfTree<Type>* value) { first_pointer_ = value; }
};



#endif
