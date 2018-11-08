//================================================================================
//
//    衝突マネージャークラス(static)
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
// 静的メンバ変数
//==============================
private:
	static LimitedPointerArray<CollisionBase*, ARRAY_NUM> all_collision_;	//!< 全衝突配列
	static LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_add_;		//!< 追加待ち配列
	static LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_release_;	//!< 解放待ち配列

	static MeshPlanePolygon* ground_polygon_;		//!< 地面ポリゴン


//==============================
// 静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	static void Init();

	/**
	* @brief
	* 終了関数
	*/
	static void Uninit();

	/**
	* @brief
	* シーン変更時の終了関数
	*/
	static void UninitWhenChangeScene();

	/**
	* @brief
	* 更新関数
	*/
	static void Update();

	/**
	* @brief
	* 衝突基底クラスの追加関数
	*/
	static void AddCollisionBaseToArray(CollisionBase* collision);

	/**
	* @brief
	* 衝突基底クラスの上書き関数
	*/
	static void OverwriteArrayCollisionBase(GameObjectBase* game_object,
											CollisionBase* new_collision);

	/**
	* @brief
	* 衝突基底クラスの解放関数
	*/
	static void ReleaseCollisionBaseFromArray(CollisionBase* collision);


	// プロパティ
	static void SetGround(MeshPlanePolygon* ground_polygon);

private:
	/**
	* @brief
	* 追加待ち配列の中身を追加関数
	*/
	static void AddContentsOfAwaitAddArray();

	/**
	* @brief
	* 解放待ち配列の中身を解放関数
	*/
	static void ReleaseContentsOfAwaitReleaseArray();

	/**
	* @brief
	* 衝突判定関数
	*/
	static void CollisionDetermination();
	
	/**
	* @brief
	* 地面との衝突判定関数
	*/
	static void CollisionGround();
	
	/**
	* @brief
	* 実際の計算関数
	*/
	static void ActualCalculation(CollisionBase* collision0, CollisionBase* collision1);
	
	/**
	* @brief
	* 衝突計算振り分け関数
	*/
	static bool SortCollisionCalculation(CollisionObject* collision_object0, 
										 CollisionObject* collision_object1);



//==============================
// 非静的メンバ関数
//==============================
private:
	/**
	* @brief
	* コンストラクタ(削除)
	*/
	CollisionManager() = delete;

	/**
	* @brief
	* コピーコンストラクタ(削除)
	*/
	CollisionManager(const CollisionManager& value) = delete;

	/**
	* @brief
	* 代入演算子のオーバーロード(削除)
	*/
	CollisionManager& operator = (const CollisionManager& value) = delete;
};



#endif
