//================================================================================
//
//    キューブポリゴンクラスヘッダ
//    Author : Araki Kai                                作成日 : 2017/10/16
//
//================================================================================

#ifndef	_CUBE_POLYGON_H_
#define _CUBE_POLYGON_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <vector>
#include <string>

#include <Vector3D.h>

#include <Renderer\Renderer.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class CubePolygon
{
//------------------------------------------------------------
private:
	// 定数
	static const int PRIMITIVE_NUM;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// デフォルトコンストラクタ
	CubePolygon(XColor4 color = XColor4(1.0f, 1.0f, 1.0f, 1.0f));


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// デストラクタ
	~CubePolygon();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// メンバ関数
	void Draw();

	void SetColor(XColor4 color);

	unsigned getMeshNum() { return 1; }
	D3DMATERIAL9* GetMaterial() { return &material_; }



//------------------------------------------------------------
private:
	// 非公開メンバ関数
	void CreateVertex(Color4 color);
	void CreateIndex();
	void CreateMaterial();

	void AccessVRAM();

	void RegistrationVertex();
	void RegistrationIndex();


//------------------------------------------------------------
private:
	std::vector<RendererDirectX9::VERTEX_3D> vertex_;
	std::vector<WORD>      index_;

	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;
	LPDIRECT3DINDEXBUFFER9  index_buffer_;
	D3DMATERIAL9			material_;
	LPDIRECT3DDEVICE9		device_;
};



#endif
