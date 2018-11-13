//================================================================================
//
//    �V�F�[�_�[�}�l�[�W���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************




//****************************************
// �N���X�錾
//****************************************
class DrawBase;
class Camera;
class FixedVertexShader;
class FixedPixelShader;



/*********************************************************//**
* @brief
* �V�F�[�_�[�}�l�[�W���[�N���X
*
* �V�F�[�_�[���Ǘ�����N���X
*************************************************************/
class ShaderManager
{
//==============================
// �񋓌^��`
//==============================
public:
	// ���_�V�F�[�_�[�^�C�v
	enum VertexShaderType
	{
		VERTEX_NONE = -1,
		VERTEX_FIXED,
		VERTEX_MAX
	};

	// �s�N�Z���V�F�[�_�[�^�C�v
	enum PixelShaderType
	{
		PIXEL_NONE = -1,
		PIXEL_FIXED,
		PIXEL_MAX
	};


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	// �e��V�F�[�_�[������(�{���͔z������)
	FixedVertexShader* fixed_vertex_shader_ = nullptr;
	FixedPixelShader* fixed_pixel_shader_ = nullptr;


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	void Init();

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit();

	/**
	* @brief
	* �V�F�[�_�[�ݒ�֐�
	* @param
	* draw : �`����N���X
	* forced_vertex_type : �������_�V�F�[�_�[�^�C�v
	* forced_pixel_type : �����s�N�Z���V�F�[�_�[�^�C�v
	*/
	void SetShader(DrawBase* draw, VertexShaderType forced_vertex_type,
				   PixelShaderType forced_pixel_type);
	/**
	* @brief
	* ���ʐݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* forced_vertex_type : �������_�V�F�[�_�[�^�C�v
	* forced_pixel_type : �����s�N�Z���V�F�[�_�[�^�C�v
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	*/
	void CommonSetting(DrawBase* draw, Camera* camera, 
					   VertexShaderType forced_vertex_type,
					   PixelShaderType forced_pixel_type, unsigned object_index);

	/**
	* @brief
	* �ŗL�ݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* forced_vertex_type : �������_�V�F�[�_�[�^�C�v
	* forced_pixel_type : �����s�N�Z���V�F�[�_�[�^�C�v
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	void SpecificSetting(DrawBase* draw, Camera* camera, 
						 VertexShaderType forced_vertex_type,
						 PixelShaderType forced_pixel_type, 
						 unsigned object_index, unsigned mesh_index);
};



#endif
