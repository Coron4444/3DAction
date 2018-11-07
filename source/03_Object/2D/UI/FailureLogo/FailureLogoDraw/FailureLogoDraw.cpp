//================================================================================
//
//    ���s���S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "FailureLogoDraw.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const std::string FailureLogoDraw::TEXTURE_NAME = "UI/GameOver.png";

const float FailureLogoDraw::SCALE = 1.25f;



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

void FailureLogoDraw::Init()
{
	// �X�e�[�g�̕ύX
	SetState(DrawComponent::State::FIXED_2D);

	// FailureLogo�Ƀ_�E���L���X�g
	failure_logo_ = (FailureLogo*)GetGameObjectOrigin();

	// �e�N�X�`���̓o�^
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);

	// �g�k
	failure_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth() * SCALE;
	failure_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * (SCALE + 0.2f);

	// �ړ�
	*failure_logo_->GetTransform()->GetPosition() = Vec3(0.0f, 0.0f, 0.0f);
	
	failure_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FailureLogoDraw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FailureLogoDraw::Draw(unsigned mesh_index)
{
	mesh_index = mesh_index;

	failure_logo_->plane_polygon_->Draw();
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���b�V�����擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned FailureLogoDraw::GetMeshNum()
{
	return failure_logo_->plane_polygon_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �}�e���A���̎擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* FailureLogoDraw::GetMaterial(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return failure_logo_->plane_polygon_->GetMaterial();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�J�[���e�N�X�`�������擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 FailureLogoDraw::GetDecaleTexture(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}