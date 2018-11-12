//================================================================================
//
//    �X�V�}�l�[�W���[�N���X
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
// ��ÓI�����o�ϐ�
//==============================
private:
	LimitedPointerArray<UpdateBase*, ARRAY_NUM> all_update_;	//!< �S�X�V�z��
	LimitedPointerArray<UpdateBase*, ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	LimitedPointerArray<UpdateBase*, ARRAY_NUM> await_release_;	//!< ����҂��z��


//==============================
// ��ÓI�����o�֐�
//==============================
public:
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
	* �V�[���ύX���̏I���֐�
	*/
	void UninitWhenChangeScene();

	/**
	* @brief
	* �X�V�֐�
	*/
	void Update();

	/**
	* @brief
	* �X�V���N���X�̒ǉ��֐�
	*/
	void AddUpdateBaseToArray(UpdateBase* update);
	
	/**
	* @brief
	* �X�V���N���X�̏㏑���֐�
	*/
	void OverwriteArrayUpdateBase(GameObjectBase* game_object, 
										 UpdateBase* new_update);
	
	/**
	* @brief
	* �X�V���N���X�̉���֐�
	*/
	void ReleaseUpdateBaseFromArray(UpdateBase* update);

private:
	/**
	* @brief
	* �ǉ��҂��z��̒��g��ǉ��֐�
	*/
	void AddContentsOfAwaitAddArray();

	/**
	* @brief
	* ����҂��z��̒��g������֐�
	*/
	void ReleaseContentsOfAwaitReleaseArray();

};



#endif
