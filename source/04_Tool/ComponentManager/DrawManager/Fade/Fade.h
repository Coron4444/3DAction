//================================================================================
//
//    フェードクラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================

#ifndef	_FADE_H_
#define _FADE_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/DrawBase/DrawNull.h>
#include <Transform\Transform.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <Texture\TextureManager\TextureManager.h>



/*********************************************************//**
* @brief
* フェードクラス
*
* フェードのクラス
*************************************************************/
class Fade : public DrawNull
{
//==============================
// 定数定義
//==============================
public:
	static const std::string TEXTURE_PATH;
	static const std::string TEXTURE_NAME_TRANSITION_01;


//==============================
// 列挙型定義
//==============================
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

//==============================
// 非静的メンバ変数
//==============================
private:
	Type type_;			//!< タイプ
	State state_;		//!< ステート

	PlanePolygon* plane_polygon_;		//!< 板ポリゴン
	Transform transform_;				//!< 状態
	XColor4 color_;						//!< 色

	float speed_;		//!< フェード速度
	bool end_flag_;		//!< 終了フラグ

	TextureObject* transition01_texture_;	//!< テクスチャオブジェクト


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* コンストラクタ
	*/
	Fade();

	/**
	* @brief
	* デストラクタ
	*/
	~Fade();

	/**
	* @brief
	* 初期化関数
	* @param
	* type : タイプ
	* state : ステート
	* size : 拡縮
	* color : 色
	* speed : フェード速度
	*/
	void Init(Type type, State state, Vec2 size, XColor4 color, float speed);

	/**
	* @brief
	* 終了関数
	*/
	void Uninit() override;

	/**
	* @brief
	* 更新関数
	*/
	void Update();

	/**
	* @brief
	* 描画関数
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override;

	// プロパティ
	const MATRIX* GetMatrix(unsigned object_index) override
	{
		object_index = object_index;
		return transform_.GetMatrixExtend()->GetWorldMatrix();
	}
	const Type* GetType()   const { return &type_; }
	const State* GetState() const { return &state_; }
	bool GetEndFlag() const { return end_flag_; }
	Transform* GetTransform() { return &transform_; }
	TextureObject* GetTransition01Object() { return transition01_texture_; }
};



#endif