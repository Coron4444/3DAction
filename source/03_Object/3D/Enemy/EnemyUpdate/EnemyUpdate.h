//================================================================================
//
//    敵更新クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================

#ifndef	_ENEMY_UPDATE_H_
#define _ENEMY_UPDATE_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <Component/UpdateBase/UpdateBase.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class EnemyUpdate : public UpdateBase
{
//------------------------------------------------------------
private :
	// 定数
	static const float SPEED;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()		  override;
	void Uninit()	  override;
	void Update()	  override;
	void LateUpdate() override;
};



#endif