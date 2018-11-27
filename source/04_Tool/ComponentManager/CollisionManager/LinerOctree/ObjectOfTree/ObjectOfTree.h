//================================================================================
//
//    分木オブジェクトクラス
//    Author : Araki Kai                                作成日 : 2018/11/26
//
//================================================================================

#ifndef	_OBJECT_OF_TREE_H_
#define _OBJECT_OF_TREE_H_



//****************************************
// インクルード文
//****************************************



//****************************************
// クラス宣言
//****************************************
template<class Type>
class SpaceOfTree;



/*********************************************************//**
* @brief
* 分木オブジェクトクラス
*
* 分木のオブジェクトクラス
*************************************************************/
template <class Type>
class ObjectOfTree
{
//==============================
// 非静的メンバ変数
//==============================
private:
	SpaceOfTree<Type>* belonging_space_ = nullptr;		//!< 所属空間
	Type object_ = nullptr;								//!< オブジェクト
	ObjectOfTree<Type>* previous_pointer_ = nullptr;	//!< 前ポインタ
	ObjectOfTree<Type>* next_pointer_ = nullptr;		//!< 次ポインタ


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* リストから消去する関数
	*/
	void DeleteFromList()
	{
		if (belonging_space_ == nullptr) return;

		// 所属している空間に消去を通知
		belonging_space_->CheckDeleteObject(this);

		// 前後のオブジェクトを結びつける
		if (previous_pointer_ != nullptr)
		{
			previous_pointer_->setNextPointer(next_pointer_);
		}
		if (next_pointer_ != nullptr)
		{
			next_pointer_->setPreviousPointer(previous_pointer_);
		}
		previous_pointer_ = nullptr;
		next_pointer_ = nullptr;
		belonging_space_ = nullptr;
	}

	// プロパティ
	SpaceOfTree<Type>* getBelongingSpace() { return belonging_space_; }
	void setBelongingSpace(SpaceOfTree<Type>* value) { belonging_space_ = value; }
	Type getObject() { return object_; }
	void setObject(Type value) { object_ = value; }
	ObjectOfTree<Type>* getPreviousPointer() { return previous_pointer_; }
	void setPreviousPointer(ObjectOfTree<Type>* value) { previous_pointer_ = value; }
	ObjectOfTree<Type>* getNextPointer() { return next_pointer_; }
	ObjectOfTree<Type>** getNextPointer2() { return &next_pointer_; }
	void setNextPointer(ObjectOfTree<Type>* value) { next_pointer_ = value; }
};



#endif
