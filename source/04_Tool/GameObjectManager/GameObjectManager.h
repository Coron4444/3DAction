//================================================================================
//
//    ゲームオブジェクトマネージャクラス(static)
//    Author : Araki Kai                                作成日 : 2018/07/13
//
//================================================================================

#ifndef	_GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <LimitedPointerArray\LimitedPointerArray.h>
#include "GameObjectReferenceManager\GameObjectReferenceManager.h"
#include "ComponentManager/UpdateManager/UpdateManager.h"
#include "ComponentManager/DrawManager/DrawManager.h"
#include "ComponentManager/CollisionManager/CollisionManager.h"



//****************************************
// クラス宣言
//****************************************
class GameObjectBase;



/*********************************************************//**
* @brief
* ゲームオブジェクトマネージャクラス
*
* ゲームオブジェクト全体の管理をするクラス
*************************************************************/
class GameObjectManager
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
	static LimitedPointerArray<GameObjectBase*, ARRAY_NUM> all_game_object_;	//!< 全ゲームオブジェクト配列
	static LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_add_;			//!< 追加待ち配列
	static LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_release_;		//!< 解放待ち配列

	static GameObjectReferenceManager reference_manager_;	//!< 参照マネージャ
	static UpdateManager update_manager_;					//!< 更新マネージャ
	static DrawManager draw_manager_;						//!< 描画マネージャ
	static CollisionManager collision_manager_;				//!< 衝突マネージャ


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
	* 描画関数
	*/
	static void Draw();

	/**
	* @brief
	* 全ゲームオブジェクトリセット関数
	*/
	static void AllReset();

	/**
	* @brief
	* ゲームオブジェクト基底クラスの追加関数
	*/
	static void AddGameObjectBaseToArray(GameObjectBase* game_object);

	/**
	* @brief
	* ゲームオブジェクト基底クラスの解放関数
	*/
	static void ReleaseGameObjectBaseFromArray(GameObjectBase* game_object);

	/**
	* @brief
	* ゲームオブジェクト参照の取得
	*/
	template<class Type>
	static void GetPointer_RegistrationReference(GameObjectBase* reference_object,
												 Type* reference_destination,
												 Type* reference_pointer)
	{
		// 参照先の代入
		*reference_pointer = reference_destination;

		// 参照の登録
		reference_manager_.RegistrationReference(reference_object,
			(void*)reference_pointer,
												 (GameObjectBase*)reference_destination);
	}

	// プロパティ
	static UpdateManager* GetUpdateManager() { return &update_manager_; }
	static DrawManager* GetDrawManager() { return &draw_manager_; }
	static CollisionManager* GetCollisionManager() { return &collision_manager_; }


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
	* コンポーネントをマネージャーへ設定関数
	*/
	static void SetComponentToManager(GameObjectBase* game_object);

	/**
	* @brief
	* コンポーネントをマネージャーから解放関数
	*/
	static void ReleaseComponentFromManager(GameObjectBase* game_object);

	/**
	* @brief
	* 全ゲームオブジェクトの解放関数
	*/
	static void AllRelease();


//==============================
// 非静的メンバ関数
//==============================
private:
	/**
	* @brief
	* コンストラクタ(削除)
	*/
	GameObjectManager() = delete;

	/**
	* @brief
	* コピーコンストラクタ(削除)
	*/
	GameObjectManager(const GameObjectManager& value) = delete;

	/**
	* @brief
	* 代入演算子のオーバーロード(削除)
	*/
	GameObjectManager& operator = (const GameObjectManager& value) = delete;
};



#endif
