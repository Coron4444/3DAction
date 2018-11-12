//================================================================================
//
//    物理クラス
//    Author : Araki Kai                                作成日 : 2018/08/19
//
//================================================================================

#ifndef	_PHYSICS_H_
#define _PHYSICS_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <Vector3D.h>



//======================================================================
//
// クラス宣言
//
//======================================================================

class GameObjectBase;



//======================================================================
//
// クラス定義
//
//======================================================================

class Physics
{
//------------------------------------------------------------
private :
	static const float VELOCITY_MIN;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	Physics(GameObjectBase* game_object);



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	~Physics();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 更新
	void Update();

	// 加速度
	Vector3D* GetAcceleration(){return &acceleration_;}

	// 速度
	Vector3D* GetVelocity(){return &velocity_;}
	void      SetMaxVelocity(float max_velocity){max_velocity_ = max_velocity;}
	float     GetMaxVelocity(){return max_velocity_;}

	// 質量
	void  SetMass(float mass){mass_ = mass;}
	float GetMass(){return mass_;}

	// 摩擦力
	void  AddFriction(float friction){friction_ += friction;}
	float GetFriction(){return friction_;}
	void  SetMyFriction(float my_friction){my_friction_ = my_friction;}
	float GetMyFriction(){return my_friction_;}

	// 反発力
	void  AddBounciness(float bounciness){bounciness_ += bounciness;}
	float GetBounciness(){return bounciness_;}
	void  SetMyBounciness(float bounciness){bounciness_ = bounciness;}
	float GetMyBounciness(){return bounciness_;}

	// 重力
	void SetGravity(bool is_gravity){is_gravity_ = is_gravity;}
	bool IsGravity() {return is_gravity_;}

	// 地面
	void SetOnTheGround(){is_on_tha_ground_ = true;}
	

//------------------------------------------------------------
private :
	void Reset();
	void UpdateAcceleration();
	void UpdateVelocity();
	void UpdatePosition();
	void SetGravity();
	void SetGround();
	void CheckVelocityMinMax();


//------------------------------------------------------------
private :
	// ゲームオブジェクト
	GameObjectBase* game_object_;

	// 加速度
	Vector3D acceleration_;

	// 速度
	Vector3D velocity_;
	float    max_velocity_;

	// 質量
	float mass_;

	// 摩擦
	float friction_;
	float my_friction_;

	// 反発力(後でちゃんとした跳ね返りを検討)
	float bounciness_;
	float my_bounciness_;
	
	// 重力
	bool is_gravity_;
	float gravity_acceleration_;
	Vector3D gravity_direction_;

	// 地面
	bool is_on_tha_ground_;
	bool is_landing_;



};



#endif