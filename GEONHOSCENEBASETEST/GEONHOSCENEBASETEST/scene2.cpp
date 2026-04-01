#include "Common.h"
#include "PokemonData.h" // 일반 몬스터(고오스 등)용
#include "StarterData.h" // [추가] 파이리, 꼬부기, 이상해씨 클래스가 여기 있습니다!
#include <conio.h>

extern Pokemon* g_playerPoke; // Data.cpp에 선언된 전역 포인터

void scene2() {
	Sleep(500);
	setFontSize(24);
	system("cls");
	int w, h;
	getActualSize(w, h);

	// --- [1. 이름 입력] ---
	int midX = (w / 2) - 20;
	int midY = (h / 2) - 5;

	goToXY(midX, midY);     cout << "========================================";
	goToXY(midX, midY + 1); cout << "           [ 당신의 이름은? ]           ";
	goToXY(midX, midY + 2); cout << "========================================";
	goToXY(midX + 5, midY + 4); cout << " 입력: ";

	string tempName;
	cin >> tempName;
	g_playerName = tempName;
	cin.ignore(1000, '\n');

	talk("오박사", g_playerName + "군 왔는가?");
	talk("오박사", "오늘은 자네가 이 포켓몬 탑에 처음 들어가보는 날이 아닌가!");
	talk("오박사", "자네는 마침 운이 정말 좋아. 내 아들이 하루 늦어진 덕분에...");
	talk("오박사", "이 세 마리의 스타팅 포켓몬 중 원하는 아이를 파트너로 고를 수 있다네!");

	// --- [2. 스타팅 포켓몬 선택 및 객체 생성] ---
	bool selectionDone = false;
	while (!selectionDone) {
		system("cls");
		getActualSize(w, h);
		midX = (w / 2) - 25;
		midY = (h / 2) - 5;

		goToXY(midX, midY);     cout << "==================================================";
		goToXY(midX, midY + 1); cout << " [오박사: 자, 이 세 마리 중 하나를 고르렴!] ";
		goToXY(midX, midY + 2); cout << "==================================================";
		goToXY(midX + 2, midY + 4); cout << " 1. 파이리(불)  2. 꼬부기(물)  3. 이상해씨(풀)";
		goToXY(midX, midY + 5);     cout << "--------------------------------------------------";
		goToXY(midX + 15, midY + 7); cout << " 선택 번호: ";

		int choice;
		if (!(cin >> choice)) {
			cin.clear(); cin.ignore(1000, '\n'); continue;
		}
		cin.ignore(1000, '\n');

		// 기존에 혹시 데이터가 있다면 삭제 (메모리 누수 방지)
		if (g_playerPoke != nullptr) delete g_playerPoke;

		// [핵심] 선택한 번호에 따라 실제 클래스 객체 생성 (레벨 5로 시작)
		if (choice == 1) {
			g_playerPoke = new Charmander(5);
			g_starterName = "파이리";
		}
		else if (choice == 2) {
			g_playerPoke = new Squirtle(5);
			g_starterName = "꼬부기";
		}
		else if (choice == 3) {
			g_playerPoke = new Bulbasaur(5);
			g_starterName = "이상해씨";
		}
		else {
			talk("오박사", "허허, 장난치지 말고 하나를 골라보려무나.");
			continue;
		}
		g_playerParty.push_back(g_playerPoke);
		talk("오박사", g_starterName + "은(는) 정말 탁월한 선택일세!");
		talk("시스템", g_starterName + "이(가) 파트너가 되었습니다! (LV.5)");
		talk("오박사", g_starterName + "의 성격은 " + g_playerPoke->getNature() + "일세.");
		selectionDone = true;
	}

	// --- [3. 보너스 시퀀스] ---
	talk("오박사", "..음? 저기 구석에 있는 저 친구는 누군가?");
	talk("오박사", "허허, 이 한카리아스(Garchomp)도 자네를 따라가고 싶은 모양이구먼.");
	Pokemon* bonusPoke = new Garchomp(100);
	g_playerParty.push_back(bonusPoke);
	talk("오박사", "강한 포켓몬이니 위험에 빠지면 꼭 도움 받을 수 있을걸세.");
	talk("시스템", "여행 가방에 포션(Potion)과 약간의 골드가 추가되었습니다!");

	// 초기 아이템 및 골드 지급
	g_playerGold += 500;
	g_player.AddItem("HPPotion");

	system("cls");
	getActualSize(w, h);
	goToXY(w / 2 - 15, h / 2);
	cout << "      여행이 시작되었습니다!       ";
	Sleep(2000);
}
