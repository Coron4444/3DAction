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
#include "Camera\Camera.h"
#include "Camera\CameraState_CrawlUp\CameraState_CrawlUp.h"
#include "Camera\CameraState_HomingTarget\CameraState_HomingTarget.h"

#include "Fade\Fade.h"

#include <LimitedPointerArray\LimitedPointerArray.h>



//****************************************
// �N���X�錾
//****************************************
class DrawBase;
class GameObjectBase;



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
	static const unsigned CAMERA_ARRAY_NUM = 4;		//!< �J�����z��



//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_draw_;		//!< �S�`��z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_release_;	//!< ����҂��z��

	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_opacity_draw_;		//!< �s�����z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_transparent_draw_;	//!< �����z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_2D_draw_;			//!< 2D�z��

	LimitedPointerArray<Camera*, CAMERA_ARRAY_NUM> all_camera_;	//!< �J�����z��

	Fade* fade_;		//!< �t�F�[�h
	bool  is_fade_;	//!< �t�F�[�h���t���O


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

	/**
	* @brief
	* �f�t�H���g�J�����̍쐬�֐�
	*/
	void CreateDefaultCamera(Camera::State* camera_state = nullptr,
							 Camera::Type camra_type = Camera::Type::NORMAL);

	/**
	* @brief
	* �J�����̒ǉ��֐�
	*/
	void AddCamera(Camera::State* camera_state = nullptr,
				   Camera::Type camra_type = Camera::Type::NORMAL);

	/**
	* @brief
	* �J�����̉���֐�
	*/
	void ReleaseCamera(unsigned index);

	/**
	* @brief
	* �J�����̃X�e�[�g�ύX�֐�
	*/
	void ChangeCameraState(unsigned index, Camera::State* camera_state);

	/**
	* @brief
	* �t�F�[�h�������֐�
	*/
	void InitFade(Fade::Type type, Fade::State state, Vec2 size, XColor4 fade_color,
				  float fade_speed);

	/**
	* @brief
	* �t�F�[�h�I���֐�
	*/
	void UninitFade();

	/**
	* @brief
	* �t�F�[�h�I�����̊m�F�֐�
	*/
	bool IsFadeEnd() { return fade_->GetEndFlag(); }

	/**
	* @brief
	* �t�F�[�h�X�e�[�g�̖��O����֐�
	*/
	bool IsFadeStateName(Fade::State state) { return *fade_->GetState() == state; }

	// �v���p�e�B
	Camera* GetCamera(unsigned index) { return all_camera_.GetArrayObject(index); }

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
	* �X�V�֐�
	*/
	void Update(unsigned index);

	/**
	* @brief
	* �`��R���|�[�l���g�z��̃��Z�b�g�֐�
	*/
	void ResetDrawComponentArray();

	/**
	* @brief
	* �`��R���|�[�l���g�U�蕪���֐�
	*/
	void DistributeDrawComponent(unsigned index);

	/**
	* @brief
	* �����`��R���|�[�l���g�̃\�[�g�֐�
	*/
	void SortTransparent(unsigned index);

	/**
	* @brief
	* �r���{�[�h�p�s��ύX�֐�
	*/
	void SetBillboardMatrix(DrawBase* draw, unsigned index);

	/**
	* @brief
	* �e�p�C�v���C���`��֐�
	*/
	void DrawEachPipeline(LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM>* draw,
						  unsigned index);

	/**
	* @brief
	* �m�[�}���J�����p�C�v���C���֐�
	*/
	void NormalCameraPipeline(unsigned index);

	/**
	* @brief
	* �t�F�[�h�̍X�V�y�ѕ`��֐�
	*/
	void FadeUpdate_Draw();
};



#endif
