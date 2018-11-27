//================================================================================
//
//    衝突ペア判定クラス(static)
//    Author : Araki Kai                                作成日 : 2018/04/20
//
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "CollisionPairCheck.h"



//****************************************
// 静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +衝突基底クラスペア判定関数
//--------------------------------------------------
bool CollisionPairCheck::IsCheck(CollisionBase* collision0, CollisionBase* collision1)
{
	if (!IsPair(collision0, collision1)) return false;

	return true;
}



//--------------------------------------------------
// -ペア判定関数
//--------------------------------------------------
bool CollisionPairCheck::IsPair(CollisionBase* collision0, CollisionBase* collision1)
{
	// 指定したコンポーネントを格納する
	CollisionBase* temp;

	// 一方がプレイヤーの場合
	temp = IsState(CollisionBase::State::PLAYER, collision0, collision1);
	temp = OtherSideComponent(temp, collision0, collision1);

	if (temp != nullptr) return PairList_Player(temp);

	return false;
}



//--------------------------------------------------
// -指定した衝突ステートの検索関数
//--------------------------------------------------
CollisionBase* CollisionPairCheck::IsState(CollisionBase::State state,
										   CollisionBase* collision0,
										   CollisionBase* collision1)
{
	if (state == collision0->getState()) return collision0;
	if (state == collision1->getState()) return collision1;

	return nullptr;
}



//--------------------------------------------------
// -指定したコンポーネントの逆を返す関数
//--------------------------------------------------
CollisionBase* CollisionPairCheck::OtherSideComponent(CollisionBase* age_component,
													  CollisionBase* collision0,
													  CollisionBase* collision1)
{
	if (age_component == nullptr) return nullptr;
	if (age_component == collision0) return collision1;
	if (age_component == collision1) return collision0;

	return nullptr;
}



//--------------------------------------------------
// -プレイヤーのペアリスト関数
//--------------------------------------------------
bool CollisionPairCheck::PairList_Player(CollisionBase* collision)
{
	switch (collision->getState())
	{
		// 衝突を許可しない衝突コンポーネント
		case CollisionBase::State::PLAYER:
		{
			return false;
		}


		default:
		{
			return true;
		}
	}
}