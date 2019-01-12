//================================================================================
//
//    平面ポリゴンクラスヘッダ
//    Author : Araki Kai                                作成日 : 2017/12/06
//
//================================================================================

#ifndef	_PLANE_POLYGON_H_
#define _PLANE_POLYGON_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>
#include <vector>

#include <Vector3D.h>

#include <Renderer\Renderer.h>



//======================================================================
//
// クラス宣言
//
//======================================================================

class TextureObject;



//======================================================================
//
// クラス定義
//
//======================================================================

class PlanePolygon
{
//------------------------------------------------------------
private :
	// 定数
	static const int PRIMITIVE_NUM; 


// ============================================================
public:
	// デフォルトコンストラクタ
	PlanePolygon(XColor4 color = XColor4 (1.0f, 1.0f, 1.0f, 1.0f), Vec2 plane_size = Vec2 (1.0f, 1.0f));


// ============================================================
public:
	// デストラクタ
	virtual ~PlanePolygon();


// ============================================================
public:
	// メンバ関数
	void Draw();

	void SetColor(XColor4 color);
	void SetUV(TextureObject* texture, int pattern_num = 0);

	XColor4 GetColor(){ return vertex_[0].color_; }

	unsigned getMeshNum(){return 1;}
	D3DMATERIAL9* GetMaterial(){return &material_;}


//------------------------------------------------------------
private:
	// 非公開メンバ関数
	void CreateVertex(Color4 color, Vec2 plane_size);
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
