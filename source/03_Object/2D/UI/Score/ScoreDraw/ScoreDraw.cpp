//================================================================================
//
//    �X�R�A�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/20
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "ScoreDraw.h"



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void ScoreDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void ScoreDraw::Uninit()
{
	
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void ScoreDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* ScoreDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	// ���b�V�����̎擾
	return getpGameObject()->GetTransform()->getpWorldMatrix();
}