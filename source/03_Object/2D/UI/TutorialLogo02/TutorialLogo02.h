//================================================================================
//
//    �`���[�g���A�����S02�N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_02_H_
#define _TUTORIAL_LOGO_02_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>



//======================================================================
//
// �N���X�錾
//
//======================================================================

class PlanePolygon;



//======================================================================
//
// �N���X��`
//
//======================================================================

class TutorialLogo02 : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init(DrawComponent* draw_component);
	void Uninit() override;
	void Reset()  override;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���J�����o�ϐ�
	PlanePolygon*    plane_polygon_;
};



#endif