//================================================================================
//
//    �G�N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================

#ifndef	_ENEMY_H_
#define _ENEMY_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Polygon\CubePolygon\CubePolygon.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Enemy : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init(UpdateComponent*    update_component,
			  DrawComponent*      draw_component,
			  CollisionComponent* collision_component);
	void Uninit() override;
	void Reset()  override;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���J�����o�ϐ�
	CubePolygon* cube_polygon_;
};



#endif