/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
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
	void move();
	void ghostMove();
	void collision();
	void restartBerries();
	void handleSuper();
	void ghostRespawn();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text score; //text used for score 
	sf::CircleShape pacMan; // pacman enitity
	sf::RectangleShape ghost; //ghost entity
	sf::CircleShape berries[8]; // berries array
	sf::RectangleShape backGround; //backdrop entity
	sf::RectangleShape ghostWarning; //warning entity

	bool super = false;
	int superTime = 0;

	bool berriesAte[8];
	int powerBerry;
	int scoreNum = 0;

	int speed = 4;

	const float MAX_GHOST_SPEED = 3.5;

	bool ghostDied = false;

	float ghostSpeed = 1;
	int dir = 1;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

