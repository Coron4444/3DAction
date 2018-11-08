//================================================================================
//
//    衝突ペア判定クラス(static)
//    Author : Araki Kai                                作成日 : 2018/04/20
//
//================================================================================

#ifndef	_COLLISION_PAIR_CHECK_H_
#define _COLLISION_PAIR_CHECK_H_



//****************************************
// インクルード文
//****************************************
#include <vector>

#include <Component/CollisionBase/CollisionBase.h>

#include <Vector3D.h>



/*********************************************************//**
* @brief
* 衝突ペア判定クラス
*
* 衝突基底クラスのペアを判定するクラス
*************************************************************/
class CollisionPairCheck
{
//==============================
// 静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 衝突基底クラスペア判定関数
	*/
	static bool IsCheck(CollisionBase* collision0, CollisionBase* collision1);


private:
	/**
	* @brief
	* ペア判定関数
	*/
	static bool IsPair(CollisionBase* collision0, CollisionBase* collision1);

	/**
	* @brief
	* 指定した衝突ステートの検索関数
	*/
	static CollisionBase* IsState(CollisionBase::State state,
								  CollisionBase* collision0,
								  CollisionBase* collision1);

	/**
	* @brief
	* 指定したコンポーネントの逆を返す関数
	*/
	static CollisionBase* OtherSideComponent(CollisionBase* age_component,
											 CollisionBase* collision0,
											 CollisionBase* collision1);

	/**
	* @brief
	* プレイヤーのペアリスト関数
	*/
	static bool PairList_Player(CollisionBase* collision);


//==============================
// 非静的メンバ関数
//==============================
private:
	/**
	* @brief
	* コンストラクタ(削除)
	*/
	CollisionPairCheck() = delete;

	/**
	* @brief
	* コピーコンストラクタ(削除)
	*/
	CollisionPairCheck(const CollisionPairCheck& value) = delete;

	/**
	* @brief
	* 代入演算子のオーバーロード(削除)
	*/
	CollisionPairCheck& operator = (const CollisionPairCheck& value) = delete;
};



#endif