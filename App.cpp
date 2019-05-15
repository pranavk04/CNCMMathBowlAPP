#include "App.h"
// app header file

// since most functions being used are in the sf{} namespace, this is most appropriate
using namespace sf;

// initial score values set to 0
int t1Score = 0, t2Score = 0;

// drawable text class for the scores and timer
Text team1S, team2S;
Text timerText;

// font class for the text font.
Font font;

//texture and sprite for main scene
Texture Background;
Sprite back;

// texture and background for the team 1 answer scene
Texture Team1Answer;
Sprite T1Answer;

// texture and background for the team 2 answer scene. 
Texture Team2Answer;
Sprite T2Answer;

// texture and bakground for the team 1 win screen. 
Texture Team1Win;
Sprite T1Win;

// texture and background for the team 2 win screen. 
Texture Team2Win;
Sprite T2Win;

// texture and background for the start screen. 
Texture StartScreen;
Sprite Start;

// texture and background for the time up screen. 
Texture TimeUp;
Sprite timeUp;

// inital scene set to start. 
char Scene = 'S';

// event class allows us to poll for events such as resize or window.close()
Event event;

// declares the timer for the questions. 
cxxtimer::Timer MBTimer = new cxxtimer::Timer(false);

// constructor, enables v-sync
App::App() : window(VideoMode(800, 800), "CNCM MathBowl") // also defines extra window properties
{
	window.setVerticalSyncEnabled(true);
}

// processes ALL input. 
void App::eventProcessor()
{
	// while the window is open basically
	while (window.pollEvent(event))
	{
		// if someone clicks the close button
		if (event.type == Event::Closed)
			window.close();
		
		// calls the key input functions
		keyCommands();

		// if both controllers are connected
		if (team1->is_connected() && team2->is_connected())
		{
			// upadate the states constantly
			team1->update();
			team2->update();

			// calls the xbox input function 
			xboxCommands();

		}
	}
}

// casts the (int)score to drawable (sf::Text) format
void App::textCast()
{
	// loads font from file by passive if statement, STDERR if unable to find
	if (!font.loadFromFile("C:\\Windows\\Fonts\\abel-regular.ttf"))
	{
		std::cerr << "Error: could not load font.\n";
	}
	
	// sets the font 
	team1S.setFont(font);
	team2S.setFont(font);

	// the stringstream is used to convert from int to std::string
	std::stringstream t1, t2;

	// reads t1score into t1
	t1 << t1Score;
	
	// sets the string for the text to be the score
	team1S.setString(t1.str());
	// sets the position on the xy plane
	team1S.setPosition(90, 679);
	// sets the fill color to be red.
	team1S.setFillColor(Color::Red);

	// reads t2score into t2
	t2 << t2Score;

	// sets the string for the text to be the score
	team2S.setString(t2.str());
	// sets the position on the xy plane 
	team2S.setPosition(Vector2f(650, 679));
	// sets the fill color to be red 
	team2S.setFillColor(Color::Blue);

	// sets the font size to be 30 px 
	team1S.setCharacterSize(30);
	team2S.setCharacterSize(30);

}

void App::timer()
{
	// sets the timer font 
	timerText.setFont(font);
	
	// similar to text cast, stringstream converts the long long std::chrono::seconds into a drawable string
	std::stringstream timerStream;
	
	// reads the current timer time. 
	timerStream << MBTimer.count<std::chrono::seconds>();

	// sets fill color black
	timerText.setFillColor(Color::Black);
	// sets the string to be the time. 
	timerText.setString("Seconds spent answering question: " + timerStream.str());
	// sets postition on xy plane
	timerText.setPosition(10, 720);
	// sets font size to 40 px
	timerText.setCharacterSize(40);

	// if the timer exceeds 1.5 minutes, change scene and reset the timer [stop it also]
	if (MBTimer.count<std::chrono::seconds>() > 90)
	{
		Scene = 't';
		MBTimer.reset();
	}

}

void App::render()
{
	// starts the initial timer, clears the window white after each time for minimal disturbance. 
	timer();
	window.clear(Color::White);
	sceneHandler();

	// displays all drawn objects. 
	window.display();

}

void App::team1AnswerScene()
{
	// load by passive reference. 
	if (!Team1Answer.loadFromFile("C:\\Users\\Pranav\\Desktop\\t1Answer.png", IntRect(0, 0, 800, 800)))
	{
		std::cerr << "Error: Could not Load Image.";
	}

	// sets the IntRect texture as the image, draws on the screen. 
	T1Answer.setTexture(Team1Answer);

	// draws the object
	window.draw(T1Answer);
}

void App::team2AnswerScene()
{
	// load by passive reference. 
	if (!Team2Answer.loadFromFile("C:\\Users\\Pranav\\Desktop\\t2Answer.png", IntRect(0, 0, 800, 800)))
	{
		std::cerr << "Error: Could not Load Image";
	}

	// sets the IntRect texture as the image, draws on the screen. 
	T2Answer.setTexture(Team2Answer);

	// draws the object
	window.draw(T2Answer);
}

void App::timeUpScene()
{
	// load by passive reference. 
	if (!TimeUp.loadFromFile("C:\\Users\\Pranav\\Desktop\\timeUp.png", IntRect(0, 0, 800, 800)))
	{
		std::cerr << "Error: Could not Load Image";
	}

	// sets the IntRect texture as the image, draws on the screen. 
	timeUp.setTexture(TimeUp);

	// draws the object
	window.draw(timeUp);
}

void App::team1WinScene()
{
	// load by passive reference. 
	if (!Team1Win.loadFromFile("C:\\Users\\Pranav\\Desktop\\t1win.png", IntRect(0, 0, 800, 800)))
	{
		std::cerr << "Error: Could not load image";
	}

	// sets the IntRect texture as the image, draws on the screen. 
	T1Win.setTexture(Team1Win);

	// draws the object
	window.draw(T1Win);
}

void App::team2WinScene()
{
	// load by passive reference. 
	if (!Team2Win.loadFromFile("C:\\Users\\Pranav\\Desktop\\t2win.png", IntRect(0, 0, 800, 800)))
	{
		std::cerr << "Error: Could not load image";
	}

	// sets the IntRect texture as the image, draws on the screen. 
	T2Win.setTexture(Team2Win);

	// draws the object
	window.draw(T2Win);
}

void App::startScene()
{
	// load by passive reference. 
	if (!StartScreen.loadFromFile("start_screen.png", IntRect(0, 0, 800, 800)))
	{
		std::cerr << "Error: Could not load image";
	}

	// sets the IntRect texture as the image, draws on the screen. 
	Start.setTexture(StartScreen);

	// draws the object
	window.draw(Start);
}

// the main scene, with the scores and the timer. 
void App::mainScene() 
{
	// load by passive reference, also starts the timer and casts text to screen. 
	if (!Background.loadFromFile("C:\\Users\\Pranav\\Desktop\\cncmBackground.png", IntRect(0, 0, 800, 800)))
	{
		std::cerr << "Could not load background texture." << std::endl;
	}

	// starts the timer
	MBTimer.start();
	
	// sets IntRect texture as the image 
	back.setTexture(Background);

	//calls textcast
	textCast();
	//draws objects
	window.draw(back);
	window.draw(team1S);
	window.draw(team2S);
	window.draw(timerText);
}

void App::sceneHandler()
{
	// a switch statement that draws the different scenes on the screen based on (char)Scene. 
	switch (Scene)
	{
	case 'S':
		startScene();
		break;
	case 'M':
		mainScene();
		break;
	case 't':
		timeUpScene();
		break;
	case '1':
		team1AnswerScene();
		break;
	case '2':
		team2AnswerScene();
		break;
	case 'O':
		team1WinScene();
		break;
	case 'T':
		team2WinScene();
		break;
	// if by any bug the scene is not one of the above, do nothing and STDERR 
	default:
		std::cerr << "invalid scene";
		break;
	}
}

void App::run()
{

	// while the window is open, process and draw
	while (window.isOpen())
	{
		eventProcessor();
		render();
	}
}

void App::keyCommands()
{
	// checks that the scene is correct before moving onto specfic key controls for each scene
	if (Scene == 'S' && Keyboard::isKeyPressed(Keyboard::Enter))
		Scene = 'M';
	
	if (Scene == 'O' && Keyboard::isKeyPressed(Keyboard::Escape))
		window.close();
	
	if (Scene == 'T' && Keyboard::isKeyPressed(Keyboard::Escape))
		window.close();

	if (Scene == '1' && Keyboard::isKeyPressed(Keyboard::C))
	{
		// adds to the score and resets[stops] the timer
		t1Score++;
		MBTimer.reset();
		Scene = 'M';
	}

	if (Scene == '1' && Keyboard::isKeyPressed(Keyboard::W))
		Scene = 'M';

	if (Scene == '1' && Keyboard::isKeyPressed(sf::Keyboard::Num1))
		Scene = 'O';

	if (Scene == '1' && Keyboard::isKeyPressed(Keyboard::Num2))
		Scene = 'T';

	if (Scene == '2' && Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		// adds to the score and resets[stops] the timer 
		t2Score++;
		MBTimer.reset();
		Scene = 'M';
	}

	if (Scene == '2' && Keyboard::isKeyPressed(sf::Keyboard::W))
		Scene = 'M';
	
	if (Scene == '2' && Keyboard::isKeyPressed(sf::Keyboard::Num1))
		Scene = 'O';

	if (Scene == '2' && Keyboard::isKeyPressed(Keyboard::Num2))
		Scene = 'T';

	if (Scene == 't' && Keyboard::isKeyPressed(Keyboard::C))
	{
		// adds to the score 
		t1Score++;
		Scene = 'M';
	}

	if (Scene == 't' && Keyboard::isKeyPressed(Keyboard::W))
	{
		// adds to the score 
		t2Score++;
		Scene = 'M';
	}

	if (Scene == 't' && Keyboard::isKeyPressed(Keyboard::N))	
		Scene = 'M';

}

void App::buzzTeam1()
{
	// stops timer and changes scene
	MBTimer.stop();
	Scene = '1';
}

void App::buzzTeam2()
{
	// stops timer and changes scene
	MBTimer.stop();
	Scene = '2';
}

void App::xboxCommands()
{
	// Team 1 Xbox Controller, any button press triggers the buzz

	if (team1->State._buttons[GamePad_Button_A])
		buzzTeam1();

	if (team1->State._buttons[GamePad_Button_B])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_X])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_Y])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_LEFT_SHOULDER])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_RIGHT_SHOULDER])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_LEFT_THUMB])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_RIGHT_THUMB])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_DPAD_UP])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_DPAD_DOWN])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_DPAD_LEFT])
		buzzTeam1();
	
	if (team1->State._buttons[GamePad_Button_DPAD_RIGHT])
		buzzTeam1();

	// Team 2 Xbox Controller, same as above

	if (team2->State._buttons[GamePad_Button_A])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_B])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_X])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_Y])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_LEFT_SHOULDER])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_RIGHT_SHOULDER])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_LEFT_THUMB])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_RIGHT_THUMB])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_DPAD_UP])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_DPAD_DOWN])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_DPAD_LEFT])
		buzzTeam2();
	
	if (team2->State._buttons[GamePad_Button_DPAD_RIGHT])
		buzzTeam2();
}