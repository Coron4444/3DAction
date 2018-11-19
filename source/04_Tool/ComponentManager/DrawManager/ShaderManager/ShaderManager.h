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
class VertexShaderBase;
class PixelShaderBase;



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
		VERTEX_BUMP_MAPPING,
		VERTEX_MAX
	};

	// �s�N�Z���V�F�[�_�[�^�C�v
	enum PixelShaderType
	{
		PIXEL_NONE = -1,
		PIXEL_FIXED,
		PIXEL_BUMP_MAPPING,
		PIXEL_MAX
	};


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	// �e��V�F�[�_�[
	VertexShaderBase* vertex_shaders_[VERTEX_MAX] = {nullptr};
	PixelShaderBase* pixel_shaders_[PIXEL_MAX] = {nullptr};


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

private:
	/**
	* @brief
	* ���_�V�F�[�_�[�������֐�
	*/
	void InitVertexShaders();

	/**
	* @brief
	* �s�N�Z���V�F�[�_�[�������֐�
	*/
	void InitPixelShaders();


	/**
	* @brief
	* ���_�V�F�[�_�[�I���֐�
	*/
	void UninitVertexShaders();

	/**
	* @brief
	* �s�N�Z���V�F�[�_�[�I���֐�
	*/
	void UninitPixelShaders();

	/**
	* @brief
	* ���_�V�F�[�_�[�ݒ�֐�
	* @param
	* draw : �`����N���X
	* forced_vertex_type : �������_�V�F�[�_�[�^�C�v
	*/
	void SetVertexShader(DrawBase* draw, VertexShaderType forced_vertex_type);

	/**
	* @brief
	* �s�N�Z���V�F�[�_�[�ݒ�֐�
	* @param
	* draw : �`����N���X
	* forced_pixel_type : �����s�N�Z���V�F�[�_�[�^�C�v
	*/
	void SetPixelShader(DrawBase* draw, PixelShaderType forced_pixel_type);

	/**
	* @brief
	* ���_�V�F�[�_�[���ʐݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* forced_vertex_type : �������_�V�F�[�_�[�^�C�v
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	*/
	void CommonSettingVertexShader(DrawBase* draw, Camera* camera,
								   VertexShaderType forced_vertex_type,
								   unsigned object_index);

	/**
	* @brief
	* �s�N�Z���V�F�[�_�[���ʐݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* forced_pixel_type : �����s�N�Z���V�F�[�_�[�^�C�v
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	*/
	void CommonSettingPixelShader(DrawBase* draw, Camera* camera,
								  PixelShaderType forced_pixel_type,
								  unsigned object_index);

	/**
	* @brief
	* ���_�V�F�[�_�[�ŗL�ݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* forced_vertex_type : �������_�V�F�[�_�[�^�C�v
	* forced_pixel_type : �����s�N�Z���V�F�[�_�[�^�C�v
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	void SpecificSettingVertexShader(DrawBase* draw, Camera* camera,
									 VertexShaderType forced_vertex_type,
									 unsigned object_index, unsigned mesh_index);

	/**
	* @brief
	* �s�N�Z���V�F�[�_�[�ŗL�ݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* forced_vertex_type : �������_�V�F�[�_�[�^�C�v
	* forced_pixel_type : �����s�N�Z���V�F�[�_�[�^�C�v
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	void SpecificSettingPixelShader(DrawBase* draw, Camera* camera,
									PixelShaderType forced_pixel_type,
									unsigned object_index, unsigned mesh_index);
};



#endif
