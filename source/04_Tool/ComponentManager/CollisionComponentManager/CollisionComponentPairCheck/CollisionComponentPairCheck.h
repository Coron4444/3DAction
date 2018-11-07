//================================================================================
//
//    衝突コンポーネントペア判定クラス(static)
//    Author : Araki Kai                                作成日 : 2018/04/20
//
//================================================================================

#ifndef	_COLLISION_COMPONENT_PAIR_CHECK_H_
#define _COLLISION_COMPONENT_PAIR_CHECK_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <vector>
#include <Component\CollisionComponent\CollisionComponent.h>

#include <Vector3D.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class CollisionComponentPairCheck
{
//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	CollisionComponentPairCheck() = delete;

	// コピーコンストラクタ
	CollisionComponentPairCheck(const CollisionComponentPairCheck& class_name) = delete;

	// 代入演算子のオーバーロード
	CollisionComponentPairCheck& operator = (const CollisionComponentPairCheck& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 衝突コンポーネントペア判定
	static bool IsCheck(CollisionComponent* component_0, CollisionComponent* component_1);



//------------------------------------------------------------
private :
	// ペア判定
	static bool IsPair(CollisionComponent* component_0, CollisionComponent* component_1);
	
	// ペアリスト
	static bool PairList_Player(CollisionComponent* component);

	// 内部処理
	static CollisionComponent* IsState(CollisionComponent::State state, 
									   CollisionComponent* component_0, 
									   CollisionComponent* component_1);

	static CollisionComponent* OtherSideComponent(CollisionComponent* age_component, 
												  CollisionComponent* component_0, 
												  CollisionComponent* component_1);
};



#endif