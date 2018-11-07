//================================================================================
//
//    �`��R���|�[�l���g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================

#ifndef	_DRAW_COMPONENT_H_
#define _DRAW_COMPONENT_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../ComponentOrigin/ComponentOrigin.h"

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



//======================================================================
//
// �N���X��`
//
//======================================================================

class DrawComponent : public ComponentOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �X�e�[�g
	enum State
	{
		NONE = -1,
		FIXED,
		FIXED_ALPHA,
		FIXED_BILLBOARD,
		FIXED_BILLBOARD_ALPHA,
		FIXED_2D,
		TEST_SHADER,
		TEST_SHADER_BILLBOARD,
		MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���z�f�X�g���N�^
	virtual ~DrawComponent(){}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	virtual void Draw(unsigned mesh_index) = 0;

	// �f�o�b�O
	virtual void Debug(){}

	virtual unsigned		   GetMeshNum()							{return 1;}
	virtual D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		{mesh_index = mesh_index; return nullptr;}
	virtual LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index){mesh_index = mesh_index; return nullptr;}
	virtual LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned mesh_index){mesh_index = mesh_index; return nullptr;}


	// ���
	DrawComponent::State GetState(){return state_;}
	void SetState(DrawComponent::State state){state_ = state;}


//------------------------------------------------------------
private :
	// �����o�ϐ�
	DrawComponent::State state_ = NONE;
};



#endif