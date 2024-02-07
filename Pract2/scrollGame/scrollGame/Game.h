/// <summary>
/// @author danny delaney
/// @date feb 2024
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void terrianMovement();
	void movement();
	void collision();
	void shoot();

	void restart();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text loseMessage;

	bool m_exitGame; // control exiting game
	bool lose = false;

	int speed = 0;

	static const int terrainNUM = 250;

	int COLOUMS = 5;
	int terrainControl[terrainNUM] = {
		1,1,0,1,1,
		1,1,0,0,2,
		1,1,0,0,1,
		1,2,0,0,1,
		1,1,0,1,1,
		1,1,0,1,1,
		1,0,0,1,1,
		1,0,0,2,1,
		1,0,0,1,1,
		1,2,0,1,1,
		1,1,0,1,1,
		1,1,0,0,2,
		1,1,0,0,1,
		1,2,0,0,1,
		1,1,0,1,1,
		1,1,0,1,1,
		1,0,0,1,1,
		1,0,0,2,1,
		1,0,0,1,1,
		1,2,0,1,1,
		1,1,0,1,1,
		1,1,0,0,2,
		1,1,0,0,1,
		1,2,0,0,1,
		1,1,0,1,1,
		1,1,0,1,1,
		1,0,0,1,1,
		1,0,0,2,1,
		1,0,0,1,1,
		1,2,0,1,1,
		1,1,0,1,1,
		1,1,0,0,2,
		1,1,0,0,1,
		1,2,0,0,1,
		1,1,0,1,1,
		1,1,0,1,1,
		1,0,0,1,1,
		1,0,0,2,1,
		1,0,0,1,1,
		1,2,0,1,1,
		1,1,0,1,1,
		1,1,0,0,2,
		1,1,0,0,1,
		1,2,0,0,1,
		1,1,0,1,1,
		1,1,0,1,1,
		1,0,0,1,1,
		1,0,0,2,1,
		1,0,0,1,1,
		1,2,0,1,1
	};
	sf::RectangleShape terrain[250];
	sf::RectangleShape player;
	sf::CircleShape bullets[10];

};

#endif // !GAME_HPP

