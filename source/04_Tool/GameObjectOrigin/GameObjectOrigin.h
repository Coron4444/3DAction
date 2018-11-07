//================================================================================
//
//    ゲームオブジェクトの原点クラス
//    Author : Araki Kai                                作成日 : 2018/03/22
//
//================================================================================

#ifndef	_GAME_OBJECT_ORIGIN_H_
#define _GAME_OBJECT_ORIGIN_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../Component/UpdateComponent/UpdateComponent.h"
#include "../Component/DrawComponent/DrawComponent.h"
#include "../Component/CollisionComponent/CollisionComponent.h"

#include <Transform\Transform.h>
#include <Physics\Physics.h>
#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	GameObjectOrigin(bool is_registration = true);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	virtual ~GameObjectOrigin();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// マネージャー用
	virtual void Reset() = 0;
	void ReleaseObject();
	
	// セッタ
	void SetComponentAll(UpdateComponent* update_component, DrawComponent* draw_component, CollisionComponent* collision_component)
	{
		SetUpdateComponent(update_component);
		SetDrawComponent(draw_component);
		SetCollisionComponent(collision_component);
	}
	void SetUpdateComponent(UpdateComponent* component)		  {update_component_ = component;}
	void SetDrawComponent(DrawComponent* component)			  {draw_component_ = component;}
	void SetCollisionComponent(CollisionComponent* component) {collision_component_ = component;}

	// ゲッタ
	UpdateComponent*	GetUpdateComponent()	{return update_component_;}
	DrawComponent*		GetDrawComponent()		{return draw_component_;}
	CollisionComponent* GetCollisionComponent() {return collision_component_;}

	Transform* GetTransform(){return &transform_;}
	
	// 剛体
	void CreatePhysics()
	{
		if (physics_ != nullptr) return;
		physics_ = new Physics(this);
	}

	Physics* GetPhysics(){return physics_;}


//############################################################
protected :
	// スーパークラス
	void Init_SuperClass(UpdateComponent* update_component, DrawComponent* draw_component, CollisionComponent* collision_component);
	void Uninit_SuperClass();
	
	// サブクラス
	virtual void Uninit() = 0;

	// コンポーネント
	void SetGameObject();
	void InitComponent();
	void UninitComponent();
	void RegistrationComponentManager();
	void ReleaseComponentManager();


//------------------------------------------------------------
private :
	// 非公開メンバ変数
	Transform transform_;
	Physics*  physics_;

	bool is_registration_;

	UpdateComponent*    update_component_;
	DrawComponent*      draw_component_;
	CollisionComponent* collision_component_;
};



#endif
