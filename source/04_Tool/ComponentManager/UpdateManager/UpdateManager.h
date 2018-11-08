//================================================================================
//
//    更新マネージャークラス(static)
//    Author : Araki Kai                                作成日 : 2018/03/26
//
//================================================================================

#ifndef	_UPDATE_MANAGER_H_
#define _UPDATE_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <LimitedPointerArray\LimitedPointerArray.h>


//****************************************
// クラス宣言
//****************************************
class UpdateBase;
class GameObjectBase;



/*********************************************************//**
* @brief
* 更新マネージャークラス
*
* 登録されている更新基底クラスを管理するクラス
*************************************************************/
class UpdateManager
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
	static LimitedPointerArray<UpdateBase*, ARRAY_NUM> all_update_;		//!< 全更新配列
	static LimitedPointerArray<UpdateBase*, ARRAY_NUM> await_add_;		//!< 追加待ち配列
	static LimitedPointerArray<UpdateBase*, ARRAY_NUM> await_release_;	//!< 解放待ち配列


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
	* 更新基底クラスの追加関数
	*/
	static void AddUpdateBaseToArray(UpdateBase* update);
	
	/**
	* @brief
	* 更新基底クラスの上書き関数
	*/
	static void OverwriteArrayUpdateBase(GameObjectBase* game_object, 
										 UpdateBase* new_update);
	
	/**
	* @brief
	* 更新基底クラスの解放関数
	*/
	static void ReleaseUpdateBaseFromArray(UpdateBase* update);

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


//==============================
// 非静的メンバ関数
//==============================
private :
	/**
	* @brief
	* コンストラクタ(削除)
	*/
	UpdateManager() = delete;

	/**
	* @brief
	* コピーコンストラクタ(削除)
	*/
	UpdateManager(const UpdateManager& value) = delete;

	/**
	* @brief
	* 代入演算子のオーバーロード(削除)
	*/
	UpdateManager& operator = (const UpdateManager& value) = delete;
};



#endif
