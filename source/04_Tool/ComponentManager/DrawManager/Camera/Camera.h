//================================================================================
//
//    カメラクラス
//    Author : Araki Kai                                作成日 : 2017/12/07
//
//================================================================================

#ifndef	_CAMERA_H_
#define _CAMERA_H_



//****************************************
// インクルード文
//****************************************
#include <Transform\AxisVector\AxisVector.h>



/*********************************************************//**
* @brief
* カメラクラス
*
* カメラのクラス
*************************************************************/
class Camera
{
/***************************//**
* @brief
* カメラステートクラス
*
* カメラのステートクラス
*******************************/
public:
	class State
	{
	//==============================
	// 非静的メンバ関数
	//==============================
	public:
		/**
		* @brief
		* デストラクタ
		*/
		virtual ~State() {}

		/**
		* @brief
		* 初期化関数
		* @param
		* camera : カメラ
		*/
		virtual void Init(Camera* camera) = 0;

		/**
		* @brief
		* 終了関数
		* @param
		* camera : カメラ
		*/
		virtual void Uninit() = 0;

		/**
		* @brief
		* 更新関数
		* @param
		* camera : カメラ
		*/
		virtual void Update(Camera* camera) = 0;
	};


//==============================
// 定数定義
//==============================
public:
	static const float NEAR_CLIPPING_PLANE;		//!< 近面クリップ
	static const float FAR_CLIPPING_PLANE;		//!< 遠面クリップ
	static const int   DEFAULT_ANGLE_OF_VIEW;	//!< 画角

//==============================
// 列挙型定義
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
// 非静的メンバ変数
//==============================
private:
	Vector3D position_;				//!< 座標
	Vector3D look_at_point_;		//!< 注視点
	Vector3D up_;					//!< 上ベクトル

	int angle_of_view_;				//!< 画角

	AxisVector axis_;				//!< 軸

	MATRIX view_;						//!< ビュー行列
	MATRIX view_2D_;					//!< ビュー行列(2D)
	MATRIX projection_perspective_;		//!< プロジェクション行列(透視投影)
	MATRIX projection_ortho_;			//!< プロジェクション行列(正射影)
	MATRIX projection_2D_;				//!< プロジェクション行列(2D)

	State* state_ = nullptr;			//!< ステート
	Type type_ = Type::PERSPECTIVE;		//!< タイプ


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	* @param
	* state : ステート
	* position : 座標
	* look_at_point : 注視点
	* up : 上ベクトル
	*/
	void Init(State* state, Vec3 position = {0.0f, 0.0f, -10.0f},
			  Vec3 look_at_point = {0.0f, 0.0f, 0.0f}, Vec3 up = {0.0f, 1.0f, 0.0f});

	/**
	* @brief
	* 終了関数
	*/
	void Uninit();

	/**
	* @brief
	* 更新関数
	*/
	void Update();

	/**
	* @brief
	* ビュー行列作成関数
	*/
	void CreateViewMatrix();

	/**
	* @brief
	* プロジェクション行列作成関数(透視投影行列)
	*/
	void CreateProjectionMatrix_PerspectiveFov();

	/**
	* @brief
	* プロジェクション行列作成関数(正射影行列)
	*/
	void CreateProjectionMatrix_Ortho();

	/**
	* @brief
	* プロジェクション行列作成関数(2D)
	*/
	void CreateProjectionMatrix_2D();

	/**
	* @brief
	* カメラステートの変更
	*/
	void ChangeState(State* new_camera_state);

	// プロパティ
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