//================================================================================
//
//    �t�F�[�h�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================

#ifndef	_FADE_H_
#define _FADE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/DrawBase/DrawNull.h>
#include <Transform\Transform.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <Texture\TextureManager\TextureManager.h>



/*********************************************************//**
* @brief
* �t�F�[�h�N���X
*
* �t�F�[�h�̃N���X
*************************************************************/
class Fade : public DrawNull
{
//==============================
// �萔��`
//==============================
public:
	static const std::string TEXTURE_PATH;
	static const std::string TEXTURE_NAME_TRANSITION_01;


//==============================
// �񋓌^��`
//==============================
public:
	enum Type
	{
		TYPE_NONE = -1,
		TYPE_NORMAL,
		TYPE_TRANSITION_01,
		TYPE_MAX
	};

	enum State
	{
		STATE_NONE = -1,
		STATE_FADE_IN,
		STATE_FADE_OUT,
		STATE_MAX
	};

//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	Type type_;			//!< �^�C�v
	State state_;		//!< �X�e�[�g

	PlanePolygon* plane_polygon_;		//!< �|���S��
	Transform transform_;				//!< ���
	XColor4 color_;						//!< �F

	float speed_;		//!< �t�F�[�h���x
	bool end_flag_;		//!< �I���t���O

	TextureObject* transition01_texture_;	//!< �e�N�X�`���I�u�W�F�N�g


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �R���X�g���N�^
	*/
	Fade();

	/**
	* @brief
	* �f�X�g���N�^
	*/
	~Fade();

	/**
	* @brief
	* �������֐�
	* @param
	* type : �^�C�v
	* state : �X�e�[�g
	* size : �g�k
	* color : �F
	* speed : �t�F�[�h���x
	*/
	void Init(Type type, State state, Vec2 size, XColor4 color, float speed);

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit() override;

	/**
	* @brief
	* �X�V�֐�
	*/
	void Update();

	/**
	* @brief
	* �`��֐�
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override;

	// �v���p�e�B
	const MATRIX* GetMatrix(unsigned object_index) override
	{
		object_index = object_index;
		return transform_.GetMatrixExtend()->GetWorldMatrix();
	}
	const Type* GetType()   const { return &type_; }
	const State* GetState() const { return &state_; }
	bool GetEndFlag() const { return end_flag_; }
	Transform* GetTransform() { return &transform_; }
	TextureObject* GetTransition01Object() { return transition01_texture_; }
};



#endif