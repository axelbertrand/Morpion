#pragma once

#include "Defs.h"
#include "Grid.h"

class Player
{
	public :
		Player(int playerNo);
		~Player();

		bool play(Grid &grid, int x, int y);

	private :
		int m_playerNo;
		int m_score;
};

