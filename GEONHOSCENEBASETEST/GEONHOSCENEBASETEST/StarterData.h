#pragma once
#include "GameData.h"

// 이현준 - 데이터 순서 수정완료: {이름, 타입, 분류, 데미지, 명중률, 현재PP, 최대PP, 습득레벨} 

// --- 1. 이상해씨 (Bulbasaur) --- 
class Bulbasaur : public Monster {
public:
	Bulbasaur(int lv) {
		name = "Bulbasaur"; type = { "Grass" }; level = lv;
		hp = 11.0f; attack = 5.0f; defense = 5.0f; specialAttack = 7.0f; specialDefense = 7.0f; speed = 5.0f;
		hpGrowth = 2.15f; attackGrowth = 1.15f; defenseGrowth = 1.15f; specialAttackGrowth = 1.65f; specialDefenseGrowth = 1.65f; speedGrowth = 1.05f;
		newpokescale(lv);
		learnableSkills = {
			{"Tackle", "Normal", "Physical", 40, 100, 35, 35, 1}, {"Growl", "Normal", "Status", 0, 100, 40, 40, 1},
			{"Vine Whip", "Grass", "Physical", 45, 100, 25, 25, 5} ,{"Leech Seed", "Grass", "Status", 0, 90, 10, 10, 99},
			{"Poison Powder", "Poison", "Status", 0, 75, 35, 35, 13}, {"Sleep Powder", "Grass", "Status", 0, 75, 15, 15, 13},
			{"Take Down", "Normal", "Physical", 90, 85, 20, 20, 15}, {"Razor Leaf", "Grass", "Physical", 55, 95, 25, 25, 19},
			{"Sweet Scent", "Normal", "Status", 0, 100, 20, 20, 23}, {"Growth", "Normal", "Status", 0, 100, 20, 20, 27},
			{"Double-Edge", "Normal", "Physical", 120, 100, 15, 15, 31}, {"Solar Beam", "Grass", "Special", 120, 100, 10, 10, 37}
		};
		newpokeSkills();
	}
};

// --- 2. 파이리 (Charmander) ---
class Charmander : public Monster {
public:
	Charmander(int lv) {
		name = "Charmander"; type =  { "Fire" }; level = lv;
		hp = 10.0f; attack = 6.0f; defense = 4.0f; specialAttack = 7.0f; specialDefense = 5.0f; speed = 7.0f;
		hpGrowth = 1.85f; attackGrowth = 1.25f; defenseGrowth = 0.95f; specialAttackGrowth = 1.55f; specialDefenseGrowth = 1.15f; speedGrowth = 1.65f;
		newpokescale(lv);
		learnableSkills = {
			{"Scratch", "Normal", "Physical", 40, 100, 35, 35, 1}, {"Growl", "Normal", "Status", 0, 100, 40, 40, 1},
			{"Ember", "Fire", "Special", 40, 100, 25, 25, 5}, {"Smokescreen", "Normal", "Status", 0, 100, 20, 20, 10},
			{"Dragon Breath", "Dragon", "Special", 60, 100, 20, 20, 16}, {"Fire Fang", "Fire", "Physical", 65, 95, 15, 15, 19},
			{"Slash", "Normal", "Physical", 70, 100, 20, 20, 25}, {"Flamethrower", "Fire", "Special", 90, 100, 15, 15, 30},
			{"Scary Face", "Normal", "Status", 0, 100, 10, 10, 34}, {"Fire Spin", "Fire", "Special", 35, 85, 15, 15, 39},
			{"Inferno", "Fire", "Special", 100, 50, 5, 5, 43}, {"Flare Blitz", "Fire", "Physical", 120, 100, 15, 15, 48}
		};
		newpokeSkills();
	}
};

// --- 3. 꼬부기 (Squirtle) ---
class Squirtle : public Monster {
public:
	Squirtle(int lv) {
		name = "Squirtle"; type = { "Water"}; level = lv;
		hp = 11.0f; attack = 5.0f; defense = 7.0f; specialAttack = 5.0f; specialDefense = 7.0f; speed = 4.0f;
		hpGrowth = 1.95f; attackGrowth = 1.15f; defenseGrowth = 1.65f; specialAttackGrowth = 1.25f; specialDefenseGrowth = 1.65f; speedGrowth = 1.05f;
		newpokescale(lv);
		learnableSkills = {
			{"Tackle", "Normal", "Physical", 40, 100, 35, 35, 1}, {"Tail Whip", "Normal", "Status", 0, 100, 30, 30, 1},
			{"Water Gun", "Water", "Special", 40, 100, 25, 25, 5}, {"Withdraw", "Water", "Status", 0, 100, 40, 40, 10},
			{"Rapid Spin", "Normal", "Physical", 20, 100, 40, 40, 13}, {"Bite", "Dark", "Physical", 60, 100, 25, 25, 16},
			{"Water Pulse", "Water", "Special", 60, 100, 20, 20, 22}, {"Protect", "Normal", "Status", 0, 100, 10, 10, 25},
			{"Rain Dance", "Water", "Status", 0, 100, 5, 5, 28}, {"Aqua Tail", "Water", "Physical", 90, 90, 10, 10, 31},
			{"Shell Smash", "Normal", "Status", 0, 100, 15, 15, 35}, {"Hydro Pump", "Water", "Special", 110, 80, 5, 5, 41}
		};
		newpokeSkills();
	}
};
