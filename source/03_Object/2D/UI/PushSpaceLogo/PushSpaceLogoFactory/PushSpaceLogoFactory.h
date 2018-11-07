//================================================================================
//
//    プッシュスペースロゴファクトリークラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================

#ifndef	_PUSH_SPACE_LOGO_FACTORY_H_
#define _PUSH_SPACE_LOGO_FACTORY_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include "../PushSpaceLogo.h"
#include "../PushSpaceLogoDraw/PushSpaceLogoDraw.h"
#include "../PushSpaceLogoUpdate/PushSpaceLogoUpdate.h"


//======================================================================
//
// クラス定義
//
//======================================================================

class PushSpaceLogoFactory
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	PushSpaceLogo* Create()
	{
		PushSpaceLogo* temp = new PushSpaceLogo();

		// 初期化
		temp->Init(new PushSpaceLogoUpdate(),
			       new PushSpaceLogoDraw());

		return temp;
	}
};



#endif