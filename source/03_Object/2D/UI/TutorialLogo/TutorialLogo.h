//================================================================================
//
//    チュートリアルロゴクラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_H_
#define _TUTORIAL_LOGO_H_



//****************************************
// インクルード文
//****************************************
#include <GameObjectBase/GameObjectBase.h>



/*********************************************************//**
* @brief
* チュートリアルロゴクラス
*
* チュートリアルロゴのクラス
*************************************************************/
class TutorialLogo : public GameObjectBase
{
//==============================
// 非静的メンバ関数
//==============================
private:
	unsigned logo_num_ = 0;					//!< チュートリアル


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(DrawBase* draw);
	void Uninit() override;
	void Reset()  override;

	unsigned GetLogoNum() { return logo_num_; }
	void SetLogoNum(unsigned value) { logo_num_ = value; }
};



#endif