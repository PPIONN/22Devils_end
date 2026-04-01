#include "Common.h"

// [scene6: 최종 엔딩 장면]
void scene6() {
	system("cls");
	int w, h;
	getActualSize(w, h);

	// 네가 원했던 오박사님과의 마지막 대화 로직입니다.
	talk("오박사", "허허허! " + g_playerName + "군, 정말 대단하구먼!");
	talk("오박사", "자네와 " + g_starterName + "(이)가 포켓몬 탑의 모든 시련을 이겨내다니!");
	talk("오박사", "자네는 이제 진정한 포켓몬 마스터라네. 축하하네!");

	system("cls");
	int midX = (w / 2) - 25;
	int midY = (h / 2) - 5;

	// 엔딩 크레딧 연출
	goToXY(midX, midY);     cout << "==================================================";
	goToXY(midX, midY + 1); cout << "                                                  ";
	goToXY(midX, midY + 2); cout << "           ★ CONGRATULATIONS! ★               ";
	goToXY(midX, midY + 3); cout << "                                                  ";
	goToXY(midX, midY + 4); cout << "       " << g_playerName << "님은 포켓몬 마스터가 되었습니다!      ";
	goToXY(midX, midY + 5); cout << "                                                  ";
	goToXY(midX, midY + 6); cout << "==================================================";

	goToXY(midX + 12, midY + 8);
	cout << "파트너: " << g_starterName << "와(과) 함께한 대모험";
	g_playerParty.clear();
	// 3. 전역 포인터 초기화 (댕글링 포인터 방지)
	g_playerPoke = nullptr;

	Sleep(5000); // 5초간 대기 후 종료
}
