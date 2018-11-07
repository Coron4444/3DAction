//================================================================================
//
//    セーフリリースクラス(static)
//    Author : Araki Kai                                作成日 : 2018/05/08
//
//================================================================================

#ifndef	_SAFE_RELEASE_H_
#define _SAFE_RELEASE_H_



//****************************************
// インクルード文
//****************************************

#include <Windows.h>



/*********************************************************//**
* @brief
* セーフリリースクラス(static)
*
* 動的オブジェクトの安全な解放を担う関数群クラス
*************************************************************/
class SafeRelease
{
//==============================
// メンバ関数
//==============================
public:
	/**
	* @brief
	* 解放関数
	* @param
	* pointer : 解放対象のポインタ
	*/
	template <class Type>
	static void Normal(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			delete *pointer;
			*pointer = nullptr;
		}
	}

	/**
	* @brief
	* 解放関数(終了有)
	* @param
	* pointer : 解放対象のポインタ
	*/
	template <class Type>
	static void PlusUninit(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			(*pointer)->Uninit();
			delete *pointer;
			*pointer = nullptr;
		}
	}

	/**
	* @brief
	* 解放関数(Release有)
	* @param
	* pointer : 解放対象のポインタ
	*/
	template <class Type>
	static void PlusRelease(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			(*pointer)->Release();
			*pointer = nullptr;
		}
	}
};



#endif