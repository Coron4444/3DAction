//================================================================================
//
//    �N���A���S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "ClearLogoDraw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// �萔��`
//****************************************
const std::string ClearLogoDraw::TEXTURE_NAME = "UI/Clear.png";
const float ClearLogoDraw::SCALE = 1.25f;



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void ClearLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// �_�E���L���X�g
	clear_logo_ = (ClearLogo*)getpGameObject();

	// �e�N�X�`���̓o�^
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);

	// �g�k&�ړ�
	clear_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth() * SCALE;
	clear_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * (SCALE + 0.2f);
	*clear_logo_->GetTransform()->GetPosition() = Vec3(0.0f, 0.0f, 0.0f);
	clear_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void ClearLogoDraw::Uninit()
{
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void ClearLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	clear_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned ClearLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return clear_logo_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* ClearLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* ClearLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return clear_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 ClearLogoDraw::getpDecaleTexture(unsigned object_index,
													unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}