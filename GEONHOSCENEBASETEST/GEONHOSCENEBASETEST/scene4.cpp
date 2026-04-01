#include "Common.h"
#include "PokemonData.h"
#include "BossData.h"
#include <random>

// 외부 전역 변수 참조
extern Pokemon* g_playerPoke;
extern Player g_player;
extern vector<Pokemon*> g_playerParty;
extern vector<string> g_normalPool;
extern vector<string> g_legendaryPool;
std::random_device rd; // 이현준 추가 수정사항 - 랜덤씨드 생성
std::mt19937 gen(rd()); // 이현준 추가 수정사항 - 랜덤씨드 생성
// --- [적 스폰 함수] ---
// 아까 추가한 엠페르트, 루카리오, 가디안, 한카리아스, 마기라스 등이 모두 등장하도록 수정했습니다.
int getAliveCount() {
	int count = 0;
	for (auto p : g_playerParty) {
		if (p != nullptr && p->gethp() > 0) {
			count++;
		}
	}
	return count;
}
void SwapPokemon() {
	system("cls");
	cout << "\n========== [ 포켓몬 교체 ] ==========" << endl;
	for (int i = 0; i < (int)g_playerParty.size(); i++) {
		cout << i + 1 << ". " << g_playerParty[i]->getName()
			<< " (HP: " << (int)g_playerParty[i]->gethp() << "/" << (int)g_playerParty[i]->getmaxhp() << ")"
			<< (g_playerParty[i] == g_playerPoke ? " [전투중]" : "") << endl;
	}
	cout << "0. 취소" << endl;
	cout << "=====================================" << endl;
	cout << "교체할 포켓몬 번호: ";

	int choice;
	cin >> choice;
	if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); return; }

	if (choice >= 1 && choice <= (int)g_playerParty.size()) {
		Pokemon* selected = g_playerParty[choice - 1];

		if (selected == g_playerPoke) {
			cout << "이미 전투 중인 포켓몬입니다!" << endl;
			Sleep(1000);
		}
		else if (selected->gethp() <= 0) {
			cout << selected->getName() << "은(는) 기력이 없어 싸울 수 없다!" << endl;
			Sleep(1000);
		}
		else {
			// 1. 기존 포켓몬 퇴장 메시지
			cout << g_playerPoke->getName() << ", 고생했어! 돌아와!" << endl;
			Sleep(800);

			// 2. 실제 포켓몬 교체 (포인터 변경)
			g_playerPoke = selected;

			// 3. [핵심] 새로 나온 포켓몬의 전투용 스탯(warstat)을 현재 능력치 기반으로 초기화
			// 이 함수가 호출되면서 이전 포켓몬이 쌓아둔 버프/디버프가 사라지고 깨끗한 상태가 됩니다.
			g_playerPoke->setwarstat();

			// 4. 등장 메시지
			cout << "가라! " << g_playerPoke->getName() << "!" << endl;
			Sleep(1000);
		}
	}
}

unique_ptr<Monster> spawnEnemy(int floor) { // 
	string name = "";
	int lv = floor + 2;

	// 1. 보스 스폰 (5층 단위)
	if (floor % 5 == 0 && !g_legendaryPool.empty()) {
		std::uniform_int_distribution<int> dist(0, (int)g_legendaryPool.size() - 1);
		int randIdx = dist(gen);
		name = g_legendaryPool[randIdx];
		// g_legendaryPool.erase(g_legendaryPool.begin() + randIdx); // 보스를 한 번만 나오게 하려면 삭제 활성화
	}
	// 2. 일반 몬스터 스폰 (랜덤 인덱스)
	else if (!g_normalPool.empty()) {
		std::uniform_int_distribution<int> dist(0, (int)g_normalPool.size() - 1);
		int randIdx = dist(gen);
		name = g_normalPool[randIdx];
	}

	// 이름에 맞춰 실제 객체 생성 (PokemonData.h의 클래스명과 일치)
	if (name == "Rayquaza") return make_unique<Rayquaza>(lv + 5);
	if (name == "Suicune")  return make_unique<Suicune>(lv + 2);
	if (name == "Lugia")    return make_unique<Lugia>(lv + 3);
	if (name == "Gardevoir") return make_unique<Gardevoir>(lv);
	if (name == "Garchomp")  return make_unique<Garchomp>(lv);
	if (name == "Tyranitar") return make_unique<Tyranitar>(lv);
	if (name == "Lucario")   return make_unique<Lucario>(lv);
	if (name == "Empoleon")  return make_unique<Empoleon>(lv);
	if (name == "Gastly")    return make_unique<Gastly>(lv);
	if (name == "Snorlax")   return make_unique<Snorlax>(lv);
	if (name == "Cyndaquil") return make_unique<Cyndaquil>(lv);

	return make_unique<Magikarp>(lv); // 기본값
}

// --- [메인 배틀 로직] ---
void scene4() {
	if (g_playerPoke == nullptr) return;
	std::uniform_int_distribution<int> dis(0, 99); // 이현준 추가 수정사항 - 랜덤씨드 생성
	g_playerPoke->setwarstat(); // 이현준 추가 전투용 스텟 변화기 전용
	// 1. 적 스폰 및 초기 메시지
	unique_ptr<Monster> enemy = spawnEnemy(g_currentFloor);
	enemy->setwarstat();
	talk("시스템", enemy->getName() + "이(가) 나타났다! (LV." + to_string(enemy->getlevel()) + ")");

	while (g_playerPoke->gethp() > 0 && enemy->gethp() > 0) {
		system("cls");
		cout << "\n================ [ BATTLE ] ================" << endl;
		cout << " [적] " << enemy->getName() << " (HP: " << (int)enemy->gethp() << " / " << (int)enemy->getmaxhp() << ")" << endl;
		cout << "--------------------------------------------" << endl;
		cout << " [나] " << g_playerPoke->getName() << " (HP: " << (int)g_playerPoke->gethp() << " / " << (int)g_playerPoke->getmaxhp() << ")" << endl;
		cout << "============================================" << endl;
		cout << " 1. 싸운다  2. 가방  3. 포켓몬  4. 도망친다" << endl;
		cout << " 선택: ";

		int menu; cin >> menu;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(LLONG_MAX, '\n');
			cout << "숫자만 입력 가능합니다!" << endl;
			Sleep(1000);
			continue;
		}
		if (menu == 1) { // [싸운다]
			cout << "\n--- 기술 목록 ---" << endl;
			for (int i = 0; i < (int)g_playerPoke->currentSkills.size(); i++) {
				cout << i + 1 << ". " << g_playerPoke->currentSkills[i].name <<" " << g_playerPoke->currentSkills[i].type << " " << g_playerPoke->currentSkills[i].category << " (PP: " << g_playerPoke->currentSkills[i].pp << "/" << g_playerPoke->currentSkills[i].maxPp << ")" << endl;
			}
			cout << "0. 취소" << endl;
			cout << " 선택: ";
			int sIdx; cin >> sIdx;

			if (cin.fail()) {
				cin.clear(); // 에러 상태 초기화
				cin.ignore(LLONG_MAX, '\n'); // 버퍼 비우기
				cout << "숫자만 입력 가능합니다!" << endl;
				Sleep(1000);
				continue; // 다시 루프 처음으로
			}

			if (sIdx == 0) continue;
			if (sIdx >= 1 && sIdx <= (int)g_playerPoke->currentSkills.size()) {
					// 선택한 기술 객체를 미리 가져옵니다.
				Skill& selectedSkill = g_playerPoke->currentSkills[sIdx - 1];

				// 플레이어 공격 (Setter 사용으로 에러 해결)
				int damage = g_playerPoke->useSkill(sIdx - 1, *enemy);
				enemy->sethp(enemy->gethp() - (float)damage);
				if (selectedSkill.category != "Status") {
					cout << damage << "의 데미지를 입혔다!" << endl;
				}
				Sleep(1000);

				if (enemy->gethp() <= 0) {
					talk("시스템", enemy->getName() + "은(는) 쓰러졌다!");
					// 경험치 및 골드 보상
					talk("시스템", "승리했습니다.");
					int expReward = enemy->getlevel() * 30;
					g_playerPoke->gainExp(expReward);
					g_player.setmoney(g_currentFloor * 100);
					return;
				}
				
			}
		}
		else if (menu == 2) { // [가방]
			g_player.InventoryUI(); // 전투 중 아이템 사용
			continue;
		}
		else if (menu == 3) { // [가방]
			SwapPokemon();
			// 교체 시에도 턴이 넘어가는게 원작 고증이지만, 
			// 우선은 교체 후 다시 내 메뉴가 나오게 하려면 continue;
			continue;
		}
		else if (menu == 4) { // [도망] ///
			if (g_currentFloor % 5 == 0) {
				talk("시스템", "보스에게서 도망칠 수 없다!");
				continue;
			}
			/// 여기까지 아래로 수정사항 - 이현준


			// 3. 랜덤 숫자 하나 생성 0~99 100
			int randomNumber = dis(gen);

			// 4. 30% 확률 체크 (0~29까지 나오면 당첨!)
			if (randomNumber < 30) {
				talk("시스템", "도망치지 못했다...");
			}
			else {
				talk("시스템", "무사히 도망쳤다!");
				return;
			}

			// 여기까지 위로 수정사항
			//talk("시스템", "무사히 도망쳤다!");
			//return;
		}
		else {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(LLONG_MAX, '\n');
				cout << "숫자만 입력 가능합니다!" << endl;
				Sleep(1000);
				continue;
			}
		}
		// --- 적의 턴 ---
		if (enemy->gethp() > 0) {
			// 1. 적에게 기술이 아예 없는 경우 (데이터 오류 대비)
			if (enemy->currentSkills.empty()) {
				cout << enemy->getName() << "은(는) 사용할 수 있는 기술이 없다!" << endl;
				// 기술이 아예 없어도 발버둥은 나갈 수 있도록 호출 (인덱스 -1 전달)
				int eDamage = enemy->useSkill(-1, *g_playerPoke);
				g_playerPoke->sethp(g_playerPoke->gethp() - (float)eDamage);
			}
			else {
				// 2. 사용 가능한 기술(PP > 0)이 있는지 확인
				bool hasPP = false;
				for (const auto& s : enemy->currentSkills) {
					if (s.pp > 0) {
						hasPP = true;
						break;
					}
				}

				int eDamage = 0;
				if (!hasPP) {
					// 모든 기술의 PP가 0이면 -> 발버둥 발동
					eDamage = enemy->useSkill(-1, *g_playerPoke);
					g_playerPoke->sethp(g_playerPoke->gethp() - (float)eDamage);
					// 발버둥은 useSkill 내부에서 메시지를 출력하므로 별도 출력 생략 가능
				}
				else {
					// PP가 남아있는 기술 중 하나를 랜덤하게 선택
					int eSkillIdx;
					do {
						eSkillIdx = rand() % (int)enemy->currentSkills.size();
					} while (enemy->currentSkills[eSkillIdx].pp <= 0); // PP가 0인 기술은 다시 뽑기

					// 기술 정보 가져오기 및 실행
					Skill& eSkill = enemy->currentSkills[eSkillIdx];
					eDamage = enemy->useSkill(eSkillIdx, *g_playerPoke);
					g_playerPoke->sethp(g_playerPoke->gethp() - (float)eDamage);
					if (eSkill.category != "Status") {
						cout << eDamage << "의 데미지를 입혔다!" << endl;
					}
				}
			}

			Sleep(1500);

			// 플레이어 패배 확인
			if (g_playerPoke->gethp() <= 0) {
				int aliveCount = getAliveCount(); // 실시간으로 생존 포켓몬 수 확인
				if (aliveCount == 0) {
					talk("시스템", g_playerPoke->getName() + "은(는) 쓰러졌다...더이상 포켓몬이 없다. 눈앞이 캄캄해졌다!");
					return;
				}
				cout << "남은 포켓몬은 " << aliveCount << " 마리!" << endl;
				Sleep(1500);
				SwapPokemon();
				continue;
				// 교체 시에도 턴이 넘어가는게 원작 고증이지만, 
				// 우선은 교체 후 다시 내 메뉴가 나오게 하려면 continue;
				//talk("시스템", g_playerPoke->getName() + "은(는) 쓰러졌다... 눈앞이 캄캄해졌다!");
				//return;
			}
		}
	}
}
