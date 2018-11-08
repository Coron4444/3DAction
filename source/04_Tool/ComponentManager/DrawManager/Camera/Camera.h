//================================================================================
//
//    カメラクラス
//    Author : Araki Kai                                作成日 : 2017/12/07
//
//================================================================================

#ifndef	_CAMERA_H_
#define _CAMERA_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <Transform\AxisVector\AxisVector.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Camera
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 定数
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
	// カメラステートクラス
	class State
	{
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	public :
		// デストラクタ
		virtual ~State() {}


	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	public :
		// メンバ変数
		virtual void Init  (Camera* camera) = 0;
		virtual void Uninit(Camera* camera) = 0;
		virtual void Update(Camera* camera) = 0;
	};




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// コンストラクタ
	Camera(State* state, Type type, Vec3 position = {0.0f, 0.0f, -10.0f}, 
		   Vec3 look_at_point = {0.0f, 0.0f, 0.0f}, Vec3 up = {0.0f, 1.0f, 0.0f});


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	~Camera();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 更新
	void Update();

	// 行列
	void CreateViewMatrix();
	void CreateProjectionMatrix(float angle_of_view, float aspect, 
								float near_clipping_plane, float far_clipping_plane);
	void CreateProjectionMatrix_PerspectiveFov();
	void CreateProjectionMatrix_Ortho();
	const MATRIX* GetViewMatrix()		const {return &matrix_view_;}
	const MATRIX* GetProjectionMatrix() const {return &matrix_projection_;}

	// 姿勢
	Vector3D*   GetPositon()    {return &position_;}
	Vector3D*   GetLookAtPoint(){return &look_at_point_;}
	Vector3D*   GetUp()         {return &up_;}

	// 画角
	int* GetAngleOfView() {return &angle_of_view_;}

	// 軸
	AxisVector* GetAxis(){return &axis_;}
	const Vector3D* GetForwardVector() const {return axis_.GetForawrd();}

	// ステート&タイプ
	void ChangeState(State* new_camera_state);
	bool IsCameraTypeName(Type type);
	const State* GetCameraState() const {return state_;}

//------------------------------------------------------------
private :
	// 姿勢
	Vector3D position_;
	Vector3D look_at_point_;
	Vector3D up_;

	// 画角
	int angle_of_view_;

	// 軸ベクトル
	AxisVector axis_;

	// 行列
	MATRIX matrix_view_;
	MATRIX matrix_projection_;

	// ステート
	State* state_;

	// カメラタイプ
	Type type_;
};



#endif