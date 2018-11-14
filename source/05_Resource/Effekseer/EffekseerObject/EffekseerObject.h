//================================================================================
//
//    �G�t�F�N�V�A�I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2017/12/18
//
//================================================================================

#ifndef	_EFFEKSEER_OBJECT_H_
#define _EFFEKSEER_OBJECT_H_



//======================================================================
//
// �C���N���[�h��
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
// �N���X��`
//
//======================================================================

class EffekseerObject
{
//------------------------------------------------------------
private :
	static const int MAX_SPRITE_NUM;



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	EffekseerObject(const std::string* file_path);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~EffekseerObject();

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �X�V
	void Update();

	// �`��
	void Draw();

	// �Đ�
	void Play();
    bool IsPlaing(){return is_playing_;}

	// ��~
	void Stop();
	
	// �ꎞ��~
	void SetPause(bool is_pause);
	bool GetPause(){return is_pause_;}

	// ���s�[�g
	void SetRepeat(bool is_repeat){is_repeat_ = is_repeat;}
	bool GetRepeat(){return is_repeat_;}

	// ���x
	void SetVelocity(float velocity);
	
	// �F
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	
	// �s��
	void SetProjectionMatrix(Effekseer::Matrix44* projection_matrix);
	void SetViewMatrix(Effekseer::Matrix44* view_matrix);
	


	// �p��
	Transform* GetTransform(){return &transform_;}


//------------------------------------------------------------
private :
	// ����J�����o�֐�
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