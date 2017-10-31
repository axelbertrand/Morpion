#include "Player.h"

Player::Player(int playerNo) :
	m_playerNo(playerNo),
	m_score(0)
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
		grid.setGrid(i, j, m_playerNo);
		if (m_playerNo == 1)
		{
			grid.drawCross(i, j);
		}
		else if (m_playerNo == 2)
		{
			grid.drawCircle(i, j);
		}

		return true;
	}

	return false;
}

bool Player::checkWin(Grid & grid, int turnNum)
{
	int gagnant = 0;

	for (int i = 0; i < 3; ++i)
	{
		if ((grid.getGrid(0, i) == m_playerNo) && (grid.getGrid(1, i) == m_playerNo) && (grid.getGrid(2, i) == m_playerNo))
		{
			gagnant = m_playerNo;
			// Dessiner une ligne verticale
		}
		if ((grid.getGrid(i, 0) == m_playerNo) && (grid.getGrid(i, 1) == m_playerNo) && (grid.getGrid(i, 2) == m_playerNo))
		{
			gagnant = m_playerNo;
			// Dessiner une ligne horizontale
		}
	}

	if ((grid.getGrid(0, 0) == m_playerNo) && (grid.getGrid(1, 1) == m_playerNo) && (grid.getGrid(2, 2) == m_playerNo))
	{
		gagnant = m_playerNo;
		// Dessiner une ligne diagonale NO-SE
	}
	if ((grid.getGrid(2, 0) == m_playerNo) && (grid.getGrid(1, 1) == m_playerNo) && (grid.getGrid(0, 2) == m_playerNo))
	{
		gagnant = m_playerNo;
		// Dessiner une ligne diagonale SO-NE
	}

	if (gagnant != 0)
	{
		++m_score;
		return gagnant;
	}
	else if (turnNum >= 9)
	{
		return 3; // Egalité
	}
}
