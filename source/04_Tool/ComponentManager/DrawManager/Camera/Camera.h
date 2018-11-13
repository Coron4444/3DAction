//================================================================================
//
//    �J�����N���X
//    Author : Araki Kai                                �쐬�� : 2017/12/07
//
//================================================================================

#ifndef	_CAMERA_H_
#define _CAMERA_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Transform\AxisVector\AxisVector.h>



/*********************************************************//**
* @brief
* �J�����N���X
*
* �J�����̃N���X
*************************************************************/
class Camera
{
/***************************//**
* @brief
* �J�����X�e�[�g�N���X
*
* �J�����̃X�e�[�g�N���X
*******************************/
public:
	class State
	{
	//==============================
	// ��ÓI�����o�֐�
	//==============================
	public:
		/**
		* @brief
		* �f�X�g���N�^
		*/
		virtual ~State() {}

		/**
		* @brief
		* �������֐�
		* @param
		* camera : �J����
		*/
		virtual void Init(Camera* camera) = 0;

		/**
		* @brief
		* �I���֐�
		* @param
		* camera : �J����
		*/
		virtual void Uninit() = 0;

		/**
		* @brief
		* �X�V�֐�
		* @param
		* camera : �J����
		*/
		virtual void Update(Camera* camera) = 0;
	};


//==============================
// �萔��`
//==============================
public:
	static const float NEAR_CLIPPING_PLANE;		//!< �ߖʃN���b�v
	static const float FAR_CLIPPING_PLANE;		//!< ���ʃN���b�v
	static const int   DEFAULT_ANGLE_OF_VIEW;	//!< ��p

//==============================
// �񋓌^��`
//==============================
public:
	enum Type
	{
		NONE = -1,
		PERSPECTIVE,
		ORTHO,
		TWO_DIMENSIONAL,
		MAX
	};



//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	Vector3D position_;				//!< ���W
	Vector3D look_at_point_;		//!< �����_
	Vector3D up_;					//!< ��x�N�g��

	int angle_of_view_;				//!< ��p

	AxisVector axis_;				//!< ��

	MATRIX view_;						//!< �r���[�s��
	MATRIX view_2D_;					//!< �r���[�s��(2D)
	MATRIX projection_perspective_;		//!< �v���W�F�N�V�����s��(�������e)
	MATRIX projection_ortho_;			//!< �v���W�F�N�V�����s��(���ˉe)
	MATRIX projection_2D_;				//!< �v���W�F�N�V�����s��(2D)

	State* state_ = nullptr;			//!< �X�e�[�g
	Type type_ = Type::PERSPECTIVE;		//!< �^�C�v


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	* @param
	* state : �X�e�[�g
	* position : ���W
	* look_at_point : �����_
	* up : ��x�N�g��
	*/
	void Init(State* state, Vec3 position = {0.0f, 0.0f, -10.0f},
			  Vec3 look_at_point = {0.0f, 0.0f, 0.0f}, Vec3 up = {0.0f, 1.0f, 0.0f});

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit();

	/**
	* @brief
	* �X�V�֐�
	*/
	void Update();

	/**
	* @brief
	* �r���[�s��쐬�֐�
	*/
	void CreateViewMatrix();

	/**
	* @brief
	* �v���W�F�N�V�����s��쐬�֐�(�������e�s��)
	*/
	void CreateProjectionMatrix_PerspectiveFov();

	/**
	* @brief
	* �v���W�F�N�V�����s��쐬�֐�(���ˉe�s��)
	*/
	void CreateProjectionMatrix_Ortho();

	/**
	* @brief
	* �v���W�F�N�V�����s��쐬�֐�(2D)
	*/
	void CreateProjectionMatrix_2D();

	/**
	* @brief
	* �J�����X�e�[�g�̕ύX
	*/
	void ChangeState(State* new_camera_state);

	// �v���p�e�B
	const MATRIX* GetViewMatrix() const
	{
		if (type_ == Type::TWO_DIMENSIONAL) return &view_2D_;
		return &view_;
	}
	const MATRIX* GetProjectionMatrix() const
	{
		if (type_ == Type::PERSPECTIVE) return &projection_perspective_;
		if (type_ == Type::ORTHO) return &projection_ortho_;
		return &projection_2D_;
	}
	Vector3D* GetPositon() { return &position_; }
	Vector3D* GetLookAtPoint() { return &look_at_point_; }
	Vector3D* GetUp() { return &up_; }
	int GetAngleOfView() { return angle_of_view_; }
	void SetAngleOfView(int value)
	{
		angle_of_view_ = value;
		CreateProjectionMatrix_PerspectiveFov();
		CreateProjectionMatrix_Ortho();
	}
	AxisVector* GetAxis() { return &axis_; }
	const Vector3D* GetForwardVector() const { return axis_.GetForawrd(); }
	const State* GetCameraState() const { return state_; }
	Type GetType() { return type_; }
	void SetType(Type value) { type_ = value; }
};



#endif