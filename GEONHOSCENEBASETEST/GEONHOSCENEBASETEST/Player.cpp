#include "Common.h"
#include "PokemonData.h"

// 1. 경험치 획득 및 레벨업 (Player.cpp의 핵심)
void Player::gainExp(int amount) {
	exp += amount;
	int nextLevelExp = level * 100; // 레벨업 기준
	while (exp >= nextLevelExp) {
		exp -= nextLevelExp;
		level++;
		cout << "\n[LEVEL UP!] 플레이어 레벨 " << level << " 달성!" << endl;
		// 파트너 포켓몬도 같이 레벨업 시키기
		if (g_playerPoke != nullptr) g_playerPoke->levelup();
		nextLevelExp = level * 100;
	}
}

// 2. 인벤토리 UI (가방 열기)
void Player::InventoryUI() {
	if (inventory.empty()) {
		talk("가방", "가방이 텅 비어 있습니다.");
		return;
	}

	while (true) {
		system("cls");
		cout << "=== [ MY INVENTORY ] ===" << endl;
		for (int i = 0; i < (int)inventory.size(); i++) {
			cout << i + 1 << ". " << inventory[i] << endl;
		}
		cout << "0. 닫기" << endl;
		cout << "선택: ";

		int sel;
		if (!(cin >> sel)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
		if (sel == 0) break;
		if (sel < 1 || sel >(int)inventory.size()) continue;

		string item = inventory[sel - 1];

		// 아이템 효과 즉시 적용 (Item 클래스의 함수 호출)
		if (item == "HPPotion") Item::UseHPPotion(*this, g_playerPoke);
		else if (item == "FHPPotion") Item::UseFHPPotion(*this, g_playerPoke);
		else if (item == "RareCandy") Item::RareCandy(*this);
		else if (item == "PowerPotion") Item::UsePowerPotion(*this, g_playerPoke);
		else if (item == "randomexp") Item::Userandomexp(*this);
		else if (item == "randomgold") Item::Userandomgold(*this);

		// 사용한 아이템 삭제
		// RemoveItem(item); - 이현준 아이템 사용안해도 사용한 이유.
		Sleep(1000);
		break;
	}
}

// 3. 상태창 확인
void Player::ShowStatus() {
	system("cls");
	cout << "--- " << g_playerName << " 님의 정보 ---" << endl;
	cout << "LV: " << level << " | EXP: " << exp << " / " << (level * 100) << endl;
	cout << "GOLD: " << money << " G" << endl;
	if (g_playerPoke != nullptr) {
		cout << "PARTNER: " << g_playerPoke->getName() << " (Lv." << g_playerPoke->getlevel() << ")" << endl;
		cout << "HP: " << (int)g_playerPoke->gethp() << " / " << (int)g_playerPoke->getmaxhp() << endl;
	}
	cout << "-----------------------" << endl;
	system("pause");
}

// 4. 아이템 리스트 관리 기본 함수들
void Player::AddItem(string itemName) { inventory.push_back(itemName); }
bool Player::HasItem(string itemName) {
	return find(inventory.begin(), inventory.end(), itemName) != inventory.end();
}
void Player::RemoveItem(string itemName) {
	auto it = find(inventory.begin(), inventory.end(), itemName);
	if (it != inventory.end()) inventory.erase(it);
}
