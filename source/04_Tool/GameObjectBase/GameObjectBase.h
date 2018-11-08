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

#include "../Component/UpdateBase/UpdateBase.h"
#include "../Component/DrawBase/DrawBase.h"
#include "../Component/CollisionBase/CollisionBase.h"



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
	* リセット関数
	*/
	virtual void Reset() = 0;

	/**
	* @brief
	* オブジェクト解放関数
	*/
	void ReleaseObject();

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
	* 基底クラス初期化関数
	* @param
	* update_component : 更新コンポーネント
	* draw_component : 描画コンポーネント
	* collision_component : 衝突コンポーネント
	*/
	void BaseClassInit(UpdateBase* update, DrawBase* draw, CollisionBase* collision);
	
	/**
	* @brief
	* 基底クラス終了関数
	*/
	void BaseClassUninit();

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit() = 0;

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

	/**
	* @brief
	* コンポーネントをマネージャーへ設定関数
	*/
	void SetComponentToManager();

	/**
	* @brief
	* コンポーネントをマネージャーから解放関数
	*/
	void ReleaseComponentFromManager();

	// プロパティ
	void SetGameObjectToComponent();
};



#endif
