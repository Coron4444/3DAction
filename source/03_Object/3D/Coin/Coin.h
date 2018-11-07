//================================================================================
//
//    �R�C���N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================

#ifndef	_COIN_H_
#define _COIN_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Coin : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init(DrawComponent*      draw_component,
			  CollisionComponent* collision_component);
	void Uninit() override;
	void Reset()  override;

	PlanePolygon* GetPolygon(){return polygon_;}


//------------------------------------------------------------
private :
	// ���J�����o�ϐ�
	PlanePolygon* polygon_;
};



#endif