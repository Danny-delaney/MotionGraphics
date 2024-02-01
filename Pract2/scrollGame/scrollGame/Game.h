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
	void terrianMovement();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // control exiting game

	static const int terrainNUM = 50;

	int ROWS = 10;
	int COLOUMS = 5;
	int terrainControl[terrainNUM] = {
		1,1,0,1,1,
		1,1,0,0,1,
		1,1,0,0,1,
		1,1,0,0,1,
		1,1,0,1,1,
		1,1,0,1,1,
		1,0,0,1,1,
		1,0,0,1,1,
		1,0,0,1,1,
		1,1,0,1,1,
	};
	sf::RectangleShape terrain[50];

};

#endif // !GAME_HPP

