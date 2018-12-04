//================================================================================
//!	@file	 SceneBase.h
//!	@brief	 �V�[��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_SCENE_BASE_H_
#define _SCENE_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <SafeRelease/SafeRelease.h>



//****************************************
// �N���X�錾
//****************************************
class SceneManager;



//************************************************************														   
//! @brief   �V�[��BaseClass
//!
//! @details �V�[����BaseClass
//************************************************************
class SceneBase
{
//****************************************														   
//! @brief   �V�[���X�e�[�gBaseClass
//!
//! @details �V�[���X�e�[�g��BaseClass
//****************************************
public:
	class StateBase
	{
	//====================
	// �ϐ�
	//====================
	protected:
		SceneBase* scene_ = nullptr;		//!< �V�[��


	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief ���z�f�X�g���N�^
		//! @param void �Ȃ�
		//----------------------------------------
		virtual ~StateBase() {}

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
		//! @brief ���Z�b�g�֐�
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		virtual void Reset() = 0;

		// �v���p�e�B
		void setScene(SceneBase* value) { scene_ = value; }
	};


//====================
// �ϐ�
//====================
private:
	SceneManager* scene_manager_ = nullptr;		//!< �V�[���}�l�[�W��
	StateBase* state_ = nullptr;				//!< �X�e�[�g


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param[in] state �ŏ��̃X�e�[�g
	//----------------------------------------
	SceneBase(StateBase* state) 
	{
		state_ = state;
		state_->setScene(this);
	}

	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~SceneBase() {}

	//----------------------------------------
	//! @brief �������֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief �I���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Reset();

	//----------------------------------------
	//! @brief �X�e�[�g����֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseState();

	// �v���p�e�B
	SceneManager* getpSceneManager() { return scene_manager_; }
	void setSceneManager(SceneManager* value) { scene_manager_ = value; }
	StateBase* getpState() { return state_; }
	void setState(StateBase* value)
	{
		if (state_ != nullptr)
		{
			SafeRelease::PlusUninit(&state_);
		}

		state_ = value;

		if (state_ != nullptr)
		{
			state_->setScene(this);
			state_->Init();
		}
	}
};



#endif