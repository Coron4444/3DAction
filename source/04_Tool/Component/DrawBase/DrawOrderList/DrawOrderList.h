//================================================================================
//
//    �`�撍�����X�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================

#ifndef	_DRAW_ORDER_LIST_H_
#define _DRAW_ORDER_LIST_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <ComponentManager/DrawManager/ShaderManager/ShaderManager.h>
#include <Flag/Flag.h>




/*********************************************************//**
* @brief
* �`�撍�����X�g�N���X
*
* �`��Ɋւ��钍�����X�g�N���X
*************************************************************/
class DrawOrderList
{
//==============================
// �萔��`
//==============================
public:
	static const unsigned RENDER_TARGET_BACK_BUFFER = 1 << 0;


//==============================
// �񋓌^��`
//==============================
public:
	// �`��^�C�v
	enum DrawType
	{
		NONE = -1,
		OPACITY,
		TRANSPARENCY,
		TWO_DIMENSIONAL,
		MAX
	};


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	ShaderManager::VertexShaderType vertex_shader_type_ = ShaderManager::VertexShaderType::VERTEX_FIXED;	//!< ���_�V�F�[�_�[�̎��
	ShaderManager::PixelShaderType pixel_shader_type_ = ShaderManager::PixelShaderType::PIXEL_FIXED;		//!< �s�N�Z���V�F�[�_�[�̎��

	DrawType draw_type_ = DrawType::OPACITY;	//!< �`��̎��

	Flag render_target_flag_;			//!< �����_�[�^�[�Q�b�g�t���O
	bool is_billboard_ = false;			//!< �r���{�[�h���t���O
	int sort_2D_layer_num_ = 0;			//!< �\�[�g�p2D���C���[��


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	// �v���p�e�B
	ShaderManager::VertexShaderType GetVertexShaderType() { return vertex_shader_type_; }
	void SetVertexShaderType(ShaderManager::VertexShaderType value) { vertex_shader_type_ = value; }
	ShaderManager::PixelShaderType GetPixelShaderType() { return pixel_shader_type_; }
	void SetPixelShaderType(ShaderManager::PixelShaderType value) { pixel_shader_type_ = value; }
	DrawType GetDrawType() { return draw_type_; }
	void SetDrawType(DrawType value) { draw_type_ = value; }
	Flag* GetRenderTargetFlag() { return &render_target_flag_; }
	bool GetIsBillboard() { return is_billboard_; }
	void SetIsBillboard(bool value) { is_billboard_ = value; }
	int GetSort2DLayerNum() { return sort_2D_layer_num_; }
	void SetSort2DLayerNum(int value) { sort_2D_layer_num_ = value; }
};



#endif