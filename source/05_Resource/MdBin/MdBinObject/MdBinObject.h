//================================================================================
//!	@file	 MdBinObject.h
//!	@brief	 バイナリーモデルオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_MD_BIN_OBJECT_H_
#define _MD_BIN_OBJECT_H_



//****************************************
// インクルード文
//****************************************
#include <windows.h>
#include <string>
#include <vector>

#include <Vector3D.h>



//****************************************
// クラス宣言
//****************************************
class TextureObject;
class MdBinDataContainer;



//************************************************************														   
//! @brief   バイナリーモデルオブジェクトClass
//!
//! @details バイナリーモデルのオブジェクトClass
//************************************************************
class MdBinObject
{
//====================
// クラス定義
//====================
public:
	//****************************************														   
	//! @brief 頂点Struct
	//!
	//! @details 頂点用のStruct
	//****************************************
	struct Vertex
	{
	//====================
	// 変数
	//====================
	public:
		Vec3   posisiont_;	//!< 座標
		Vec3   normal_;		//!< 法線
		Color4 color_;		//!< カラー
		Vec2   uv_;			//!< UV
	};

	//****************************************														   
	//! @brief メッシュClass
	//!
	//! @details メッシュのClass
	//****************************************
	class Mesh
	{
	//====================
	// 変数
	//====================
	private:
		int material_index_;								//!< マテリアルインデックス
		std::vector<WORD> index_;							//!< インデックス配列
		std::vector<Vertex> vertex_;						//!< 頂点配列
		TextureObject* diffuse_texture_object_ = nullptr;	//!< ディヒューズテクスチャオブジェクト
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer_ = nullptr;	//!< 頂点バッファ
		LPDIRECT3DINDEXBUFFER9  index_buffer_ = nullptr;	//!< インデックスバッファ


	//====================
	// プロパティ
	//====================
	public:
		//----------------------------------------
		//! @brief 頂点配列サイズ取得関数
		//! @details
		//! @param void なし 
		//! @retval int サイズ
		//----------------------------------------
		int getVertexArraySize();

		//----------------------------------------
		//! @brief 頂点配列サイズ設定関数
		//! @details
		//! @param value サイズ
		//! @retval void なし
		//----------------------------------------
		void setVertexArraySize(int value);

		//----------------------------------------
		//! @brief 頂点取得関数
		//! @details
		//! @param index インデックス
		//! @retval Vertex* 頂点
		//----------------------------------------
		Vertex* getpVertex(int index);

		//----------------------------------------
		//! @brief インデックス配列サイズ取得関数
		//! @details
		//! @param void なし 
		//! @retval int サイズ
		//----------------------------------------
		int getIndexArraySize();

		//----------------------------------------
		//! @brief インデックス配列サイズ設定関数
		//! @details
		//! @param value サイズ
		//! @retval void なし
		//----------------------------------------
		void setIndexArraySize(int value);

		//----------------------------------------
		//! @brief インデックス取得関数
		//! @details
		//! @param index インデックス
		//! @retval WORD* インデックス
		//----------------------------------------
		WORD* getpIndex(int index);

		//----------------------------------------
		//! @brief マテリアルインデックス取得関数
		//! @details
		//! @param void なし 
		//! @retval int マテリアルインデックス
		//----------------------------------------
		int getMaterialIndex();

		//----------------------------------------
		//! @brief マテリアルインデックス設定関数
		//! @details
		//! @param value マテリアルインデックス
		//! @retval void なし
		//----------------------------------------
		void setMaterialIndex(int value);

		//----------------------------------------
		//! @brief ディヒューズテクスチャオブジェクト取得関数
		//! @details
		//! @param void なし 
		//! @retval TextureObject* ディヒューズテクスチャオブジェクト
		//----------------------------------------
		TextureObject* getpDiffuseTextureObject();

		//----------------------------------------
		//! @brief ディヒューズテクスチャオブジェクト設定関数
		//! @details
		//! @param *value ディヒューズテクスチャオブジェクト
		//! @retval void なし
		//----------------------------------------
		void setDiffuseTextureObject(TextureObject* value);
	};


//====================
// 変数
//====================
private:
	std::vector<Mesh> mesh_;				//!< メッシュ配列
	std::vector<D3DMATERIAL9> material_;	//!< マテリアル配列

	LPDIRECT3DDEVICE9 device_ = nullptr;	//!< デバイス

	unsigned reference_counter_ = 0;			//!< 参照カウンタ


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init(std::string* file_path);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief 参照カウンタ追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddReferenceCounter();

	//----------------------------------------
	//! @brief 解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Release();

private:
	//----------------------------------------
	//! @brief マテリアル生成関数
	//! @details
	//! @param md_bin バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateMaterial(MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief メッシュ生成関数
	//! @details
	//! @param md_bin バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateMesh(MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief マテリアルインデックス生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param md_bin       バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateMaterialIndex(int mesh_index, MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief インデックス生成関数
	//! @details
	//! @param mesh_index メッシュインデックス
	//! @param md_bin     バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateIndex(int mesh_index, MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief 頂点生成関数
	//! @details
	//! @param mesh_index メッシュインデックス
	//! @param md_bin     バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateVertex(int mesh_index, MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief 頂点座標生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param vertex_index 頂点インデックス
	//! @param md_bin       バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateVertexPosition(int mesh_index, int vertex_index,
							  MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief 法線生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param vertex_index 頂点インデックス
	//! @param md_bin       バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateNormal(int mesh_index, int vertex_index,
					  MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief カラー生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param vertex_index 頂点インデックス
	//! @retval void なし
	//----------------------------------------
	void CreateColor(int mesh_index, int vertex_index);

	//----------------------------------------
	//! @brief UV生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param vertex_index 頂点インデックス
	//! @param md_bin       バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateUV(int mesh_index, int vertex_index,
				  MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief ディヒューズテクスチャ生成関数
	//! @details
	//! @param mesh_index メッシュインデックス
	//! @param md_bin     バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateDiffuseTexture(int mesh_index, MdBinDataContainer* md_bin_data);

	//----------------------------------------
	//! @brief ファイルパス&キー名生成関数
	//! @details
	//! @param *file_path ファイルパス
	//! @param *key_name  キー名
	//! @retval void なし
	//----------------------------------------
	void CreateFilePathAndKeyName(std::string* file_path,
								  std::string* key_name);

	//----------------------------------------
	//! @brief バッファ生成関数
	//! @details
	//! @param mesh_index メッシュインデックス
	//! @param md_bin     バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateBuffer(int mesh_index, MdBinDataContainer* md_bin_data);
};



#endif
