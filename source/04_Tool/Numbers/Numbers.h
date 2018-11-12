//================================================================================
//
//    複数の数字クラス
//    Author : Araki Kai                                作成日 : 2018/06/19
//
//================================================================================

#ifndef	_NUMBERS_H_
#define _NUMBERS_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <GameObjectBase/GameObjectBase.h>

#include <Vector3D.h>
#include <vector>



//======================================================================
//
// クラス宣言
//
//======================================================================
class Number;
class NumberFactory;


//======================================================================
//
// クラス定義
//
//======================================================================

class Numbers : public GameObjectBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init();
	void Uninit() override;
	void Reset()  override;

	void SetNumbers(int numbers, int digits, bool is_zero, 
					Vec2 position, Vec2 scale, XColor4 color);


//------------------------------------------------------------
private :
	// メンバ関数
	void LeftJustified(int numbers, int* digits);
	void NotLeftJustified(int* digits);
	void IsCountStop(int numbers, int digits);
	void UpdateEachDigit(int numbers, int digits, bool is_zero, 
						 Vec2 position, Vec2 scale, XColor4 color);
	void ReleaseNumber();


//------------------------------------------------------------
private :
	// 公開メンバ変数
	NumberFactory* number_factory_;

	std::vector<Number*> numbers_;

};



#endif