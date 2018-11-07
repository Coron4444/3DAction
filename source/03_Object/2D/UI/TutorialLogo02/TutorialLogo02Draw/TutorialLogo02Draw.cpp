//================================================================================
//
//    �`���[�g���A�����S02�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "TutorialLogo02Draw.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const std::string TutorialLogo02Draw::TEXTURE_NAME = "UI/Tutorial02.png";
const float TutorialLogo02Draw::SCALE = 1.25f;



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

void TutorialLogo02Draw::Init()
{
	// �X�e�[�g�̕ύX
	SetState(DrawComponent::State::FIXED_2D);

	// TutorialLogo02�Ƀ_�E���L���X�g
	title_logo_ = (TutorialLogo02*)GetGameObjectOrigin();

	// �e�N�X�`���̓o�^
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);
	
	// �g�k
	title_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth() * SCALE;
	title_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * (SCALE + 0.2f);

	// �s��X�V
	title_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo02Draw::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo02Draw::Draw(unsigned mesh_index)
{
	mesh_index = mesh_index;

	title_logo_->plane_polygon_->Draw();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���b�V�����擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned TutorialLogo02Draw::GetMeshNum()
{
	return title_logo_->plane_polygon_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �}�e���A���̎擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* TutorialLogo02Draw::GetMaterial(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return title_logo_->plane_polygon_->GetMaterial();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�J�[���e�N�X�`�������擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 TutorialLogo02Draw::GetDecaleTexture(unsigned mesh_index)
{
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}