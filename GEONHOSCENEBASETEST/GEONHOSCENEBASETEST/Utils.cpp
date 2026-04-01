#include "Common.h"
#include <conio.h>

void goToXY(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hConsole, pos);
}

void setFontSize(int size) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = size;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void getActualSize(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
}

void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void initConsole() {
	HWND hwnd = GetConsoleWindow();

	// 1. 폰트 먼저 설정
	setFontSize(30);

	// 2. 창 최대화
	ShowWindow(hwnd, SW_MAXIMIZE);

	// [핵심] 창이 커지는 동안 코드가 앞서나가지 않게 대기 (깨짐 방지)
	Sleep(200);

	// 3. 설정 마무리
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode & ~ENABLE_QUICK_EDIT_MODE);
	hideCursor();

	// 4. 깨끗한 화면으로 시작
	system("cls");
}

void talk(string name, string text) {
	int w, h;
	getActualSize(w, h);
	int baseY = h - 10;
	system("cls");

	goToXY(5, baseY);
	for (int i = 0; i < w - 10; i++) cout << "=";
	goToXY(10, baseY + 2);
	cout << "[" << name << "]";
	goToXY(10, baseY + 4);

	while (_kbhit()) (void)_getch();

	bool skip = false;
	for (int i = 0; i < (int)text.length(); i++) {
		if (!skip && _kbhit()) { skip = true; while (_kbhit()) (void)_getch(); }
		if (text[i] & 0x80) { cout << text[i] << text[i + 1]; i++; }
		else { cout << text[i]; }
		if (!skip) Sleep(20);
	}

	goToXY(w - 30, h - 3);
	cout << "▶ [Enter]";
	while (true) { if (_kbhit()) { if (_getch() == 13) break; } }
}
