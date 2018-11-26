//================================================================================
//
//    分木空間クラス
//    Author : Araki Kai                                作成日 : 2018/11/26
//
//================================================================================

#ifndef	_SPACE_OF_TREE_H_
#define _SPACE_OF_TREE_H_



//****************************************
// インクルード文
//****************************************

#include "../ObjectOfTree/ObjectOfTree.h"



/*********************************************************//**
* @brief
* 分木空間クラス
*
* 分木の空間クラス
*************************************************************/
template <class Type>
class SpaceOfTree
{
//==============================
// 非静的メンバ変数
//==============================
private:
	ObjectOfTree<Type>* first_pointer_ = nullptr;	//!< 最初のオブジェクトポインタ


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 終了関数
	*/
	void Uninit()
	{
		if (first_pointer_ == nullptr) return;

		ResetLink(&first_pointer_);
	}

	/**
	* @brief
	* リンクのリセット関数
	* @param
	* object : リンクをリセットしたいオブジェクトのポインタのポインタ
	*/
	void ResetLink(ObjectOfTree<Type>** object)
	{
		if ((*object)->getNextPointer() != nullptr)
		{
			ResetLink((*object)->getNextPointer2());
		}

		*object = nullptr;
	}

	/**
	* @brief
	* オブジェクトの追加関数
	* @param
	* object : 追加したいオブジェクトポインタ
	*/
	void AddObject(ObjectOfTree<Type>* object)
	{
		// NULL&2重登録チェック
		if (object == nullptr) return;
		if (object->getBelongingSpace() == this) return;

		// 最初のオブジェクトポインタが登録されているかどうか
		if (first_pointer_ == nullptr)
		{
			// 最初のオブジェクトポインタに登録
			first_pointer_ = object;
		}
		else
		{
			// 最初のオブジェクトポインタを更新
			object->setNextPointer(first_pointer_);
			first_pointer_->setPreviousPointer(object);
			first_pointer_ = object;
		}

		// 空間を登録
		object->setBelongingSpace(this);
	}

	/**
	* @brief
	* 消去オブジェクトのチェック関数
	* @param
	* object : チェックしたい消去オブジェクトポインタ
	*/
	void CheckDeleteObject(ObjectOfTree<Type>* object)
	{
		if (first_pointer_ != object) return;
		if (first_pointer_ == nullptr) return;

		// 次のポインタへ挿げ替える
		first_pointer_ = first_pointer_->getNextPointer();
	}

	// プロパティ
	ObjectOfTree<Type>* getFirstObject() { return first_pointer_; }
	void setFirstObject(ObjectOfTree<Type>* value) { first_pointer_ = value; }
};



#endif
