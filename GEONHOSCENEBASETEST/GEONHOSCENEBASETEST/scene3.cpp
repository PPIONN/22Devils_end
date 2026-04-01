#include "Common.h"
#include <io.h>
#include <fcntl.h>
#include <vector>

void drawFrame(const vector<wstring>& frame, int x, int y) {
	for (int i = 0; i < (int)frame.size(); i++) {
		goToXY(x, y + i);
		wcout << frame[i];
	}
}

void scene3() {
	// [수정] C6031 경고 해결: (void) 추가
	int oldMode = _setmode(_fileno(stdout), _O_U16TEXT);
	int w, h;
	getActualSize(w, h);
	int midY = h / 2 - 10;

	vector<vector<wstring>> frames = {
		{ L"      .      ", L"     / \\     ", L"    |   |    ", L"   /     \\   ", L"  |_______|  " },
		{ L"        .        ", L"       / \\       ", L"      |   |      ", L"     /     \\     ", L"    |  [ ]  |    ", L"   /         \\   ", L"  |___________|  " },
		{ L"             .             ", L"            / \\            ", L"           |   |           ", L"          /     \\          ", L"         |  [ ]  |         ", L"         |       |         ", L"        /         \\        ", L"       |   [   ]   |       ", L"       |           |       ", L"      /             \\      ", L"     |    [입 구]    |     ", L"     |_______________|     " }
	};

	for (int f = 0; f < (int)frames.size(); f++) {
		system("cls");
		getActualSize(w, h);
		int midX = w / 2;
		goToXY(midX - 30, midY - 5); wcout << L"  .  *   '  .  '   *  ";
		int currentX = midX - ((int)frames[f][0].length() / 2);
		drawFrame(frames[f], currentX, midY);
		Sleep(700);
	}

	// [수정] C6031 경고 해결: (void) 추가
	(void)_setmode(_fileno(stdout), oldMode);

	talk("나", "드디어 도착했어... 여기가 바로 '포켓몬 탑'인가.");
	talk("나", "공기가 무거워... 무언가 강력한 기운이 느껴져.");
}
