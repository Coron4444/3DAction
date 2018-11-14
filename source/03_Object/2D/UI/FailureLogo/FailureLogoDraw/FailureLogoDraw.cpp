//================================================================================
//
//    ���s���S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "FailureLogoDraw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// �萔��`
//****************************************
const std::string FailureLogoDraw::TEXTURE_NAME = "UI/GameOver.png";

const float FailureLogoDraw::SCALE = 1.25f;



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void FailureLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);


	// �_�E���L���X�g
	failure_logo_ = (FailureLogo*)GetGameObject();

	// �e�N�X�`���̓o�^
	decale_texture_ = TextureManager::AddUniqueData(&TEXTURE_NAME);

	// �g�k&�ړ�
	failure_logo_->GetTransform()->GetScale()->x = decale_texture_->GetWidth() * SCALE;
	failure_logo_->GetTransform()->GetScale()->y = decale_texture_->GetHeight() * (SCALE + 0.2f);
	*failure_logo_->GetTransform()->GetPosition() = Vec3(0.0f, 0.0f, 0.0f);
	failure_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void FailureLogoDraw::Uninit()
{	
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void FailureLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	failure_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
const MATRIX* FailureLogoDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	// ���b�V�����̎擾
	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned FailureLogoDraw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;

	return failure_logo_->plane_polygon_->GetMeshNum();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* FailureLogoDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return failure_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 FailureLogoDraw::GetDecaleTexture(unsigned object_index, 
													 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}