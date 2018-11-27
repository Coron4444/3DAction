//================================================================================
//
//    ���؃I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/26
//
//================================================================================

#ifndef	_OBJECT_OF_TREE_H_
#define _OBJECT_OF_TREE_H_



//****************************************
// �C���N���[�h��
//****************************************



//****************************************
// �N���X�錾
//****************************************
template<class Type>
class SpaceOfTree;



/*********************************************************//**
* @brief
* ���؃I�u�W�F�N�g�N���X
*
* ���؂̃I�u�W�F�N�g�N���X
*************************************************************/
template <class Type>
class ObjectOfTree
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	SpaceOfTree<Type>* belonging_space_ = nullptr;		//!< �������
	Type object_ = nullptr;								//!< �I�u�W�F�N�g
	ObjectOfTree<Type>* previous_pointer_ = nullptr;	//!< �O�|�C���^
	ObjectOfTree<Type>* next_pointer_ = nullptr;		//!< ���|�C���^


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���X�g�����������֐�
	*/
	void DeleteFromList()
	{
		if (belonging_space_ == nullptr) return;

		// �������Ă����Ԃɏ�����ʒm
		belonging_space_->CheckDeleteObject(this);

		// �O��̃I�u�W�F�N�g�����т���
		if (previous_pointer_ != nullptr)
		{
			previous_pointer_->setNextPointer(next_pointer_);
		}
		if (next_pointer_ != nullptr)
		{
			next_pointer_->setPreviousPointer(previous_pointer_);
		}
		previous_pointer_ = nullptr;
		next_pointer_ = nullptr;
		belonging_space_ = nullptr;
	}

	// �v���p�e�B
	SpaceOfTree<Type>* getBelongingSpace() { return belonging_space_; }
	void setBelongingSpace(SpaceOfTree<Type>* value) { belonging_space_ = value; }
	Type getObject() { return object_; }
	void setObject(Type value) { object_ = value; }
	ObjectOfTree<Type>* getPreviousPointer() { return previous_pointer_; }
	void setPreviousPointer(ObjectOfTree<Type>* value) { previous_pointer_ = value; }
	ObjectOfTree<Type>* getNextPointer() { return next_pointer_; }
	ObjectOfTree<Type>** getNextPointer2() { return &next_pointer_; }
	void setNextPointer(ObjectOfTree<Type>* value) { next_pointer_ = value; }
};



#endif
