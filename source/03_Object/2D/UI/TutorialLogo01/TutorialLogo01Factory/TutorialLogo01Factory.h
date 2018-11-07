//================================================================================
//
//    �`���[�g���A�����S01�t�@�N�g���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_01_FACTORY_H_
#define _TUTORIAL_LOGO_01_FACTORY_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../TutorialLogo01.h"
#include "../TutorialLogo01Draw/TutorialLogo01Draw.h"



//======================================================================
//
// �N���X��`
//
//======================================================================

class TutorialLogo01Factory
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	TutorialLogo01* Create()
	{
		TutorialLogo01* temp = new TutorialLogo01();

		// ������
		temp->Init(new TutorialLogo01Draw());

		return temp;
	}
};



#endif