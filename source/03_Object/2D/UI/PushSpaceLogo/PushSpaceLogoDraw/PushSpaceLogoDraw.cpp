//================================================================================
//
//    �v�b�V���X�y�[�X���S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "PushSpaceLogoDraw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// �萔��`
//****************************************
const std::string PushSpaceLogoDraw::TEXTURE_NAME = "UI/PushSpace_Rogo.png";
const float PushSpaceLogoDraw::SCALE = 0.5f;



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void PushSpaceLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// �_�E���L���X�g
	push_space_logo_ = (PushSpaceLogo*)getpGameObject();

	// �e�N�X�`���̓o�^
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);
	
	// �g�k&�ړ�
	push_space_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth()  * SCALE;
	push_space_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * SCALE;
	push_space_logo_->GetTransform()->GetPosition()->y += -300.0f;
	push_space_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void PushSpaceLogoDraw::Uninit()
{
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void PushSpaceLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	push_space_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned PushSpaceLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return push_space_logo_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* PushSpaceLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	// ���b�V�����̎擾
	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* PushSpaceLogoDraw::getpMaterial(unsigned object_index, 
											  unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return push_space_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PushSpaceLogoDraw::getpDecaleTexture(unsigned object_index,
												   unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}