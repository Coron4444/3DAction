//================================================================================
//
//    �J�����N���X
//    Author : Araki Kai                                �쐬�� : 2017/12/07
//
//================================================================================

#ifndef	_CAMERA_H_
#define _CAMERA_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <Transform\AxisVector\AxisVector.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Camera
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �萔
	static const float NEAR_CLIPPING_PLANE;
	static const float FAR_CLIPPING_PLANE;
	static const int   DEFAULT_ANGLE_OF_VIEW;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	enum Type
	{
		NONE = -1,
		NORMAL,
		MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �J�����X�e�[�g�N���X
	class State
	{
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	public :
		// �f�X�g���N�^
		virtual ~State() {}


	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	public :
		// �����o�ϐ�
		virtual void Init  (Camera* camera) = 0;
		virtual void Uninit(Camera* camera) = 0;
		virtual void Update(Camera* camera) = 0;
	};




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �R���X�g���N�^
	Camera(State* state, Type type, Vec3 position = {0.0f, 0.0f, -10.0f}, 
		   Vec3 look_at_point = {0.0f, 0.0f, 0.0f}, Vec3 up = {0.0f, 1.0f, 0.0f});


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	~Camera();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �X�V
	void Update();

	// �s��
	void CreateViewMatrix();
	void CreateProjectionMatrix(float angle_of_view, float aspect, 
								float near_clipping_plane, float far_clipping_plane);
	void CreateProjectionMatrix_PerspectiveFov();
	void CreateProjectionMatrix_Ortho();
	const MATRIX* GetViewMatrix()		const {return &matrix_view_;}
	const MATRIX* GetProjectionMatrix() const {return &matrix_projection_;}

	// �p��
	Vector3D*   GetPositon()    {return &position_;}
	Vector3D*   GetLookAtPoint(){return &look_at_point_;}
	Vector3D*   GetUp()         {return &up_;}

	// ��p
	int* GetAngleOfView() {return &angle_of_view_;}

	// ��
	AxisVector* GetAxis(){return &axis_;}
	const Vector3D* GetForwardVector() const {return axis_.GetForawrd();}

	// �X�e�[�g&�^�C�v
	void ChangeState(State* new_camera_state);
	bool IsCameraTypeName(Type type);
	const State* GetCameraState() const {return state_;}

//------------------------------------------------------------
private :
	// �p��
	Vector3D position_;
	Vector3D look_at_point_;
	Vector3D up_;

	// ��p
	int angle_of_view_;

	// ���x�N�g��
	AxisVector axis_;

	// �s��
	MATRIX matrix_view_;
	MATRIX matrix_projection_;

	// �X�e�[�g
	State* state_;

	// �J�����^�C�v
	Type type_;
};



#endif