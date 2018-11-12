//================================================================================
//
//    数字クラス
//    Author : Araki Kai                                作成日 : 2018/06/19
//
//================================================================================

#ifndef	_NUMBER_H_
#define _NUMBER_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <GameObjectBase/GameObjectBase.h>

#include <Vector3D.h>
#include <ResourceManager\ResourceManager.h>


//======================================================================
//
// クラス宣言
//
//======================================================================

class PlanePolygon;



//======================================================================
//
// クラス定義
//
//======================================================================

class Number : public GameObjectBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 定数
	static const std::string TEXTURE_PATH;
	static const std::string TEXTURE_NAME;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(DrawBase* draw);
	void Uninit() override;
	void Reset()  override;

	void SetNumber(int number);
	void SetColor(XColor4 color);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ変数
	PlanePolygon* plane_polygon_;
	TextureObject* decale_texture_;

	int number_;
	int old_number_;
};



#endif