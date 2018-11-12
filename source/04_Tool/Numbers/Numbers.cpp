//================================================================================
//
//    複数の数字クラス
//    Author : Araki Kai                                作成日 : 2018/06/19
//
//================================================================================


//======================================================================
//
// インクルード文
//
//======================================================================

#include "Numbers.h"
#include "Number\NumberFactory\NumberFactory.h"

#include "Renderer\RendererDirectX9\RendererDirectX9.h"
#include <GameObjectManager\GameObjectManager.h>



//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 初期化関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Numbers::Init()
{
	// 基底クラスの初期化
	GameObjectBase::Init(nullptr, nullptr, nullptr);

	number_factory_ = new NumberFactory();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Numbers::Uninit()
{
	// 基底クラスの終了処理
	GameObjectBase::Uninit();

	SafeRelease::Normal(&number_factory_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Reset処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Numbers::Reset()
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 数字群設定関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Numbers::SetNumbers(int numbers, int digits, bool is_zero, 
						 Vec2 position, Vec2 scale, XColor4 color)
{
	int temp_digits = digits;
	// 左詰めするかどうか
	if (temp_digits <= 0)
	{
		// 左詰め
		LeftJustified(numbers, &temp_digits);
	}
	else
	{
		// 桁数が変わったとき更新
		NotLeftJustified(&temp_digits);
	}

	// カンスト判定
	IsCountStop(numbers, temp_digits);
	
	// 各桁の更新
	UpdateEachDigit(numbers, temp_digits, is_zero, position, scale, color);
}



//--------------------------------------------------------------------------------
//
// [ 左詰め処理関数 ]
//
//--------------------------------------------------------------------------------

void Numbers::LeftJustified(int numbers, int* digits)
{
	// 現在の数値の解放
	ReleaseNumber();

	// 新たな桁数の取得
	int temp_numbers = numbers;

	*digits = 1;

	for ( ; ; )
	{
		temp_numbers /= 10;

		if (temp_numbers == 0) break;

		(*digits)++;
	}

	for (int i = 0; i < *digits; i++)
	{
		numbers_.push_back(number_factory_->Create());
	}
}



//--------------------------------------------------------------------------------
//
// [ 左詰め処理関数 ]
//
//--------------------------------------------------------------------------------

void Numbers::NotLeftJustified(int* digits)
{
	// 桁数の変更
	if (*digits == (int)numbers_.size()) return;
	
	// 現在の数値の解放
	ReleaseNumber();

	for (int i = 0; i < *digits; i++)
	{
		numbers_.push_back(number_factory_->Create());
	}
}



//--------------------------------------------------------------------------------
//
// [ カンスト処理関数 ]
//
//--------------------------------------------------------------------------------

void Numbers::IsCountStop(int numbers, int digits)
{
	int numbers_max = 1;

	for (int i = 0; i < digits; i++)
	{
		numbers_max *= 10;
	}
	
	numbers_max--;

	numbers = min(numbers_max, numbers);
}



//--------------------------------------------------------------------------------
//
// [ 各桁の更新関数 ]
//
//--------------------------------------------------------------------------------

void Numbers::UpdateEachDigit(int numbers, int digits, bool is_zero, 
									 Vec2 position, Vec2 scale, XColor4 color)
{
	// ずらし量
	float AmountOfShift = (numbers_.size() - 1) * (scale.x / 2);

	for (int i = (digits - 1); i >= 0; i--)
	{
		int temp_number = numbers % 10;
		numbers /= 10;

		numbers_[i]->SetNumber(temp_number);
		numbers_[i]->SetColor (color);
		*numbers_[i]->GetTransform()->GetPosition() = Vec3(position.x + AmountOfShift, position.y, 0.0f);
		*numbers_[i]->GetTransform()->GetScale() = Vec3(scale.x, scale.y, 1.0f);
		numbers_[i]->GetTransform()->UpdateWorldMatrixSRT();

		AmountOfShift -= (scale.x / 2);

		// ゼロ詰めしないならループ終了
		if ( !is_zero && !numbers ) return;
	}
}



//--------------------------------------------------------------------------------
//
// [ 数字解放関数 ]
//
//--------------------------------------------------------------------------------

void Numbers::ReleaseNumber()
{
	// 数字を解放
	for (auto& contents : numbers_)
	{
		GameObjectManager::ReleaseGameObjectBaseFromArray(contents);
	}

	// 数字配列をリセット
	numbers_.clear();
}