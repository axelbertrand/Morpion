#pragma once

#include "Defs.h"
#include "Grid.h"

class Player
{
	public :
		Player(int playerNo);
		~Player();

		bool play(Grid &grid, int x, int y);
		int checkWin(Grid &grid, int turnNum) const;

		void incrementScore();
		int getScore() const;

	private :
		int mPlayerNo;
		int mScore;
};

