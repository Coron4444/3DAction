//================================================================================
//
//    ゲームオブジェクトの参照マネージャクラス
//    Author : Araki Kai                                作成日 : 2018/07/15
//
//================================================================================

#ifndef	_GAME_OBJECT_REFERENCE_MANAGER_H_
#define _GAME_OBJECT_REFERENCE_MANAGER_H_



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include <LimitedPointerArray\LimitedPointerArray.h>
#include <unordered_map>



//**********************************************************************
//
// クラス宣言
//
//**********************************************************************

class GameObjectOrigin;



//**********************************************************************
//
// クラス定義
//
//**********************************************************************

class GameObjectReferenceManager
{
// ============================================================
public : 
	// 定数
	static const unsigned ARRAY_NUM = 1000;

// ============================================================
public : 
	struct ReferenceData
	{
		// コンストラクタ
		ReferenceData(GameObjectOrigin* source, void* pointer, GameObjectOrigin* destination)
		{
			reference_source_	   = source;
			reference_destination_ = destination;
			reference_pointer_	   = pointer;
		}

		// メンバ変数
		GameObjectOrigin* reference_source_;
		GameObjectOrigin* reference_destination_;
		void*			  reference_pointer_;
		int				  registration_index_;
	};

	struct ReferenceMap
	{
		// キーのオブジェクトが参照元のマップ
		std::unordered_map<GameObjectOrigin*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> source_map_;
		
		// キーのオブジェクトが参照先のマップ
		std::unordered_map<GameObjectOrigin*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> destination_map_;
	};


// ============================================================
public :
	// デフォルトコンストラクタ
	GameObjectReferenceManager();


// ============================================================
public :
	// デストラクタ
	~GameObjectReferenceManager();


// ============================================================
public :
	// メンバ関数
	void RegistrationReference(GameObjectOrigin* source, void* pointer, GameObjectOrigin* destination);
	void ReleaseReference(GameObjectOrigin* object);
	void AllReleaseReference();



// ============================================================
private :
	// メンバ関数
	void RegistrationReference_Source(GameObjectOrigin* source, void* pointer, GameObjectOrigin* destination);
	void RegistrationReference_Destination(GameObjectOrigin* source, void* pointer, GameObjectOrigin* destination);

	void ReleaseReference_Source(GameObjectOrigin* object);
	void ReleaseReference_Destination(GameObjectOrigin* object);

	
// ============================================================
private :
	// メンバ変数
	ReferenceMap reference_map_;
};



#endif
