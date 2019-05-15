#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <Xinput.h>
#include "Vector2.h"
#pragma comment(lib, "xinput.lib")

// creates an enum for every button on the xbox controller, such that code is much more understandable than using numbers 1-14. 
typedef enum
{
	GamePad_Button_DPAD_UP = 0,
	GamePad_Button_DPAD_DOWN = 1,
	GamePad_Button_DPAD_LEFT = 2,
	GamePad_Button_DPAD_RIGHT = 3,
	GamePad_Button_START = 4,
	GamePad_Button_BACK = 5,
	GamePad_Button_LEFT_THUMB = 6,
	GamePad_Button_RIGHT_THUMB = 7,
	GamePad_Button_LEFT_SHOULDER = 8,
	GamePad_Button_RIGHT_SHOULDER = 9,
	GamePad_Button_A = 10,
	GamePad_Button_B = 11,
	GamePad_Button_X = 12,
	GamePad_Button_Y = 13,
	GamePadButton_Max = 14
} GamePadButton;

// created an enum for the 4 players supported by xinput, although in our case we only need 2. 
typedef enum {
	GamePad_Index_One = 0,
	GamePad_Index_Two = 1,
	GamePad_Index_Three = 2,
	GamePad_Index_Four = 3
} GamePadIndex;

// a structure for the state of the controller, holding values such as the r/l joystick position, trigger position, and the reset state function. 
struct GamePadState
{
	bool _buttons[GamePadButton_Max];
	vector2	_left_thumbstick;
	vector2 _right_thumbstick;
	float _left_trigger;
	float _right_trigger;
	void reset()
	{
		for (int i = 0; i < (int)GamePadButton_Max; ++i) _buttons[i] = false;
		_left_thumbstick.set(0.0f, 0.0f);
		_right_thumbstick.set(0.0f, 0.0f);
		_left_trigger = _right_trigger = 0.0f;
	}
};

// actual xbox controller class. 
class XboxGamePad
{
public:
	// constructor. defines the xbox controller with the playerID of the @param. 
	XboxGamePad(GamePadIndex player);

	//destructor. Prevents vibration when disconnecting the controller. 
	virtual ~XboxGamePad(void);
	
	// function returning a boolean as to whether the controller is connected. 
	bool is_connected();

	// function that sets motor values so that the controller can vibrate. 
	void vibrate(float leftmotor = 0.0f, float rightmotor = 0.0f);

	// function called in a while loop that updates the state of every button defined in it on whether it is pressed down or not. 
	void update();

public:
	// state of the controller, previous struct. 
	GamePadState State;
private:
	// library defined state and player index, constructor used to set this internally. 
	XINPUT_STATE _controllerState;
	GamePadIndex _playerIndex;

};