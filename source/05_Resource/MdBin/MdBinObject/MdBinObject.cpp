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

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <Vector3D.h>
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



TextureObject* MdBinObject::Mesh::getpDiffuseTextureObject()
{
	return diffuse_texture_object_;
}



void MdBinObject::Mesh::setDiffuseTextureObject(TextureObject* value)
{
	diffuse_texture_object_ = value;
}



//****************************************
// �֐���`
//****************************************
void MdBinObject::Init(std::string* file_path)
{
	// �o�C�i���[���f���f�[�^�̓ǂݍ���
	MdBinDataContainer md_bin_data;
	if (MdBinDataContainer::InportData(&md_bin_data, *file_path))
	{
		MessageBox(NULL, "�o�C�i���[���f�����C���|�[�g�o���܂���ł����B", "Error", MB_OK);
		return;
	}

	// �}�e���A������
	CreateMaterial(&md_bin_data);

	// ���b�V������
	CreateMesh(&md_bin_data);
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



void MdBinObject::CreateMesh(MdBinDataContainer* md_bin_data)
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
		CreateDiffuseTexture(i, md_bin_data);

		// �o�b�t�@����
		CreateBuffer(i, md_bin_data);
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
	for (int i = 0; i = mesh_[mesh_index].getIndexArraySize(); i++)
	{
		int index = *md_bin_data->getpMesh(mesh_index)->getpIndex(i);
		*mesh_[mesh_index].getpIndex(i) = index;
	}
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
		CreateColor(mesh_index, i, md_bin_data);
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



void MdBinObject::CreateColor(int mesh_index, int vertex_index,
							  MdBinDataContainer* md_bin_data)
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
									   MdBinDataContainer* md_bin_data)
{
	std::string file_path = *md_bin_data->getpMesh(mesh_index)->getpUVSet(0)
		->getpTexture(0)->getpFilePath();
	std::string key_name;
	CreateFilePathAndKeyName(&file_path, &key_name);
	TextureObject* texture_object = TextureManager::AddUniqueData(&key_name, &file_path);
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