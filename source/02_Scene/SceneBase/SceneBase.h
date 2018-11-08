//================================================================================
//
//    �V�[�����N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/02
//
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



/*********************************************************//**
* @brief
* �V�[�����N���X
*
* �V�[���̊��N���X
*************************************************************/
class SceneBase
{
/***************************//**
* @brief
* �V�[���X�e�[�g���ۃN���X
*
* �V�[���X�e�[�g�̒��ۃN���X
*******************************/
public:
	class StateAbstract
	{
	//==============================
	// ��ÓI�����o�ϐ�
	//==============================
	protected:
		SceneBase* scene_ = nullptr;		//!< �V�[��


	//==============================
	// ��ÓI�����o�֐�
	//==============================
	public:
		/**
		* @brief
		* �f�X�g���N�^
		*/
		virtual ~StateAbstract() {}

		/**
		* @brief
		* �������֐�
		*/
		virtual void Init() = 0;

		/**
		* @brief
		* �I���֐�
		*/
		virtual void Uninit() = 0;

		/**
		* @brief
		* �X�V�֐�
		*/
		virtual void Update() = 0;

		/**
		* @brief
		* ���Z�b�g�֐�
		*/
		virtual void Reset() = 0;

		// �v���p�e�B
		void SetScene(SceneBase* value) { scene_ = value; }
	};



//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	SceneManager* scene_manager_ = nullptr;		//!< �V�[���}�l�[�W��
	StateAbstract* state_ = nullptr;			//!< �X�e�[�g



//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �R���X�g���N�^
	* @param
	* state : �ŏ��̃X�e�[�g
	*/
	SceneBase(StateAbstract* state)
	{
		state_ = state;
		state_->SetScene(this);
	}

	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~SceneBase() {}

	/**
	* @brief
	* �������֐�
	*/
	void Init();

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit();

	/**
	* @brief
	* �X�V�֐�
	*/
	void Update();

	/**
	* @brief
	* ���Z�b�g�֐�
	*/
	void Reset();

	/**
	* @brief
	* �X�e�[�g����֐�
	*/
	void ReleaseState();

	// �v���p�e�B
	SceneManager* GetSceneManager() { return scene_manager_; }
	void SetSceneManager(SceneManager* value) { scene_manager_ = value; }
	StateAbstract* GetState() { return state_; }
	void SetState(StateAbstract* value)
	{
		if (state_ != nullptr)
		{
			SafeRelease::PlusUninit(&state_);
		}

		state_ = value;

		if (state_ != nullptr)
		{
			state_->SetScene(this);
			state_->Init();
		}
	}
};



#endif