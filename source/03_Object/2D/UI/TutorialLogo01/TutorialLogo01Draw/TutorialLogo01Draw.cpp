//================================================================================
//
//    �`���[�g���A�����S01�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TutorialLogo01Draw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// �萔��`
//****************************************
const std::string TutorialLogo01Draw::TEXTURE_NAME = "UI/Tutorial01.png";
const float TutorialLogo01Draw::SCALE = 1.25f;



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void TutorialLogo01Draw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// �_�E���L���X�g
	tutorial_logo_ = (TutorialLogo01*)GetGameObject();

	// �e�N�X�`���̓o�^
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);

	// �g�k
	tutorial_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth() * SCALE;
	tutorial_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * (SCALE + 0.2f);
	tutorial_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void TutorialLogo01Draw::Uninit()
{
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void TutorialLogo01Draw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	tutorial_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
const MATRIX* TutorialLogo01Draw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	// ���b�V�����̎擾
	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned TutorialLogo01Draw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;

	return tutorial_logo_->plane_polygon_->GetMeshNum();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* TutorialLogo01Draw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return tutorial_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 TutorialLogo01Draw::GetDecaleTexture(unsigned object_index,
														unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}