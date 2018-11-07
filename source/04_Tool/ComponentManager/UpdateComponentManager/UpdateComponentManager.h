//================================================================================
//
//    更新コンポーネントマネージャークラス(static)
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_UPDATE_COMPONENT_MANAGER_H_
#define _UPDATE_COMPONENT_MANAGER_H_



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
//======================================================================

class UpdateComponent;
class GameObjectOrigin;



//======================================================================
//
// クラス定義
//
//======================================================================

class UpdateComponentManager
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	static const unsigned ARRAY_NUM = 1000;


//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	UpdateComponentManager() = delete;

	// コピーコンストラクタ
	UpdateComponentManager(const UpdateComponentManager& class_name) = delete;

	// 代入演算子のオーバーロード
	UpdateComponentManager& operator = (const UpdateComponentManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 静的公開メンバ関数
	static void Init();
	static void Uninit();
	static void Uninit_ChangeScene();
	static void Update();

	static void RegistrationComponent(UpdateComponent* update_component);
	static void OverwriteComponent	 (GameObjectOrigin* game_object, UpdateComponent* new_update_component);
	static void ReleaseComponent	 (UpdateComponent* update_component);

	
//------------------------------------------------------------
private :
	// 静的非公開メンバ関数
	static void RegistrationUpdateComponentALL();
	static void ReleaseUpdateComponentALL();


//------------------------------------------------------------
private :
	// 静的メンバ変数
	static LimitedPointerArray<UpdateComponent*, ARRAY_NUM> all_update_component_;
	static LimitedPointerArray<UpdateComponent*, ARRAY_NUM> registration_;
	static LimitedPointerArray<UpdateComponent*, ARRAY_NUM> release_;
};



#endif
