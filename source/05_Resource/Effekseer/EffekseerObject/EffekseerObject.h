//================================================================================
//
//    エフェクシアオブジェクトクラス
//    Author : Araki Kai                                作成日 : 2017/12/18
//
//================================================================================

#ifndef	_EFFEKSEER_OBJECT_H_
#define _EFFEKSEER_OBJECT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>
#include <vector>

#include <Vector3D.h>
#include <Transform\Transform.h>

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>





//======================================================================
//
// クラス定義
//
//======================================================================

class EffekseerObject
{
//------------------------------------------------------------
private :
	static const int MAX_SPRITE_NUM;



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	EffekseerObject(const std::string* file_path);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	virtual ~EffekseerObject();

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 更新
	void Update();

	// 描画
	void Draw();

	// 再生
	void Play();
    bool IsPlaing(){return is_playing_;}

	// 停止
	void Stop();
	
	// 一時停止
	void SetPause(bool is_pause);
	bool GetPause(){return is_pause_;}

	// リピート
	void SetRepeat(bool is_repeat){is_repeat_ = is_repeat;}
	bool GetRepeat(){return is_repeat_;}

	// 速度
	void SetVelocity(float velocity);
	
	// 色
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	
	// 行列
	void SetProjectionMatrix(Effekseer::Matrix44* projection_matrix);
	void SetViewMatrix(Effekseer::Matrix44* view_matrix);
	


	// 姿勢
	Transform* GetTransform(){return &transform_;}


//------------------------------------------------------------
private :
	// 非公開メンバ関数
	void InitRenderer_Manager();
	void InputEffect(const std::string* file_path);
	void SetWorldMatrix(const MATRIX* world_matrix);

	
//------------------------------------------------------------
private :
	EffekseerRendererDX9::Renderer* effekseer_renderer_;
	Effekseer::Manager*				effekseer_manager_;
	Effekseer::Effect*              effekseer_effect_;
	Effekseer::Handle               effekseer_handle_;
    Effekseer::Matrix43				world_matrix_;
	bool is_playing_;
	bool is_pause_;
	bool is_repeat_;

	Transform transform_;
};



#endif