//================================================================================
//
//    �����N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================

#ifndef	_NUMBER_H_
#define _NUMBER_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Vector3D.h>
#include <ResourceManager\ResourceManager.h>


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

class Number : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �萔
	static const std::string TEXTURE_PATH;
	static const std::string TEXTURE_NAME;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init(DrawComponent* draw_component);
	void Uninit() override;
	void Reset()  override;

	void SetNumber(int number);
	void SetColor(XColor4 color);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���J�����o�ϐ�
	PlanePolygon* plane_polygon_;
	TextureObject* decale_texture_;

	int number_;
	int old_number_;
};



#endif