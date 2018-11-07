//================================================================================
//
//    �����̐����N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================

#ifndef	_NUMBERS_H_
#define _NUMBERS_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <GameObjectOrigin\GameObjectOrigin.h>

#include <Vector3D.h>
#include <vector>



//======================================================================
//
// �N���X�錾
//
//======================================================================

class DrawComponentManager;
class Number;
class NumberFactory;


//======================================================================
//
// �N���X��`
//
//======================================================================

class Numbers : public GameObjectOrigin
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init();
	void Uninit() override;
	void Reset()  override;

	void SetNumbers(int numbers, int digits, bool is_zero, 
					Vec2 position, Vec2 scale, XColor4 color);


//------------------------------------------------------------
private :
	// �����o�֐�
	void LeftJustified(int numbers, int* digits);
	void NotLeftJustified(int* digits);
	void IsCountStop(int numbers, int digits);
	void UpdateEachDigit(int numbers, int digits, bool is_zero, 
						 Vec2 position, Vec2 scale, XColor4 color);
	void ReleaseNumber();


//------------------------------------------------------------
private :
	// ���J�����o�ϐ�
	NumberFactory* number_factory_;

	std::vector<Number*> numbers_;

};



#endif