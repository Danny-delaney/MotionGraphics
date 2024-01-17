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
	ghostMove();
	collision();
	restartBerries();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Blue);
	m_window.draw(backGround);
	for (int i = 0; i < 8; i++)
	{
		if (!berriesAte[i])
		{
			m_window.draw(berries[i]);
		}
	}
	m_window.draw(ghost);
	m_window.draw(pacMan);
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
			pos.x -= ghostSpeed;
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
			pos.x += ghostSpeed;
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
		m_exitGame = true;
	}
	for (int i = 0; i < 8; i++)
	{
		if (pacMan.getGlobalBounds().intersects(berries[i].getGlobalBounds()))
		{
			berriesAte[i] = true;
			if (i == powerBerry)
			{
				super = true;
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

		powerBerry = rand() % 8;
		for (int i = 0; i < 8; i++)
		{
			berriesAte[i] = false;

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

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
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

	powerBerry = rand() % 8;
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
}

