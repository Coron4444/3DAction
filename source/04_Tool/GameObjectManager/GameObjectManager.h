//================================================================================
//
//    ゲームオブジェクトのマネージャクラス(static)
//    Author : Araki Kai                                作成日 : 2018/07/13
//
//================================================================================

#ifndef	_GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <LimitedPointerArray\LimitedPointerArray.h>
#include "GameObjectReferenceManager\GameObjectReferenceManager.h"



//======================================================================
//
// クラス宣言
//
//======================================================================

class GameObjectOrigin;



//======================================================================
//
// クラス定義
//
//======================================================================

class GameObjectManager
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 定数
	static const unsigned ARRAY_NUM = 1000;

//------------------------------------------------------------
private :
	// デフォルトコンストラクタ
	GameObjectManager() = delete;

	// コピーコンストラクタ
	GameObjectManager(const GameObjectManager& class_name) = delete;

	// 代入演算子のオーバーロード
	GameObjectManager& operator = (const GameObjectManager& class_name) = delete;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 静的メンバ関数
	static void Registration(GameObjectOrigin* game_object);
	static void Release		(GameObjectOrigin* game_object);
	static void ReleaseAllWaitingObjects();
	static void ReleaseAll	();
	static void ResetAll	();

	// 参照の登録
	template<class Type>
	static void GetPointer_RegistrationReference(GameObjectOrigin* reference_source,
												 Type* reference_destination,
												 Type* reference_pointer)
	{
		// 参照先の代入
		*reference_pointer = reference_destination;

		// 参照の登録
		reference_manager_.RegistrationReference(reference_source, 
												 (void*)reference_pointer, 
												 (GameObjectOrigin*)reference_destination);
	}



//------------------------------------------------------------
private :
	// 静的メンバ変数
	static LimitedPointerArray<GameObjectOrigin*, ARRAY_NUM> all_game_object_;
	static LimitedPointerArray<GameObjectOrigin*, ARRAY_NUM> all_release_game_object_;

	static GameObjectReferenceManager reference_manager_;
};



#endif
