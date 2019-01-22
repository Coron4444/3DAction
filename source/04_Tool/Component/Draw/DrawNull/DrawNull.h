//================================================================================
//!	@file	 DrawNull.h
//!	@brief	 空白描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_DRAW_NULL_H_
#define _DRAW_NULL_H_



//****************************************
// インクルード文
//****************************************
#include "../DrawBase/DrawBase.h"



//************************************************************														   
//! @brief   空白描画Class
//!
//! @details 描画の空白Class
//************************************************************
class DrawNull : public DrawBase
{
//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief オブジェクト数取得関数
	//! @details
	//! @param void なし
	//! @retval unsigned オブジェクト数
	//----------------------------------------
	virtual unsigned getObjectNum() override;

	//----------------------------------------
	//! @brief メッシュ数取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval unsigned メッシュ数
	//----------------------------------------
	virtual unsigned getMeshNum(unsigned object_index) override;

	//----------------------------------------
	//! @brief ボーン数取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval unsigned ボーン数
	//----------------------------------------
	virtual unsigned getBoneNum(unsigned object_index,
								unsigned mesh_index) override;

	//----------------------------------------
	//! @brief ワールド行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval MATRIX* ワールド行列
	//----------------------------------------
	virtual MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief ボーン行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @param bone_index   ボーンインデックス
	//! @retval MATRIX* ボーン行列
	//----------------------------------------
	virtual MATRIX* getpBoneMatrix(unsigned object_index,
								   unsigned mesh_index,
								   unsigned bone_index) override;

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	virtual D3DMATERIAL9* getpMaterial(unsigned object_index,
									   unsigned mesh_index) override;

	//----------------------------------------
	//! @brief ディヒューズテクスチャ取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval LPDIRECT3DTEXTURE9 ディヒューズテクスチャ
	//----------------------------------------
	virtual LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index,
												  unsigned mesh_index) override;

	 //----------------------------------------
	 //! @brief 法線テクスチャ取得関数
	 //! @details
	 //! @param object_index オブジェクトインデックス
	 //! @param mesh_index   メッシュインデックス
	 //! @retval RendererInterface* 法線テクスチャ
	 //----------------------------------------
	virtual LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index,
												 unsigned mesh_index) override;


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~DrawNull();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Init() override;

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Update() override;

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void DebugDisplay() override;

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void Draw(unsigned object_index, unsigned mesh_index) override;

	//----------------------------------------
	//! @brief 描画前設定関数
	//! @details
	//! @param *camera       カメラ
	//! @param object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) override;

	//----------------------------------------
	//! @brief 描画後設定関数
	//! @details
	//! @param *camera      カメラ
	//! @param object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) override;
};



#endif