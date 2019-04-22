#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include "resource.h"
#include "Table.h"
#include "Snake.h"


#define GAME_STATE_WAIT		(0)
#define GAME_STATE_RUN		(1)
#define GAME_STATE_END		(2)

#define   WALL_WIDTH	 (80)
#define   WALL_HEIGHT	 (80)

#define BMP_SCORE_BOARD_WIDTH		(256)
#define BMP_SCORE_BOARD_HEIGHT		(55)

#define BMP_WALL_WIDTH			(16)
#define BMP_WALL_HEIGHT			(16)

HDC windowDC = NULL;
HDC bufferDC = NULL;
HDC picDC = NULL;
HDC endDC = NULL;
HDC scoreDC = NULL;

HBITMAP picBMP = NULL;
HBITMAP bufferBMP = NULL;
HBITMAP endBMP = NULL;
HBITMAP hbmpWall = NULL;
HBITMAP hbmpScore = NULL;

HBRUSH hbrushWall = NULL;

HWND hAppWnd = NULL;

UINT uSnakeMoveTimer;
UINT uFoodAddTimer;

RECT g_ClientRect;
int g_iClientWidth;
int g_iClientHeight;

CSTable table;
int tableBlockWidth;
int tableBlockHeight;
int iScores = 0;

UINT uGameState = GAME_STATE_WAIT;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam);
void StartGame();
void ShellDraw(HDC hdc);
void OnTimer(UINT uTIMER_ID);
void GameAreaDraw(HDC hdc);
void EndGame(void);

int WINAPI WinMain(HINSTANCE hCurrentInst, HINSTANCE hPrevInstance,
	PSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS wndClass;
	HWND hWnd;
	MSG msg;
	UINT width, height;


	//定义窗口
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hCurrentInst;
	wndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_MAIN));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "Snake_CLASS";
	//注册窗口
	RegisterClass(&wndClass);


	//取整个屏幕的尺寸	
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);
	//创建窗口
	hWnd = CreateWindow(
		"Snake_CLASS",
		"skyblue snake",
		WS_POPUP,
		0, 0,
		width, height,
		NULL, NULL,
		hCurrentInst,
		NULL);

	hAppWnd = hWnd;

	//显示窗口
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	GetClientRect(hAppWnd, &g_ClientRect);
	g_iClientWidth = g_ClientRect.right - g_ClientRect.left;
	g_iClientHeight = g_ClientRect.bottom - g_ClientRect.top;

	tableBlockWidth = (g_iClientWidth - 2 * WALL_WIDTH) / 20;
	tableBlockHeight = (g_iClientHeight - 2 * WALL_HEIGHT) / 20;

	windowDC = GetDC(hAppWnd);
	bufferDC = CreateCompatibleDC(windowDC);
	picDC = CreateCompatibleDC(windowDC);
	endDC = CreateCompatibleDC(windowDC);
	scoreDC = CreateCompatibleDC(windowDC);
	bufferBMP = CreateCompatibleBitmap(windowDC, g_iClientWidth, g_iClientHeight);
	picBMP = (HBITMAP)LoadImage(NULL, "snake.bmp", IMAGE_BITMAP, 160, 80, LR_LOADFROMFILE);
	hbmpWall = (HBITMAP)LoadImage(NULL, "brick.bmp", IMAGE_BITMAP, 16, 16, LR_LOADFROMFILE);
	endBMP = (HBITMAP)LoadImage(NULL, "end.bmp", IMAGE_BITMAP, 369, 300, LR_LOADFROMFILE);
	hbmpScore = (HBITMAP)LoadImage(NULL, "scoreboard.bmp", IMAGE_BITMAP, 265, 55, LR_LOADFROMFILE);

	SelectObject(bufferDC, bufferBMP);
	SelectObject(picDC, picBMP);
	SelectObject(endDC, endBMP);
	SelectObject(scoreDC, hbmpScore);

	hbrushWall = CreatePatternBrush(hbmpWall);

	StartGame();

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_TIMER:
		OnTimer((UINT)wParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		default:
			break;
		case VK_ESCAPE:
			exit(0);
			break;
		case VK_UP:
			table.ChangeSnakeDirect(S_UP);
			break;
		case VK_DOWN:
			table.ChangeSnakeDirect(S_DOWN);
			break;
		case VK_LEFT:
			table.ChangeSnakeDirect(S_LEFT);
			break;
		case VK_RIGHT:
			table.ChangeSnakeDirect(S_RIGHT);
			break;
		case VK_SPACE:
			if (uGameState == GAME_STATE_END)
			{
				StartGame();
				break;
			}
		}
		return 0;
		break;
	case WM_SETCURSOR:
		SetCursor(NULL);
		return 0;
	case WM_DESTROY:
		ReleaseDC(hWnd, picDC);
		ReleaseDC(hWnd, bufferDC);
		ReleaseDC(hWnd, windowDC);
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void StartGame()
{
	iScores = 0;

	table.InitialTable(tableBlockWidth, tableBlockHeight);
	table.GetSnake()->ChangeDirect(S_RIGHT);
	table.GetSnake()->SetHeadPos(tableBlockWidth / 2, tableBlockHeight / 2);

	srand((unsigned)time(NULL));
	for (int iFoodNum = 0; iFoodNum < 4; iFoodNum++)
	{
		table.AddFood((rand()) % tableBlockWidth, (rand()) % tableBlockHeight);
	}

	uSnakeMoveTimer = SetTimer(hAppWnd, 500, 100, NULL);
	uFoodAddTimer = SetTimer(hAppWnd, 600, 7000, NULL);

	uGameState = GAME_STATE_RUN;
}

void DrawGame(void)
{
	ShellDraw(bufferDC);
	GameAreaDraw(bufferDC);
	BitBlt(windowDC, 0, 0, g_iClientWidth, g_iClientHeight, bufferDC, 0, 0, SRCCOPY);
}

void ShellDraw(HDC hdc)
{
	char szText[30] = "Score: ";
	char szNum[20];

	int iNowScore = iScores * 100;
	sprintf(szNum, "%d", iNowScore);
	
	strcat(szText, szNum);

	RECT rt, rect;
	GetClientRect(hAppWnd, &rt);

	SelectObject(hdc, hbrushWall);
	PatBlt(hdc, rt.left, rt.top, rt.right, rt.bottom, PATCOPY);

	rect.left = rt.left + WALL_WIDTH;
	rect.top = rt.top + WALL_HEIGHT;
	rect.right = rt.right - WALL_WIDTH;
	rect.bottom = rt.bottom - WALL_HEIGHT;
	FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

	BitBlt(hdc, GetSystemMetrics(SM_CXSCREEN) / 3, 
		10, 256, 55, scoreDC, 0, 0, SRCCOPY);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, GetSystemMetrics(SM_CXSCREEN) / 3 + 50,
		30, szText, strlen(szText));
}

void GameAreaDraw(HDC hdc)
{
	int i, j;
	int x, y, x_pos, y_pos;
	BitmapState state;
	char strMark[20];

	for(i = 0; i < tableBlockHeight; i ++)
		for (j = 0; j  < tableBlockWidth; j ++)
		{
			x_pos = j * 20 + WALL_WIDTH;
			y_pos = i * 20 + WALL_HEIGHT;
			switch (table.GetData(j, i))
			{
			case TB_STATE_FOOD:
				BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 100, 0, SRCPAINT);
				BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 20, 0, SRCAND);
				break;
			case TB_STATE_BLOCK:
				BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 80, 0, SRCPAINT);
				BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 0, 0, SRCAND);
				break;
			default:
				break;
			}
		}
	x = table.GetSnake()->GetPos()[0].x;
	y = table.GetSnake()->GetPos()[0].y;
	x_pos = x * 20 + WALL_WIDTH;
	y_pos = y * 20 + WALL_HEIGHT;
	state = table.GetSnake()->GetStateArray()[0];

	switch (state)
	{
	case M_UP_UP:
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 80, 20, SRCPAINT);
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 0, 20, SRCAND);
		break;
	case M_DOWN_DOWN:
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 140, 20, SRCPAINT);
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 60, 20, SRCAND);
		break;
	case M_LEFT_LEFT:
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 100, 20, SRCPAINT);
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 20, 20, SRCAND);
		break;
	case M_RIGHT_RIGHT:
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 120, 20, SRCPAINT);
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 40, 40, SRCAND);
		break;
	default:
		break;
	}
	for (i = 1; i < table.GetSnake()->GetLength()-1; i++)
	{
		x = table.GetSnake()->GetPos()[i].x;
		y = table.GetSnake()->GetPos()[i].y;
		x_pos = x * 20 + WALL_WIDTH;
		y_pos = y * 20 + WALL_HEIGHT;
		state = table.GetSnake()->GetStateArray()[i];
		switch (state)
		{
		case M_UP_UP:			
		case M_DOWN_DOWN:
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 80, 40, SRCPAINT);
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 0, 40, SRCAND);
			break;
		case M_LEFT_LEFT:
		case M_RIGHT_RIGHT:
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 100, 40, SRCPAINT);
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 20, 40, SRCAND);
			break;
		case M_UP_LEFT:
		case M_RIGHT_DOWN:
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 100, 60, SRCPAINT);
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 20, 60, SRCAND);
			break;
		case M_UP_RIGHT:
		case M_LEFT_DOWN:
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 80, 60, SRCPAINT);
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 0, 60, SRCAND);
			break;
		case M_RIGHT_UP:
		case M_DOWN_LEFT:
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 140, 40, SRCPAINT);
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 60, 40, SRCAND);
			break;
		case M_LEFT_UP:
		case M_DOWN_RIGHT:
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 120, 40, SRCPAINT);
			BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 40, 40, SRCAND);
			break;	
		default:
			break;
		}
	}
	x = table.GetSnake()->GetPos()[table.GetSnake()->GetLength() - 1].x;
	y = table.GetSnake()->GetPos()[table.GetSnake()->GetLength() - 1].y;
	x_pos = x * 20 + WALL_WIDTH;
	y_pos = y * 20 + WALL_HEIGHT;
	state = table.GetSnake()->GetStateArray()[table.GetSnake()->GetLength() - 1];
	switch (state)
	{
	case M_UP_UP:
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 120, 60, SRCPAINT);
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 40, 60, SRCAND);
		break;
	case M_DOWN_DOWN:
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 120, 0, SRCPAINT);
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 40, 0, SRCAND);
		break;
	case M_LEFT_LEFT:
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 140, 60, SRCPAINT);
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 60, 60, SRCAND);
		break;
	case M_RIGHT_RIGHT:
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 140, 0, SRCPAINT);
		BitBlt(hdc, x_pos, y_pos, 20, 20, picDC, 60, 0, SRCAND);
		break;
	default:
		break;
	}
	if (uGameState == GAME_STATE_END)
	{
		int x_pos = g_iClientWidth;
		int y_pos = g_iClientHeight;

		BitBlt(hdc, x_pos, y_pos, 369, 300, endDC, 0, 0, SRCCOPY);
	}
}

void OnTimer(UINT uTIMER_ID)
{
	if (uTIMER_ID == uSnakeMoveTimer)
	{
		table.SnakeMove();
		if (table.GetSnake()->IsHeadTouchBody(table.GetSnake()->GetPos()[0].x, table.GetSnake()->GetPos()[0].y))
		{
			EndGame();
		}
		switch (table.GetData(table.GetSnake()->GetPos()[0].x, table.GetSnake()->GetPos()[0].y))
		{
		case TB_STATE_FOOD:
			table.ClearFood(table.GetSnake()->GetPos()[0].x, table.GetSnake()->GetPos()[0].y);
			table.AddBlock((rand()) % tableBlockWidth, (rand()) % tableBlockHeight);
			table.GetSnake()->AddBody();
			++iScores;
			break;
		case TB_STATE_BLOCK:
		case TB_STATE_SBLOCK:
			EndGame();
			break;
		default:
			break;
		}
		DrawGame();
	}
	else
	{
		if (uTIMER_ID == uFoodAddTimer)
		{
			table.AddFood((rand()) % tableBlockWidth, (rand()) % tableBlockHeight);
		}
	}
}

void EndGame(void)
{
	KillTimer(hAppWnd, uSnakeMoveTimer);
	KillTimer(hAppWnd, uFoodAddTimer);
	uGameState = GAME_STATE_END;
}