//================================================================================
//!	@file	 ComponentBase.h
//!	@brief	 �R���|�[�l���gBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COMPONENT_BASE_H_
#define _COMPONENT_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#ifdef _DEBUG
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_dx9.h>
#endif



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   �R���|�[�l���gBaseClass
//!
//! @details �R���|�[�l���g��BaseClass
//************************************************************
class ComponentBase
{
//====================
// �ϐ�
//====================
private:
	GameObjectBase* game_object_;		//!< �Q�[���I�u�W�F�N�g


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~ComponentBase() {}

	//----------------------------------------
	//! @brief �������֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Init() = 0;

	//----------------------------------------
	//! @brief �I���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Update() = 0;

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DebugDisplay() = 0;

	// �v���p�e�B
	GameObjectBase* getpGameObject() { return game_object_; }
	void setGameObject(GameObjectBase* value) { game_object_ = value; }
};



#endif