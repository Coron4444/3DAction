//================================================================================
//
//    エフェクシア配列クラス
//    Author : Araki Kai                                作成日 : 2018/09/01
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "EffekseerArray.h"

#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const unsigned EffekseerArray::DISPOSABLE_ARRAY_NUM = 5;
const unsigned EffekseerArray::REFERENCE_ARRAY_NUM  = 5;


//======================================================================
//
// 非静的メンバ関数定義
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトコンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerArray::EffekseerArray(const std::string* file_path)
	: next_reference_index_(0)
{
	// 使い捨てエフェクシアオブジェクトの作成
	disposable_effekseer_array_.resize(DISPOSABLE_ARRAY_NUM);
	for (auto& contents : disposable_effekseer_array_)
	{
		contents = new EffekseerObject(file_path);
	}

	// 参照エフェクシアオブジェクトの作成
	reference_effekseer_array_.resize(REFERENCE_ARRAY_NUM);
	for (auto& contents : reference_effekseer_array_)
	{
		contents = new EffekseerObject(file_path);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerArray::~EffekseerArray()
{
	// 使い捨てエフェクシアオブジェクトの解放
	for (auto& contents : disposable_effekseer_array_)
	{
		SafeRelease::Normal(&contents);
	}

	// 参照エフェクシアオブジェクトの解放
	for (auto& contents : reference_effekseer_array_)
	{
		SafeRelease::Normal(&contents);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerArray::Update(Effekseer::Matrix44* projection_matrix, Effekseer::Matrix44* view_matrix)
{
	// リストの更新
	UpdateList();

	// 使い捨てエフェクシアオブジェクトの更新
	for (auto contents : disposable_effekseer_list_)
	{
		contents->SetProjectionMatrix(projection_matrix);
		contents->SetViewMatrix(view_matrix);
		contents->Update();
	}

	// 参照エフェクシアオブジェクトの更新
	for (unsigned i = 0; i < next_reference_index_; i++)
	{
		reference_effekseer_array_[i]->SetProjectionMatrix(projection_matrix);
		reference_effekseer_array_[i]->SetViewMatrix(view_matrix);
		reference_effekseer_array_[i]->Update();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 描画関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerArray::Draw()
{
	// 使い捨てエフェクシアオブジェクトの描画
	for (auto contents : disposable_effekseer_list_)
	{
		contents->Draw();
	}

	// 参照エフェクシアオブジェクトの描画
	for (unsigned i = 0; i < next_reference_index_; i++)
	{
		reference_effekseer_array_[i]->Draw();
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 使い捨てエフェクシアオブジェクトの作成関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void EffekseerArray::CreateDisposableEffekseerObject(Vec3 position, Vec3 scale)
{
	// 停止しているオブジェクトを探す
	for (auto contents : disposable_effekseer_array_)
	{
		if (contents->IsPlaing()) continue;

		// リストへ追加
		disposable_effekseer_list_.push_back(contents);

		// 状態更新
		*contents->GetTransform()->GetPosition() = position;
		*contents->GetTransform()->GetScale()    = scale;
		contents->GetTransform()->UpdateWorldMatrixSRT();

		// 再生
		contents->Play();
		
		break;
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 参照オブジェクトの取得関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EffekseerObject* EffekseerArray::GetReferenceEffekseerObject()
{
	if (next_reference_index_ == reference_effekseer_array_.size()) return nullptr;

	return reference_effekseer_array_[next_reference_index_++];
}



//--------------------------------------------------------------------------------
//
// [ リスト更新関数 ]
//
//--------------------------------------------------------------------------------

void EffekseerArray::UpdateList()
{
	auto iterator = disposable_effekseer_list_.begin();

	while (iterator != disposable_effekseer_list_.end())
	{
		// 再生中かどうか
		if ((*iterator)->IsPlaing())
		{
			iterator++;
		}
		else
		{
			// 再生が終わったオブジェクトを消去
			iterator = disposable_effekseer_list_.erase(iterator);
		}
	}
}