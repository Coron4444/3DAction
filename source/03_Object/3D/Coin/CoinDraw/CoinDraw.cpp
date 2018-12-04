//================================================================================
//!	@file	 CoinDraw.cpp
//!	@brief	 �R�C���`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "CoinDraw.h"

#include <ResourceManager/ResourceManager.h>



//****************************************
// �萔��`
//****************************************
const std::string CoinDraw::DECALE_TEXTURE = "Coin.png";



//****************************************
// �֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void CoinDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	getpDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
	getpDrawOrderList()->SetIsBillboard(true);

	// �_�E���L���X�g
	coin_ = (Coin*)getpGameObject();

	// �f�J�[���e�N�X�`���̓ǂݍ���
	decale_texture_ = TextureManager::AddUniqueData(&DECALE_TEXTURE);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void CoinDraw::Uninit()
{
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void CoinDraw::Update()
{
	if (coin_->getCount() > 0)
	{
		coin_->GetPolygon()->SetColor(XColor4(1.0f, 0.0f, 0.0f, 1.0f));

		coin_->setCount(coin_->getCount() - 1);
	}
	else
	{
		coin_->GetPolygon()->SetColor(XColor4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void CoinDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// �|���S���`��
	coin_->GetPolygon()->Draw();
}



//--------------------------------------------------
// +�`��O�ݒ�֐�
//--------------------------------------------------
void CoinDraw::SettingBeforeDrawing(Camera* camera, unsigned object_index)
{
	camera = camera;
	object_index = object_index;
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned CoinDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return coin_->GetPolygon()->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* CoinDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return coin_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* CoinDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return coin_->GetPolygon()->GetMaterial();
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CoinDraw::getpDecaleTexture(unsigned object_index,
											   unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}