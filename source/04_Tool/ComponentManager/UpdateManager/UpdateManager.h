//================================================================================
//
//    更新マネージャークラス
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
// 非静的メンバ変数
//==============================
private:
	LimitedPointerArray<UpdateBase*, ARRAY_NUM> all_update_;	//!< 全更新配列
	LimitedPointerArray<UpdateBase*, ARRAY_NUM> await_add_;		//!< 追加待ち配列
	LimitedPointerArray<UpdateBase*, ARRAY_NUM> await_release_;	//!< 解放待ち配列


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init();

	/**
	* @brief
	* 終了関数
	*/
	void Uninit();

	/**
	* @brief
	* シーン変更時の終了関数
	*/
	void UninitWhenChangeScene();

	/**
	* @brief
	* 更新関数
	*/
	void Update();

	/**
	* @brief
	* 更新基底クラスの追加関数
	*/
	void AddUpdateBaseToArray(UpdateBase* update);
	
	/**
	* @brief
	* 更新基底クラスの上書き関数
	*/
	void OverwriteArrayUpdateBase(GameObjectBase* game_object, 
										 UpdateBase* new_update);
	
	/**
	* @brief
	* 更新基底クラスの解放関数
	*/
	void ReleaseUpdateBaseFromArray(UpdateBase* update);

private:
	/**
	* @brief
	* 追加待ち配列の中身を追加関数
	*/
	void AddContentsOfAwaitAddArray();

	/**
	* @brief
	* 解放待ち配列の中身を解放関数
	*/
	void ReleaseContentsOfAwaitReleaseArray();

};



#endif
