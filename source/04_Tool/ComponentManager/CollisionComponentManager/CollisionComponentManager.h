//================================================================================
//
//    衝突コンポーネントマネージャークラス(static)
//    Author : Araki Kai                                作成日 : 2018/04/17
//
//================================================================================

#ifndef	_COLLISION_COMPONENT_MANAGER_H_
#define _COLLISION_COMPONENT_MANAGER_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <LimitedPointerArray\LimitedPointerArray.h>



//======================================================================
//
// クラス宣言
//
//**********************************************************************

class CollisionComponent;
class CollisionObject;
class GameObjectOrigin;
class MeshPlanePolygon;


//======================================================================
//
// クラス定義
//
//======================================================================

class CollisionComponentManager
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	static const unsigned ARRAY_NUM = 1000;


//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	CollisionComponentManager() = delete;

	// コピーコンストラクタ
	CollisionComponentManager(const CollisionComponentManager& class_name) = delete;

	// 代入演算子のオーバーロード
	CollisionComponentManager& operator = (const CollisionComponentManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 静的公開メンバ関数
	static void Init();
	static void Uninit();
	static void Uninit_ChangeScene();
	static void Update();

	static void RegistrationComponent(CollisionComponent* collision_component);
	static void OverwriteComponent   (GameObjectOrigin* game_object, CollisionComponent* new_collision_component);
	static void ReleaseComponent	 (CollisionComponent* collision_component);

	// 地面
	static void SetGround(MeshPlanePolygon* ground_polygon);
	

//------------------------------------------------------------
private :
	// 静的非公開メンバ関数
	static void ReleaseUpdateComponentALL();
	static void CollisionDetermination();
	static void CollisionGround();
	static void ActualCalculation		(CollisionComponent* collision_component_0, CollisionComponent* collision_component_1);
	static bool SortCollisionCalculation(CollisionObject* collision_object_0, CollisionObject* collision_object_1);

//------------------------------------------------------------
private :
	// 静的メンバ変数
	static LimitedPointerArray<CollisionComponent*, ARRAY_NUM> all_collision_component_;
	static LimitedPointerArray<CollisionComponent*, ARRAY_NUM> release_;

	// 地面ポリゴン
	static MeshPlanePolygon* ground_polygon_;
};



#endif
