//================================================================================
//!	@file	 Fade.h
//!	@brief	 フェードClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_FADE_H_
#define _FADE_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include <Vector3D.h>
#include <Transform\Transform.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// クラス宣言
//****************************************
class PlanePolygon;
class TextureObject;


//************************************************************														   
//! @brief   フェードClass
//!
//! @details フェードのClass
//************************************************************
class Fade : public DrawNull
{
//====================
// 列挙型定義
//====================
public:
	enum Type
	{
		TYPE_NONE = -1,
		TYPE_NORMAL,
		TYPE_TRANSITION_01,
		TYPE_MAX
	};

	enum State
	{
		STATE_NONE = -1,
		STATE_FADE_IN,
		STATE_FADE_OUT,
		STATE_MAX
	};


//====================
// 定数
//====================
public:
	static const std::string TEXTURE_PATH;					//!< テクスチャパス
	static const std::string TEXTURE_NAME_TRANSITION_01;	//!< テクスチャ名


//====================
// 変数
//====================
private:
	Type type_;										//!< タイプ
	State state_;									//!< ステート
	PlanePolygon plane_polygon_;					//!< 板ポリゴン
	Transform transform_;							//!< 状態
	TextureObject* transition01_texture_ = nullptr;	//!< テクスチャオブジェクト
	XColor4 color_;									//!< 色
	float speed_;									//!< フェード速度
	bool end_flag_;									//!< 終了フラグ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval MATRIX* 行列
	//----------------------------------------
	MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;

	//----------------------------------------
	//! @brief タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval Type* タイプ
	//----------------------------------------
	const Type* getpType() const;
	
	//----------------------------------------
	//! @brief ステート取得関数
	//! @details
	//! @param void なし
	//! @retval State* ステート
	//----------------------------------------
	const State* getpState() const;
	
	//----------------------------------------
	//! @brief 終了フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 終了フラグ
	//----------------------------------------
	bool getpEndFlag() const;
	
	//----------------------------------------
	//! @brief 状態取得関数
	//! @details
	//! @param void なし
	//! @retval Transform* 状態
	//----------------------------------------
	Transform* getpTransform();
	
	//----------------------------------------
	//! @brief テクスチャオブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval TextureObject* テクスチャオブジェクト
	//----------------------------------------
	TextureObject* getpTransition01Object();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param type  タイプ
	//! @param state ステート
	//! @param size  拡縮
	//! @param color 色
	//! @param speed フェード速度
	//! @retval void なし
	//----------------------------------------
	void Init(Type type, State state, Vec2 size, XColor4 color, float speed);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif