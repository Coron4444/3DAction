//================================================================================
//
//    X���f���N���X
//    Author : Araki Kai                                �쐬�� : 2017/12/18
//
//================================================================================

#ifndef	_MODEL_X_OBJECT_H_
#define _MODEL_X_OBJECT_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>
#include <vector>

#include <Vector3D.h>
#include <Texture\TextureManager\TextureManager.h>
#include <Renderer\Renderer.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class ModelXObject
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	ModelXObject(const std::string* file_path, bool is_share_data);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~ModelXObject();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���b�V��
	LPD3DXMESH GetMesh(){return mesh_;}
	unsigned getMeshNum(){return material_num_;}	// X���f���̓}�e���A���������b�V�����̑���
	void UpdateMeshDeclaration(const D3DVERTEXELEMENT9* DECLARATION);
	
	// �}�e���A��
	D3DMATERIAL9* GetMaterial(unsigned index){return &material_[index];}
	void SetMaterialColor(unsigned index, XColor4 color);

	// �e�N�X�`��
	const TextureObject* GetDecaleTextureName(unsigned index){return texture_object_array_.at(index);}


//------------------------------------------------------------
private :
	// ����J�����o�֐�
	void InputModelX   (const std::string* file_path, LPD3DXBUFFER* material_buffer);
	void InputMaterial (const std::string* file_path, LPD3DXBUFFER* material_buffer, bool is_share_data);
	void MakeTextureFilePathAndKeyName(std::string* texture_key_name, std::string* texture_file_path);
	

//------------------------------------------------------------
private :
	// ���b�V��
	LPD3DXMESH	 mesh_;
	DWORD		 material_num_;
	
	// �}�e���A��
	std::vector<D3DMATERIAL9> material_;

	// �e�N�X�`��
	std::vector<TextureObject*> texture_object_array_;
};



#endif