//================================================================================
//
//    �v���C���[�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "StencilShadowTestDraw.h"

#include <main.h>

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const std::string StencilShadowTestDraw::MODEL_NAME   = "knight_low/knight_low.X";//"kyouryuu/kyouryuu.x";//"BlockSphere/BlockSphere.x";
const std::string StencilShadowTestDraw::TEXTURE_PATH = "resource/ModelX/";
const std::string StencilShadowTestDraw::NORMAL_TEXTURE_NAME01 = "knight_low/knight_01.png";
const std::string StencilShadowTestDraw::NORMAL_TEXTURE_NAME02 = "knight_low/sword_01.png";



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

void StencilShadowTestDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	GetDrawOrderList()->SetDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	GetDrawOrderList()->GetRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	GetDrawOrderList()->SetVertexShaderType(ShaderManager::VertexShaderType::VERTEX_FIXED);
	GetDrawOrderList()->SetPixelShaderType(ShaderManager::PixelShaderType::PIXEL_FIXED);

	// X���f���o�^
	player_model_ = ModelXManager::AddUniqueData(&MODEL_NAME);
	GetGameObject()->GetTransform()->GetPosition()->y += -1.0f;
	GetGameObject()->GetTransform()->UpdateWorldMatrixSRT();


	// �v���[���|���S���쐬
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->SetColor(XColor4(0.0f, 0.0f, 0.0f, 1.0f));
	temp_transform_.GetScale()->x = SCREEN_WIDTH;
	temp_transform_.GetScale()->y = SCREEN_HEIGHT;
	temp_transform_.UpdateWorldMatrixSRT();

	// �@���}�b�v�̃��[�h
	normal_texture_[0] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_NAME01, &TEXTURE_PATH);
	normal_texture_[1] = TextureManager::AddUniqueData(&NORMAL_TEXTURE_NAME02, &TEXTURE_PATH);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StencilShadowTestDraw::Uninit()
{
	// �e��J��
	SafeRelease::Normal(&plane_polygon_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StencilShadowTestDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	LPDIRECT3DDEVICE9 device;
	Renderer::GetInstance()->GetDevice(&device);
	if (object_index == 0)
	{
		device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		device->SetRenderState(D3DRS_STENCILREF, 1);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// ���݂̃��b�V���̕`��
		player_model_->GetMesh()->DrawSubset(mesh_index);
	}
	else if (object_index == 1)
	{
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		// ���݂̃��b�V���̕`��
		player_model_->GetMesh()->DrawSubset(mesh_index);
	}
	else
	{
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		
		// �|���S���`��
		plane_polygon_->Draw();
		
		device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �s��擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const MATRIX* StencilShadowTestDraw::GetMatrix(unsigned object_index)
{
	if (object_index == 2)
	{
		return temp_transform_.GetWorldMatrix();
	}
	
	// ���b�V�����̎擾
	return GetGameObject()->GetTransform()->GetWorldMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���b�V�����擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned StencilShadowTestDraw::GetMeshNum(unsigned object_index)
{
	if (object_index == 2) return 1;

	return player_model_->GetMeshNum();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �}�e���A���̎擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

D3DMATERIAL9* StencilShadowTestDraw::GetMaterial(unsigned object_index, unsigned mesh_index)
{
	if (object_index == 2) return nullptr;

	object_index = object_index;

	return player_model_->GetMaterial(mesh_index);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�J�[���e�N�X�`�������擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 StencilShadowTestDraw::GetDecaleTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	if (object_index == 2) return nullptr;

	return player_model_->GetDecaleTextureName(mesh_index)->GetHandler();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �m�[�}���e�N�X�`�������擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LPDIRECT3DTEXTURE9 StencilShadowTestDraw::GetNormalTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	if (object_index == 2) return nullptr;

	return normal_texture_[mesh_index]->GetHandler();
}