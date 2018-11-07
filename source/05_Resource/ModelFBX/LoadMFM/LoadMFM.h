//================================================================================
//
//    FBXモデルクラスヘッダ
//    Author : Araki Kai, Munesada                         作成日 : 2018/01/19
//
//================================================================================

#ifndef _LOAD_MFM_H_
#define _LOAD_MFM_H_



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include <Windows.h>
#include <vector>



//**********************************************************************
//
// 構造体定義&クラス定義
//
//**********************************************************************

const int MFM_BONE_MAX = 4;



//**********************************************************************
//
// 構造体定義&クラス定義
//
//**********************************************************************

namespace mfmlib
{
	// float3つ
	struct Float3
	{
		float x;
		float y;
		float z;
	};
	
	// float2つ
	struct Float2
	{
		float U;
		float V;
	};
	
	// マテリアルカラー
	struct COLOR
	{
		Float3 Ambient;
		Float3 Diffuse;
		Float3 Emissive;
		Float3 Specular;
		Float3 Bump;
		float  Transparency;
		float  Shininess;
		float  Reflectivity;
	};
	
	// 4×4行列
	struct MATRIX4D
	{
	public:
		void  Set(int r, int c, float in) {Element[r][c] = in;}
		float Get(int r, int c)			  {return Element[r][c];}
	private:
		float Element[4][4];
	};
	
	
	// 重み
	struct Weight
	{
	public:
		float weight[MFM_BONE_MAX];
		int   index [MFM_BONE_MAX];	//directxでつかうときはunsignedだけど正の数しかはいらんからたぶん大丈夫
	};
	
	
	// マテリアル
	struct Material
	{
		COLOR Color;
		TCHAR pTexName[MAX_PATH];
	};
	
	// 行列
	class MATRIX
	{
	public:
		int Num;
		std::vector<MATRIX4D> Data;
	};
	
	// float型データ管理
	class FloatData
	{
	public:
		void  SetNum(float in) {Num = in;}
		float GetNum()         {return Num;}
	private:
		float Num;
	};

	// float3つvector
	class Float3pData
	{
	public:
		int Num;
		std::vector<Float3> Data;
	};

	// float2つvector
	class Float2pData
	{
	public:
		int Num;
		std::vector<Float2> Data;
	};

	// float1つvector
	class Float1pData
	{
	public:
		FloatData Num;
		std::vector<float> Data;
	};

	// int型vector
	class IntpData
	{
	public:
		int Num;
		std::vector<int> Data;
	};

	// 頂点のボーンの重み
	class VertexBoneWeight
	{
	public:
		int Num;
		std::vector<Weight> Data;
	};

	// ボーンアニメ行列
	class BoneAnim
	{
	public:
		MATRIX4D init;
		MATRIX   perFrame;
	};
	
	// ボーンメッシュ
	class BoneMesh
	{
	public:
		int BoneNum;
		std::vector<BoneAnim> Data;
		VertexBoneWeight VertexData;
	};

	// メッシュ
	class Mesh
	{
	public:
		//データを出し入れするクラス群
		Float3pData Vertex;
		Float3pData Normals;
		Float2pData TexUV;
		IntpData Index;
		int MaterialIndex;
		int PrimitiveIndex;
	};
	
	// MFModel
	class Model
	{
	public:
		int						materialNum;	//マテリアル数
		int						MeshNum;		//メッシュ数
		int						FrameNum;		//アニメーションのフレーム数
		std::vector<Mesh>		MeshData;		//メッシュの実データ
		std::vector<Material>	MaterialData;	//マテリアルの実データ
		std::vector<BoneMesh>	BoneData;

		//データをファイルから出し入れする関数
		void SetFileName     (TCHAR* File_name);
		bool FileSaveMeshData();
		bool FileLoadMeshData(TCHAR* File_name);
		bool FileSaveFullData();
		bool FileLoadFullData(TCHAR* File_name);
	private:
		std::string Filename;
	};
	
}



#endif
