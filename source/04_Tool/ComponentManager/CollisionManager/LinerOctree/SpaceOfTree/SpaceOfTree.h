//================================================================================
//!	@file	 SpaceOfTree.h
//!	@brief	 分木空間Class
//! @details template
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_SPACE_OF_TREE_H_
#define _SPACE_OF_TREE_H_



//****************************************
// インクルード文
//****************************************
#include "../ObjectOfTree/ObjectOfTree.h"



//************************************************************														   
//! @brief   分木空間Class
//!
//! @details 分木の空間Class(template)
//************************************************************
template <class Type>
class SpaceOfTree
{
//====================
// 変数
//====================
private:
	ObjectOfTree<Type>* first_object_ = nullptr;	//!< 最初のオブジェクト


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 最初のオブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval ObjectOfTree<Type>* 最初のオブジェクト
	//----------------------------------------
	ObjectOfTree<Type>* getFirstObject() 
	{ 
		return first_object_; 
	}

	//----------------------------------------
	//! @brief 最初のオブジェクト設定関数
	//! @details
	//! @param *value 最初のオブジェクト
	//! @retval void なし
	//----------------------------------------
	void setFirstObject(ObjectOfTree<Type>* value) 
	{ 
		first_object_ = value;
	}


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit()
	{
		if (first_object_ == nullptr) return;

		ResetLink(&first_object_);
	}

	//----------------------------------------
	//! @brief リンクのリセット関数
	//! @details
	//! @param **object リンクをリセットしたいオブジェクト
	//! @retval void なし
	//----------------------------------------
	void ResetLink(ObjectOfTree<Type>** object)
	{
		if ((*object)->getpNext() != nullptr)
		{
			ResetLink((*object)->getp2Next());
		}

		*object = nullptr;
	}

	//----------------------------------------
	//! @brief オブジェクトの追加関数
	//! @details
	//! @param *object 追加したいオブジェクト
	//! @retval void なし
	//----------------------------------------
	void AddObject(ObjectOfTree<Type>* object)
	{
		// NULL&2重登録チェック
		if (object == nullptr) return;
		if (object->getpBelongingSpace() == this) return;

		// 最初のオブジェクトポインタが登録されているかどうか
		if (first_object_ == nullptr)
		{
			// 最初のオブジェクトポインタに登録
			first_object_ = object;
		}
		else
		{
			// 最初のオブジェクトポインタを更新
			object->setNext(first_object_);
			first_object_->setPrevious(object);
			first_object_ = object;
		}

		// 空間を登録
		object->setBelongingSpace(this);
	}

	//----------------------------------------
	//! @brief 消去オブジェクトのチェック関数
	//! @details
	//! @param *object チェックしたい消去オブジェクト
	//! @retval void なし
	//----------------------------------------
	void CheckDeleteObject(ObjectOfTree<Type>* object)
	{
		if (first_object_ != object) return;
		if (first_object_ == nullptr) return;

		// 次のポインタへ挿げ替える
		first_object_ = first_object_->getpNext();
	}
};



#endif
