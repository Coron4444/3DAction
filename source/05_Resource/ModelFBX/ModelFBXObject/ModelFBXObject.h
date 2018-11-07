//================================================================================
//
//    FBXモデルクラスオブジェクトヘッダ
//    Author : Araki Kai                                作成日 : 2018/01/19
//
//================================================================================

#ifndef	_MODEL_FBX_OBJECT_H_
#define _MODEL_FBX_OBJECT_H_



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include <string>
#include <vector>

#include <Vector3D.h>
#include <ModelFBX\LoadMFM\LoadMFM.h>



//**********************************************************************
//
// 定数定義
//
//**********************************************************************

const int MAX_MFM_BONE = 4;



//**********************************************************************
//
// クラス宣言
//
//**********************************************************************

class TextureManager;
class Model;



//**********************************************************************
//
// クラス定義
//
//**********************************************************************

class ModelFBXObject
{
// ============================================================
private :
	// 影響
	struct Impact
	{
		float         weight[MAX_MFM_BONE];
		unsigned char matrixIndex[MAX_MFM_BONE];
	};

	// 頂点構造体
	struct VERTEX_3D
	{
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Normal;
		D3DCOLOR	color;
		D3DXVECTOR2 texcoord;
		Impact		ImpactMap;
	};

	struct Shaderbuff
	{
		std::vector<VERTEX_3D> Vertex;
	};


	struct Mesh_DirectX9
	{
		int         MaterialIndex;
		int         PrimitiveNum;
		std::string TexName;
	};

	struct Bone
	{
		std::vector<D3DXMATRIX> MatAry;
	};

	class MFMANIMEDATA
	{
	public:
		std::vector<Mesh_DirectX9>			 MeshData;
		std::vector<D3DMATERIAL9>			 Material;
		std::vector<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;
		std::vector<LPDIRECT3DTEXTURE9>      Texture;
		std::vector<std::vector<Bone>>		 bone;
		int									 nAnimFrame;
	};

	


// ============================================================
public :
	// デフォルトコンストラクタ
	ModelFBXObject(TextureManager* texture_manager, const std::string* key_name, const std::string* file_path = nullptr);


// ============================================================
public :
	// デストラクタ
	virtual ~ModelFBXObject();


// ============================================================
public :
	// 公開メンバ関数
	void SetModelFBXObject();

	int GetAnimationFrameNum(const int animation_count, int animation_speed);


	void SetColor(XColor4 color);

	int  GetAnimationFrameMax(){return mfm_model_data_.nAnimFrame;}


// ============================================================
private :
	// 非公開メンバ関数
	void CreateVertex  (mfmlib::Model* temp_model, std::vector<Shaderbuff>* temp_mesh, const std::string* file_path);
	void CreateMaterial(mfmlib::Model* temp_model);

	void AccessVRAM(LPDIRECT3DDEVICE9 pDevice, std::vector<Shaderbuff>* temp_mesh);

	void RegistrationVertex(std::vector<Shaderbuff>* temp_mesh);

// ============================================================
public :
	// 公開メンバ変数
	Vec3		light_vector_;
	std::string shader_name_;


// ============================================================
private :
	// mfmモデルデータ
	MFMANIMEDATA mfm_model_data_;	
	
	// テクスチャマネージャ
	TextureManager* texture_manager_;

	// 頂点宣言
	IDirect3DVertexDeclaration9* vertex_declaration_;

	// メッシュ情報
	std::vector<Shaderbuff> mesh_;
};



#endif
