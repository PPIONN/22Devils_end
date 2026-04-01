#include "Common.h"
#include "TypeChart.h"
#include "GameData.h"
#include <algorithm>
#include <iostream>
#include <conio.h>
#include "natureChart.h"
using namespace std;

// 1. 경험치 획득 로직
void Pokemon::gainExp(int amount) {
	if (level >= 10) {
		cout << "해당 포켓몬은 더이상 경험치를 올릴 수 없습니다!" << endl; {
			_getch();
			return;
		}
	}if (exp > 100) {
		levelup();
	}
	exp += amount;
	cout << "\n" << name << "은(는) " << amount << "의 경험치를 얻었다!" << endl;

	int nextLevelExp = level * 50;
	while (exp >= nextLevelExp) {
		exp -= nextLevelExp;
		levelup();
		nextLevelExp = level * 50;
	}
}

// 2. 기술 사용 및 데미지 계산 (복합타입 & 발버둥 통합)
int Pokemon::useSkill(int skillIdx, Pokemon& target) {
	// [체크] 모든 기술의 PP가 0인지 먼저 확인 (발버둥 발동 조건)
	bool outOfPP = true;
	for (const auto& s : currentSkills) {
		if (s.pp > 0) {
			outOfPP = false;
			break;
		}
	}

	// --- [발버둥 로직] ---
	if (outOfPP) {
		cout << "\n" << name << "은(는) 사용할 수 있는 기술이 없다!" << endl;
		cout << name << "의 발버둥!" << endl;

		float atkStat = static_cast<float>(warattack);
		float defStat = static_cast<float>(target.wardefense);
		if (defStat <= 0) defStat = 1.0f;

		float damage = (((2.0f * (float)level / 5.0f + 2.0f) * 50.0f * (atkStat / defStat)) / 50.0f) + 2.0f;
		damage *= (float)(rand() % 16 + 85) / 100.0f; // 난수

		// 반동 데미지 (최대 체력의 25%)
		float recoil = maxHp * 0.25f;
		sethp(gethp() - recoil);
		cout << name << "은(는) 반동으로 데미지를 입었다!" << endl;

		return static_cast<int>(damage);
	}

	// --- [일반 기술 로직] ---
	if (skillIdx < 0 || skillIdx >= (int)currentSkills.size()) return 0;
	Skill& skill = currentSkills[skillIdx];

	if (skill.pp <= 0) {
		cout << skill.name << "은(는) 기력이 부족하다!" << endl;
		return 0;
	}

	skill.pp--;
	cout << "\n" << name << "의 " << skill.name << "!" << endl;

	// 명중률 체크
	if (skill.accuracy != -1 && (rand() % 100) + 1 > skill.accuracy) {
		cout << "하지만 공격은 빗나갔다!" << endl;
		return 0;
	}

	// 랭크 배율 계산 람다함수
	auto GetRankMult = [](int rank) -> float {
		if (rank >= 0) return (2.0f + rank) / 2.0f;
		else return 2.0f / (2.0f - (float)rank);
		};

	// --- 1. 변화기(Status) 로직 ---
	if (skill.category == "Status") {
		if (skill.name == "Defense Curl" || skill.name == "Withdraw" || skill.name == "Harden") {
			defRank = std::clamp(defRank + 1, -6, 6);
			cout << name << "의 방어가 올라갔다!" << endl;
		}
		else if (skill.name == "Leer" || skill.name == "Tail Whip") {
			target.defRank = std::clamp(target.defRank - 1, -6, 6);
			cout << target.name << "의 방어가 내려갔다!" << endl;
		}
		else if (skill.name == "Growl") {
			target.atkRank = std::clamp(target.atkRank - 1, -6, 6);
			cout << target.name << "의 공격이 내려갔다!" << endl;
		}
		else if (skill.name == "Growth" || skill.name == "Howl") {
			atkRank = std::clamp(atkRank + 1, -6, 6);
			spatkRank = std::clamp(spatkRank + 1, -6, 6);
			cout << name << "의 공격과 특수공격이 올라갔다!" << endl;
		}
		else if (skill.name == "Synthesis" || skill.name == "Rest") {
			float recovery = maxHp * 0.5f;
			hp = (hp + recovery > maxHp) ? maxHp : (hp + recovery);
			cout << name << "은 체력을 회복했다!" << endl;
		}
		else {
			cout << "하지만 아무 일도 일어나지 않았다!" << endl;
		}
		return 0;
	}

	// --- 2. 공격기 데미지 계산 ---
	float baseAtk = (skill.category == "Special") ? warspecialAttack : warattack;
	float atkMult = (skill.category == "Special") ? GetRankMult(spatkRank) : GetRankMult(atkRank);
	float finalAtk = baseAtk * atkMult;

	float baseDef = (skill.category == "Special") ? target.warspecialDefense : target.wardefense;
	float defMult = (skill.category == "Special") ? GetRankMult(target.spdefRank) : GetRankMult(target.defRank);
	float finalDef = baseDef * defMult;

	// 기본 데미지 공식
	float damage = (((2.0f * (float)level / 5.0f + 2.0f) * (float)skill.power * (finalAtk / finalDef)) / 50.0f) + 2.0f;

	// [복합 타입 상성 계산] 방어자의 모든 타입 순회
	float eff = 1.0f;
	for (const string& tType : target.type) {
		eff *= TypeChart::getEffectiveness(skill.type, tType);
	}
	damage *= eff;

	// [자속 보정(STAB)] 내 타입 중 하나라도 기술 타입과 같으면 1.5배
	bool hasSTAB = false;
	for (const string& myType : this->type) {
		if (myType == skill.type) {
			hasSTAB = true;
			break;
		}
	}
	if (hasSTAB) damage *= 1.5f;

	// 결과 메시지
	if (eff >= 2.0f) cout << "효과가 굉장했다!" << endl;
	else if (eff > 0.0f && eff <= 0.5f) cout << "효과가 별로인 듯하다..." << endl;
	else if (eff == 0.0f) cout << "효과가 없는 것 같다." << endl;

	damage *= (float)(rand() % 16 + 85) / 100.0f; // 랜덤 변수 적용

	return static_cast<int>(damage);
}

// 3. 스탯 스케일링
void Pokemon::newpokescale(int targetLevel) {
	level = targetLevel;
	hp += hpGrowth * level;
	maxHp = hp;
	attack += attackGrowth * level;
	defense += defenseGrowth * level;
	specialAttack += specialAttackGrowth * level;
	specialDefense += specialDefenseGrowth * level;
	speed += speedGrowth * level;
	newpokeSkills();
}

// 4. 레벨업 시 스탯 상승
//void Pokemon::levelup() {
//	cout << "\n" << name << "은(는) LV." << level+1 << "(으)로 올랐다!" << endl;
//	level++;
//	hp += hpGrowth;
//	maxHp += hpGrowth;
//	attack += attackGrowth;
//	defense += defenseGrowth;
//	specialAttack += specialAttackGrowth;
//	specialDefense += specialDefenseGrowth;
//	speed += speedGrowth;
//	cout << " [체  력]  " << (int)maxHp - (int)hpGrowth << "  ->  " << (int)maxHp << "  (+" << (int)hpGrowth << ")"
//		 << " [공  격]  " << (int)attack - (int)attackGrowth << "  ->  " << (int)attack << "  (+" << (int)attackGrowth << ")"
//		<< " [방  어]  " << (int)defense - (int)defenseGrowth << "  ->  " << (int)defense << "  (+" << (int)defenseGrowth << ")"
//		<< " [특수공격] " << (int)specialAttack - (int)specialAttackGrowth << "  ->  " << (int)specialAttack << "  (+" << (int)specialAttackGrowth << ")"
//		<< " [특수방어] " << (int)specialDefense - (int)specialDefenseGrowth << "  ->  " << (int)specialDefense << "  (+" << (int)specialDefenseGrowth << ")"
//		<< " [스 피 드] " << (int)speed - (int)speedGrowth << "  ->  " << (int)speed << "  (+" << (int)speedGrowth << ")" << endl;
//	updateSkills(); // 레벨업 시에는 새 기술을 배울지 물어보는 함수 호출
//}
void Pokemon::levelup() {
	// 1. 상승 전 스탯 저장
	if (getlevel() >= 10) {
		cout << "해당 포켓몬은 더이상 레벨을 올릴 수 없습니다!" << endl;
		_getch();
		return;
	}
	float oldMaxHp = maxHp;
	float oldAtk = attack;
	float oldDef = defense;
	float oldSpAtk = specialAttack;
	float oldSpDef = specialDefense;
	float oldSpeed = speed;

	// 2. 레벨 및 스탯 상승
	level++;
	maxHp += hpGrowth;
	hp = maxHp; // 레벨업 시 풀회복
	attack += attackGrowth;
	defense += defenseGrowth;
	specialAttack += specialAttackGrowth;
	specialDefense += specialDefenseGrowth;
	speed += speedGrowth;

	// 3. 깔끔한 시각화 출력 (줄바꿈 최적화)
	cout << "\n==================================================" << endl;
	cout << "    [LEVEL UP] " << name << " LV." << level - 1 << " -> LV." << level  << endl;
	cout << "==================================================" << endl;

	// 왼쪽 열
	cout << " [체  력] " << (int)oldMaxHp << " -> " << (int)maxHp << " (+" << (int)maxHp - (int)oldMaxHp << ")\t";
	// 오른쪽 열 (탭 문자 \t 사용으로 간격 유지)
	cout << " [공  격] " << (int)oldAtk << " -> " << (int)attack << " (+" <<  (int)attack - (int)oldAtk << ")" << endl;

	cout << " [방  어] " << (int)oldDef << " -> " << (int)defense << " (+" <<  (int)defense - (int)oldDef << ")\t";
	cout << " [특수공격] " << (int)oldSpAtk << " -> " << (int)specialAttack << " (+" <<  (int)specialAttack - (int)oldSpAtk << ")" << endl;

	cout << " [특수방어] " << (int)oldSpDef << " -> " << (int)specialDefense << " (+" <<  (int)specialDefense  - (int)oldSpDef << ")\t";
	cout << " [스 피 드] " << (int)oldSpeed << " -> " << (int)speed << " (+" <<  (int)speed - (int)oldSpeed <<  ")" << endl;

	cout << "==================================================\n" << endl;
	_getch();
	updateSkills();
	_getch();
}

// 5. 기술 관리 시스템 (레벨업 전용)
void Pokemon::updateSkills() {
	for (auto it = learnableSkills.begin(); it != learnableSkills.end(); ) {
		if (it->level == level) {
			if (currentSkills.size() < 4) {
				cout << "\n[!] " << name << "은(는) " << it->name << "을(를) 배웠다!" << endl;
				currentSkills.push_back(*it);
				it = learnableSkills.erase(it);
			}
			else {
				cout << "\n[!] " << name << "은(는) " << it->name << "을(를) 배우고 싶어 한다!" << endl;
				cout << "하지만 기술을 이미 4개나 알고 있어 더 이상 배울 수 없다..." << endl;
				cout << it->name << "을(를) 배우기 위해 다른 기술을 잊게 하겠습니까? (1: 예 / 0: 아니오): ";

				int choice; cin >> choice;
				if (choice == 1) {
					cout << "\n--- 현재 기술 목록 ---" << endl;
					for (int i = 0; i < (int)currentSkills.size(); ++i) {
						cout << i + 1 << ". " << currentSkills[i].name << " (PP:" << currentSkills[i].maxPp << ")" << endl;
					}
					cout << "5. 그만둔다 (배우지 않음)" << endl;
					cout << "잊게 할 기술의 번호를 선택하세요: ";

					int replaceIdx; cin >> replaceIdx;
					if (replaceIdx >= 1 && replaceIdx <= 4) {
						cout << "\n하나... 둘... 짠!" << endl;
						cout << currentSkills[replaceIdx - 1].name << "을(를) 잊고..." << endl;
						cout << it->name << "을(를) 배웠다!" << endl;
						currentSkills[replaceIdx - 1] = *it;
						it = learnableSkills.erase(it);
					}
					else {
						cout << it->name << " 배우는 것을 포기했습니다." << endl;
						it = learnableSkills.erase(it);
					}
				}
				else {
					cout << it->name << " 배우는 것을 포기했습니다." << endl;
					it = learnableSkills.erase(it);
				}
			}
		}
		else if (it->level < level) it = learnableSkills.erase(it);
		else { ++it; }
	}
}

// 6. 초기 기술 생성 시스템 (야생 몬스터 등)
void Pokemon::newpokeSkills() {
	for (auto it = learnableSkills.begin(); it != learnableSkills.end(); ) {
		if (it->level <= level) {
			if (currentSkills.size() >= 4) {
				currentSkills.erase(currentSkills.begin());
			}
			currentSkills.push_back(*it);
			it = learnableSkills.erase(it);
		}
		else {
			++it;
		}
	}
}

// 7. 전투용 임시 스텟 설정
void Pokemon::setwarstat() {
	warattack = static_cast<int>(getattack());
	wardefense = static_cast<int>(getdefense());
	warspecialAttack = static_cast<int>(getspecialAttack());
	warspecialDefense = static_cast<int>(getspecialDefense());
	warspeed = static_cast<int>(getspeed());

	// 랭크 초기화
	atkRank = defRank = spatkRank = spdefRank = spdRank = accRank = evaRank = 0;
}
// 성격 보정
std::string Pokemon::applyNatureEffect(std::string nName) {
	if (natureChart.find(nName) == natureChart.end()) return "";

	Nature n = natureChart[nName];

	// 상승 스탯 보정 (1.1배)
	if (n.upStat == "attack") this->attack *= 1.1f;
	else if (n.upStat == "defense") this->defense *= 1.1f;
	else if (n.upStat == "specialAttack") this->specialAttack *= 1.1f;
	else if (n.upStat == "specialDefense") this->specialDefense *= 1.1f;
	else if (n.upStat == "speed") this->speed *= 1.1f;

	// 하강 스탯 보정 (0.9배)
	if (n.downStat == "attack") this->attack *= 0.9f;
	else if (n.downStat == "defense") this->defense *= 0.9f;
	else if (n.downStat == "specialAttack") this->specialAttack *= 0.9f;
	else if (n.downStat == "specialDefense") this->specialDefense *= 0.9f;
	else if (n.downStat == "speed") this->speed *= 0.9f;

	std::cout << nName << " 성격이 적용되었습니다!\n";
	return { n.name };
}


