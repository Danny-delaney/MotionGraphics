/// <summary>
/// @author Danny Delaney
/// @date 16 January 20124
/// </summary>

#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Left == t_event.key.code)
	{
		dir = 0;
	}
	if (sf::Keyboard::Right == t_event.key.code)
	{
		dir = 1;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	move();
	collision();
	restartBerries();
	handleSuper();
	if (ghostDied)
	{
		ghostRespawn();
	}
	else
	{
		ghostMove();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(backGround);
	for (int i = 0; i < 8; i++)
	{
		if (!berriesAte[i])
		{
			m_window.draw(berries[i]);
		}
	}
	if (ghostDied) 
	{
		m_window.draw(ghostWarning);
	}
	m_window.draw(ghost);
	m_window.draw(pacMan);
	m_window.draw(score);
	m_window.display();
}

void Game::move()
{
	sf::Vector2f pos = pacMan.getPosition();
	if (dir == 1)
	{
		pos.x += speed;
		if (pos.x >= 850)
		{
			pos.x = -49;
		}
		pacMan.setPosition(pos);
	}
	else
	{
		pos.x -= speed;
		if (pos.x <= -50)
		{
			pos.x = 849;
		}
		pacMan.setPosition(pos);
	}
}

void Game::ghostMove()
{
	sf::Vector2f pacmanPos = pacMan.getPosition();
	sf::Vector2f pos = ghost.getPosition();
	if (pacmanPos.x > pos.x)
	{
		if (super)
		{
			pos.x -= ghostSpeed - 0.5;
		}
		else
		{
			pos.x += ghostSpeed;
		}
		ghost.setPosition(pos);
	}
	else
	{
		if (super)
		{
			pos.x += ghostSpeed - 0.5;
		}
		else
		{
			pos.x -= ghostSpeed;
		}
		ghost.setPosition(pos);
	}
}

void Game::collision()
{
	if (pacMan.getGlobalBounds().intersects(ghost.getGlobalBounds() ))
	{
		if (!ghostDied)
		{
			if (super)
			{
				scoreNum += 100;
				ghostDied = true;
				ghost.setFillColor(sf::Color::White);
				score.setString(std::to_string(scoreNum));
			}
			else
			{
				m_exitGame = true;
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (pacMan.getGlobalBounds().intersects(berries[i].getGlobalBounds()))
		{
			berriesAte[i] = true;
			berries[i].setPosition((100.0f * i) + 50.0f, 700.0f);
			scoreNum += 10;
			score.setString(std::to_string(scoreNum));
			if (i == powerBerry)
			{
				super = true;
				superTime = 100;
			}
		}
	}
}

void Game::restartBerries()
{
	bool allAte = true;

	for (int i = 0; i < 8; i++)
	{
		if (!berriesAte[i])
		{
			allAte = false;
		}
	}
	if (allAte)
	{
		berries[powerBerry].setRadius(20);
		berries[powerBerry].setOrigin(20.0f, 20.0f);
		berries[powerBerry].setFillColor(sf::Color::Green);
		berries[powerBerry].setPosition((100.0f * powerBerry) + 50.0f, 300.0f);

		scoreNum += 50;
		score.setString(std::to_string(scoreNum));

		float speedDiffrence = MAX_GHOST_SPEED - ghostSpeed;
		ghostSpeed += (speedDiffrence/2);

		powerBerry = rand() % 8;
		for (int i = 0; i < 8; i++)
		{
			berriesAte[i] = false;
			berries[i].setPosition((100.0f * i) + 50.0f, 300.0f);

			if (i == powerBerry)
			{
				berries[i].setRadius(30);
				berries[i].setOrigin(30.0f, 30.0f);
				berries[i].setFillColor(sf::Color::Cyan);
				berries[i].setPosition((100.0f * i) + 50.0f, 300.0f);
			}
		}
	}
}

void Game::handleSuper()
{
	if (super)
	{
		if (superTime <= 0)
		{
			super = false;
			ghost.setFillColor(sf::Color::Red);
		}
		else
		{
			superTime -= 1;
			ghost.setFillColor(sf::Color::Blue);
		}
	}
}

void Game::ghostRespawn()
{
	sf::Vector2f pos = ghost.getPosition();
	ghost.setFillColor(sf::Color::Transparent);
	if (pos.x > 400)
	{
		ghostWarning.setPosition(790.0f, 200.0f);
		pos.x += ghostSpeed;
		ghost.setPosition(pos);
		if (pos.x > 850)
		{
			ghostDied = false;
			ghost.setFillColor(sf::Color::Red);
		}
	}
	else
	{
		ghostWarning.setPosition(0.0f, 200.0f);
		pos.x -= ghostSpeed;
		ghost.setPosition(pos);
		if (pos.x < -50)
		{
			ghostDied = false;
			ghost.setFillColor(sf::Color::Red);
		}
	}
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	score.setFont(m_ArialBlackfont);
	score.setCharacterSize(60);
	score.setPosition(0.0f, 540.0f);
	score.setString(std::to_string(scoreNum));
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	pacMan.setRadius(50);
	pacMan.setOrigin(50.0f, 50.0f);
	pacMan.setFillColor(sf::Color::Yellow);
	pacMan.setPosition(200.0f, 300.0f);

	ghost.setSize(sf::Vector2f(70.0f, 100.0f));
	ghost.setOrigin(35.0f, 50.0f);
	ghost.setFillColor(sf::Color::Red);
	ghost.setPosition(600.0f, 300.0f);

	powerBerry = 7;
	for (int i = 0; i < 8; i++)
	{
		if (i == powerBerry)
		{
			berries[powerBerry].setRadius(30);
			berries[powerBerry].setOrigin(30.0f, 30.0f);
			berries[powerBerry].setFillColor(sf::Color::Cyan);
			berries[powerBerry].setPosition((100.0f * powerBerry) + 50.0f, 300.0f);
			berriesAte[powerBerry] = false;
		}
		else
		{
			berries[i].setRadius(20);
			berries[i].setOrigin(20.0f, 20.0f);
			berries[i].setFillColor(sf::Color::Green);
			berries[i].setPosition((100.0f * i) + 50.0f, 300.0f);
			berriesAte[i] = false;
		}
	}

	backGround.setSize(sf::Vector2f(800.0f, 200.0f));
	backGround.setFillColor(sf::Color::Black);
	backGround.setPosition(0.0f, 200.0f);
	backGround.setOutlineThickness(10.0f);
	backGround.setOutlineColor(sf::Color::Magenta);

	ghostWarning.setSize(sf::Vector2f(10.0f, 200.0f));
	ghostWarning.setFillColor(sf::Color::White);
	ghostWarning.setPosition(0.0f, 200.0f);
}

