//================================================================================
//
//    �G�t�F�N�V�A�z��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/01
//
//================================================================================

#ifndef	_EFFEKSEER_ARRAY_H_
#define _EFFEKSEER_ARRAY_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>
#include <vector>
#include <list>

#include "../EffekseerObject/EffekseerObject.h"



//======================================================================
//
// �N���X��`
//
//======================================================================

class EffekseerArray
{
//------------------------------------------------------------
private :
	static const unsigned DISPOSABLE_ARRAY_NUM;
	static const unsigned REFERENCE_ARRAY_NUM;



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �R���X�g���N�^
	EffekseerArray(const std::string* file_path);

	// �f�X�g���N�^
	~EffekseerArray();



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	void Update(Effekseer::Matrix44* projection_matrix, Effekseer::Matrix44* view_matrix);
	void Draw();

	// �g���̂ăG�t�F�N�V�A�I�u�W�F�N�g�̍쐬
	void CreateDisposableEffekseerObject(Vec3 position, Vec3 scale);
	
	// �Q�ƃI�u�W�F�N�g�̎擾
	EffekseerObject* GetReferenceEffekseerObject();


//------------------------------------------------------------
private :
	void UpdateList();


//------------------------------------------------------------
private :
	// �g���̂ăG�t�F�N�V�A�I�u�W�F�N�g
	std::vector<EffekseerObject*> disposable_effekseer_array_;
	std::list<EffekseerObject*>   disposable_effekseer_list_;

	// �Q�ƃG�t�F�N�V�A�I�u�W�F�N�g
	std::vector<EffekseerObject*> reference_effekseer_array_;
	unsigned next_reference_index_;
};



#endif