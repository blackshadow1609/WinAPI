#include<Windows.h>
#include<stdio.h>
#include"resource.h"

CONST CHAR g_sz_CLASS_NAME[] = "My First Window";

INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE pRevInst, LPSTR lpCmdLine, INT nCmdShow)
{


	//1) Регистрация класса окна:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_BITCOIN));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_ATOM));
	//wClass.hIcon = (HICON)LoadImage(hInstance, "atom.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE); 
	//wClass.hIcon = (HICON)LoadImage(hInstance, "bitcoin.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE); 
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadimagea
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	


	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_CLASS_NAME;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}


	//2) Создание окна:
	
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	INT window_width = screen_width * .75;
	INT window_height = screen_height * 3 / 4;
	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME, //Class name
		g_sz_CLASS_NAME, // Win name
		WS_OVERLAPPEDWINDOW, //такой стиль задается для всех  главных окон. Это окно будет родительским для других окон приложения.
		window_start_x, window_start_y, //CW_USEDEFAULT, CW_USEDEFAULT,
		window_width, window_height, //CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, //Perent win
		NULL, //Стркоа меню для главного окна или же ID ресурса для дочернего окна
		hInstance, //это экземпляр exe файла нашей программы
		NULL

	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); //Задает режим отображения окна: развернуто на весь экран, Свернуто в окно, свернуто на панель задач.
	UpdateWindow(hwnd);//Прорисовывает рабочую область окна.

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return msg.message;
}


INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_MOVE:
	/* {
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		INT window_width = window_rect.right - window_rect.left;
		INT Window_heigth = window_rect.bottom - window_rect.top;
		CONST INT SIZE = 256;
		CHAR sz_title[SIZE] = {};
		sprintf
		(sz_title, "%s - Position:%ix%i", g_sz_CLASS_NAME, window_rect.left, window_rect.top, window_width, Window_heigth);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
	break;*/
	case WM_SIZE:
	{
		RECT window_rect; //Rectangle - Прямоугольник
		GetWindowRect(hwnd, &window_rect);
		INT window_width = window_rect.right - window_rect.left;
		INT Window_heigth = window_rect.bottom - window_rect.top;
		CONST INT SIZE = 256;
		CHAR sz_title[SIZE] = {};
		sprintf
		(
			sz_title, 
			"%s - Position:%ix%i",
			g_sz_CLASS_NAME,
			window_rect.left, window_rect.top, 
			window_width, Window_heigth
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
	break;

	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}







// Абсолютно у любого класса окна есть имя
//Имя класса окна это самая обычная строка
//Класс окна зарегестрируется с ..... именем
