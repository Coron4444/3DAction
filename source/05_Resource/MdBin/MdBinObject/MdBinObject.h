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

#include "../MdBinData/MdBinData.h"
#include <Vector3D.h>



//****************************************
// クラス宣言
//****************************************
class TextureObject;



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
		Vec3 posisiont_;	//!< 座標
		Vec3 normal_;		//!< 法線
		Color4 color_;		//!< カラー
		Vec2 uv_;			//!< UV
		float bone_weight_[MdBinData::Mesh::BoneWeight::MAX_BONE_NUM];			//!< ボーンの重み
		unsigned char bone_index_[MdBinData::Mesh::BoneWeight::MAX_BONE_NUM];	//!< ボーンインデックス
	};


	//****************************************														   
	//! @brief ボーンClass
	//!
	//! @details ボーンのClass
	//****************************************
	class Bone
	{
	//====================
	// 変数
	//====================
	private:
		std::string name_;						//!< ボーン名
		MATRIX offset_matrix_;					//!< オフセット行列
		std::vector<MATRIX> animation_matrix_;	//!< アニメーション行列


	//====================
	// プロパティ
	//====================
	public:
		//----------------------------------------
		//! @brief ボーン名取得関数
		//! @details
		//! @param void なし
		//! @retval std::string* ボーン名
		//----------------------------------------
		std::string* getpName();

		//----------------------------------------
		//! @brief オフセット行列取得関数
		//! @details
		//! @param void なし
		//! @retval MATRIX* オフセット配列
		//----------------------------------------
		MATRIX* getpOffsetMatrix();

		//----------------------------------------
		//! @brief アニメーション行列配列サイズ取得関数
		//! @details
		//! @param void なし
		//! @retval int アニメーション行列配列サイズ
		//----------------------------------------
		int getAnimationMatrixArraySize();

		//----------------------------------------
		//! @brief アニメーション行列配列サイズ設定関数
		//! @details
		//! @param value アニメーション行列配列サイズ
		//! @retval void なし
		//----------------------------------------
		void setAnimationMatrixArraySize(int value);

		//----------------------------------------
		//! @brief アニメーション行列取得関数
		//! @details
		//! @param index インデックス
		//! @retval MATRIX* アニメーション行列
		//----------------------------------------
		MATRIX* getpAnimationMatrix(int index);
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
		std::vector<Vertex> vertex_;						//!< 頂点配列
		std::vector<WORD> index_;							//!< インデックス配列
		std::vector<Bone> bone_;							//!< ボーン配列
		int material_index_;								//!< マテリアルインデックス
		int primitive_num_;									//!< プリミティブ数
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
		//! @brief ボーン配列サイズ取得関数
		//! @details
		//! @param void なし 
		//! @retval int サイズ
		//----------------------------------------
		int getBoneArraySize();

		//----------------------------------------
		//! @brief ボーン配列サイズ設定関数
		//! @details
		//! @param value サイズ
		//! @retval void なし
		//----------------------------------------
		void setBoneArraySize(int value);

		//----------------------------------------
		//! @brief ボーン取得関数
		//! @details
		//! @param index インデックス
		//! @retval Bone* 頂点
		//----------------------------------------
		Bone* getpBone(int index);

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
		//! @brief プリミティブ数取得関数
		//! @details
		//! @param void なし 
		//! @retval int プリミティブ数
		//----------------------------------------
		int getPrimitiveNum();

		//----------------------------------------
		//! @brief プリミティブ数設定関数
		//! @details
		//! @param value プリミティブ数
		//! @retval void なし
		//----------------------------------------
		void setPrimitiveNum(int value);

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

		//----------------------------------------
		//! @brief 頂点バッファ取得関数
		//! @details
		//! @param void なし
		//! @retval LPDIRECT3DVERTEXBUFFER9 頂点バッファ
		//----------------------------------------
		LPDIRECT3DVERTEXBUFFER9 getpVertexBuffer();

		//----------------------------------------
		//! @brief 頂点バッファ変数ポインタ取得関数
		//! @details
		//! @param void なし
		//! @retval LPDIRECT3DVERTEXBUFFER9* 頂点バッファ変数ポインタ
		//----------------------------------------
		LPDIRECT3DVERTEXBUFFER9* getp2VertexBuffer();

		//----------------------------------------
		//! @brief インデックスバッファ取得関数
		//! @details
		//! @param void なし
		//! @retval LPDIRECT3DINDEXBUFFER9 インデックスバッファ
		//----------------------------------------
		LPDIRECT3DINDEXBUFFER9 getpIndexBuffer();

		//----------------------------------------
		//! @brief インデックスバッファ変数ポインタ取得関数
		//! @details
		//! @param void なし
		//! @retval LPDIRECT3DINDEXBUFFER9* インデックスバッファ変数ポインタ
		//----------------------------------------
		LPDIRECT3DINDEXBUFFER9* getp2IndexBuffer();

	//====================
	// 関数
	//====================
	public:
		//----------------------------------------
		//! @brief 終了関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		void Uninit();
	};


//====================
// 変数
//====================
private:
	std::vector<Mesh> mesh_;				//!< メッシュ配列
	std::vector<D3DMATERIAL9> material_;	//!< マテリアル配列
	int animation_frame_num_;				//!< アニメーションフレーム数
	LPDIRECT3DDEVICE9 device_ = nullptr;	//!< デバイス
	std::string map_key_name_;				//!< マップ用キー名
	int reference_counter_ = 0;				//!< 参照カウンタ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief メッシュ数取得関数
	//! @details
	//! @param void なし 
	//! @retval unsigned メッシュ数
	//----------------------------------------
	unsigned getMeshNum();

	//----------------------------------------
	//! @brief メッシュ取得関数
	//! @details
	//! @param index インデックス 
	//! @retval Mesh* メッシュ
	//----------------------------------------
	Mesh* getpMesh(int index);

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param mesh_index メッシュインデックス 
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned mesh_index);

	//----------------------------------------
	//! @brief ディヒューズテクスチャオブジェクト取得関数
	//! @details
	//! @param mesh_index メッシュインデックス 
	//! @retval TextureObject* ディヒューズテクスチャオブジェクト
	//----------------------------------------
	TextureObject* getpDiffuseTextureObject(unsigned mesh_index);

	//----------------------------------------
	//! @brief ディヒューズテクスチャハンドラ取得関数
	//! @details
	//! @param mesh_index メッシュインデックス  
	//! @retval LPDIRECT3DTEXTURE9 ディヒューズテクスチャハンドラ
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpDiffuseTextureHandler(unsigned mesh_index);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *file_path    ファイルパス
	//! @param *map_key_name マップ用キー名
	//! @retval void なし
	//----------------------------------------
	void Init(std::string* file_path, const std::string* map_key_name);

	//----------------------------------------
	//! @brief 解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Release();

	//----------------------------------------
	//! @brief 強制解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ForcedRelease();

	//----------------------------------------
	//! @brief 参照カウンタ追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddReferenceCounter();

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param mesh_index メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void Draw(unsigned mesh_index);

private:
	//----------------------------------------
	//! @brief マテリアル生成関数
	//! @details
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateMaterial(MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief メッシュ生成関数
	//! @details
	//! @param *file_path   ファイルパス
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateMesh(std::string* file_path, MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief マテリアルインデックス生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateMaterialIndex(int mesh_index, MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief インデックス生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateIndex(int mesh_index, MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief 頂点生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateVertex(int mesh_index, MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief 頂点座標生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param vertex_index 頂点インデックス
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateVertexPosition(int mesh_index, int vertex_index,
							  MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief 法線生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param vertex_index 頂点インデックス
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateNormal(int mesh_index, int vertex_index,
					  MdBinData* md_bin_data);

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
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateUV(int mesh_index, int vertex_index,
				  MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief ボーンの重み生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param vertex_index 頂点インデックス
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateBoneWeight(int mesh_index, int vertex_index,
						  MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief ディヒューズテクスチャ生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param *file_path   ファイルパス
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateDiffuseTexture(int mesh_index,
							  std::string* file_path,
							  MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief ボーン生成関数
	//! @details
	//! @param mesh_index   メッシュインデックス
	//! @param *md_bin_data バイナリーモデルデータ
	//! @retval void なし
	//----------------------------------------
	void CreateBone(int mesh_index,
					MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief 行列変換関数
	//! @details
	//! @param *directx_matrix DirectX行列
	//! @param *md_bin_matrix  バイナリーモデル行列
	//! @retval void なし
	//----------------------------------------
	void ChangeMatrix(MATRIX* directx_matrix,
					  MdBinData::Matrix* md_bin_matrix);

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
	//! @retval void なし
	//----------------------------------------
	void CreateBuffer(int mesh_index);

	//----------------------------------------
	//! @brief 頂点バッファ生成関数
	//! @details
	//! @param mesh_index メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void CreateVertexBuffer(int mesh_index);

	//----------------------------------------
	//! @brief インデックスバッファ生成関数
	//! @details
	//! @param mesh_index メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void CreateIndexBuffer(int mesh_index);
};



#endif
