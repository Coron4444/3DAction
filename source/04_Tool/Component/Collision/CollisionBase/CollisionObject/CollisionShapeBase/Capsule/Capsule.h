//================================================================================
//!	@file	 Capsule.h
//!	@brief	 カプセルClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_CAPSULE_H_
#define _CAPSULE_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"
#include "../Cylinder/Cylinder.h"
#include "../Sphere/Sphere.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   カプセルClass
//!
//! @details カプセルのClass
//************************************************************
class Capsule : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Cylinder cylinder_;		//!< 円柱
	Sphere sphere0_;		//!< 球0
	Sphere sphere1_;		//!< 球1


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 球0取得関数
	//! @details
	//! @param void なし
	//! @retval Sphere* 球0
	//----------------------------------------
	Sphere* getpSphere0();

	//----------------------------------------
	//! @brief 球1取得関数
	//! @details
	//! @param void なし
	//! @retval Sphere* 球1
	//----------------------------------------
	Sphere* getpSphere1();

	//----------------------------------------
	//! @brief 円柱取得関数
	//! @details
	//! @param void なし
	//! @retval Cylinder* 円柱
	//----------------------------------------
	Cylinder* getpCylinder();

	//----------------------------------------
	//! @brief 線分取得関数
	//! @details
	//! @param void なし
	//! @retval LineSegment* 線分
	//----------------------------------------
	LineSegment* getpLineSegment();

	//----------------------------------------
	//! @brief 座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 座標
	//----------------------------------------
	Vector3D* getpPosition();

	//----------------------------------------
	//! @brief 方向取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 方向
	//----------------------------------------
	Vector3D* getpVector();

	//----------------------------------------
	//! @brief 方向ベクトル加算済み座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 方向ベクトル加算済み座標
	//----------------------------------------
	Vector3D getAddVectorToPosition();

	//----------------------------------------
	//! @brief 半径取得関数
	//! @details
	//! @param void なし
	//! @retval float 半径
	//----------------------------------------
	float getRadius();

	//----------------------------------------
	//! @brief 半径設定関数
	//! @details
	//! @param value 半径
	//! @retval void なし
	//----------------------------------------
	void setRadius(float value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	Capsule();

	//----------------------------------------
	//! @brief 初期化関数
	//! @param position 始点座標
	//! @param vector   方向
	//! @param radius   半径
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector, float radius);

	//----------------------------------------
	//! @brief 初期化関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();
};



#endif