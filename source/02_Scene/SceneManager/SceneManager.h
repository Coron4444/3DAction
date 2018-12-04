//================================================================================
//!	@file	 SceneManager.h
//!	@brief	 �V�[���}�l�[�W��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameObjectManager\GameObjectManager.h>

#include <Vector3D.h>



//****************************************
// �N���X�錾
//****************************************
class SceneBase;



//************************************************************														   
//! @brief   �V�[���}�l�[�W��Class
//!
//! @details �V�[���̃}�l�[�W��Class
//************************************************************
class SceneManager
{
//****************************************														   
//! @brief   �V�[���ԋ��ʃf�[�^Class
//!
//! @details �V�[���Ԃ̋��ʃf�[�^Class
//****************************************
public:
	class CommonData
	{
	//====================
	// �ϐ�
	//====================
	private:
		bool is_update_;		//!< �S�̂��X�V���邩�t���O
		bool is_clear_;			//!< �Q�[�����N���A�������t���O


	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief ���Z�b�g�֐�
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		void Reset()
		{
			is_update_ = false;
			is_clear_ = false;
		}

		// �v���p�e�B
		bool getIsUpdate() { return is_update_; }
		void setIsUpdate(bool value) { is_update_ = value; }
		bool getIsClear() { return is_clear_; }
		void setIsClear(bool value) { is_clear_ = value; }
	};


//====================
// �񋓌^��`
//====================
public:
	// �X�e�[�g
	enum State
	{
		NONE = -1,
		CHANGE_SCENE,
		RESET_SCENE,
		MAX
	};


//====================
// �萔
//====================
private:
	static const Fade::Type DEFAULT_FADE_TYPE;		//!< �����t�F�[�h�^�C�v
	static const float      DEFAULT_FADE_SPEED;		//!< �����t�F�[�h���x
	static const XColor4    DEFAULT_FADE_COLOR;		//!< �����t�F�[�h�F


//====================
// �ϐ�
//====================
private:
	State state_ = State::NONE;				//!< �V�[���}�l�[�W���X�e�[�g
	CommonData* common_data_ = nullptr;		//!< �V�[���ԋ��ʃf�[�^

	SceneBase* current_scene_ = nullptr;	//!< ���݂̃V�[��
	SceneBase* next_scene_ = nullptr;		//!< ���̃V�[��

	Fade::Type fade_type_ = DEFAULT_FADE_TYPE;		//!< �t�F�[�h�̎��
	float fade_speed_ = DEFAULT_FADE_SPEED;			//!< �t�F�[�h���x
	XColor4 fade_color_ = DEFAULT_FADE_COLOR;		//!< �t�F�[�h�F


//====================
// ��ÓI�����o�֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @param[in] scene �ŏ��̃V�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(SceneBase* scene);

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
	//! @brief �V�[���X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateScene();

	//----------------------------------------
	//! @brief �V�[���`��֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawScene();

	//----------------------------------------
	//! @brief �V�[�����Z�b�g�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetScene();

	// �v���p�e�B
	void setNextScene(SceneBase* value);
	CommonData* getpCommonData() { return common_data_; }
	void setFadeType(Fade::Type value) { fade_type_ = value; }
	void setFadeSpeed(float value) { fade_speed_ = value; }
	void setFadeColor(XColor4 value) { fade_color_ = value; }

private:
	//----------------------------------------
	//! @brief �V�[���ύX�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SceneChange();

	//----------------------------------------
	//! @brief �V�[�����Z�b�g�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SceneReset();
};



#endif