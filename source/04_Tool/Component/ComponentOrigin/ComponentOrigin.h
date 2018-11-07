//================================================================================
//
//    �R���|�[�l���g�̌��_�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/30
//
//================================================================================

#ifndef	_COMPONENT_ORIGIN_H_
#define _COMPONENT_ORIGIN_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <Vector3D.h>
#include <Renderer\RendererDirectX9\RendererDirectX9.h>



//======================================================================
//
// �N���X�錾
//
//======================================================================

class GameObjectOrigin;



//======================================================================
//
// �N���X��`
//
//======================================================================

class ComponentOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���z�f�X�g���N�^
	virtual ~ComponentOrigin(){}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	virtual void Init()	  = 0;
	virtual void Uninit() = 0;

	// �A�N�Z�b�T
	void SetGameObjectOrigin(GameObjectOrigin* game_object_origin){game_object_origin_ = game_object_origin;}
	GameObjectOrigin* GetGameObjectOrigin(){return game_object_origin_;}


//------------------------------------------------------------
private :
	// �����o�ϐ�
	GameObjectOrigin* game_object_origin_;
};



#endif