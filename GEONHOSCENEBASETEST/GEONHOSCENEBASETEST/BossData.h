#ifndef BOSS_DATA_H
#define BOSS_DATA_H

#include "GameData.h"

// [Boss 1] 스이쿤 (Suicune)
class Suicune : public Monster {
public:
	Suicune(int lv) {
		name = "Suicune";
		type = { "Water" }; // [수정] 단일 타입도 반드시 중괄호 사용
		level = lv;
		hp = 20.0f; attack = 8.0f; defense = 12.0f; specialAttack = 9.0f; specialDefense = 12.0f; speed = 9.0f;
		hpGrowth = 3.85f; attackGrowth = 2.15f; defenseGrowth = 3.65f; specialAttackGrowth = 2.85f; specialDefenseGrowth = 3.65f; speedGrowth = 2.45f;

		newpokescale(lv);

		learnableSkills = {
			{"Bite", "Dark", "Physical", 60, 100, 25, 25, 1}, {"Leer", "Normal", "Status", 0, 100, 30, 30, 1},
			{"Bubble Beam", "Water", "Special", 65, 100, 20, 20, 8}, {"Rain Dance", "Water", "Status", 0, 100, 5, 5, 12},
			{"Gust", "Flying", "Special", 40, 100, 35, 35, 17}, {"Aurora Beam", "Ice", "Special", 65, 100, 20, 20, 24},
			{"Mist", "Ice", "Status", 0, 100, 30, 30, 29}, {"Mirror Coat", "Psychic", "Special", 0, 100, 20, 20, 35},
			{"Ice Beam", "Ice", "Special", 90, 100, 10, 10, 42}, {"Hydro Pump", "Water", "Special", 110, 80, 5, 5, 50},
			{"Blizzard", "Ice", "Special", 110, 70, 5, 5, 58}, {"Sheer Cold", "Ice", "Special", 200, 30, 5, 5, 65}
		};
		newpokeSkills();
	}
};

// [Boss 2] 루기아 (Lugia)
class Lugia : public Monster {
public:
	Lugia(int lv) {
		name = "Lugia";
		type = { "Psychic", "Flying" }; // [수정] 복합 타입 중괄호 리스트화
		level = lv;
		hp = 22.0f; attack = 9.0f; defense = 13.0f; specialAttack = 9.0f; specialDefense = 15.0f; speed = 11.0f;
		hpGrowth = 4.55f; attackGrowth = 2.85f; defenseGrowth = 3.85f; specialAttackGrowth = 2.85f; specialDefenseGrowth = 4.85f; speedGrowth = 3.45f;
		newpokescale(lv);
		learnableSkills = {
			{"Gust", "Flying", "Special", 40, 100, 35, 35, 1}, {"Whirlwind", "Normal", "Status", 0, 100, 20, 20, 1},
			{"Weather Ball", "Normal", "Special", 50, 100, 10, 10, 9}, {"Ancient Power", "Rock", "Special", 60, 100, 5, 5, 15},
			{"Recover", "Normal", "Status", 0, 100, 10, 10, 23}, {"Air Blast", "Flying", "Special", 80, 100, 15, 15, 29},
			{"Extrasensory", "Psychic", "Special", 80, 100, 20, 20, 35}, {"Psychic", "Psychic", "Special", 90, 100, 10, 10, 42},
			{"Aeroblast", "Flying", "Special", 100, 95, 5, 5, 50}, {"Sky Attack", "Flying", "Physical", 140, 90, 5, 5, 58},
			{"Hydro Pump", "Water", "Special", 110, 80, 5, 5, 65}
		};
		newpokeSkills();
	}
};

// [Boss 3] 레쿠쟈 (Rayquaza)
class Rayquaza : public Monster {
public:
	Rayquaza(int lv) {
		name = "Rayquaza";
		type = { "Dragon", "Flying" }; // [수정] 공백 제거 및 형식 통일
		level = lv;
		hp = 25.0f; attack = 15.0f; defense = 10.0f; specialAttack = 15.0f; specialDefense = 10.0f; speed = 11.0f;
		hpGrowth = 5.25f; attackGrowth = 4.85f; defenseGrowth = 3.05f; specialAttackGrowth = 4.85f; specialDefenseGrowth = 3.05f; speedGrowth = 3.45f;
		newpokescale(lv);
		learnableSkills = {
			{"Twister", "Dragon", "Special", 40, 100, 20, 20, 1}, {"Scary Face", "Normal", "Status", 0, 100, 10, 10, 1},
			{"Ancient Power", "Rock", "Special", 60, 100, 5, 5, 9}, {"Crunch", "Dark", "Physical", 80, 100, 15, 15, 18},
			{"Air Slash", "Flying", "Special", 75, 95, 15, 15, 27}, {"Dragon Pulse", "Dragon", "Special", 85, 100, 10, 10, 35},
			{"Extreme Speed", "Normal", "Physical", 80, 100, 5, 5, 42}, {"Dragon Dance", "Dragon", "Status", 0, 100, 20, 20, 48},
			{"Outrage", "Dragon", "Physical", 120, 100, 10, 10, 55}, {"Hyper Beam", "Normal", "Special", 150, 90, 5, 5, 62},
			{"Dragon Ascent", "Flying", "Physical", 120, 100, 5, 5, 70}
		};
		newpokeSkills();
	}
};

#endif
