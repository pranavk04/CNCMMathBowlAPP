#pragma once
#include "framework.h"
#include "XboxGamePad.h"
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <thread>
#include "cxxtimer.hpp"

class App
{

public:
	
	// constructor, sets vertical-sync to be enabled to prevent screen tearing. 
	App();
	
	// calls eventProcess and render, public so it can be accessed by any class. 
	void run();

private:
	
	// processes events such as closing the window, xbox input, and keyboard input. 
	void eventProcessor();

	// draws all needed content to the screen. 
	void render();

	// casts the text for the score to the screen through a variety of different conversions. 
	void textCast();

	// function for the timer. 
	void timer();

	// exists so that application can be open indefinitely without timer starting 
	void startScene();

	// main screen
	void mainScene();

	// essentially same function but for both teams
	void team1AnswerScene();
	void team2AnswerScene();
	
	// scene when time runs out before problem is solved. 
	void timeUpScene();
	
	// essentially same function but for both teams
	void team1WinScene();
	void team2WinScene();

	// essentially same function but for both teams
	void buzzTeam1();
	void buzzTeam2();

	// changes the scene based on logical descisions
	void sceneHandler();

	// key / input detection functions
	void keyCommands();
	void xboxCommands();

	// program window
	sf::RenderWindow window;

	// Xbox game pad pointers for 2 controllers, team1 and team2 
	XboxGamePad* team1 = new XboxGamePad(GamePad_Index_One);
	XboxGamePad* team2 = new XboxGamePad(GamePad_Index_Two);

};