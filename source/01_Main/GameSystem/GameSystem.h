//================================================================================
//
//    �Q�[���V�X�e���N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/08
//
//================================================================================

#ifndef	_GAME_SYSTEM_H_
#define _GAME_SYSTEM_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Windows.h>



//****************************************
// �N���X�錾
//****************************************
class SceneManager;



/*********************************************************//**
* @brief
* �Q�[���V�X�e���N���X
*
* �Q�[���V�X�e���S�̂��Ǘ�����
* Renderer�ASceneManager�AInput�ASound�ADebuger�����Ǘ�����
*************************************************************/
class GameSystem
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	SceneManager* scene_manager_ = nullptr;	//!< ���C���V�[���̊Ǘ���



//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	* @param
	* hInstance : �C���X�^���X�n���h��
	* hWnd : Windows�n���h��
	* is_full_screen : �t���X�N���[���t���O
	* window_width : Window��
	* window_height : Window����
	*/
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					 int window_width, int window_height);

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
	* �`��֐�
	*/
	void Draw();

	/**
	* @brief
	* ��X�V�֐�
	*/
	void LateUpdate();
};



#endif