//================================================================================
//
//    プレイヤー更新クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================



//======================================================================
//
// インクルード文
//
//======================================================================

#include "PlayerUpdate_Special.h"

#include <Keyboard\Keyboard.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <3D/Player/PlayerUpdate/PlayerUpdate.h>
#include <GameObjectManager/GameObjectManager.h>



//======================================================================
//
// 定数定義
//
//======================================================================

const float PlayerUpdate_Special::SPEED = MeterPerSecondSquared_To_MeterPerFrameSquared(1.0f);

static const std::string TEST_EFFEKSEER = "Beam/Beam.efk";

//static EffekseerObject* temp_object_;

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

void PlayerUpdate_Special::Init()
{
	// ダウンキャスト
	player_ = (Player*)getpGameObject();

	// 剛体設定
	player_->CreatePhysics();
	player_->GetPhysics()->SetMaxVelocity(MeterPerSecond_To_MeterPerFlame(10.0f));
	player_->GetPhysics()->SetMass(0.1f);
	player_->GetPhysics()->SetMyFriction(1.0f);
	player_->GetPhysics()->SetMyBounciness(1.0f);

	//EffekseerManager::AddUniqueData(&TEST_EFFEKSEER);

	//temp_object_ = EffekseerManager::GetReferenceEffekseerObject(&TEST_EFFEKSEER);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate_Special::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate_Special::Update()
{
	// 平行移動
	Vector3D temp_vector;

	if (GetKeyboardPress(DIK_RIGHT))
	{
		temp_vector += *player_->GetTransform()->GetRight();
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		temp_vector += -*player_->GetTransform()->GetRight();
	}
	if (GetKeyboardPress(DIK_UP))
	{
		temp_vector += *player_->GetTransform()->GetForawrd();
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		temp_vector += -*player_->GetTransform()->GetForawrd();
	}

	*player_->GetPhysics()->GetAcceleration() += temp_vector.AnyLengthVector(SPEED);

	// ブレーキ
	if (GetKeyboardTrigger(DIK_N))
	{
		GameObjectManager::GetUpdateManager()
			->OverwriteArrayUpdateBase(player_, new PlayerUpdate());
		return;
	}


	player_->GetTransform()->UpdateAxisVector_WorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 後更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate_Special::LateUpdate()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デバッグ関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate_Special::DebugDisplay()
{
#ifdef _DEBUG
	 // ウィンドウの設定
    ImGui::SetNextWindowPos(ImVec2(30, 30), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(150, 500), ImGuiSetCond_Once);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive,    ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.5f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg,          ImVec4(0.5f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f, 0.5f, 0.5f, 1.0f));

	// 開始
	ImGui::Begin("Player", nullptr, ImGuiWindowFlags_MenuBar);

	// メニュー
	if (ImGui::BeginMenuBar()) 
	{
		// メニュー名
		if (ImGui::BeginMenu("File"))
		{
		    // メニューごとの処理
		    if (ImGui::MenuItem("Save")) 
		    {

		    }
		    if (ImGui::MenuItem("Load"))
		    {
		    }

		    ImGui::EndMenu();
		}
			ImGui::EndMenuBar();	
	}

	// 座標
	if (ImGui::CollapsingHeader("Position"))
    {
        // テキスト表示
		ImGui::Text("X : %f", player_->GetTransform()->GetPosition()->x);
		ImGui::Text("Y : %f", player_->GetTransform()->GetPosition()->y);
		ImGui::Text("Z : %f", player_->GetTransform()->GetPosition()->z);
	}

	// 軸ベクトル
	if (ImGui::CollapsingHeader("Axis"))
    {
        // ノード
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Right")) 
		{
			ImGui::Text("X : %f", player_->GetTransform()->GetRight()->x);
			ImGui::Text("Y : %f", player_->GetTransform()->GetRight()->y);
			ImGui::Text("Z : %f", player_->GetTransform()->GetRight()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Up")) 
		{
			ImGui::Text("X : %f", player_->GetTransform()->GetUp()->x);
			ImGui::Text("Y : %f", player_->GetTransform()->GetUp()->y);
			ImGui::Text("Z : %f", player_->GetTransform()->GetUp()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Forawrd")) 
		{
			ImGui::Text("X : %f", player_->GetTransform()->GetForawrd()->x);
			ImGui::Text("Y : %f", player_->GetTransform()->GetForawrd()->y);
			ImGui::Text("Z : %f", player_->GetTransform()->GetForawrd()->z);

			ImGui::TreePop();
		}
	}

	// 物理
	if (ImGui::CollapsingHeader("Physics"))
    {
        // ノード
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Velocity")) 
		{
			ImGui::Text("X : %f", player_->GetPhysics()->GetVelocity()->x);
			ImGui::Text("Y : %f", player_->GetPhysics()->GetVelocity()->y);
			ImGui::Text("Z : %f", player_->GetPhysics()->GetVelocity()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Mass")) 
		{
			static float mass = 0.1f;
			ImGui::SliderFloat("slider 1", &mass, 0.1f, 2.0f);
			player_->GetPhysics()->SetMass(mass);
			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Friction")) 
		{
			static float friction = 0.0f;
			ImGui::SliderFloat("slider 1", &friction, 0.0f, 1.0f);
			player_->GetPhysics()->AddFriction(friction);
			ImGui::TreePop();
		}
	}

	// 終了
    ImGui::End();

    // 色の解放(設定でプッシュした分だけ)
    ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
#endif
}