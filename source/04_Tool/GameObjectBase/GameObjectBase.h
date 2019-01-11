//================================================================================
//
//    ゲームオブジェクト基底クラス
//    Author : Araki Kai                                作成日 : 2018/03/22
//
//================================================================================

#ifndef	_GAME_OBJECT_BASE_H_
#define _GAME_OBJECT_BASE_H_



//****************************************
// インクルード文
//****************************************
#include <SafeRelease/SafeRelease.h>
#include <Transform\Transform.h>
#include <Physics\Physics.h>

#include "../Component/Update/UpdateBase/UpdateBase.h"
#include "../Component/Draw/DrawBase/DrawBase.h"
#include "../Component/Collision/CollisionBase/CollisionBase.h"



/*********************************************************//**
* @brief
* ゲームオブジェクト基底クラス
*
* ゲームオブジェクトの基底クラス
*************************************************************/
class GameObjectBase
{
//==============================
// 非静的メンバ変数
//==============================
private:
	Transform transform_;		//!< トランスフォーム
	Physics*  physics_;			//!< 剛体

	bool is_registration_;		//!< 登録フラグ

	UpdateBase*    update_;		//!< 更新コンポーネント
	DrawBase*      draw_;		//!< 描画コンポーネント
	CollisionBase* collision_;	//!< 衝突コンポーネント



//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* コンストラクタ
	* @param
	* is_registration : 登録フラグ
	*/
	GameObjectBase(bool is_registration = true);

	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~GameObjectBase();

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit();

	/**
	* @brief
	* リセット関数
	*/
	virtual void Reset() = 0;

	/**
	* @brief
	* 剛体生成関数
	*/
	void CreatePhysics();

	// プロパティ
	Transform* GetTransform() { return &transform_; }
	Physics* GetPhysics() { return physics_; }
	void SetAllComponent(UpdateBase* value0, DrawBase* value1, CollisionBase* value2)
	{
		SetUpdate(value0);
		SetDraw(value1);
		SetCollision(value2);
	}
	UpdateBase* GetUpdate() { return update_; }
	void SetUpdate(UpdateBase* value) { update_ = value; }
	DrawBase* GetDraw() { return draw_; }
	void SetDraw(DrawBase* value) { draw_ = value; }
	CollisionBase* GetCollision() { return collision_; }
	void SetCollision(CollisionBase* value) { collision_ = value; }
	

protected:
	/**
	* @brief
	* 初期化関数
	* @param
	* update : 更新基底クラス
	* draw : 描画基底クラス
	* collision : 衝突基底クラス
	*/
	void Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision);
	
	

private:
	/**
	* @brief
	* コンポーネント初期化関数
	*/
	void InitComponent();

	/**
	* @brief
	* コンポーネント終了関数
	*/
	void UninitComponent();
};



#endif
