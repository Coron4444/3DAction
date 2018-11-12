//================================================================================
//
//    衝突マネージャークラス
//    Author : Araki Kai                                作成日 : 2018/04/17
//
//================================================================================

#ifndef	_COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <LimitedPointerArray\LimitedPointerArray.h>



//****************************************
// クラス宣言
//****************************************
class CollisionBase;
class CollisionObject;
class GameObjectBase;
class MeshPlanePolygon;



/*********************************************************//**
* @brief
* 衝突マネージャークラス
*
* 登録されている衝突基底クラスを管理するクラス
*************************************************************/
class CollisionManager
{
//==============================
// 定数
//==============================
public:
	static const unsigned ARRAY_NUM = 1000;		//!< 配列数


//==============================
// 非静的メンバ変数
//==============================
private:
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> all_collision_;	//!< 全衝突配列
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_add_;		//!< 追加待ち配列
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_release_;	//!< 解放待ち配列

	MeshPlanePolygon* ground_polygon_;		//!< 地面ポリゴン


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init();

	/**
	* @brief
	* 終了関数
	*/
	void Uninit();

	/**
	* @brief
	* シーン変更時の終了関数
	*/
	void UninitWhenChangeScene();

	/**
	* @brief
	* 更新関数
	*/
	void Update();

	/**
	* @brief
	* 衝突基底クラスの追加関数
	*/
	void AddCollisionBaseToArray(CollisionBase* collision);

	/**
	* @brief
	* 衝突基底クラスの上書き関数
	*/
	void OverwriteArrayCollisionBase(GameObjectBase* game_object,
									 CollisionBase* new_collision);

	/**
	* @brief
	* 衝突基底クラスの解放関数
	*/
	void ReleaseCollisionBaseFromArray(CollisionBase* collision);


	// プロパティ
	void SetGround(MeshPlanePolygon* ground_polygon);

private:
	/**
	* @brief
	* 追加待ち配列の中身を追加関数
	*/
	void AddContentsOfAwaitAddArray();

	/**
	* @brief
	* 解放待ち配列の中身を解放関数
	*/
	void ReleaseContentsOfAwaitReleaseArray();

	/**
	* @brief
	* 衝突判定関数
	*/
	void CollisionDetermination();

	/**
	* @brief
	* 地面との衝突判定関数
	*/
	void CollisionGround();

	/**
	* @brief
	* 実際の計算関数
	*/
	void ActualCalculation(CollisionBase* collision0, CollisionBase* collision1);

	/**
	* @brief
	* 衝突計算振り分け関数
	*/
	bool SortCollisionCalculation(CollisionObject* collision_object0,
								  CollisionObject* collision_object1);
};



#endif
