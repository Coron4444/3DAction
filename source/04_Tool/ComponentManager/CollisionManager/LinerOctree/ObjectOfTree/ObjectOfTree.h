//================================================================================
//!	@file	 ObjectOfTree.h
//!	@brief	 分木オブジェクトClass
//! @details template
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_OBJECT_OF_TREE_H_
#define _OBJECT_OF_TREE_H_



//****************************************
// クラス宣言
//****************************************
template<class Type>
class SpaceOfTree;



//************************************************************														   
//! @brief   分木オブジェクトClass
//!
//! @details 分木のオブジェクトClass(template)
//************************************************************
template <class Type>
class ObjectOfTree
{
//====================
// 変数
//====================
private:
	SpaceOfTree<Type>* belonging_space_ = nullptr;	//!< 所属空間
	Type object_ = nullptr;							//!< オブジェクト
	ObjectOfTree<Type>* previous_ = nullptr;		//!< 前分木オブジェクト
	ObjectOfTree<Type>* next_ = nullptr;			//!< 次分木オブジェクト


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 所属空間取得関数
	//! @details
	//! @param void なし
	//! @retval SpaceOfTree<Type>* 所属空間
	//----------------------------------------
	SpaceOfTree<Type>* getpBelongingSpace() 
	{
		return belonging_space_; 
	}
	
	//----------------------------------------
	//! @brief 所属空間設定関数
	//! @details
	//! @param *value 所属空間
	//! @retval void なし
	//----------------------------------------
	void setBelongingSpace(SpaceOfTree<Type>* value) 
	{
		belonging_space_ = value; 
	}
	
	//----------------------------------------
	//! @brief オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval Type オブジェクト
	//----------------------------------------
	Type getObject() 
	{
		return object_; 
	}
	
	//----------------------------------------
	//! @brief オブジェクト設定関数
	//! @details
	//! @param value オブジェクト
	//! @retval void なし
	//----------------------------------------
	void setObject(Type value)
	{ 
		object_ = value; 
	}
	
	//----------------------------------------
	//! @brief 前分木オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval SpaceOfTree<Type>* 前分木オブジェクト
	//----------------------------------------
	ObjectOfTree<Type>* getpPrevious() 
	{
		return previous_; 
	}
	
	//----------------------------------------
	//! @brief 前分木オブジェクト設定関数
	//! @details
	//! @param *value 前分木オブジェクト
	//! @retval void なし
	//----------------------------------------
	void setPrevious(ObjectOfTree<Type>* value) 
	{ 
		previous_ = value; 
	}

	//----------------------------------------
	//! @brief 後分木オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval SpaceOfTree<Type>* 後分木オブジェクト
	//----------------------------------------
	ObjectOfTree<Type>* getpNext() 
	{ 
		return next_; 
	}
	
	//----------------------------------------
	//! @brief 後分木オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval SpaceOfTree<Type>** 後分木オブジェクト
	//----------------------------------------
	ObjectOfTree<Type>** getp2Next() 
	{
		return &next_; 
	}
	
	//----------------------------------------
	//! @brief 後分木オブジェクト設定関数
	//! @details
	//! @param *value 後分木オブジェクト
	//! @retval void なし
	//----------------------------------------
	void setNext(ObjectOfTree<Type>* value)
	{
		next_ = value; 
	}


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief リストから消去する関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DeleteFromList()
	{
		if (belonging_space_ == nullptr) return;

		// 所属している空間に消去を通知
		belonging_space_->CheckDeleteObject(this);

		// 前後のオブジェクトを結びつける
		if (previous_ != nullptr)
		{
			previous_->setNext(next_);
		}
		if (next_ != nullptr)
		{
			next_->setPrevious(previous_);
		}
		previous_ = nullptr;
		next_ = nullptr;
		belonging_space_ = nullptr;
	}
};



#endif
