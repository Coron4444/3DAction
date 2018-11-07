//================================================================================
//
//    �`���[�g���A�����S01�N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "TutorialLogo01.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo01::Init(DrawComponent* draw_component)
{
	// �v���[���|���S���쐬
	plane_polygon_ = new PlanePolygon();

	// ���N���X�̏�����
	Init_SuperClass(nullptr, draw_component, nullptr);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo01::Uninit()
{
	// ���N���X�̏I������
	Uninit_SuperClass();

	// �e��J��
	SafeRelease::Normal(&plane_polygon_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Reset�����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TutorialLogo01::Reset()
{

}