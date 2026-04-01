#include "Common.h"

// 1. 레어캔디: 플레이어 레벨업 (기존 로직 유지)
void Item::RareCandy(Player& player) {
	if (player.getmoney() < 500) { cout << "돈이 부족합니다! (필요: 500G)" << endl; return; }
	player.setmoney(-500);
	player.level++; // 플레이어 레벨 상승
	if (g_playerPoke != nullptr) g_playerPoke->levelup(); // 파트너도 같이 레벨업
	cout << "레어캔디 사용! 레벨이 올랐습니다!" << endl;
}

// 2. HP 포션 구매 및 사용
void Item::BuyHPPotion(Player& player) {
	if (player.getmoney() < 100) { cout << "돈이 부족합니다!" << endl; return; }
	player.setmoney(-100);
	player.AddItem("HPPotion");
}

void Item::UseHPPotion(Player& player, Pokemon* poke) {
	if (poke == nullptr) return;
	if (player.HasItem("HPPotion")) {
		float currentHp = poke->gethp();
		float maxHp = poke->getmaxhp();

		if (currentHp >= maxHp) {
			cout << "이미 체력이 가득 차 있습니다!" << endl;
			return;
		}

		// 20 회복 (최대 체력 초과 방지 로직 유지)
		float nextHp = (currentHp + 20 > maxHp) ? maxHp : currentHp + 20;
		poke->sethp(nextHp);

		player.RemoveItem("HPPotion");
		cout << poke->getName() << "의 체력이 20 회복되었습니다!" << endl;
	}
}

// 3. 풀 회복약 (FHPPotion)
void Item::BuyFHPPotion(Player& player) {
	if (player.getmoney() < 300) { cout << "돈이 부족합니다!" << endl; return; }
	player.setmoney(-300);
	player.AddItem("FHPPotion");
}

void Item::UseFHPPotion(Player& player, Pokemon* poke) {
	if (poke == nullptr) return;
	if (player.HasItem("FHPPotion")) {
		float currentHp = poke->gethp();
		float maxHp = poke->getmaxhp();

		if (currentHp >= maxHp) {
			cout << "이미 체력이 가득 차 있습니다!" << endl;
			return;
		}
		poke->sethp(poke->getmaxhp()); // 최대 체력으로 설정
		player.RemoveItem("FHPPotion");
		cout << poke->getName() << "의 체력이 모두 회복되었습니다!" << endl;
	}
}

// 4. 파워포션: 공격력 증가 (atk 오타 수정본)
void Item::BuyPowerPotion(Player& player) {
	if (player.getmoney() < 200) { cout << "돈이 부족합니다!" << endl; return; }
	player.setmoney(-200);
	player.AddItem("PowerPotion");
}

void Item::UsePowerPotion(Player& player, Pokemon* poke) {
	if (poke == nullptr) return;
	if (player.HasItem("PowerPotion")) {
		// 기존 poke->atk += 20 로직을 sethp/getattack으로 안전하게 수정
		poke->setattack(poke->getattack() + 20);
		poke->setspecialAttack(poke->getspecialAttack() + 20);
		player.RemoveItem("PowerPotion");
		cout << poke->getName() << "의 공격력 및 특수공격력이 20 증가했습니다!" << endl;
	}
}

// 5. 랜덤 경험치/골드 상자
void Item::Userandomexp(Player& player) {
	int expGain = (rand() % 451) + 50; // 50~500 사이
	player.gainExp(expGain);
	cout << "랜덤 상자에서 " << expGain << " 경험치를 획득했습니다!" << endl;
}

void Item::Userandomgold(Player& player) {
	int goldGain = (rand() % 451) + 50; // 50~500 사이
	player.setmoney(goldGain);
	cout << "랜덤 상자에서 " << goldGain << " 골드를 획득했습니다!" << endl;
}

// 6. 멀티렌즈 (기능 선언 유지)
void Item::BuyMultiLens(Player& player) {
	if (player.getmoney() < 200) { cout << "돈이 부족합니다!" << endl; return; }
	player.setmoney(-200);
	player.AddItem("MultiLens");
}
