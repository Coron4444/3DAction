//================================================================================
//
//    コントローラー
//    Author : Araki Kai                                作成日 : 2017/09/24
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "Controller.h"



//**********************************************************************
//
// 定数定義
//
//**********************************************************************

// スティック感度(トリガー)
const int STICK_TRIGGER_SENSITIVITY  = 30000;
const int STICK_HOLD_SENSITIVITY     = 100;
const int TRIGGER_BUTTON_SENSITIVITY = 5;



//**********************************************************************
//
// グローバル変数
//
//**********************************************************************

namespace
{
	XInputController controller[CONTOROLLER_NUM_MAX];
}






//**********************************************************************
//
// プロトタイプ宣言
//
//**********************************************************************

//================================================================================
//
// [ コントローラーの値設定関数 ]
//
// ｢ 引数 ｣
//
// ･なし
//
// ｢ 戻り値 ｣
//
// ･なし
//
//【 詳細 】
//
// ･コントローラーの値を設定する
//
//================================================================================

void SetController()
{
	for (int i = 0; i < CONTOROLLER_NUM_MAX; i++)
	{
		controller[i].oldState = controller[i].state;

		controller[i].connectionMessage = XInputGetState(i, &controller[i].state);

	}
}



//================================================================================
//
// [ コントローラーのボタン判定関数( HOLD ) ]
//
// ｢ 引数 ｣
//
// ･controllerNum : コントローラー番号
// ･buttonNum     : 判定したいボタン
//
// ｢ 戻り値 ｣
//
// ･bool型 : 押しっぱなしかどうかを返す
//
//【 詳細 】
//
// ･引数で渡されたコントローラーのボタンがHOLD状態かを判定する
//
//================================================================================

bool InputHoldController(int controllerNum, int buttonNum)
{
	if (controller[controllerNum].state.Gamepad.wButtons & buttonNum)
	{
		return true;
	}

	return false;
}



//================================================================================
//
// [ コントローラーのボタン判定関数( TRIG ) ]
//
// ｢ 引数 ｣
//
// ･controllerNum : コントローラー番号
// ･buttonNum     : 判定したいボタン
//
// ｢ 戻り値 ｣
//
// ･bool型 : 押しっぱなしかどうかを返す
//
//【 詳細 】
//
// ･引数で渡されたコントローラーのボタンがTRIG状態かを判定する
//
//================================================================================

bool InputTriggerController(int controllerNum, int buttonNum)
{
	if (controller[controllerNum].state.Gamepad.wButtons & buttonNum)
	{
		if (controller[controllerNum].oldState.Gamepad.wButtons & buttonNum)
		{
			return false;
		}

		return true;
	}

	return false;
}



//================================================================================
//
// [ コントローラーのボタン判定関数( RELEASE ) ]
//
// ｢ 引数 ｣
//
// ･controllerNum : コントローラー番号
// ･buttonNum     : 判定したいボタン
//
// ｢ 戻り値 ｣
//
// ･bool型 : 押しっぱなしかどうかを返す
//
//【 詳細 】
//
// ･引数で渡されたコントローラーのボタンがRELEASE状態かを判定する
//
//================================================================================

bool InputReleaseController(int controllerNum, int buttonNum)
{
	if (controller[controllerNum].oldState.Gamepad.wButtons & buttonNum)
	{
		if (!(controller[controllerNum].state.Gamepad.wButtons & buttonNum))
		{
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [ コントローラーのLスティック判定関数(TRIG ) ]
//
// ｢ 引数 ｣
//
// ･controllerNum : コントローラー番号
//
// ｢ 戻り値 ｣
//
// ･bool型 : ある一定数を超えたら反応する
//
//【 詳細 】
//
// ･引数で渡されたコントローラーのLスティックのTRIGかを判定する
//
//================================================================================

bool InputLStickTriggerController(int controllerNum, int direction)
{
	switch (direction)
	{
		case STICK_UP :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLY      <  STICK_TRIGGER_SENSITIVITY) return false;
			if (controller[ controllerNum ].oldState.Gamepad.sThumbLY >= STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}	
		case STICK_DOWN :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLY    >  -STICK_TRIGGER_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.sThumbLY <= -STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
		case STICK_LEFT :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLX    >  -STICK_TRIGGER_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.sThumbLX <= -STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
		case STICK_RIGHT :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLX    <  STICK_TRIGGER_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.sThumbLX >= STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [ コントローラーのLスティック判定関数(HOLD) ]
//
//================================================================================

bool InputLStickHoldController(int controllerNum, int direction)
{
	switch (direction)
	{
		case STICK_UP :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLY < STICK_HOLD_SENSITIVITY) return false;
			return true;
		}	
		case STICK_DOWN :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLY > -STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
		case STICK_LEFT :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLX > -STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
		case STICK_RIGHT :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLX < STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [コントローラーのR2L2判定関数(TRIG)]
//
//================================================================================

bool InputR2L2TriggerController(int controllerNum, int direction)
{
	switch (direction)
	{
		case TRIGGER_BUTTON_R2 :
		{
			if (controller[controllerNum].state.Gamepad.bRightTrigger    <  TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.bRightTrigger >= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}	
		case TRIGGER_BUTTON_L2 :
		{
			if (controller[controllerNum].state.Gamepad.bLeftTrigger    <  TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.bLeftTrigger >= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [コントローラーのR2L2判定関数(HOLD)]
//
//================================================================================

bool InputR2L2HoldController(int controllerNum, int direction)
{
	switch (direction)
	{
		case TRIGGER_BUTTON_R2 :
		{
			if (controller[controllerNum].state.Gamepad.bRightTrigger < TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}	
		case TRIGGER_BUTTON_L2 :
		{
			if (controller[controllerNum].state.Gamepad.bLeftTrigger < TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [コントローラーのR2L2判定関数(RELEASE)]
//
//================================================================================

bool InputR2L2ReleaseController(int controllerNum, int direction)
{
	switch (direction)
	{
		case TRIGGER_BUTTON_R2 :
		{
			if (controller[controllerNum].state.Gamepad.bRightTrigger    >  TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.bRightTrigger <= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}	
		case TRIGGER_BUTTON_L2 :
		{
			if (controller[controllerNum].state.Gamepad.bLeftTrigger    >  TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.bLeftTrigger <= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [ コントローラーが繋がっているかの判定関数 ]
//
// ｢ 引数 ｣
//
// ･controllerNum : コントローラー番号
//
// ｢ 戻り値 ｣
//
// ･bool型 : 接続されていればtrueを返す
//
//【 詳細 】
//
// ･接続されていればtrueを返す
//
//================================================================================

bool CheckController(int controllerNum)
{
	if (controller[controllerNum].connectionMessage == ERROR_DEVICE_NOT_CONNECTED)
	{
		return false;
	}

	return true;
}



//================================================================================
//
// [ 接続されているコントローラー数の取得関数 ]
//
// ｢ 引数 ｣
//
// ･なし
//
// ｢ 戻り値 ｣
//
// ･int型 : 接続されているコントローラーの数を返す
//
//【 詳細 】
//
// ･接続されているコントローラー数を返す
//
//================================================================================

int GetControllerNum()
{
	int tempNum = 0;

	for (int i = 0; i < CONTOROLLER_NUM_MAX; i++)
	{
		if (controller[i].connectionMessage == ERROR_SUCCESS)
		{
			tempNum++;
		}
	}

	return tempNum;
}



//================================================================================
//
// [ 1台でもコントローラーが接続されているかフラグ関数 ]
//
// ｢ 引数 ｣
//
// ･なし
//
// ｢ 戻り値 ｣
//
// ･int型 : 1台でもコントローラーが接続されていると1を返す
//
//【 詳細 】
//
// ･1台でもコントローラーが接続されていると1を返す
//
//================================================================================

int GetControllerConnect()
{
	for (int i = 0; i < CONTOROLLER_NUM_MAX; i++)
	{
		if (controller[i].connectionMessage == ERROR_SUCCESS)
		{
			return CONNECT_ONE;
		}
	}

	return 0;
}