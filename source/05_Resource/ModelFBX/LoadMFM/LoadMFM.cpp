//================================================================================
//
//    FBXモデルクラスヘッダ
//    Author : Araki Kai, Munesada                         作成日 : 2018/01/19
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "LoadMFM.h"



//**********************************************************************
//
// 非静的メンバ関数定義
//
//**********************************************************************

namespace mfmlib
{
	//================================================================================
	//
	// [ ファイル名設定関数( MFModel ) ]
	//
	//================================================================================

	void Model::SetFileName(TCHAR* File_name)
	{
		this->Filename.append(File_name);
	}



	//================================================================================
	//
	// [ メッシュセーブ関数( MFModel ) ]
	//
	//================================================================================
	
	bool Model::FileSaveMeshData()
	{
		FILE *fp = NULL;
		
		if ((fp = fopen(&this->Filename[0], "wb")) == NULL)
		{
			printf("ファイル(%s)が開けませんでした", &this->Filename[0]);
			return true;
		}

		int nBuff = NULL;
		Float3 fBuff;
		Float2 f2Buff;
		
		//Mesh数を渡す
		fwrite(&this->MeshNum, sizeof(int), 1, fp);

		for (size_t i = 0; i < (size_t)this->MeshNum; i++)
		{
			fwrite(&this->MeshData[i].MaterialIndex,  sizeof(int), 1, fp);
			fwrite(&this->MeshData[i].PrimitiveIndex, sizeof(int), 1, fp);
			fwrite(&this->MeshData[i].Vertex, sizeof(int), 1, fp);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Vertex.Num; j++)
			{
				fBuff = this->MeshData[i].Vertex.Data[j];
				fwrite(&fBuff, sizeof(Float3), 1, fp);
			}
			fwrite(&this->MeshData[i].Index.Num, sizeof(int), 1, fp);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Index.Num; j++)
			{
				nBuff = this->MeshData[i].Index.Data[j];
				fwrite(&nBuff, sizeof(int), 1, fp);
			}
			fwrite(&this->MeshData[i].Normals.Num, sizeof(int), 1, fp);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Normals.Num; j++)
			{
				fBuff = this->MeshData[i].Normals.Data[j];
				fwrite(&fBuff, sizeof(Float3), 1, fp);
			}
			fwrite(&this->MeshData[i].TexUV.Num, sizeof(int), 1, fp);
			for (size_t j = 0; j < (size_t)this->MeshData[i].TexUV.Num; j++)
			{
				f2Buff = this->MeshData[i].TexUV.Data[j];
				fwrite(&f2Buff, sizeof(Float2), 1, fp);
			}
		}
		fwrite(&this->materialNum, sizeof(int), 1, fp);
		for (size_t i = 0; i < (size_t)this->materialNum; i++)
		{
			fwrite(&this->MaterialData[i].Color.Ambient,	  sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Bump,         sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Diffuse,      sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Emissive,     sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Reflectivity, sizeof(float),  1, fp);
			fwrite(&this->MaterialData[i].Color.Specular,	  sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Shininess,	  sizeof(float),  1, fp);
			fwrite(&this->MaterialData[i].Color.Transparency, sizeof(float),  1, fp);
			fwrite(this->MaterialData[i].pTexName,			  sizeof(TCHAR), MAX_PATH, fp);
		
		}

		fclose(fp);
		return false;
	}
	
	
	
	//================================================================================
	//
	// [ メッシュロード関数( MFModel ) ]
	//
	//================================================================================
	
	bool Model::FileLoadMeshData(TCHAR* File_name)
	{
		FILE *fp = NULL;

		if ((fp = fopen(File_name, "rb")) == NULL)
		{
			printf("ファイルが開けませんでした");
			return true;
		}
		//Mesh数を受け取る
		fread(&this->MeshNum, sizeof(int), 1, fp);
		this->MeshData.resize(this->MeshNum);
		for (size_t i = 0; i < (size_t)this->MeshNum; i++)
		{

			fread(&this->MeshData[i].MaterialIndex,  sizeof(int), 1, fp);
			fread(&this->MeshData[i].PrimitiveIndex, sizeof(int), 1, fp);
			fread(&this->MeshData[i].Vertex.Num,     sizeof(int), 1, fp);
			this->MeshData[i].Vertex.Data.resize(this->MeshData[i].Vertex.Num);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Vertex.Num; j++)
			{
				fread(&this->MeshData[i].Vertex.Data[j], sizeof(Float3), 1, fp);

			}

			fread(&this->MeshData[i].Index.Num, sizeof(int), 1, fp);
			this->MeshData[i].Index.Data.resize(this->MeshData[i].Index.Num);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Index.Num; j++)
			{
				fread(&this->MeshData[i].Index.Data[j], sizeof(int), 1, fp);
			}

			fread(&this->MeshData[i].Normals.Num, sizeof(int), 1, fp);
			this->MeshData[i].Normals.Data.resize(this->MeshData[i].Normals.Num);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Normals.Num; j++)
			{
				fread(&this->MeshData[i].Normals.Data[j], sizeof(Float3), 1, fp);
			}

			fread(&this->MeshData[i].TexUV.Num, sizeof(int), 1, fp);
			this->MeshData[i].TexUV.Data.resize(this->MeshData[i].TexUV.Num);
			for (size_t j = 0; j < (size_t)this->MeshData[i].TexUV.Num; j++)
			{
				fread(&this->MeshData[i].TexUV.Data[j], sizeof(Float2), 1, fp);
			}
		}
	
		fread(&this->materialNum, sizeof(int), 1, fp);
		this->MaterialData.resize(this->materialNum);
		for (size_t i = 0; i < (size_t)this->materialNum; i++)
		{
			fread(&this->MaterialData[i].Color.Ambient,		 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Bump,		 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Diffuse,		 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Emissive,	 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Specular,	 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Reflectivity, sizeof(float),  1, fp);
			fread(&this->MaterialData[i].Color.Shininess,	 sizeof(float),  1, fp);
			fread(&this->MaterialData[i].Color.Transparency, sizeof(float),  1, fp);
			fread(&this->MaterialData[i].pTexName,			 sizeof(TCHAR), MAX_PATH, fp);
			printf("%s\n", this->MaterialData[i].pTexName);
		}
		fclose(fp);

		return false;
		
	}

	//================================================================================
	//
	// [ アニメーション込みのデータセーブ関数( MFModel ) ]
	//
	//================================================================================

	bool Model::FileSaveFullData()
	{
		FILE *fp = NULL;

		if ((fp = fopen(&this->Filename[0], "wb")) == NULL)
		{
			printf("ファイル(%s)が開けませんでした", &this->Filename[0]);
			return true;
		}
		//Mesh数を渡す
		fwrite(&this->MeshNum, sizeof(int), 1, fp);

		for (size_t i = 0; i < (size_t)this->MeshNum; i++)
		{
			fwrite(&this->MeshData[i].MaterialIndex,  sizeof(int), 1, fp);
			fwrite(&this->MeshData[i].PrimitiveIndex, sizeof(int), 1, fp);
			fwrite(&this->MeshData[i].Vertex.Num,     sizeof(int), 1, fp);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Vertex.Num; j++)
			{
				fwrite(&this->MeshData[i].Vertex.Data[j], sizeof(Float3), 1, fp);
			}
			fwrite(&this->MeshData[i].Index.Num, sizeof(int), 1, fp);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Index.Num; j++)
			{
				fwrite(&this->MeshData[i].Index.Data[j], sizeof(int), 1, fp);
			}
			fwrite(&this->MeshData[i].Normals.Num, sizeof(int), 1, fp);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Normals.Num; j++)
			{
				fwrite(&this->MeshData[i].Normals.Data[j], sizeof(Float3), 1, fp);
			}
			fwrite(&this->MeshData[i].TexUV.Num, sizeof(int), 1, fp);
			for (size_t j = 0; j < (size_t)this->MeshData[i].TexUV.Num; j++)
			{
				fwrite(&this->MeshData[i].TexUV.Data[j], sizeof(Float2), 1, fp);
			}
		}
		fwrite(&this->materialNum, sizeof(int), 1, fp);
		for (size_t i = 0; i < (size_t)this->materialNum; i++)
		{
			fwrite(&this->MaterialData[i].Color.Ambient,	  sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Bump,		  sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Diffuse,	  sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Emissive,	  sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Reflectivity, sizeof(float),  1, fp);
			fwrite(&this->MaterialData[i].Color.Specular,	  sizeof(Float3), 1, fp);
			fwrite(&this->MaterialData[i].Color.Shininess,	  sizeof(float),  1, fp);
			fwrite(&this->MaterialData[i].Color.Transparency, sizeof(float),  1, fp);
			fwrite(this->MaterialData[i].pTexName,			  sizeof(TCHAR), MAX_PATH, fp);
		}

		fwrite(&this->FrameNum, sizeof(int), 1, fp);
		//ボーンの書き出し
		for (size_t i = 0; i < (size_t)this->MeshNum; i++)
		{
			fwrite(&this->BoneData[i].BoneNum, sizeof(int), 1, fp);
			for (int cn = 0; cn < this->BoneData[i].BoneNum; cn++)
			{
				fwrite(&this->BoneData[i].Data[cn].init, sizeof(MATRIX4D), 1, fp);
				for (int fn = 0; fn < this->BoneData[i].Data[cn].perFrame.Num; fn++)
				{
					fwrite(&this->BoneData[i].Data[cn].perFrame.Data[fn], sizeof(MATRIX4D), 1, fp);
				}
			}
			fwrite(&this->BoneData[i].VertexData.Num, sizeof(int), 1, fp);
			for (int vc = 0; vc < this->BoneData[i].VertexData.Num; vc++)
			{
				for (int bc = 0; bc < MFM_BONE_MAX; bc++)
				{
					fwrite(&this->BoneData[i].VertexData.Data[vc].index[bc],  sizeof(int), 1, fp);
					fwrite(&this->BoneData[i].VertexData.Data[vc].weight[bc], sizeof(float), 1, fp);
				}
			}

		}
		fclose(fp);
		return false;
	}



	//================================================================================
	//
	// [ アニメーション込みのデータロード関数( MFModel ) ]
	//
	//================================================================================

	bool Model::FileLoadFullData(TCHAR* File_name)
	{
		FILE *fp = NULL;

		if ((fp = fopen(File_name, "rb")) == NULL)
		{
			printf("ファイルが開けませんでした");
			return true;
		}
		//Mesh数を受け取る
		fread(&this->MeshNum, sizeof(int), 1, fp);
		this->MeshData.resize(this->MeshNum);
		for (size_t i = 0; i < (size_t)this->MeshNum; i++)
		{

			fread(&this->MeshData[i].MaterialIndex,  sizeof(int), 1, fp);
			fread(&this->MeshData[i].PrimitiveIndex, sizeof(int), 1, fp);
			fread(&this->MeshData[i].Vertex.Num,	 sizeof(int), 1, fp);
			this->MeshData[i].Vertex.Data.resize(this->MeshData[i].Vertex.Num);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Vertex.Num; j++)
			{
				fread(&this->MeshData[i].Vertex.Data[j], sizeof(Float3), 1, fp);

			}
			fread(&this->MeshData[i].Index.Num, sizeof(int), 1, fp);
			this->MeshData[i].Index.Data.resize(this->MeshData[i].Index.Num);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Index.Num; j++)
			{
				fread(&this->MeshData[i].Index.Data[j], sizeof(int), 1, fp);
			}

			fread(&this->MeshData[i].Normals.Num, sizeof(int), 1, fp);
			this->MeshData[i].Normals.Data.resize(this->MeshData[i].Normals.Num);
			for (size_t j = 0; j < (size_t)this->MeshData[i].Normals.Num; j++)
			{
				fread(&this->MeshData[i].Normals.Data[j], sizeof(Float3), 1, fp);
			}

			fread(&this->MeshData[i].TexUV.Num, sizeof(int), 1, fp);
			this->MeshData[i].TexUV.Data.resize(this->MeshData[i].TexUV.Num);
			for (size_t j = 0; j < (size_t)this->MeshData[i].TexUV.Num; j++)
			{
				fread(&this->MeshData[i].TexUV.Data[j], sizeof(Float2), 1, fp);
			}
		}

		fread(&this->materialNum, sizeof(int), 1, fp);
		this->MaterialData.resize(this->materialNum);
		for (size_t i = 0; i < (size_t)this->materialNum; i++)
		{
			fread(&this->MaterialData[i].Color.Ambient,		 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Bump,		 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Diffuse,		 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Emissive,	 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Specular,	 sizeof(Float3), 1, fp);
			fread(&this->MaterialData[i].Color.Reflectivity, sizeof(float),  1, fp);
			fread(&this->MaterialData[i].Color.Shininess,	 sizeof(float),  1, fp);
			fread(&this->MaterialData[i].Color.Transparency, sizeof(float),  1, fp);
			fread(&this->MaterialData[i].pTexName,			 sizeof(TCHAR), MAX_PATH, fp);
			printf("%s\n", this->MaterialData[i].pTexName);
		}

		fread(&this->FrameNum, sizeof(int), 1, fp);
		//ボーンの読み出し
		this->BoneData.resize(this->MeshNum);
		for (size_t i = 0; i < (size_t)this->MeshNum; i++)
		{
			fread(&this->BoneData[i].BoneNum, sizeof(int), 1, fp);
			this->BoneData[i].Data.resize(this->BoneData[i].BoneNum);
			for (int cn = 0; cn < this->BoneData[i].BoneNum; cn++)
			{
				fread(&this->BoneData[i].Data[cn].init, sizeof(MATRIX4D), 1, fp);
				this->BoneData[i].Data[cn].perFrame.Num = this->FrameNum;
				this->BoneData[i].Data[cn].perFrame.Data.resize(this->FrameNum);
				for (int fn = 0; fn < this->BoneData[i].Data[cn].perFrame.Num; fn++)
				{
					fread(&this->BoneData[i].Data[cn].perFrame.Data[fn], sizeof(MATRIX4D), 1, fp);
				}
			}

			fread(&this->BoneData[i].VertexData.Num, sizeof(int), 1, fp);
			this->BoneData[i].VertexData.Data.resize(this->BoneData[i].VertexData.Num);
			for (int vc = 0; vc < this->BoneData[i].VertexData.Num; vc++)
			{
				for (int bc = 0; bc < MFM_BONE_MAX; bc++)
				{
					fread(&this->BoneData[i].VertexData.Data[vc].index[bc],  sizeof(int), 1, fp);
					fread(&this->BoneData[i].VertexData.Data[vc].weight[bc], sizeof(float), 1, fp);
				}
			}
		}
		fclose(fp);

		return false;
	}

}