//================================================================================
//
//    �R���|�[�l���g���N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/30
//
//================================================================================

#ifndef	_COMPONENT_BASE_H_
#define _COMPONENT_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Vector3D.h>
#include <Renderer\RendererDirectX9\RendererDirectX9.h>



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;



/*********************************************************//**
* @brief
* �R���|�[�l���g���N���X
*
* �R���|�[�l���g�̊��N���X
*************************************************************/
class ComponentBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	GameObjectBase* game_object_;		//!< �Q�[���I�u�W�F�N�g

//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~ComponentBase(){}

	/**
	* @brief
	* �������֐�
	*/
	virtual void Init()	  = 0;

	/**
	* @brief
	* �I���֐�
	*/
	virtual void Uninit() = 0;

	// �v���p�e�B
	void SetGameObject(GameObjectBase* value){game_object_ = value;}
	GameObjectBase* GetGameObject(){return game_object_;}
};



#endif