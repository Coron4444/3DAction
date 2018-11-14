//================================================================================
//
//    �G�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "EnemyDraw.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EnemyDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EnemyDraw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EnemyDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	
	// �G�Ƀ_�E���L���X�g
	Enemy* enemy = (Enemy*)GetGameObject();

	// �L���[�u�`��
	enemy->cube_polygon_->Draw();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �s��擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const MATRIX* EnemyDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	// ���b�V�����̎擾
	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���b�V�����擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned EnemyDraw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;

	// �G�Ƀ_�E���L���X�g
	Enemy* enemy = (Enemy*)GetGameObject();

	// ���b�V�����̎擾
	return enemy->cube_polygon_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �}�e���A���̎擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* EnemyDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// �G�Ƀ_�E���L���X�g
	Enemy* enemy = (Enemy*)GetGameObject();

	// ���b�V�����̎擾
	return enemy->cube_polygon_->GetMaterial();
}