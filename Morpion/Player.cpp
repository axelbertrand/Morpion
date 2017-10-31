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
