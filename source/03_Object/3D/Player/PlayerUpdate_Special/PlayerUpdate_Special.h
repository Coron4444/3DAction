//================================================================================
//
//    �v���C���[�X�V�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================

#ifndef	_PLAYER_UPDATE_SPECIAL_H_
#define _PLAYER_UPDATE_SPECIAL_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../Player.h"

#include <Component\UpdateComponent\UpdateComponent.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class PlayerUpdate_Special : public UpdateComponent
{
//------------------------------------------------------------
private :
	// �萔
	static const float SPEED;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()		  override;
	void Uninit()	  override;
	void Update()	  override;
	void LateUpdate() override;
	void Debug()      override;


//------------------------------------------------------------
private :
	Player* player_;

};



#endif