//================================================================================
//
//    �R�C���`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "CoinDraw.h"



//****************************************
// �萔��`
//****************************************
const std::string CoinDraw::DECALE_TEXTURE = "Coin.png";
const std::string CoinDraw::EFFECT = "CoinEffect/CoinEffect.efk";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void CoinDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);
	GetDrawOrderList()->SetIsBillboard(true);

	// �_�E���L���X�g
	coin_ = (Coin*)GetGameObject();

	// �f�J�[���e�N�X�`���̓ǂݍ���
	decale_texture_ = TextureManager::AddUniqueData(&DECALE_TEXTURE);

	// �G�t�F�N�g�̓ǂݍ���
	//EffekseerManager::AddUniqueData(&EFFECT);
	//effekseer_object_ = EffekseerManager::GetReferenceEffekseerObject(&EFFECT);
	//effekseer_object_->SetColor(255, 0, 255, 255);
	//effekseer_object_->SetRepeat(true);
	//effekseer_object_->Play();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void CoinDraw::Uninit()
{
	//effekseer_object_->Stop();
	//effekseer_object_->SetRepeat(false);
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
	
	// �G�t�F�N�g���W�X�V
	//*effekseer_object_->GetTransform()->GetPosition() = *GetGameObject()->GetTransform()->GetPosition();
	//effekseer_object_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
const MATRIX* CoinDraw::GetMatrix(unsigned object_index)
{
	object_index = object_index;

	return coin_->GetTransform()->GetWorldMatrix();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned CoinDraw::GetMeshNum(unsigned object_index)
{
	object_index = object_index;

	return coin_->GetPolygon()->GetMeshNum();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* CoinDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return coin_->GetPolygon()->GetMaterial();
}



//--------------------------------------------------
// +�f�J�[���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CoinDraw::GetDecaleTexture(unsigned object_index, 
											  unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return decale_texture_->GetHandler();
}