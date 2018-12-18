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
	Sphere sphere0_;		//!< 球
	Sphere sphere1_;		//!< 球


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 球0ポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval Sphere* 球0ポインタ
	//----------------------------------------
	Sphere* getpSphere0();

	//----------------------------------------
	//! @brief 球1ポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval Sphere* 球1ポインタ
	//----------------------------------------
	Sphere* getpSphere1();

	//----------------------------------------
	//! @brief 円柱ポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval Cylinder* 円柱ポインタ
	//----------------------------------------
	Cylinder* getpCylinder();

	//----------------------------------------
	//! @brief 線分ポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval LineSegment* 線分ポインタ
	//----------------------------------------
	LineSegment* getpLineSegment();

	//----------------------------------------
	//! @brief 座標ポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 座標ポインタ
	//----------------------------------------
	Vector3D* getpPosition();

	//----------------------------------------
	//! @brief 方向ポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 方向ポインタ
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
	//! @param[in] value 半径
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
	//! @param[in] position 始点座標
	//! @param[in] vector   方向
	//! @param[in] radius   半径
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