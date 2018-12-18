//================================================================================
//!	@file	 RendererFactoryDirectX9.cpp
//!	@brief	 DirectX9レンダラー生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "RendererFactoryDirectX9.h"

#include <Renderer/RendererDirectX9/RendererDirectX9.h>



//****************************************
// 関数定義
//****************************************
//----------------------------------------
RendererInterface* RendererFactoryDirectX9::Create()
{
	return new RendererDirectX9();
}