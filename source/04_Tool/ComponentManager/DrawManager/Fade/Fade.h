//================================================================================
//
//    �t�F�[�h�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================

#ifndef	_FADE_H_
#define _FADE_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>

#include <Transform\Transform.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <Texture\TextureManager\TextureManager.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Fade
{
//------------------------------------------------------------
private :
	// �萔
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
	// �f�t�H���g�R���X�g���N�^
	Fade();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	~Fade();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init(Type type, State state, Vec2 size, XColor4 color, float speed);
	void Uninit();
	void Update();
	void Draw();
	
	// �Q�b�^
	const Type* GetType()   const {return &type_;}
	const State* GetState() const {return &state_;}
	bool GetEndFlag() const {return end_flag_;}
	Transform* GetTransform(){return &transform_;}
	TextureObject* GetTransition01Object(){return transition01_texture_;}



//------------------------------------------------------------
private :
	// �t�F�[�h�̏��
	Type        type_;
	State       state_;

	// �|���S���̏��
	PlanePolygon* plane_polygon_;
	Transform transform_;
	XColor4 color_;
	
	// �p�����[�^
	float speed_;

	// �t���O
	bool end_flag_;

	// �e�N�X�`��
	TextureObject* transition01_texture_;
};



#endif