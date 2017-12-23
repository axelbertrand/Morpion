#include "Player.h"

Player::Player(int playerNo) :
	mPlayerNo(playerNo),
	mScore(0)
{

}

Player::~Player()
{

}

bool Player::play(Grid & grid, int x, int y)
{
	int clickedCell = grid.getClickedCell(x, y);
	if (clickedCell < 0)
	{
		return false;
	}

	int i = clickedCell / 3;
	int j = clickedCell % 3;

	if (grid.getGrid(i, j) == 0)
	{
		grid.setGrid(i, j, mPlayerNo);
		if (mPlayerNo == 1)
		{
			grid.drawCross(i, j);
		}
		else if (mPlayerNo == 2)
		{
			grid.drawCircle(i, j);
		}

		return true;
	}

	return false;
}

int Player::checkWin(Grid & grid, int turnNum) const
{
	int winner = 0;

	for (int i = 0; i < 3; ++i)
	{
		if ((grid.getGrid(0, i) == mPlayerNo) && (grid.getGrid(1, i) == mPlayerNo) && (grid.getGrid(2, i) == mPlayerNo))
		{
			winner = mPlayerNo;
			// Dessiner une ligne verticale
		}
		if ((grid.getGrid(i, 0) == mPlayerNo) && (grid.getGrid(i, 1) == mPlayerNo) && (grid.getGrid(i, 2) == mPlayerNo))
		{
			winner = mPlayerNo;
			// Dessiner une ligne horizontale
		}
	}

	if ((grid.getGrid(0, 0) == mPlayerNo) && (grid.getGrid(1, 1) == mPlayerNo) && (grid.getGrid(2, 2) == mPlayerNo))
	{
		winner = mPlayerNo;
		// Dessiner une ligne diagonale NO-SE
	}
	if ((grid.getGrid(2, 0) == mPlayerNo) && (grid.getGrid(1, 1) == mPlayerNo) && (grid.getGrid(0, 2) == mPlayerNo))
	{
		winner = mPlayerNo;
		// Dessiner une ligne diagonale SO-NE
	}

	if (winner == 0 && turnNum >= 9)
	{
		winner = 3; // Egalité
	}

	return winner;
}

void Player::incrementScore()
{
	++mScore;
}

int Player::getScore() const
{
	return mScore;
}
