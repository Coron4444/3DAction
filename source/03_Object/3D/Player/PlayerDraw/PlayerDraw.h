//================================================================================
//
//    プレイヤー描画クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================

#ifndef	_PLAYER_DRAW_H_
#define _PLAYER_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Player.h"



//****************************************
// クラス宣言
//****************************************
class ModelXObject;
class TextureObject;
class MdBinObject;



/*********************************************************//**
* @brief
* プレイヤー描画クラス
*
* プレイヤーの描画クラス
*************************************************************/
class PlayerDraw : public DrawNull
{
//==============================
// 定数
//==============================
private:
	// 定数
	static const std::string MODEL_NAME;				//!< モデル名
	static const std::string TEXTURE_PATH;				//!< モデルフォルダのテクスチャパス
	static const std::string NORMAL_TEXTURE_MODEL;		//!< 法線テクスチャ(モデル)
	static const std::string NORMAL_TEXTURE_SWORD;		//!< 法線テクスチャ(剣)


//==============================
// 非静的メンバ関数
//==============================
private:
	ModelXObject* player_model_;			//!< モデルオブジェクト
	TextureObject* normal_texture_[2];		//!< テクスチャオブジェクト
	MdBinObject* test_object_;				//!< テスト用オブジェクト

	int count_ = 0;
	int frame_ = 0;

//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init() override;

	/**
	* @brief
	* 終了関数
	*/
	void Uninit() override;

	void Update() override;

	/**
	* @brief
	* 描画関数
	* @param
	* object_index : オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override;

	// プロパティ
	unsigned getMeshNum(unsigned object_index) override;
	unsigned getBoneNum(unsigned object_index, unsigned mesh_index) override;
	MATRIX* getpMatrix(unsigned object_index) override;
	MATRIX* getpBoneMatrix(unsigned object_index, unsigned mesh_index,
						   unsigned bone_index) override;
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif