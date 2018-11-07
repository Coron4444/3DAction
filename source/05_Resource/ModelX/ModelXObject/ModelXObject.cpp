//================================================================================
//
//    X���f���I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2017/12/18
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "ModelXObject.h"

#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject::ModelXObject(const std::string* file_path, bool is_share_data)
{
	// �}�e���A���o�b�t�@
	LPD3DXBUFFER material_buffer = nullptr;
	
	// XModel�̓ǂݍ���
	InputModelX(file_path, &material_buffer);

	// �}�e���A�����̓ǂݍ���
	InputMaterial(file_path, &material_buffer, is_share_data);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ModelXObject::~ModelXObject()
{
	SafeRelease::PlusRelease(&mesh_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �}�e���A���̐F�ύX�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXObject::SetMaterialColor(unsigned index, XColor4 color)
{
	material_[index].Diffuse.r = color.r;
	material_[index].Diffuse.g = color.g;
	material_[index].Diffuse.b = color.b;
	material_[index].Diffuse.a = color.a;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���_���ύX�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ModelXObject::UpdateMeshDeclaration(const D3DVERTEXELEMENT9* DECLARATION)
{
	LPD3DXMESH temp_mesh;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(ModelXObject.cpp)", "Error", MB_OK);
		return;
	}

	mesh_->CloneMesh(mesh_->GetOptions(),
		             DECLARATION,
					 device,
		             &temp_mesh);

	SafeRelease::PlusRelease(&mesh_);

	mesh_ = temp_mesh;
}



//--------------------------------------------------------------------------------
//
// [ XModel�ǂݍ��݊֐� ]
//
//--------------------------------------------------------------------------------

void ModelXObject::InputModelX(const std::string* file_path, LPD3DXBUFFER* material_buffer)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(ModelXObject.cpp)", "Error", MB_OK);
		return;
	}

	HRESULT hr = D3DXLoadMeshFromX(file_path->c_str(),		// �t�@�C����
						           D3DXMESH_SYSTEMMEM,		// ��xCPU�ōœK���������̂�VRAM�ɓn��
						           device,					// �f�o�C�X
						           nullptr,					// �אڐ����
						           material_buffer,			// �}�e���A�����
						           NULL,					// �G�t�F�N�g�̏�����
						           &material_num_,			// �}�e���A����
						           &mesh_);					// ���b�V��

#ifdef _DEBUG
	assert(!FAILED(hr) && "ModelX�̓ǂݍ��݂Ɏ��s(ModelXObject.cpp)");
#else
	hr = hr;
#endif
}



//--------------------------------------------------------------------------------
//
// [ XModel��Material���ǂݍ��݊֐� ]
//
//--------------------------------------------------------------------------------

void ModelXObject::InputMaterial(const std::string* file_path, LPD3DXBUFFER* material_buffer, bool is_share_data)
{
	// �}�e���A���T�C�Y�ύX
	material_.resize(material_num_);

	// �}�e���A���̏����̃|�C���^�擾
	LPD3DXMATERIAL temp_material = (LPD3DXMATERIAL)(*material_buffer)->GetBufferPointer();

	// �}�e���A���ŕ��������p�[�c����
	for (DWORD i = 0; i < material_num_; i++)
	{
		ZeroMemory(&material_[i], sizeof(D3DMATERIAL9));

		// �f�q���[�Y�J���[�̐ݒ�
		material_[i].Diffuse.r = temp_material[i].MatD3D.Diffuse.r;
		material_[i].Diffuse.g = temp_material[i].MatD3D.Diffuse.g;
		material_[i].Diffuse.b = temp_material[i].MatD3D.Diffuse.b;
		material_[i].Diffuse.a = temp_material[i].MatD3D.Diffuse.a;

		// �A���r�G���g�J���[�̐ݒ�
		material_[i].Ambient.r = temp_material[i].MatD3D.Ambient.r;
		material_[i].Ambient.g = temp_material[i].MatD3D.Ambient.g;
		material_[i].Ambient.b = temp_material[i].MatD3D.Ambient.b;
		material_[i].Ambient.a = temp_material[i].MatD3D.Ambient.a;

		// �e�N�X�`���̓ǂݍ���
		if (temp_material[i].pTextureFilename == NULL) continue;
		std::string texture_key_name  = temp_material[i].pTextureFilename;
		std::string texture_file_path = *file_path;
		MakeTextureFilePathAndKeyName(&texture_key_name, &texture_file_path);
		
		TextureObject* texture_object = nullptr;

		if (is_share_data)
		{
			texture_object = TextureManager::AddShareData(&texture_key_name, &texture_file_path);
		}
		else
		{
			texture_object = TextureManager::AddUniqueData(&texture_key_name, &texture_file_path);
		}

		texture_object_array_.push_back(texture_object);
	}

	// �}�e���A���o�b�t�@�̉��
	SafeRelease::PlusRelease(material_buffer);
}



//--------------------------------------------------------------------------------
//
// [ �e�N�X�`���p�̃t�@�C���p�X&�L�[�l�[���̍쐬�֐� ]
//
//--------------------------------------------------------------------------------

void ModelXObject::MakeTextureFilePathAndKeyName(std::string* texture_key_name, std::string* texture_file_path)
{
	// �t�@�C���p�X����t�H���_����/�t���Ŏ擾
	auto slash_index = texture_file_path->rfind("/");
	auto slash_index2 = texture_file_path->rfind("/", slash_index - 1);
	unsigned temp_num = (unsigned)(slash_index - slash_index2);
	std::string temp_strign = texture_file_path->substr(slash_index2 + 1, temp_num);

	// �L�[�l�[���̍쐬
	*texture_key_name = temp_strign + *texture_key_name;

	// �t�@�C���p�X�̍쐬
	*texture_file_path = texture_file_path->substr(0, slash_index2 + 1);
}