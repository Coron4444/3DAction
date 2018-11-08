//================================================================================
//
//    �`����N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================

#ifndef	_DRAW_BASE_H_
#define _DRAW_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../ComponentBase/ComponentBase.h"

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



/*********************************************************//**
* @brief
* �`����N���X
*
* �`��̊��N���X
*************************************************************/
class DrawComponent : public ComponentBase
{
//==============================
// �񋓌^��`
//==============================
public:
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


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	DrawComponent::State state_ = NONE;		//!< �X�e�[�g


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~DrawComponent() {}

	/**
	* @brief
	* �`��֐�
	*/
	virtual void Draw(unsigned mesh_index) = 0;

	/**
	* @brief
	* �f�o�b�O�\���֐�
	*/
	virtual void Debug() {}

	// �v���p�e�B
	virtual unsigned GetMeshNum() { return 1; }
	virtual D3DMATERIAL9* GetMaterial(unsigned mesh_index) { mesh_index = mesh_index; return nullptr; }
	virtual LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index) { mesh_index = mesh_index; return nullptr; }
	virtual LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned mesh_index) { mesh_index = mesh_index; return nullptr; }
	DrawComponent::State GetState() { return state_; }
	void SetState(DrawComponent::State state) { state_ = state; }
};



#endif