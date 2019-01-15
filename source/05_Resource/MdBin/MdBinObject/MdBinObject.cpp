//================================================================================
//!	@file	 MdBinObject.cpp
//!	@brief	 �o�C�i���[���f���I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "MdBinObject.h"
#include "../MdBinDataContainer/MdBinDataContainer.h"
#include "../MdbinManager/MdBinManager.h"

#include <Vector3D.h>
#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <SafeRelease/SafeRelease.h>
#include <Texture\TextureManager\TextureManager.h>



//****************************************
// �v���p�e�B��`
//****************************************
int MdBinObject::Mesh::getVertexArraySize()
{
	return vertex_.size();
}



void MdBinObject::Mesh::setVertexArraySize(int value)
{
	vertex_.resize(value);
}



MdBinObject::Vertex* MdBinObject::Mesh::getpVertex(int index)
{
	return &vertex_[index];
}



int MdBinObject::Mesh::getIndexArraySize()
{
	return index_.size();
}



void MdBinObject::Mesh::setIndexArraySize(int value)
{
	index_.resize(value);
}



WORD* MdBinObject::Mesh::getpIndex(int index)
{
	return &index_[index];
}



int MdBinObject::Mesh::getMaterialIndex()
{
	return material_index_;
}



void MdBinObject::Mesh::setMaterialIndex(int value)
{
	material_index_ = value;
}



int MdBinObject::Mesh::getPrimitiveNum()
{
	return primitive_num_;
}



void MdBinObject::Mesh::setPrimitiveNum(int value)
{
	primitive_num_ = value;
}



TextureObject* MdBinObject::Mesh::getpDiffuseTextureObject()
{
	return diffuse_texture_object_;
}



void MdBinObject::Mesh::setDiffuseTextureObject(TextureObject* value)
{
	diffuse_texture_object_ = value;
}



LPDIRECT3DVERTEXBUFFER9 MdBinObject::Mesh::getpVertexBuffer()
{
	return vertex_buffer_;
}



LPDIRECT3DVERTEXBUFFER9* MdBinObject::Mesh::getp2VertexBuffer()
{
	return &vertex_buffer_;
}



LPDIRECT3DINDEXBUFFER9 MdBinObject::Mesh::getpIndexBuffer()
{
	return index_buffer_;
}



LPDIRECT3DINDEXBUFFER9* MdBinObject::Mesh::getp2IndexBuffer()
{
	return &index_buffer_;
}



unsigned MdBinObject::getMeshNum()
{
	return mesh_.size();
}



D3DMATERIAL9* MdBinObject::getpMaterial(unsigned mesh_index)
{
	return &material_[mesh_[mesh_index].getMaterialIndex()];
}



TextureObject* MdBinObject::getpDiffuseTextureObject(unsigned mesh_index)
{
	return mesh_[mesh_index].getpDiffuseTextureObject();
}



LPDIRECT3DTEXTURE9 MdBinObject::getpDiffuseTextureHandler(unsigned mesh_index)
{
	if (mesh_[mesh_index].getpDiffuseTextureObject() == nullptr) return nullptr;
	return mesh_[mesh_index].getpDiffuseTextureObject()->getpHandler();
}



//****************************************
// �֐���`
//****************************************
void MdBinObject::Mesh::Uninit()
{
	SafeRelease::PlusRelease(&vertex_buffer_);
	SafeRelease::PlusRelease(&index_buffer_);
	SafeRelease::PlusRelease(&diffuse_texture_object_);
}



void MdBinObject::Init(std::string* file_path, const std::string* map_key_name)
{
	// �o�C�i���[���f���f�[�^�̓ǂݍ���
	MdBinDataContainer md_bin_data;
	if (!MdBinDataContainer::InportData(&md_bin_data, *file_path))
	{
		MessageBox(NULL, "�o�C�i���[���f�����C���|�[�g�o���܂���ł����B", "Error", MB_OK);
		return;
	}

	// �}�e���A������
	CreateMaterial(&md_bin_data);

	// ���b�V������
	CreateMesh(file_path, &md_bin_data);

	// �L�[���ۑ�
	map_key_name_ = *map_key_name;
}



void MdBinObject::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	for (auto& contents : mesh_)
	{
		contents.Uninit();
	}

	MdBinManager::getpInstance()->ReleaseFromTheMap(&map_key_name_);
	delete this;
}



void MdBinObject::ForcedRelease()
{
	reference_counter_ = 0;
	Release();
}



void MdBinObject::AddReferenceCounter()
{
	reference_counter_++;
}



void MdBinObject::Draw(unsigned mesh_index)
{
	// ���_�錾�Z�b�g
	device_->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// ���_�o�b�t�@�Z�b�g
	device_->SetStreamSource(0,										// �p�C�v���C���ԍ�
							 mesh_[mesh_index].getpVertexBuffer(),	// �o�[�e�b�N�X�o�b�t�@�ϐ���
							 0,										// �ǂ����痬�����ނ�
							 sizeof(MdBinObject::Vertex));			// �X�g���C�h�l(�ׂ̒��_�܂ł̒�����1���_�̑傫��)

	// �`��
	device_->DrawPrimitive(D3DPT_TRIANGLELIST,
						  0,
						   mesh_[mesh_index].getPrimitiveNum());

	/*
	// �C���f�b�N�X�ł̕\��(FBX�̍œK�����Ŏ������邩���߂�)
	device_->SetIndices(mesh_[mesh_index].getpIndexBuffer());
	device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
								  0,											// �Z�b�g�X�g���[������ǂꂭ�炢����Ă��邩
								  0,											// �C���f�b�N�X�ň�ԏ������l
								  (UINT)mesh_[mesh_index].getVertexArraySize(),	// ���_��
								  0,											// �X�^�[�g�C���f�b�N�X�ԍ�
								  mesh_[mesh_index].getPrimitiveNum());			// �v���~�e�B�u��

	*/
}



void MdBinObject::CreateMaterial(MdBinDataContainer* md_bin_data)
{
	// �}�e���A�����擾
	int material_num = md_bin_data->getMaterialArraySize();
	material_.resize(material_num);

	// �}�e���A�����Ƃ̏���
	for (int i = 0; i < material_num; i++)
	{
		// �����x
		float alpha = *md_bin_data->getpMaterial(i)->getpTransparent();

		// �A���r�G���g
		material_[i].Ambient.r = *md_bin_data->getpMaterial(i)->getpAmbient()->getpR();
		material_[i].Ambient.g = *md_bin_data->getpMaterial(i)->getpAmbient()->getpG();
		material_[i].Ambient.b = *md_bin_data->getpMaterial(i)->getpAmbient()->getpB();
		material_[i].Ambient.a = alpha;

		// �f�B�q���[�Y
		material_[i].Diffuse.r = *md_bin_data->getpMaterial(i)->getpDiffuse()->getpR();
		material_[i].Diffuse.g = *md_bin_data->getpMaterial(i)->getpDiffuse()->getpG();
		material_[i].Diffuse.b = *md_bin_data->getpMaterial(i)->getpDiffuse()->getpB();
		material_[i].Diffuse.a = alpha;

		// �G�~�b�V�u
		material_[i].Emissive.r = *md_bin_data->getpMaterial(i)->getpEmissive()->getpR();
		material_[i].Emissive.g = *md_bin_data->getpMaterial(i)->getpEmissive()->getpG();
		material_[i].Emissive.b = *md_bin_data->getpMaterial(i)->getpEmissive()->getpB();
		material_[i].Emissive.a = alpha;

		// �X�y�L����&�X�y�L�����p���[
		material_[i].Specular.r = *md_bin_data->getpMaterial(i)->getpSpecular()->getpR();
		material_[i].Specular.g = *md_bin_data->getpMaterial(i)->getpSpecular()->getpG();
		material_[i].Specular.b = *md_bin_data->getpMaterial(i)->getpSpecular()->getpB();
		material_[i].Specular.a = alpha;
		material_[i].Power = *md_bin_data->getpMaterial(i)->getpPower();
	}
}



void MdBinObject::CreateMesh(std::string* file_path, MdBinDataContainer* md_bin_data)
{
	// ���b�V�����擾
	int mesh_num = md_bin_data->getMeshArraySize();
	mesh_.resize(mesh_num);

	// ���b�V�����Ƃ̏���
	for (int i = 0; i < mesh_num; i++)
	{
		// �}�e���A���C���f�b�N�X����
		CreateMaterialIndex(i, md_bin_data);

		// �C���f�b�N�X����
		CreateIndex(i, md_bin_data);

		// ���_����
		CreateVertex(i, md_bin_data);

		// �f�B�q���[�Y�e�N�X�`������
		CreateDiffuseTexture(i, file_path, md_bin_data);

		// �o�b�t�@����
		CreateBuffer(i);
	}
}



void MdBinObject::CreateMaterialIndex(int mesh_index, MdBinDataContainer* md_bin_data)
{
	int material_index = *md_bin_data->getpMesh(mesh_index)->getpMaterialIndex();
	mesh_[mesh_index].setMaterialIndex(material_index);
}



void MdBinObject::CreateIndex(int mesh_index, MdBinDataContainer* md_bin_data)
{
	// �C���f�b�N�X���擾
	mesh_[mesh_index].setIndexArraySize(md_bin_data->getpMesh(mesh_index)
										->getIndexArraySize());

   // �f�[�^�擾
	for (int i = 0; i < mesh_[mesh_index].getIndexArraySize(); i++)
	{
		WORD index = (WORD)*md_bin_data->getpMesh(mesh_index)->getpIndex(i);
		*mesh_[mesh_index].getpIndex(i) = index;
	}

	// �v���~�e�B�u������
	int primitive_num = mesh_[mesh_index].getIndexArraySize() / 3;
	mesh_[mesh_index].setPrimitiveNum(primitive_num);
}



void MdBinObject::CreateVertex(int mesh_index, MdBinDataContainer* md_bin_data)
{
	// ���_���擾
	mesh_[mesh_index].setVertexArraySize(md_bin_data->getpMesh(mesh_index)
										 ->getVertexArraySize());

	// �e��f�[�^�擾
	for (int i = 0; i < mesh_[mesh_index].getVertexArraySize(); i++)
	{
		CreateVertexPosition(mesh_index, i, md_bin_data);
		CreateNormal(mesh_index, i, md_bin_data);
		CreateColor(mesh_index, i);
		CreateUV(mesh_index, i, md_bin_data);
	}
}



void MdBinObject::CreateVertexPosition(int mesh_index, int vertex_index,
									   MdBinDataContainer* md_bin_data)
{
	MdBinDataContainer::Vector3* md_position = md_bin_data->getpMesh(mesh_index)
		->getpPosition(vertex_index);
	MdBinObject::Vertex* vertex = mesh_[mesh_index].getpVertex(vertex_index);
	vertex->posisiont_.x = *md_position->getpX();
	vertex->posisiont_.y = *md_position->getpY();
	vertex->posisiont_.z = *md_position->getpZ();
}



void MdBinObject::CreateNormal(int mesh_index, int vertex_index,
							   MdBinDataContainer* md_bin_data)
{
	MdBinDataContainer::Vector3* md_normal = md_bin_data->getpMesh(mesh_index)
		->getpNormal(vertex_index);
	MdBinObject::Vertex* vertex = mesh_[mesh_index].getpVertex(vertex_index);
	vertex->normal_.x = *md_normal->getpX();
	vertex->normal_.y = *md_normal->getpY();
	vertex->normal_.z = *md_normal->getpZ();
}



void MdBinObject::CreateColor(int mesh_index, int vertex_index)
{
	int material_index = mesh_[mesh_index].getMaterialIndex();
	D3DMATERIAL9 diffuse = material_[material_index];
	Color4 color = (Color4)XColor4(diffuse.Diffuse.r, diffuse.Diffuse.g,
								   diffuse.Diffuse.b, diffuse.Diffuse.a);
	MdBinObject::Vertex* vertex = mesh_[mesh_index].getpVertex(vertex_index);
	vertex->color_ = color;
}



void MdBinObject::CreateUV(int mesh_index, int vertex_index,
						   MdBinDataContainer* md_bin_data)
{
	float u = *md_bin_data->getpMesh(mesh_index)->getpUVSet(0)->getpU(vertex_index);
	float v = *md_bin_data->getpMesh(mesh_index)->getpUVSet(0)->getpV(vertex_index);
	MdBinObject::Vertex* vertex = mesh_[mesh_index].getpVertex(vertex_index);
	vertex->uv_.x = u;
	vertex->uv_.y = v;
}



void MdBinObject::CreateDiffuseTexture(int mesh_index,
									   std::string* file_path,
									   MdBinDataContainer* md_bin_data)
{
	
	if (md_bin_data->getpMesh(mesh_index)->getpUVSet(0)->getTextureArraySize() <= 0) return;

	std::string key_name = *md_bin_data->getpMesh(mesh_index)->getpUVSet(0)
		->getpTexture(0)->getpFilePath();
	std::string path = *file_path;
	CreateFilePathAndKeyName(&path, &key_name);
	TextureObject* texture_object = TextureManager::getpInstance()->getpObject(&key_name, &path);
	mesh_[mesh_index].setDiffuseTextureObject(texture_object);
}



void MdBinObject::CreateFilePathAndKeyName(std::string* file_path,
										   std::string* key_name)
{
	// �t�@�C���p�X����t�H���_����/�t���Ŏ擾
	auto slash_index = file_path->rfind("/");
	auto slash_index2 = file_path->rfind("/", slash_index - 1);
	unsigned temp_num = (unsigned)(slash_index - slash_index2);
	std::string temp_strign = file_path->substr(slash_index2 + 1, temp_num);

	// �L�[�l�[���̍쐬
	*key_name = temp_strign + *key_name;

	// �t�@�C���p�X�̍쐬
	*file_path = file_path->substr(0, slash_index2 + 1);
}



void MdBinObject::CreateBuffer(int mesh_index)
{
	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(MdBinObject.cpp)", "Error", MB_OK);
		return;
	}

	CreateVertexBuffer(mesh_index);
	CreateIndexBuffer(mesh_index);
}



void MdBinObject::CreateVertexBuffer(int mesh_index)
{
	// VRAM�̃��������m��(GPU�Ɉ˗�)(���_�o�b�t�@�̍쐬)
	unsigned buffer_num = sizeof(MdBinObject::Vertex) * mesh_[mesh_index].getVertexArraySize();
	HRESULT  hr = device_->CreateVertexBuffer(buffer_num,								// �؂肽��baf�̗�(�o�C�g)�A�܂�1���_�̗e�ʁ~�K�v���_��
											  D3DUSAGE_WRITEONLY,						// �g�p�p�r(����͏������݂̂݁AGPU�������������������񂾃f�[�^��ǂ�ł̓_��(�l���s��))
											  RendererDirectX9::FVF_VERTEX_3D,			// ���_����
											  D3DPOOL_MANAGED,							// ���_�o�b�t�@�̊Ǘ����@( MANAGED�͊Ǘ���Direct3D�ɂ��C���Ƃ����Ӗ� )
											  mesh_[mesh_index].getp2VertexBuffer(),	// �Ǘ��҂̋��ꏊ�̃�����(�|�C���^�̃|�C���^)(�S�Ă͂���̒l��m�邽�߂̍��)
											  NULL);									// �Ȃ��H
	if (FAILED(hr))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s(MdBinObject.cpp)", "Error", MB_OK);
	}

	// ���_�̓o�^
	MdBinObject::Vertex* temp_vertex;	// ���z�A�h���X�����炤���_�|�C���^

	// ���b�N����
	mesh_[mesh_index].getpVertexBuffer()->Lock(0,						// �ǂ����烍�b�N��������
											   0,						// �ǂ̂��炢�؂肽����(0��VertexBuffer�S��)
											   (void**)&temp_vertex,	// ���b�N�����VRAM�̉��z�A�h���X�����炦��(���ۂɏ�������ł���킯�ł͂Ȃ�)
											   D3DLOCK_DISCARD);		// 0�ł��悢

	for (auto i = 0; i < mesh_[mesh_index].getVertexArraySize(); i++)
	{
		temp_vertex[i] = *mesh_[mesh_index].getpVertex(i);
	}

	// �A�����b�N
	mesh_[mesh_index].getpVertexBuffer()->Unlock();
}



void MdBinObject::CreateIndexBuffer(int mesh_index)
{
	// VRAM�̃��������m��(GPU�Ɉ˗�)(�C���f�b�N�X�o�b�t�@�̍쐬)
	unsigned buffer_num = sizeof(WORD) * mesh_[mesh_index].getIndexArraySize();
	HRESULT	hr = device_->CreateIndexBuffer(buffer_num,								// �؂肽��baf�̗�(�o�C�g)�A�܂�1���_�̗e�ʁ~�K�v���_��
											D3DUSAGE_WRITEONLY,						// �g�p�p�r(����͏������݂̂݁AGPU�������������������񂾃f�[�^��ǂ�ł̓_��(�l���s��))
											D3DFMT_INDEX16,							// ���_�t�H�[�}�b�g(WORD�^������16�ADWORD�^�Ȃ�32)
											D3DPOOL_MANAGED,						// ���_�o�b�t�@�̊Ǘ����@( MANAGED�͊Ǘ���Direct3D�ɂ��C���Ƃ����Ӗ� )
											mesh_[mesh_index].getp2IndexBuffer(),	// �Ǘ��҂̋��ꏊ�̃�����(�|�C���^�̃|�C���^)(�S�Ă͂���̒l��m�邽�߂̍��)
											NULL);									// �Ȃ��H									// �Ȃ��H
	if (FAILED(hr))
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐����Ɏ��s(MdBinObject.cpp)", "Error", MB_OK);
	}

	// �C���f�b�N�X�̓o�^
	LPWORD temp_index;		// ���z�A�h���X�����炤���_�|�C���^ 

	// ���b�N����
	mesh_[mesh_index].getpIndexBuffer()->Lock(0,					// �ǂ����烍�b�N��������
											  0,					// �ǂ̂��炢�؂肽����(0��VertexBuffer�S��)
											  (void**)&temp_index,	// ���b�N�����VRAM�̉��z�A�h���X�����炦��(���ۂɏ�������ł���킯�ł͂Ȃ�)
											  D3DLOCK_DISCARD);		// 0�ł��悢

	for (auto i = 0; i < mesh_[mesh_index].getIndexArraySize(); i++)
	{
		temp_index[i] = *mesh_[mesh_index].getpIndex(i);
	}


	// �A�����b�N
	mesh_[mesh_index].getpIndexBuffer()->Unlock();
}