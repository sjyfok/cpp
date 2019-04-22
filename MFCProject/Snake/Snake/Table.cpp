#include "Table.h"
#include "Snake.h"
#include <stdio.h>



CSTable::CSTable()
{

}

CSTable::~CSTable()
{
}


void CSTable::InitialTable(int w, int h)
{
	int i, j;
	m_width = w;
	m_height = h;

	m_snake.Initial();
	if (m_board != NULL)
	{
		SAFE_DELETE_ARRAY(m_board);
	} 
	m_board = new int*[m_height];
	for (i = 0; i < h; i++)
	{
		m_board[i] = new int[m_width];
		for (j = 0; j < w; j++)
			m_board[i][j] = 0;
	}
	for (i = 0; i < h; i ++)
	{
		m_board[i][0] = TB_STATE_SBLOCK;
		m_board[i][m_width - 1] = TB_STATE_SBLOCK;
	}
	for ( i = 0; i < w; i++)
	{
		m_board[0][i] = TB_STATE_SBLOCK;
		m_board[m_height - 1][i] = TB_STATE_SBLOCK;
	}

}

bool CSTable::AddBlock(int x, int y)
{
	if ((x>=0)&&x<m_width&&(y>=0)&&(y<m_height)&&(m_board[y][x] = TB_STATE_OK))
	{
		m_board[y][x] = TB_STATE_BLOCK;
		++m_blockNumber;
		return true;
	}
	else
	{
		return false;
	}
}

bool CSTable::AddFood(int x, int y)
{
	if ((x>0)&&(x<m_width)&&(y>=0)&&(y<m_height)&&(m_board[y][x] ==TB_STATE_OK))
	{
		m_board[y][x] = TB_STATE_FOOD;
		++m_foodNumber;
		return true;
	}
	else
	{
		return false;
	}
}

bool CSTable::ClearFood(int x, int y)
{
	m_board[y][x] = TB_STATE_OK;
	return true;
}

CSnake * CSTable::GetSnake(void)
{
	return &m_snake;
}

int **CSTable::GetBoard(void)
{
	return m_board;
}

int CSTable::GetData(int x, int y)
{
	return m_board[y][x];
}

void CSTable::SnakeMove(void)
{
	m_snake.Move();
}

bool CSTable::ChangeSnakeDirect(MoveState d)
{
	m_snake.ChangeDirect(d);
	return true;
}