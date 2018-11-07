//================================================================================
//
//    レンダラーファクトリーDirectX9クラス
//    Author : Araki Kai                                作成日 : 2018/11/01
//
//================================================================================

#ifndef	_RENDERE_FACTORY_DIRECTX9_H_
#define _RENDERE_FACTORY_DIRECTX9_H_



//****************************************
// インクルード文
//****************************************
#include "../RendererFactory/RendererFactory.h"
#include "../RendererDirectX9/RendererDirectX9.h"



/*********************************************************//**
* @brief
* レンダラーファクトリーDirectX9クラス
*
* レンダラーDirectX9のファクトリー
*************************************************************/
class RendererFactoryDirectX9 : public RendererFactory
{
//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 生成関数
	*/
	RendererInterface* Create() override
	{
		return new RendererDirectX9();
	}
};



#endif