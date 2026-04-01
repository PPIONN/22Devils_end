#include "Common.h"

extern Player g_player;
extern Pokemon* g_playerPoke;

void scene5() {
	int w, h;
	getActualSize(w, h);
	bool inShop = true;

	while (inShop) {
		system("cls");

		int midX = (w / 2) - 30;
		int midY = 3;

		// 상단 프레임 및 소지금 표시
		goToXY(midX, midY);     cout << "============================================================";
		goToXY(midX, midY + 1); cout << "               [ POKEMON CENTER & SHOP ]                    ";
		goToXY(midX, midY + 2); cout << "------------------------------------------------------------";
		goToXY(midX + 2, midY + 3); cout << "PLAYER : " << g_playerName;
		goToXY(midX + 35, midY + 3); cout << "YOUR GOLD : " << g_player.getmoney() << " G";
		goToXY(midX, midY + 4); cout << "============================================================";

		// 아이템 리스트 출력
		goToXY(midX + 5, midY + 6);  cout << "1. Rare Candy   - Level Up!           (500G)";
		goToXY(midX + 5, midY + 7);  cout << "2. HPPotion     - Restores 20 HP      (100G)";
		goToXY(midX + 5, midY + 8);  cout << "3. FHPPotion    - Full Restore HP     (300G)";
		goToXY(midX + 5, midY + 9);  cout << "4. PowerPotion  - Attack +20          (200G)";
		goToXY(midX + 5, midY + 10); cout << "5. randomexp    - 50~500 EXP Box      (100G)";
		goToXY(midX + 5, midY + 11); cout << "6. randomgold   - 50~500 GOLD Box     (100G)";
		goToXY(midX + 5, midY + 12); cout << "7. Check Status - 상태창 및 가방 확인";
		goToXY(midX + 5, midY + 13); cout << "0. Exit Shop";

		int inputY = midY + 15;
		goToXY(midX, inputY);     cout << "============================================================";
		goToXY(midX + 2, inputY + 1); cout << ">> Select Number : ";

		int choice;
		if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

		cout << "\n";
		switch (choice) {
		case 1: Item::RareCandy(g_player); break;
		case 2: Item::BuyHPPotion(g_player); break;
		case 3: Item::BuyFHPPotion(g_player); break;
		case 4: Item::BuyPowerPotion(g_player); break;

		case 5: // 랜덤 경험치 상자 (구매 즉시 사용 로직 유지)
			if (g_player.getmoney() >= 100) {
				g_player.setmoney(-100);
				Item::Userandomexp(g_player);
			}
			else cout << "돈이 부족합니다!" << endl;
			break;

		case 6: // 랜덤 골드 상자
			if (g_player.getmoney() >= 100) {
				g_player.setmoney(-100);
				Item::Userandomgold(g_player);
			}
			else cout << "돈이 부족합니다!" << endl;
			break;

		case 7: // 상태창 및 가방(아이템 사용)
			g_player.ShowStatus();
			g_player.InventoryUI();
			break;

		case 0:
			cout << ">> Leaving shop...";
			Sleep(1000);
			inShop = false;
			break;
		default:
			cout << ">> Invalid choice!";
			Sleep(800);
			break;
		}

		if (choice != 0 && choice != 7) Sleep(1200);
	}
}
