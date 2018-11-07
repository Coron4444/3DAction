//================================================================================
//
//    �v�b�V���X�y�[�X���S�X�V�N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================

#ifndef	_PUSH_SPACE_LOGO_UPDATE_H_
#define _PUSH_SPACE_LOGO_UPDATE_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../PushSpaceLogo.h"

#include <Component\UpdateComponent\UpdateComponent.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class PushSpaceLogoUpdate : public UpdateComponent
{
//------------------------------------------------------------
private :
	// �萔
	static const int CHANGE_NUM;


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
	PushSpaceLogo* push_space_logo_;
	int change_count_;
	XColor4 color_;

};



#endif