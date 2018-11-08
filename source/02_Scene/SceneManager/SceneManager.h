//================================================================================
//
//    �V�[���}�l�[�W���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2018/11/02
//
//================================================================================

#ifndef	_SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Vector3D.h>

#include <ComponentManager\UpdateComponentManager\UpdateComponentManager.h>
#include <ComponentManager\DrawComponentManager\DrawComponentManager.h>
#include <ComponentManager\CollisionComponentManager\CollisionComponentManager.h>



//****************************************
// �N���X�錾
//****************************************
class SceneBase;



/*********************************************************//**
* @brief
* �V�[���}�l�[�W���N���X
*
* �V�[���̊Ǘ�������N���X
*************************************************************/
class SceneManager
{
/***************************//**
* @brief
* �V�[���ԋ��ʃf�[�^�N���X
*
* �V�[���Ԃł̋��ʃf�[�^���Ǘ�����N���X
*******************************/
public:
	class CommonData
	{
	//==============================
	// ��ÓI�����o�ϐ�
	//==============================
	private:
		bool is_update_;		//!< �S�̂��X�V���邩�t���O
		bool is_clear_;			//!< �Q�[�����N���A�������t���O


	
	//==============================
	// ��ÓI�����o�֐�
	//==============================
	public:
		/**
		* @brief
		* ���Z�b�g�֐�
		*/
		void Reset()
		{
			is_update_ = false;
			is_clear_ = false;
		}

		// �v���p�e�B
		bool GetIsUpdate() { return is_update_; }
		void SetIsUpdate(bool value) { is_update_ = value; }
		bool GetIsClear() { return is_clear_; }
		void SetIsClear(bool value) { is_clear_ = value; }
	};



//==============================
// �񋓌^��`
//==============================
public:
	// �X�e�[�g
	enum State
	{
		NONE = -1,
		CHANGE_SCENE,
		RESET_SCENE,
		MAX
	};



//==============================
// �萔
//==============================
private:
	static const Fade::Type DEFAULT_FADE_TYPE;
	static const float      DEFAULT_FADE_SPEED;
	static const XColor4    DEFAULT_FADE_COLOR;



//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	State state_;					//!< �V�[���}�l�[�W���X�e�[�g
	CommonData* common_data_;		//!< �V�[���ԋ��ʃf�[�^

	SceneBase* current_scene_;		//!< ���݂̃V�[��
	SceneBase* next_scene_;			//!< ���̃V�[��

	Fade::Type fade_type_;			//!< �t�F�[�h�̎��
	float      fade_speed_;			//!< �t�F�[�h���x
	XColor4    fade_color_;			//!< �t�F�[�h�F



//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �R���X�g���N�^
	* @param
	* scene : �ŏ��̃V�[��
	*/
	SceneManager(SceneBase* scene);

	/**
	* @brief
	* �f�X�g���N�^
	*/
	~SceneManager();

	/**
	* @brief
	* �X�V�֐�
	*/
	void Update();

	/**
	* @brief
	* �V�[���̍X�V�֐�
	*/
	void UpdateScene();

	/**
	* @brief
	* �V�[���̕`��֐�
	*/
	void DrawScene();

	/**
	* @brief
	* �V�[���̃��Z�b�g�֐�
	*/
	void ResetScene();

	// �v���p�e�B
	void SetNextScene(SceneBase* value);
	CommonData* GetCommonData() { return common_data_; }
	void SetFadeType(Fade::Type value) { fade_type_ = value; }
	void SetFadeSpeed(float value) { fade_speed_ = value; }
	void SetFadeColor(XColor4 value) { fade_color_ = value; }

private:
	void SceneChange();
	void SceneReset();
};



#endif