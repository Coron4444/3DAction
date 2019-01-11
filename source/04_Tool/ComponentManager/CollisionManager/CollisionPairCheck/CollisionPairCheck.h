//================================================================================
//!	@file	 CollisionPairCheck.h
//!	@brief	 衝突ペア判定Class
//! @details static
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_COLLISION_PAIR_CHECK_H_
#define _COLLISION_PAIR_CHECK_H_



//****************************************
// インクルード文
//****************************************
#include <vector>

#include <Component/Collision/CollisionBase/CollisionBase.h>

#include <Vector3D.h>



//************************************************************														   
//! @brief   衝突ペア判定Class
//!
//! @details 衝突基底クラスのペアを判定するClass(static)
//************************************************************
class CollisionPairCheck
{
//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief 衝突基底クラスペア判定関数
	//! @details
	//! @param *collision0 衝突基底クラス
	//! @param *collision1 衝突基底クラス
	//! @retval bool 衝突していいペアならtrue
	//----------------------------------------
	static bool IsCheck(CollisionBase* collision0, CollisionBase* collision1);


private:
	//----------------------------------------
	//! @brief ペア判定関数
	//! @details
	//! @param *collision0 衝突基底クラス
	//! @param *collision1 衝突基底クラス
	//! @retval bool 衝突していいペアならtrue
	//----------------------------------------
	static bool IsPair(CollisionBase* collision0, CollisionBase* collision1);

	//----------------------------------------
	//! @brief 指定した衝突タイプの検索関数
	//! @details
	//! @param type        衝突基底クラスタイプ
	//! @param *collision0 衝突基底クラス
	//! @param *collision1 衝突基底クラス
	//! @retval CollisionBase* 検索結果に合致した衝突基底クラス
	//----------------------------------------
	static CollisionBase* IsType(CollisionBase::Type type,
								  CollisionBase* collision0,
								  CollisionBase* collision1);

	//----------------------------------------
	//! @brief 指定したコンポーネントの逆を返す関数
	//! @details
	//! @param *age_component 指定する衝突基底クラス
	//! @param *collision0    衝突基底クラス
	//! @param *collision1    衝突基底クラス
	//! @retval CollisionBase* 指定した衝突基底クラスポインタの逆の衝突基底クラス
	//----------------------------------------
	static CollisionBase* OtherSideComponent(CollisionBase* age_component,
											 CollisionBase* collision0,
											 CollisionBase* collision1);

	//----------------------------------------
	//! @brief プレイヤーのペアリスト関数
	//! @details
	//! @param *collision 衝突基底クラス
	//! @retval bool 衝突していいペアならtrue
	//----------------------------------------
	static bool PairList_Player(CollisionBase* collision);


//====================
// 消去済み関数
//====================
private:
	CollisionPairCheck() = delete;
	CollisionPairCheck(const CollisionPairCheck& value) = delete;
	CollisionPairCheck& operator = (const CollisionPairCheck& value) = delete;
};



#endif