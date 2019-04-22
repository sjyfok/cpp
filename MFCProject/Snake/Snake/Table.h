#pragma once

#include "Snake.h"

#define TB_STATE_OK		(0)
#define TB_STATE_FOOD	(1)
#define TB_STATE_BLOCK	(2)
#define TB_STATE_SBLOCK	(3)


class CSTable
{
public:
	CSTable();
	~CSTable();
private:
	int m_width;
	int m_height;
	int m_foodNumber;
	int m_blockNumber;
	CSnake m_snake;
	int **m_board;
public:
	void InitialTable(int w, int h);
	bool AddBlock(int x, int y);
	bool AddFood(int x, int y);
	bool ClearFood(int x, int y);

	CSnake *GetSnake(void);
	int **GetBoard(void);
	int GetData(int x, int y);
	
	void SnakeMove(void);
	bool ChangeSnakeDirect(MoveState d);
};

