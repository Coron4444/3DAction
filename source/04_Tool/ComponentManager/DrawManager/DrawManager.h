//================================================================================
//
//    �`��}�l�[�W���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_DRAW_MANAGER_H_
#define _DRAW_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "RenderTarget/BackBuffer/BackBuffer.h"

#include <LimitedPointerArray\LimitedPointerArray.h>



//****************************************
// �N���X�錾
//****************************************
class DrawBase;
class GameObjectBase;
class BackBuffer;
class ShaderManager;


/*********************************************************//**
* @brief
* �`��}�l�[�W���[�N���X
*
* �o�^����Ă���`����N���X���Ǘ�����N���X
*************************************************************/
class DrawManager
{
//==============================
// �萔
//==============================
public:
	static const unsigned DRAW_ARRAY_NUM = 1000;	//!< �`��z��


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_draw_;		//!< �S�`��z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_release_;	//!< ����҂��z��

	ShaderManager* shader_manager_ = nullptr;	//!< �V�F�[�_�[�}�l�[�W��
	BackBuffer* back_buffer_ = nullptr;			//!< �o�b�N�o�b�t�@

	Vec3 directional_light_vector_ = {0.5f, -1.0f, 0.8f};		//!< �g�U���ˌ��x�N�g��


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
	* �`��֐�
	*/
	void Draw();

	/**
	* @brief
	* �`����N���X�̒ǉ��֐�
	*/
	void AddDrawBaseToArray(DrawBase* draw);

	/**
	* @brief
	* �`����N���X�̏㏑���֐�
	*/
	void OverwriteArrayDrawBase(GameObjectBase* game_object,
								DrawBase* new_draw);

	/**
	* @brief
	* �`����N���X�̉���֐�
	*/
	void ReleaseDrawBaseFromArray(DrawBase* draw);

	// �v���p�e�B
	const Vec3* GetDirectionalLightVector() { return &directional_light_vector_; }
	void SetDirectionalLightVector(Vec3 value) { directional_light_vector_ = value; }
	BackBuffer* GetBackBuffer() { return back_buffer_; }


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

	/**
	* @brief
	* �S�����_�[�^�[�Q�b�g�X�V�֐�
	*/
	void UpdateAllRenderTarget();

	/**
	* @brief
	* �S�����_�[�^�[�Q�b�g���Z�b�g�֐�
	*/
	void ResetAllRenderTarget();

	/**
	* @brief
	* �`����N���X�U�蕪���֐�
	*/
	void DistributeDrawBase();
};



#endif
