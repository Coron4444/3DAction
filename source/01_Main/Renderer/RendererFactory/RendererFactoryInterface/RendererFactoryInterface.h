//================================================================================
//!	@file	 RendererFactoryInterface.h
//!	@brief	 レンダラー生成InterfaceClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_FACTORY_INTERFACE_H_
#define _RENDERE_FACTORY_INTERFACE_H_



//****************************************
// クラス宣言
//****************************************
class RendererInterface;



//************************************************************														   
//! @brief   レンダラー生成InterfaceClass
//!
//! @details レンダラー生成のInterfaceClass
//************************************************************
class RendererFactoryInterface
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~RendererFactoryInterface() {}

	//----------------------------------------
	//! @brief 生成関数
	//! @details
	//! @param void なし
	//! @retval RendererInterface* レンダラーポインタ
	//----------------------------------------
	virtual RendererInterface* Create() = 0;
};



#endif