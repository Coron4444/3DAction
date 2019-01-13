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

#include "PlayerUpdate.h"

#include <Keyboard\Keyboard.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>

#include <3D/Player/PlayerUpdate_Special/PlayerUpdate_Special.h>
#include <GameObjectManager/GameObjectManager.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>


//======================================================================
//
// 定数定義
//
//======================================================================

const float PlayerUpdate::SPEED = MeterPerSecondSquared_To_MeterPerFrameSquared(50.0f);

static const std::string TEST_EFFEKSEER = "Beam/Beam.efk";



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

void PlayerUpdate::Init()
{
	// ダウンキャスト
	player_ = (Player*)getpGameObject();

	// 剛体設定
	player_->CreatePhysics();
	player_->GetPhysics()->SetMaxVelocity(MeterPerSecond_To_MeterPerFlame(300.0f));
	player_->GetPhysics()->SetMass(8.0f);
	player_->GetPhysics()->SetMyFriction(1.0f);
	player_->GetPhysics()->SetMyBounciness(1.0f);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 終了処理関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate::Update()
{
	// 平行移動
	Vector3D temp_vector;

	if (GetKeyboardPress(DIK_D))
	{
		temp_vector += *player_->GetTransform()->GetRight();
	}
	if (GetKeyboardPress(DIK_A))
	{
		temp_vector += -*player_->GetTransform()->GetRight();
	}
	if (GetKeyboardPress(DIK_W))
	{
		temp_vector += *player_->GetTransform()->GetForawrd();
	}
	if (GetKeyboardPress(DIK_S))
	{
		temp_vector += -*player_->GetTransform()->GetForawrd();
	}

	*player_->GetPhysics()->GetAcceleration() += temp_vector.AnyLengthVector(SPEED);

	// ブレーキ
	if (GetKeyboardTrigger(DIK_N))
	{
		//GameObjectManager::GetUpdateManager()
			//->OverwriteArrayUpdateBase(player_, new PlayerUpdate_Special());
		//return;
		player_->GetPhysics()->AddFriction(0.5f);
	}

	player_->GetPhysics()->AddFriction(0.9f);

	// ジャンプ
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		temp_vector = Vec3(0.0f, 1.0f, 0.0f);
		temp_vector.AnyLengthVector(MeterPerSecond_To_MeterPerFlame(30.0f));

		*player_->GetPhysics()->GetVelocity() += temp_vector;
	}

	// 拡縮
	if (GetKeyboardPress(DIK_Z))
	{
		*player_->GetTransform()->GetScale() += Vec3(SPEED, SPEED, SPEED);
	}
	if (GetKeyboardPress(DIK_X))
	{
		*player_->GetTransform()->GetScale() += -Vec3(SPEED, SPEED, SPEED);
	}

	player_->GetTransform()->SetLookAtSpeed(0.05f);

	// 回転
	if (GetKeyboardPress(DIK_C))
	{
		player_->GetTransform()->SetLookAtVector(Vec3(1.0f, 1.0f, 0.0f));
	}
	if (GetKeyboardPress(DIK_V))
	{
		player_->GetTransform()->SetLookAtVector(Vec3(-1.0f, 0.0f, 0.0f));
	}
	if (GetKeyboardPress(DIK_B))
	{
		player_->GetTransform()->SetLookAtVector(Vec3(0.0f, 0.0f, -1.0f));
	}

	//float temp_scale = 1.0f;

	if (GetKeyboardTrigger(DIK_P))
	{
		EffekseerObject* temp_object = EffekseerManager::getpInstance()
			->getpDisposableObject(&TEST_EFFEKSEER);
		*temp_object->getpTransform()->GetPosition() = *player_->GetTransform()->GetPosition();
		temp_object->getpTransform()->UpdateWorldMatrixSRT();
		temp_object->Play();
	}

	player_->GetTransform()->UpdateAxisVector_WorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 後更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate::LateUpdate()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デバッグ関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate::DebugDisplay()
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