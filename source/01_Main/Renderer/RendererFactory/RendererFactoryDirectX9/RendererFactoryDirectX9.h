//================================================================================
//!	@file	 RendererFactoryDirectX9.h
//!	@brief	 DirectX9レンダラー生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_FACTORY_DIRECTX9_H_
#define _RENDERE_FACTORY_DIRECTX9_H_



//****************************************
// インクルード文
//****************************************
#include "../RendererFactoryInterface/RendererFactoryInterface.h"



//****************************************
// クラス宣言
//****************************************
class RendererInterface;



//************************************************************														   
//! @brief   DirectX9レンダラー生成Class
//!
//! @details DirectX9レンダラーの生成Class
//************************************************************
class RendererFactoryDirectX9 : public RendererFactoryInterface
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 生成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	RendererInterface* Create() override;
};



#endif