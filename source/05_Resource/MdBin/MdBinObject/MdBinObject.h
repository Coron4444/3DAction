//================================================================================
//!	@file	 MdBinObject.h
//!	@brief	 �o�C�i���[���f���I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_MD_BIN_OBJECT_H_
#define _MD_BIN_OBJECT_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <windows.h>
#include <string>
#include <vector>

#include <Vector3D.h>



//****************************************
// �N���X�錾
//****************************************
class TextureObject;
class MdBinDataContainer;



//************************************************************														   
//! @brief   �o�C�i���[���f���I�u�W�F�N�gClass
//!
//! @details �o�C�i���[���f���̃I�u�W�F�N�gClass
//************************************************************
class MdBinObject
{
//====================
// �N���X��`
//====================
public:
	//****************************************														   
	//! @brief ���_Struct
	//!
	//! @details ���_�p��Struct
	//****************************************
	struct Vertex
	{
	//====================
	// �ϐ�
	//====================
	public:
		Vec3   posisiont_;	//!< ���W
		Vec3   normal_;		//!< �@��
		Color4 color_;		//!< �J���[
		Vec2   uv_;			//!< UV
	};

	//****************************************														   
	//! @brief ���b�V��Class
	//!
	//! @details ���b�V����Class
	//****************************************
	class Mesh
	{
	//====================
	// �ϐ�
	//====================
	private:
		int material_index_;								//!< �}�e���A���C���f�b�N�X
		std::vector<WORD> index_;							//!< �C���f�b�N�X�z��
		std::vector<Vertex> vertex_;						//!< ���_�z��
		TextureObject* diffuse_texture_object_ = nullptr;	//!< �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer_ = nullptr;	//!< ���_�o�b�t�@
		LPDIRECT3DINDEXBUFFER9  index_buffer_ = nullptr;	//!< �C���f�b�N�X�o�b�t�@


	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief ���_�z��T�C�Y�擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval int �T�C�Y
		//----------------------------------------
		int getVertexArraySize();

		//----------------------------------------
		//! @brief ���_�z��T�C�Y�ݒ�֐�
		//! @details
		//! @param value �T�C�Y
		//! @retval void �Ȃ�
		//----------------------------------------
		void setVertexArraySize(int value);

		//----------------------------------------
		//! @brief ���_�擾�֐�
		//! @details
		//! @param index �C���f�b�N�X
		//! @retval Vertex* ���_
		//----------------------------------------
		Vertex* getpVertex(int index);

		//----------------------------------------
		//! @brief �C���f�b�N�X�z��T�C�Y�擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval int �T�C�Y
		//----------------------------------------
		int getIndexArraySize();

		//----------------------------------------
		//! @brief �C���f�b�N�X�z��T�C�Y�ݒ�֐�
		//! @details
		//! @param value �T�C�Y
		//! @retval void �Ȃ�
		//----------------------------------------
		void setIndexArraySize(int value);

		//----------------------------------------
		//! @brief �C���f�b�N�X�擾�֐�
		//! @details
		//! @param index �C���f�b�N�X
		//! @retval WORD* �C���f�b�N�X
		//----------------------------------------
		WORD* getpIndex(int index);

		//----------------------------------------
		//! @brief �}�e���A���C���f�b�N�X�擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval int �}�e���A���C���f�b�N�X
		//----------------------------------------
		int getMaterialIndex();

		//----------------------------------------
		//! @brief �}�e���A���C���f�b�N�X�ݒ�֐�
		//! @details
		//! @param value �}�e���A���C���f�b�N�X
		//! @retval void �Ȃ�
		//----------------------------------------
		void setMaterialIndex(int value);

		//----------------------------------------
		//! @brief �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g�擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval TextureObject* �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g
		//----------------------------------------
		TextureObject* getpDiffuseTextureObject();

		//----------------------------------------
		//! @brief �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g�ݒ�֐�
		//! @details
		//! @param *value �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g
		//! @retval void �Ȃ�
		//----------------------------------------
		void setDiffuseTextureObject(TextureObject* value);
	};


//====================
// �ϐ�
//====================
private:
	std::vector<Mesh> mesh_;				//!< ���b�V���z��
	std::vector<D3DMATERIAL9> material_;	//!< �}�e���A���z��

	LPDIRECT3DDEVICE9 device_ = nullptr;	//!< �f�o�C�X

	unsigned reference_counter_ = 0;			//!< �Q�ƃJ�E���^


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(std::string* file_path);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �Q�ƃJ�E���^�ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddReferenceCounter();

	//----------------------------------------
	//! @brief ����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Release();

private:
	//----------------------------------------
	//! @brief �}�e���A�������֐�
	//! @details
	//! @param md_bin �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMaterial(MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief ���b�V�������֐�
	//! @details
	//! @param md_bin �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMesh(MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief �}�e���A���C���f�b�N�X�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param md_bin       �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMaterialIndex(int mesh_index, MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief �C���f�b�N�X�����֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @param md_bin     �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateIndex(int mesh_index, MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief ���_�����֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @param md_bin     �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateVertex(int mesh_index, MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief ���_���W�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param vertex_index ���_�C���f�b�N�X
	//! @param md_bin       �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateVertexPosition(int mesh_index, int vertex_index,
							  MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief �@�������֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param vertex_index ���_�C���f�b�N�X
	//! @param md_bin       �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateNormal(int mesh_index, int vertex_index,
					  MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief �J���[�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param vertex_index ���_�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateColor(int mesh_index, int vertex_index);

	//----------------------------------------
	//! @brief UV�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param vertex_index ���_�C���f�b�N�X
	//! @param md_bin       �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateUV(int mesh_index, int vertex_index,
				  MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief �f�B�q���[�Y�e�N�X�`�������֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @param md_bin     �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateDiffuseTexture(int mesh_index, MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief �t�@�C���p�X&�L�[�������֐�
	//! @details
	//! @param *file_path �t�@�C���p�X
	//! @param *key_name  �L�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateFilePathAndKeyName(std::string* file_path,
								  std::string* key_name);

	//----------------------------------------
	//! @brief �o�b�t�@�����֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @param md_bin     �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateBuffer(int mesh_index, MdBinDataContainer* md_bin_data);
};



#endif
