#pragma once

#define SNAKE_MOVE		(1)
#define SAFE_DELETE(p) {delete p; p = NULL;}
#define SAFE_DELETE_ARRAY(p) {delete [] p; p = NULL;}

enum BitmapState
{
	M_NONE,	M_UP_UP, M_DOWN_DOWN, M_LEFT_LEFT, M_RIGHT_RIGHT,
	M_UP_LEFT, M_UP_RIGHT, M_LEFT_UP, M_LEFT_DOWN,
	M_RIGHT_UP, M_RIGHT_DOWN, M_DOWN_RIGHT, M_DOWN_LEFT
};

enum MoveState
{
	S_NONE,	S_UP, S_DOWN, S_LEFT, S_RIGHT
};

struct SPoint
{
	int x;
	int y;
};

struct Snake_Struct
{
	MoveState head;
	MoveState *body;
	MoveState tail;
};
class CSnake
{
public:
	CSnake();
	CSnake(int x_pos, int y_pos, int len);
	~CSnake();
private:
	int m_length;
	Snake_Struct m_newSnake;
	Snake_Struct m_oldSnake;
	BitmapState *m_pStateArray;
	SPoint *m_pPos;
private:
	BitmapState GetRightState(MoveState oldDirect, MoveState newDirect);
public:
	void Move(void);
	void ChangeDirect(MoveState d);
	void AddBody(int n = 1);
	void SetHeadPos(int x, int y);
	BitmapState * GetStateArray(void);
	SPoint* GetPos(void);
	bool IsHeadTouchBody(int x, int y);
	int GetLength(void);
	void Initial(void);
};

