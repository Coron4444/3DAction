//================================================================================
//
//    �`��R���|�[�l���g�}�l�[�W���[�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_DRAW_COMPONENT_MANAGER_H_
#define _DRAW_COMPONENT_MANAGER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <LimitedPointerArray\LimitedPointerArray.h>

#include "Camera\Camera.h"
#include "Camera\CameraState_CrawlUp\CameraState_CrawlUp.h"
#include "Camera\CameraState_HomingTarget\CameraState_HomingTarget.h"

#include "Fade\Fade.h"



//======================================================================
//
// �N���X�錾
//
//======================================================================

class DrawComponent;
class GameObjectOrigin;



//======================================================================
//
// �N���X��`
//
//======================================================================

class DrawComponentManager
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �萔
	static const unsigned DRAW_ARRAY_NUM   = 1000;
	static const unsigned CAMERA_ARRAY_NUM = 4;


//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	DrawComponentManager() = delete;

	// �R�s�[�R���X�g���N�^
	DrawComponentManager(const DrawComponentManager& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	DrawComponentManager& operator = (const DrawComponentManager& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���C��
	static void Init();
	static void Uninit();
	static void Uninit_ChangeScene();
	static void Draw();

	// �R���|�[�l���g
	static void RegistrationComponent(DrawComponent* draw_component);
	static void OverwriteComponent	 (GameObjectOrigin* game_object, DrawComponent* new_draw_component);
	static void ReleaseComponent	 (DrawComponent* draw_component);


	// �J����
	static void CreateDefaultCamera(Camera::State* camera_state = nullptr, Camera::Type camra_type = Camera::Type::NORMAL);
	static void AddCamera		   (Camera::State* camera_state = nullptr, Camera::Type camra_type = Camera::Type::NORMAL);
	static void DeleteCamera	   (unsigned index);
	static void ChangeCameraState  (unsigned index, Camera::State* camera_state);
	
	static Camera* GetCamera(unsigned index){return all_camera_.GetArrayObject(index);}


	// �t�F�[�h
	static void InitFade(Fade::Type type, Fade::State state, Vec2 size, XColor4 fade_color, float fade_speed);
	static void UninitFade();
	
	static bool IsFadeEnd()						  {return fade_->GetEndFlag();}
	static bool IsFadeStateName(Fade::State state){return *fade_->GetState() == state;}


//------------------------------------------------------------
private :
	// ���C��
	static void Update(unsigned index);
	static void ResetDrawComponentArray();
	static void DistributeDrawComponent(unsigned index);
	static void SortTransparent		   (unsigned index);
	static void SetBillboardMatrix     (DrawComponent* draw_component, unsigned index);
	static void DrawEachPipeline	   (LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM>* draw_components, unsigned index);

	// �J����
	static void NormalCameraPipeline(unsigned index);

	// �t�F�[�h
	static void FadeUpdate_Draw();


//------------------------------------------------------------
private :
	// �R���|�[�l���g
	static LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM> all_draw_component_;
	static LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM> all_opacity_draw_component_;
	static LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM> all_transparent_draw_component_;
	static LimitedPointerArray<DrawComponent*, DRAW_ARRAY_NUM> all_2D_draw_component_;

	// �J����
	static LimitedPointerArray<Camera*, CAMERA_ARRAY_NUM> all_camera_;

	// �t�F�[�h
	static Fade* fade_;
	static bool  is_fade_;
};



#endif
