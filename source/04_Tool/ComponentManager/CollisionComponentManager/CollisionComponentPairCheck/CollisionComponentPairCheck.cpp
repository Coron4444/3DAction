//================================================================================
//
//    衝突コンポーネントペア判定クラス(static)
//    Author : Araki Kai                                作成日 : 2018/04/20
//
//================================================================================


//======================================================================
//
// インクルード文
//
//======================================================================

#include "CollisionComponentPairCheck.h"



//======================================================================
//
// 静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 衝突判定更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CollisionComponentPairCheck::IsCheck(CollisionComponent* component_0, CollisionComponent* component_1)
{
	if (!IsPair(component_0, component_1)) return false;

	return true;
}



//--------------------------------------------------------------------------------
//
// [ 衝突相手確認関数 ]
//
//--------------------------------------------------------------------------------

bool CollisionComponentPairCheck::IsPair(CollisionComponent* component_0, CollisionComponent* component_1)
{
	// 指定したコンポーネントを格納する
	CollisionComponent* temp_component;
	
	// 一方がプレイヤーの場合
	temp_component = IsState(CollisionComponent::State::PLAYER, component_0, component_1);
	temp_component = OtherSideComponent(temp_component, component_0, component_1);
	
	if (temp_component != nullptr) return PairList_Player(temp_component);

	return false;
}



//--------------------------------------------------------------------------------
//
// [ 指定したオブジェクトタイプの検索関数 ]
//
//--------------------------------------------------------------------------------

CollisionComponent* CollisionComponentPairCheck::IsState(CollisionComponent::State state, 
														 CollisionComponent* component_0, 
														 CollisionComponent* component_1)
{
	if (state == component_0->GetState()) return component_0;
	if (state == component_1->GetState()) return component_1;

	return nullptr;
}



//--------------------------------------------------------------------------------
//
// [ 指定したコンポーネントの逆を返す関数 ]
//
//--------------------------------------------------------------------------------

CollisionComponent* CollisionComponentPairCheck::OtherSideComponent(CollisionComponent* age_component, 
																	CollisionComponent* component_0, 
																	CollisionComponent* component_1)
{
	if (age_component == nullptr) return nullptr;
	if (age_component == component_0) return component_1;
	if (age_component == component_1) return component_0;

	return nullptr;
}



//--------------------------------------------------------------------------------
//
// [ プレイヤーのペアリスト関数 ]
//
//--------------------------------------------------------------------------------

bool CollisionComponentPairCheck::PairList_Player(CollisionComponent* component)
{
	switch(component->GetState())
	{
		// 衝突を許可しない衝突コンポーネント
		case CollisionComponent::State::PLAYER :
		{
			return false;
		}
			

		default :
		{
			return true;
		}
	}
}