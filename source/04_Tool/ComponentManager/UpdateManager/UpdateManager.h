//================================================================================
//
//    �X�V�}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_UPDATE_MANAGER_H_
#define _UPDATE_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <LimitedPointerArray\LimitedPointerArray.h>


//****************************************
// �N���X�錾
//****************************************
class UpdateBase;
class GameObjectBase;



/*********************************************************//**
* @brief
* �X�V�}�l�[�W���[�N���X
*
* �o�^����Ă���X�V���N���X���Ǘ�����N���X
*************************************************************/
class UpdateManager
{
//==============================
// �萔
//==============================
public:
	static const unsigned ARRAY_NUM = 1000;		//!< �z��


//==============================
// �ÓI�����o�ϐ�
//==============================
private:
	static LimitedPointerArray<UpdateBase*, ARRAY_NUM> all_update_;		//!< �S�X�V�z��
	static LimitedPointerArray<UpdateBase*, ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	static LimitedPointerArray<UpdateBase*, ARRAY_NUM> await_release_;	//!< ����҂��z��


//==============================
// �ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	static void Init();

	/**
	* @brief
	* �I���֐�
	*/
	static void Uninit();

	/**
	* @brief
	* �V�[���ύX���̏I���֐�
	*/
	static void UninitWhenChangeScene();

	/**
	* @brief
	* �X�V�֐�
	*/
	static void Update();

	/**
	* @brief
	* �X�V���N���X�̒ǉ��֐�
	*/
	static void AddUpdateBaseToArray(UpdateBase* update);
	
	/**
	* @brief
	* �X�V���N���X�̏㏑���֐�
	*/
	static void OverwriteArrayUpdateBase(GameObjectBase* game_object, 
										 UpdateBase* new_update);
	
	/**
	* @brief
	* �X�V���N���X�̉���֐�
	*/
	static void ReleaseUpdateBaseFromArray(UpdateBase* update);

private:
	/**
	* @brief
	* �ǉ��҂��z��̒��g��ǉ��֐�
	*/
	static void AddContentsOfAwaitAddArray();

	/**
	* @brief
	* ����҂��z��̒��g������֐�
	*/
	static void ReleaseContentsOfAwaitReleaseArray();


//==============================
// ��ÓI�����o�֐�
//==============================
private :
	/**
	* @brief
	* �R���X�g���N�^(�폜)
	*/
	UpdateManager() = delete;

	/**
	* @brief
	* �R�s�[�R���X�g���N�^(�폜)
	*/
	UpdateManager(const UpdateManager& value) = delete;

	/**
	* @brief
	* ������Z�q�̃I�[�o�[���[�h(�폜)
	*/
	UpdateManager& operator = (const UpdateManager& value) = delete;
};



#endif
