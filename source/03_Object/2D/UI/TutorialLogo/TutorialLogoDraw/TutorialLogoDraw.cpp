//================================================================================
//
//    �`���[�g���A�����S01�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TutorialLogoDraw.h"

#include <main.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// �萔��`
//****************************************
const std::string TutorialLogoDraw::TEXTURE_NAME[TEXTURE_NUM] = {"UI/Tutorial01.png",
																 "UI/Tutorial02.png"};



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void TutorialLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
	GetDrawOrderList()->SetLayerNum(0);

	// �_�E���L���X�g
	tutorial_logo_ = (TutorialLogo*)GetGameObject();

	// ���ʃ|���S���쐬
	plane_polygon_ = new PlanePolygon();

	// �e�N�X�`���̓o�^
	for (unsigned i = 0; i < TEXTURE_NUM; i++)
	{
		decale_texture_[i] = TextureManager::AddUniqueData(&TEXTURE_NAME[i]);
	}

	// �g�k
	tutorial_logo_->GetTransform()->GetScale()->x = SCREEN_WIDTH;
	tutorial_logo_->GetTransform()->GetScale()->y = SCREEN_HEIGHT;
	tutorial_logo_->GetTransform()->UpdateWorldMatrixSRT();

	// �e�N�X�`���C���f�b�N�X
	texture_index_ = 0;
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void TutorialLogoDraw::Uninit()
{
	SafeRelease::Normal(&plane_polygon_);
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void TutorialLogoDraw::Update()
{
	// �e�N�X�`���ԍ��ύX
	texture_index_ = tutorial_logo_->GetLogoNum();
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void TutorialLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	plane_polygon_->Draw();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
const MATRIX* TutorialLogoDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	return tutorial_logo_->GetTransform()->GetWorldMatrix();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned TutorialLogoDraw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;

	return plane_polygon_->GetMeshNum();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* TutorialLogoDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 TutorialLogoDraw::GetDecaleTexture(unsigned object_index,
														unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_[texture_index_]->GetHandler();
}