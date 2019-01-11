//================================================================================
//!	@file	 Cylinder.h
//!	@brief	 円柱Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_CYLINDER_H_
#define _CYLINDER_H_



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"
#include "../LineSegment/LineSegment.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   円柱Class
//!
//! @details 円柱のClass
//************************************************************
class Cylinder : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	LineSegment line_segment_;	//!< 線分
	float radius_;				//!< 半径


//====================
// プロパティ
//====================
public:
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
	//! @details
	//! @param void なし
	//----------------------------------------
	Cylinder();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param position 始点座標
	//! @param vector   方向
	//! @param radius   半径
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector, float radius);
};



#endif