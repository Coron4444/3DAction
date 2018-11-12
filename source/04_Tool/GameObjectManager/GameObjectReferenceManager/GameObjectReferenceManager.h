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

class GameObjectBase;



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
		ReferenceData(GameObjectBase* source, void* pointer, GameObjectBase* destination)
		{
			reference_source_	   = source;
			reference_destination_ = destination;
			reference_pointer_	   = pointer;
		}

		// メンバ変数
		GameObjectBase* reference_source_;
		GameObjectBase* reference_destination_;
		void*			  reference_pointer_;
		int				  registration_index_;
	};

	struct ReferenceMap
	{
		// キーのオブジェクトが参照元のマップ
		std::unordered_map<GameObjectBase*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> source_map_;
		
		// キーのオブジェクトが参照先のマップ
		std::unordered_map<GameObjectBase*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> destination_map_;
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
	void RegistrationReference(GameObjectBase* source, void* pointer, GameObjectBase* destination);
	void ReleaseReference(GameObjectBase* object);
	void AllReleaseReference();



// ============================================================
private :
	// メンバ関数
	void RegistrationReference_Source(GameObjectBase* source, void* pointer, GameObjectBase* destination);
	void RegistrationReference_Destination(GameObjectBase* source, void* pointer, GameObjectBase* destination);

	void ReleaseReference_Source(GameObjectBase* object);
	void ReleaseReference_Destination(GameObjectBase* object);

	
// ============================================================
private :
	// メンバ変数
	ReferenceMap reference_map_;
};



#endif
