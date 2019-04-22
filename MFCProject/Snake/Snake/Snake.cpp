#include "Snake.h"
#include <stdio.h>

CSnake::CSnake()
{

}

CSnake::CSnake(int x_pos, int y_pos, int len)
{
	if (len < 1)
	{
		len = 1;
	}

	int i;

	m_length = len;

	m_pPos = new SPoint[m_length + 2];
	m_pPos[0].x = x_pos;
	m_pPos[0].y = y_pos;
	for( i = 1; i < m_length+2; i++)
	{
		m_pPos[i].x = 0;
		m_pPos[i].y = 0;
	}

	m_newSnake.head = S_NONE;
	m_oldSnake.head = S_NONE;
	m_newSnake.body = new MoveState[m_length];
	m_oldSnake.body = new MoveState[m_length];

	for (i = 0; i < m_length; i++)
	{
		m_newSnake.body[i] = S_NONE;
		m_oldSnake.body[i] = S_NONE;
	}
	m_newSnake.tail = S_NONE;
	m_oldSnake.tail = S_NONE;

	m_pStateArray = new BitmapState[m_length + 2];
	for ( i = 0; i < m_length+2; i++)
	{
		m_pStateArray[i] = M_NONE;
	}
}


CSnake::~CSnake()
{
	SAFE_DELETE_ARRAY(m_pStateArray);
	SAFE_DELETE_ARRAY(m_pPos);
}

BitmapState CSnake::GetRightState(MoveState oldDirect, MoveState newDirect)
{
	BitmapState res;
	switch (oldDirect)
	{
	case S_NONE:
		switch (newDirect)
		{
		case S_NONE:
			res = M_NONE;
			break;
		case S_UP:
			res = M_UP_UP;
			break;
		case S_DOWN:
			res = M_DOWN_DOWN;
			break;
		case S_LEFT:
			res = M_LEFT_LEFT;
			break;
		case S_RIGHT:
			res = M_RIGHT_RIGHT;
			break;
		default:
			break;
		}
		break;
	case S_UP:
		switch (newDirect)
		{
		case S_UP:
			res = M_UP_UP;
			break;
		case S_LEFT:
			res = M_UP_LEFT;
			break;
		case S_RIGHT:
			res = M_UP_RIGHT;
			break;
		default:
			break;
		}
		break;
	case S_DOWN:
		switch (newDirect)
		{
		case S_DOWN:
			res = M_DOWN_DOWN;
			break;
		case S_LEFT:
			res = M_DOWN_LEFT;
			break;
		case S_RIGHT:
			res = M_DOWN_RIGHT;
			break;
		default:
			break;
		}
		break;
	case S_LEFT:
		switch (newDirect)
		{
		case S_UP:
			res = M_LEFT_UP;
			break;
		case S_DOWN:
			res = M_LEFT_DOWN;
			break;
		case S_LEFT:
			res = M_LEFT_LEFT;
			break;
		default:
			break;
		}
		break;
	case S_RIGHT:
		switch (newDirect)
		{
		case S_UP:
			res = M_RIGHT_UP;
			break;
		case S_DOWN:
			res = M_RIGHT_DOWN;
			break;
		case S_RIGHT:
			res = M_RIGHT_RIGHT;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return res;
}

void CSnake::Move(void)
{
	int i;
	for (i = 0; i < m_length; i++)
	{
		m_oldSnake.body[i] = m_newSnake.body[i];
	}

	m_newSnake.tail = m_newSnake.body[m_length - 1];
	for (i = m_length-1; i > 0; i--)
	{
		m_newSnake.body[i] = m_newSnake.body[i - 1];
	}
	m_newSnake.body[0] = m_newSnake.head;

	m_pStateArray[0] = GetRightState(m_oldSnake.head, m_newSnake.head);
	for (i = 0; i < m_length; i++)
	{
		m_pStateArray[i + 1] = GetRightState(m_oldSnake.body[i], m_newSnake.body[i]);
	}
	m_pStateArray[m_length + 1] = GetRightState(m_oldSnake.tail, m_newSnake.tail);

	for (i = m_length+1; i > 0; i--)
	{
		m_pPos[i] = m_pPos[i - 1];
	}

	switch (m_newSnake.head)
	{
	default:
		break;
	case S_UP:
		m_pPos[0].y -= SNAKE_MOVE;
		break;
	case S_DOWN:
		m_pPos[0].y += SNAKE_MOVE;
		break;
	case S_LEFT:
		m_pPos[0].x -= SNAKE_MOVE;
		break;
	case S_RIGHT:
		m_pPos[0].x += SNAKE_MOVE;
		break;
	}
}

void CSnake::AddBody(int n)
{
	int i;

	Snake_Struct saveOldSnake, saveNewSnake;
	BitmapState *savestateArray;
	SPoint *savePos;

	savePos = new SPoint[m_length + 2];
	for (i = 0; i < m_length+2; i++)
	{
		savePos[i] = m_pPos[i];
	}
	saveOldSnake.head = m_oldSnake.head;
	saveOldSnake.body = new MoveState[m_length];
	for (i = 0; i < m_length; i++)
	{
		saveOldSnake.body[i] = m_oldSnake.body[i];
	}
	saveOldSnake.tail = m_oldSnake.tail;

	saveNewSnake.head = m_newSnake.head;
	saveNewSnake.body = new MoveState[m_length];
	for ( i = 0; i < m_length; i++)
	{
		saveNewSnake.body[i] = m_newSnake.body[i];
	}
	saveNewSnake.tail = m_newSnake.tail;

	savestateArray = new BitmapState[m_length + 2];
	for (i = 0; i < m_length+2; i++)
	{
		savestateArray[i] = m_pStateArray[i];
	}
	m_length += n;
	delete[] m_oldSnake.body;
	m_oldSnake.body = NULL;
	delete[] m_newSnake.body;
	m_newSnake.body = NULL;
	delete[] m_pStateArray;
	m_pStateArray = NULL;
	delete[] m_pPos;
	m_pPos = NULL;

	m_newSnake.head = S_NONE;
	m_oldSnake.head = S_NONE;
	m_newSnake.body = new MoveState[m_length];
	m_oldSnake.body = new MoveState[m_length];

	for (i = 0; i < m_length; i++)
	{
		m_oldSnake.body[i] = S_NONE;
		m_newSnake.body[i] = S_NONE;
	}
	m_newSnake.tail = S_NONE;
	m_oldSnake.tail = S_NONE;

	m_pStateArray = new BitmapState[m_length + 2];
	for (i = 0; i < m_length+2; i++)
	{
		m_pStateArray[i] = M_NONE;
	}
	m_pPos = new SPoint[m_length + 2];
	for (i = 0; i < m_length+2; i++)
	{
		m_pPos[i].x = 0;
		m_pPos[i].y = 0;
	}
	m_newSnake.head = saveNewSnake.head;
	m_oldSnake.head = saveOldSnake.head;
	for (i = 0; i < m_length-n; i++)
	{
		m_newSnake.body[i] = saveNewSnake.body[i];
		m_oldSnake.body[i] = saveOldSnake.body[i];
	}
	m_newSnake.tail = saveNewSnake.tail;
	m_oldSnake.tail = saveOldSnake.tail;

	for (i = 0; i < m_length - n + 2; i++)
		m_pStateArray[i] = savestateArray[i];
	for (i = 0; i < m_length - n + 2; i++)
		m_pPos[i] = savePos[i];
}

void CSnake::ChangeDirect(MoveState d)
{
	switch (d)
	{
	case S_NONE:
		m_newSnake.head = d;
		break;
	case S_UP:
		if (m_newSnake.head != S_DOWN)
			m_newSnake.head = d;
		break;
	case S_DOWN:
		if (m_newSnake.head != S_UP)
		{
			m_newSnake.head = d;
		}
		break;
	case S_LEFT:
		if (m_newSnake.head != S_RIGHT)
			m_newSnake.head = d;
		break;
	case S_RIGHT:
		if (m_newSnake.head != S_LEFT)
			m_newSnake.head = d;
		break;
	default:
		break;
	}
}

void CSnake::SetHeadPos(int x, int y)
{
	m_pPos[0].x = x;
	m_pPos[0].y = y;
}

BitmapState* CSnake::GetStateArray(void)
{
	return m_pStateArray;
}

SPoint *CSnake::GetPos(void)
{
	return m_pPos;
}

int CSnake::GetLength(void)
{
	return m_length + 2;
}

bool CSnake::IsHeadTouchBody(int x, int y)
{
	int i;

	for (i = 1; i < m_length + 2; i++)
		if (m_pPos[i].x == x && m_pPos[i].y == y)
			return true;

	return false;
}

void CSnake::Initial(void)
{
	SAFE_DELETE_ARRAY(m_pStateArray);
	SAFE_DELETE_ARRAY(m_pPos);
	
	int i;
	int x = 0;
	int y = 0;

	m_length = 1;
	m_pPos = new SPoint[m_length + 2];
	m_pPos[0].x = x;
	m_pPos[0].y = y;
	for (i = 0; i < m_length + 2; i++)
	{
		m_pPos[i].x = 0;
		m_pPos[i].y = 0;
	}
	m_newSnake.head = S_NONE;
	m_oldSnake.head = S_NONE;
	m_newSnake.body = new MoveState[m_length];
	m_oldSnake.body = new MoveState[m_length];
	for ( i = 0; i < m_length; i++)
	{
		m_newSnake.body[i] = S_NONE;
		m_oldSnake.body[i] = S_NONE;
	}
	m_newSnake.tail = S_NONE;
	m_oldSnake.tail = S_NONE;

	m_pStateArray = new BitmapState[m_length];
	for (i = 0; i < m_length + 2; i++)
		m_pStateArray[i] = M_NONE;
}
