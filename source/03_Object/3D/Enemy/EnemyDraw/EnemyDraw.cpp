//================================================================================
//
//    �G�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "EnemyDraw.h"



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void EnemyDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// �_�E���L���X�g
	enemy_ = (Enemy*)GetGameObject();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void EnemyDraw::Uninit()
{
	
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void EnemyDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	
	// �L���[�u�`��
	enemy_->cube_polygon_->Draw();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
const MATRIX* EnemyDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	return enemy_->GetTransform()->GetWorldMatrix();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned EnemyDraw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;

	return enemy_->cube_polygon_->GetMeshNum();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* EnemyDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return enemy_->cube_polygon_->GetMaterial();
}