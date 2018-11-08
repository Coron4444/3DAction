//================================================================================
//
//    フェードクラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================

#ifndef	_FADE_H_
#define _FADE_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include <Transform\Transform.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <Texture\TextureManager\TextureManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class Fade
{
//------------------------------------------------------------
private :
	// 定数
	static const std::string TEXTURE_PATH;
	static const std::string TEXTURE_NAME_TRANSITION_01;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	enum Type
	{
		TYPE_NONE = -1,
		TYPE_NORMAL,
		TYPE_TRANSITION_01,
		TYPE_MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	enum State
	{
		STATE_NONE = -1,
		STATE_FADE_IN,
		STATE_FADE_OUT,
		STATE_MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	Fade();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	~Fade();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init(Type type, State state, Vec2 size, XColor4 color, float speed);
	void Uninit();
	void Update();
	void Draw();
	
	// ゲッタ
	const Type* GetType()   const {return &type_;}
	const State* GetState() const {return &state_;}
	bool GetEndFlag() const {return end_flag_;}
	Transform* GetTransform(){return &transform_;}
	TextureObject* GetTransition01Object(){return transition01_texture_;}



//------------------------------------------------------------
private :
	// フェードの状態
	Type        type_;
	State       state_;

	// ポリゴンの状態
	PlanePolygon* plane_polygon_;
	Transform transform_;
	XColor4 color_;
	
	// パラメータ
	float speed_;

	// フラグ
	bool end_flag_;

	// テクスチャ
	TextureObject* transition01_texture_;
};



#endif