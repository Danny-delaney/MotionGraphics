/// <summary>
/// @author danny delaney
/// @date feb 2024
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 650U, 900U, 32U }, "SFML Game" },
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
		speed = -2;
	}
	if (sf::Keyboard::Right == t_event.key.code)
	{
		speed = 2;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		if (lose = true)
		{
			restart();
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (!lose)
	{
		movement();
		terrianMovement();
		collision();
	}
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	if (lose)
	{
		m_window.draw(loseMessage);
	}
	else
	{
		for (int i = 0; i <= 49; i++)
		{
			m_window.draw(terrain[i]);
		}
		m_window.draw(player);
		m_window.display();
	}
}

void Game::terrianMovement()
{
	for (int i = 0; i <= (terrainNUM - 1); i++)
	{
		sf::Vector2f pos = terrain[i].getPosition();
		pos.y += 2;
		terrain[i].setPosition(pos);
	}
}

void Game::movement()
{
	sf::Vector2f pos = player.getPosition();
	pos.x += speed;
	player.setPosition(pos);
}

void Game::collision()
{
	for (int i = 0; i <= (terrainNUM - 1); i++)
	{
		if (terrainControl[i] == 1)
		{
			if (player.getGlobalBounds().intersects(terrain[i].getGlobalBounds()))
			{
				lose = true;
			}
		}
	}
}

void Game::restart()
{
	lose = false;
	int terrianLevel = -1;
	for (int i = 0; i <= (terrainNUM - 1); i++)
	{
		if (terrainControl[i] == 1)
		{
			terrain[i].setFillColor(sf::Color::Blue);
		}
		if (terrainControl[i] == 0)
		{
			terrain[i].setFillColor(sf::Color::Black);
		}

		if ((i % COLOUMS) == 0)
		{
			terrianLevel++;
		}
		terrain[i].setSize(sf::Vector2f(130.0f, 90.0f));
		terrain[i].setPosition(((i % COLOUMS) * 130), (terrianLevel * 90) - 900);
	}
	player.setFillColor(sf::Color::White);
	player.setPosition(325.0f, 800.0f);
	player.setSize(sf::Vector2f(20.0f, 20.0f));
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
	loseMessage.setFont(m_ArialBlackfont);
	loseMessage.setFillColor(sf::Color::White);
	loseMessage.setString("loser press space to retry");
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	int terrianLevel = -1;
	for (int i = 0; i <= (terrainNUM-1); i++)
	{
		if (terrainControl[i] == 1)
		{
			terrain[i].setFillColor(sf::Color::Blue);
		}
		if (terrainControl[i] == 0)
		{
			terrain[i].setFillColor(sf::Color::Black);
		}

		if ((i % COLOUMS) == 0)
		{
			terrianLevel++;
		}
		terrain[i].setSize(sf::Vector2f(130.0f, 90.0f));
		terrain[i].setPosition(((i % COLOUMS) * 130), (terrianLevel * 90) - 900);
	}
	player.setFillColor(sf::Color::White);
	player.setPosition(325.0f, 800.0f);
	player.setSize(sf::Vector2f(20.0f, 20.0f));
}