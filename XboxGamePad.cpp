#include "XboxGamePad.h"

// xbox controller class constructor. sets the XInput player index equal to the @param. 
XboxGamePad::XboxGamePad(GamePadIndex player)
{
	_playerIndex = player;
}

// xbox controller class destructor. prevents vibration. 
XboxGamePad::~XboxGamePad()
{
	if (is_connected())
		vibrate(0.0f, 0.0f);
}

// detects whether or not a controller is connected. 
bool XboxGamePad::is_connected()
{
	// clears the controllerState. 
	memset(&_controllerState, 0, sizeof(XINPUT_STATE));

	// gets the XInput state on whether or not the controller is connected. 
	DWORD Result = XInputGetState(_playerIndex, &_controllerState);

	// if result = connected, return true else false 
	if (Result == ERROR_SUCCESS)
		return true;
	else
		return false;
}

void XboxGamePad::vibrate(float rightmotor, float leftmotor)
{
	// defines the XINput vibration
	XINPUT_VIBRATION vibration;
	
	// clears the vibration 
	memset(&vibration, 0, sizeof(XINPUT_VIBRATION));

	// sets motor speed for vibration 
	int leftVib = (int)(leftmotor * 65535.0f);
	int rightVib = (int)(rightmotor * 65535.0f);

	// sets the motor speed 
	vibration.wLeftMotorSpeed = leftVib;
	vibration.wRightMotorSpeed = rightVib;

	// sets the state for vibration
	XInputSetState((int)_playerIndex, &vibration);
}

void XboxGamePad::update()
{
	//resets the state (so button only registers as pressed once)
	State.reset();

	// trigger detection, because it works by detecting whether or not you have passed a threshold for input or not. 
	if (_controllerState.Gamepad.bRightTrigger && _controllerState.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		State._right_trigger = _controllerState.Gamepad.bRightTrigger / 255.0f;
	}

	// same thing for the left trigger. 
	if (_controllerState.Gamepad.bLeftTrigger && _controllerState.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		State._left_trigger = _controllerState.Gamepad.bLeftTrigger / 255.0f;
	}

	// The following long if statement bash is required for every button you attempt to detect. it sets the State to be true for the button when detected. 
	// Adding a new button requires adding a new if statement. 
	// it cross checks with the XInput detection and the _controllerState. 
	// So far the buttons are : ABXY, DPAD, L/R Shoulder and Thumb Buttons. 
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		State._buttons[GamePad_Button_A] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		State._buttons[GamePad_Button_B] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		State._buttons[GamePad_Button_X] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		State._buttons[GamePad_Button_Y] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		State._buttons[GamePad_Button_DPAD_DOWN] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		State._buttons[GamePad_Button_DPAD_UP] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		State._buttons[GamePad_Button_DPAD_LEFT] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		State._buttons[GamePad_Button_DPAD_RIGHT] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		State._buttons[GamePad_Button_LEFT_SHOULDER] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
		State._buttons[GamePad_Button_LEFT_THUMB] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		State._buttons[GamePad_Button_RIGHT_SHOULDER] = true;

	// Since the joystick has a deadzone, detecting it works a little differently. 
	if ((_controllerState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		_controllerState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(_controllerState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			_controllerState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		_controllerState.Gamepad.sThumbLX = 0;
		_controllerState.Gamepad.sThumbLY = 0;
	}

	// updates the struct values with the get() values. 
	float leftThumbY = _controllerState.Gamepad.sThumbLY;
	if (leftThumbY)
	{
		State._left_thumbstick.Y = leftThumbY;
	}

	// does the same for the X value. 
	float leftThumbX = _controllerState.Gamepad.sThumbLX;
	if (leftThumbX)
	{
		State._left_thumbstick.X = leftThumbX;
	}

	// same thing for right Y value. 
	float rightThumbY = _controllerState.Gamepad.sThumbRY;
	if (rightThumbY)
	{
		State._right_thumbstick.Y = rightThumbY;
	}

	// same thing for right X value. 
	float rightThumbX = _controllerState.Gamepad.sThumbRX;
	if (rightThumbX)
	{
		State._right_thumbstick.X = rightThumbX;
	}

}