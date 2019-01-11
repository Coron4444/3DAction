//================================================================================
//!	@file	 CollisionBase.h
//!	@brief	 衝突BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COLLISION_BASE_H_
#define _COLLISION_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "../../ComponentBase/ComponentBase.h"
#include "CollisionObjects/CollisionObjects.h"

#include <LimitedPointerArray/LimitedPointerArray.h>
#include <Transform/Transform.h>
#include <Vector3D.h>



//************************************************************														   
//! @brief   衝突BaseClass
//!
//! @details 衝突のBaseClass
//************************************************************
class CollisionBase : public ComponentBase
{
//====================
// 列挙型定義
//====================
public:
	// タイプ
	enum Type
	{
		NONE = -1,
		PLAYER,
		COIN,
		ENEMY,
		GOAL,
		MAX
	};


//====================
// 定数
//====================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< 配列数


//====================
// 変数
//====================
private:
	LimitedPointerArray<CollisionObjects*, ARRAY_NUM> collision_objects_;	//!< 複数衝突オブジェクト配列
	Type type_ = Type::NONE;			//!< タイプ
	bool is_judgment_ground_ = true;	//!< 地面との判定フラグ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 配列の最後の末尾のインデックス取得関数
	//! @details
	//! @param void なし
	//! @retval unsigned 配列の最後の末尾のインデックス
	//----------------------------------------
	unsigned getEndIndexOfArray();
	
	//----------------------------------------
	//! @brief 複数衝突オブジェクト取得関数
	//! @details
	//! @param index 複数衝突オブジェクトのインデックス
	//! @retval CollisionObjects* 複数衝突オブジェクト
	//----------------------------------------
	CollisionObjects* getpCollisionObjects(unsigned index);
	
	//----------------------------------------
	//! @brief タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval Type タイプ
	//----------------------------------------
	Type getType();
	
	//----------------------------------------
	//! @brief タイプ設定関数
	//! @details
	//! @param value タイプ
	//! @retval void なし
	//----------------------------------------
	void setType(Type value);
	
	//----------------------------------------
	//! @brief 地面との判定フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 地面との判定フラグ
	//----------------------------------------
	bool getIsJudgmentGround();
	
	//----------------------------------------
	//! @brief 地面との判定フラグ設定関数
	//! @details
	//! @param value 地面との判定フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsJudgmentGround(bool value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~CollisionBase() = 0;

	//----------------------------------------
	//! @brief 衝突時関数
	//! @details
	//! @param *hit_collision 相手の衝突基底クラス
	//! @param *hit_object    相手の衝突オブジェクト
	//! @param *hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject* hit_object,
							  CollisionObject* hit_my_object) = 0;

	//----------------------------------------
	//! @brief 非衝突時関数
	//! @details
	//! @param *hit_collision 相手の衝突基底クラス
	//! @param *hit_object    相手の衝突オブジェクト
	//! @param *hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject* hit_object,
								 CollisionObject* hit_my_object) = 0;

	//----------------------------------------
	//! @brief フィールドとの衝突時関数
	//! @details
	//! @param position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	virtual void HitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief フィールドとの非衝突時関数
	//! @details
	//! @param position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	virtual void NotHitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief 複数衝突オブジェクト追加関数
	//! @details
	//! @param *object 追加したい複数衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void AddCollisionObjectsToArray(CollisionObjects* object);

	//----------------------------------------
	//! @brief 複数衝突オブジェクト上書き関数
	//! @details
	//! @param *object 古い複数衝突オブジェクト
	//! @param *object 新しい複数衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void OverwriteArrayCollisionsObject(CollisionObjects* old_object,
										CollisionObjects* new_object);

	//----------------------------------------
	//! @brief 複数衝突オブジェクト解放関数
	//! @details
	//! @param *object 消去したい複数衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void ReleaseCollisionObjectsFromArray(CollisionObjects* object);

	//----------------------------------------
	//! @brief 複数衝突オブジェクト全解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseAllCollisionObjectsFromArray();

	//----------------------------------------
	//! @brief めり込み解消関数
	//! @details
	//! @param *transform  めり込みを解消したい状態
	//! @param *hit_vector めり込みベクトル
	//! @retval void なし
	//----------------------------------------
	void EliminationOfNesting(Transform* transform, const Vec3* hit_vector);
};



#endif