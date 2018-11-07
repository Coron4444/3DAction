//================================================================================
//
//    衝突コンポーネントクラス
//    Author : Araki Kai                                作成日 : 2018/04/17
//
//================================================================================

#ifndef	_COLLISION_COMPONENT_H_
#define _COLLISION_COMPONENT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../ComponentOrigin/ComponentOrigin.h"
#include "CollisionObject\CollisionObject.h"
#include <LimitedPointerArray\LimitedPointerArray.h>
#include <Transform\Transform.h>

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



//======================================================================
//
// クラス定義
//
//======================================================================

class CollisionComponent : public ComponentOrigin
{
//------------------------------------------------------------
private :
	// 定数
	static const unsigned ARRAY_NUM = 100;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ステート
	enum State
	{
		NONE = -1,
		PLAYER,
		COIN,
		ENEMY,
		MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// コンストラクタ
	CollisionComponent(CollisionComponent::State state)
		: state_(state),
		  is_judgment_(true),
		  is_judgment_ground_(true)
	{
	}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 仮想デストラクタ
	virtual ~CollisionComponent(){}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	virtual void Uninit() override
	{
		// 判定フラグOFF
		SetIsJudgment(false);

		// 配列の中身を解放
		all_collision_object_.ReleaseObjectAndResetArray();
	}

	// 更新
	virtual void Update(){}

	// デバッグ
	virtual void Debug(){}

	// 衝突時処理
	virtual void HitCollision(CollisionComponent* hit_component, 
							  CollisionObject*    hit_opponent_object,
							  CollisionObject*    hit_myself_object)
	{
		// 使われていない引数の処理
		hit_component		= hit_component;
		hit_opponent_object = hit_opponent_object;
		hit_myself_object   = hit_myself_object;
	}

	// 非衝突時処理
	virtual void NotHitCollision(CollisionComponent* hit_component, 
							     CollisionObject*    hit_opponent_object,
							     CollisionObject*    hit_myself_object)
	{
		// 使われていない引数の処理
		hit_component		= hit_component;
		hit_opponent_object = hit_opponent_object;
		hit_myself_object   = hit_myself_object;
	}

	// 衝突オブジェクト配列の末端indexの取得
	unsigned GetEndIndexCollisionObjectArray(){return all_collision_object_.GetEndPointer();}

	// 衝突オブジェクトの取得
	CollisionObject* GetCollisionObject(unsigned index){return all_collision_object_.GetArrayObject(index);}

	// 全ての衝突用データをリセット
	void ResetHitData_AllCollisionObject()
	{
		for(unsigned i = 0; i < all_collision_object_.GetEndPointer(); i++)
		{
			all_collision_object_.GetArrayObject(i)->ResetHitData();
		}
	}

	// 衝突オブジェクト配列に追加
	void AddCollisionObject(CollisionObject* object)
	{
		all_collision_object_.AddToArray(object);
	}

	// 衝突オブジェクト配列の上書き
	void OverwriteCollisionObject(CollisionObject* old_object, 
								  CollisionObject* new_object)
	{
		all_collision_object_.OverwriteArray(old_object, new_object);
	}

	// 衝突オブジェクト配列から消去
	void ReleaseCollisionObject(CollisionObject* object)
	{
		all_collision_object_.DeleteFromArrayAndSortArray(object);
	}
	
	// 状態
	CollisionComponent::State GetState(){return state_;}

	// 判定フラグ
	void SetIsJudgment(bool is_judgment){is_judgment_ = is_judgment;}
	bool GetIsJudgment(){return is_judgment_;}

	// めり込み解消
	void EliminationOfNesting(Transform* transform, const Vec3* hit_vector)
	{
		*transform->GetPosition() += *hit_vector;
		transform->UpdateWorldMatrixISRT();
	}

	// フィールド
	void SetIsJudgmentGround(bool is_judgment){is_judgment_ = is_judgment;}
	bool GetIsJudgmentGround(){return is_judgment_;}
	virtual void HitGround(float position_y){position_y = position_y;}
	virtual void NotHitGround(float position_y){position_y = position_y;}


//------------------------------------------------------------
private :
	// 衝突オブジェクト配列
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> all_collision_object_;
	
	// 状態
	CollisionComponent::State state_;
	
	// 判定フラグ
	bool is_judgment_;
	bool is_judgment_ground_;


};



#endif