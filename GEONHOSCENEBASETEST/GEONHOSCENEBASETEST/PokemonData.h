#ifndef POKEMON_DATA_H 
#define POKEMON_DATA_H

#include "GameData.h" 
#include <string>
#include <vector>

using namespace std;

// --- 1. 고오스 (Gastly) ---
class Gastly : public Monster {
public:
	Gastly(int lv) {
		name = "Gastly";
		type = { "Ghost", "Poison" }; // 복합 타입 수정
		level = lv;
		hp = 10.0f; attack = 4.0f; defense = 3.0f;
		specialAttack = 10.0f; specialDefense = 4.0f; speed = 8.0f;

		hpGrowth = 1.65f; attackGrowth = 1.05f; defenseGrowth = 0.85f;
		specialAttackGrowth = 2.65f; specialDefenseGrowth = 1.15f; speedGrowth = 2.15f;

		newpokescale(lv);
		learnableSkills = {
			{"Lick", "Ghost", "Physical", 30, 100, 30, 30, 1}, {"Confuse Ray", "Ghost", "Status", 0, 100, 10, 10, 1},
			{"Hypnosis", "Psychic", "Status", 0, 60, 20, 20, 5}, {"Mean Look", "Normal", "Status", 0, 100, 5, 5, 8},
			{"Payback", "Dark", "Physical", 50, 100, 10, 10, 12}, {"Spite", "Ghost", "Status", 0, 100, 10, 10, 15},
			{"Curse", "Ghost", "Status", 0, 100, 10, 10, 19}, {"Night Shade", "Ghost", "Special", 0, 100, 15, 15, 22},
			{"Sucker Punch", "Dark", "Physical", 70, 100, 5, 5, 26}, {"Shadow Ball", "Ghost", "Special", 80, 100, 15, 15, 29},
			{"Dream Eater", "Psychic", "Special", 100, 100, 15, 15, 33}, {"Dark Pulse", "Dark", "Special", 80, 100, 15, 15, 36}
		};
		newpokeSkills();
	}
};

// --- 2. 잠만보 (Snorlax) ---
class Snorlax : public Monster {
public:
	Snorlax(int lv) {
		name = "Snorlax";
		type = { "Normal" }; // 단일 타입도 중괄호 사용
		level = lv;
		hp = 20.0f; attack = 11.0f; defense = 6.0f; specialAttack = 6.0f; specialDefense = 11.0f; speed = 3.0f;
		hpGrowth = 4.55f; attackGrowth = 3.15f; defenseGrowth = 1.85f; specialAttackGrowth = 1.65f; specialDefenseGrowth = 3.15f; speedGrowth = 0.85f;
		newpokescale(lv);
		learnableSkills = {
			{"Tackle", "Normal", "Physical", 40, 100, 35, 35, 1}, {"Defense Curl", "Normal", "Status", 0, 100, 40, 40, 1},
			{"Amnesia", "Psychic", "Status", 0, 100, 20, 20, 4}, {"Lick", "Ghost", "Physical", 30, 100, 30, 30, 9},
			{"Recycle", "Normal", "Status", 0, 100, 10, 10, 12}, {"Screech", "Normal", "Status", 0, 85, 40, 40, 17},
			{"Body Slam", "Normal", "Physical", 85, 100, 15, 15, 20}, {"Rest", "Psychic", "Status", 0, 100, 10, 10, 25},
			{"Snore", "Normal", "Special", 50, 100, 15, 15, 28}, {"Sleep Talk", "Normal", "Status", 0, 100, 10, 10, 33},
			{"Hammer Arm", "Fighting", "Physical", 100, 90, 10, 10, 36}, {"Giga Impact", "Normal", "Physical", 150, 90, 5, 5, 44}
		};
		newpokeSkills();
	}
};

// --- 3. 잉어킹 (Magikarp) ---
class Magikarp : public Monster {
public:
	Magikarp(int lv) {
		name = "Magikarp";
		type = { "Water" };
		level = lv;
		hp = 8.0f; attack = 2.0f; defense = 6.0f; specialAttack = 2.0f; specialDefense = 4.0f; speed = 8.0f;
		hpGrowth = 1.25f; attackGrowth = 0.55f; defenseGrowth = 1.85f; specialAttackGrowth = 0.55f; specialDefenseGrowth = 1.05f; speedGrowth = 1.85f;
		newpokescale(lv);
		learnableSkills = {
			{"Splash", "Normal", "Status", 0, 100, 40, 40, 1},
			{"Tackle", "Normal", "Physical", 40, 100, 35, 35, 15},
			{"Flail", "Normal", "Physical", 0, 100, 15, 15, 30},
			{"Bounce", "Flying", "Physical", 85, 85, 5, 5, 45}
		};
		newpokeSkills();
	}
};

// --- 4. 마자용 (Wobbuffet) ---
class Wobbuffet : public Monster {
public:
	Wobbuffet(int lv) {
		name = "Wobbuffet";
		type = { "Psychic" };
		level = lv;
		hp = 35.0f; attack = 2.0f; defense = 6.0f; specialAttack = 2.0f; specialDefense = 6.0f; speed = 3.0f;
		hpGrowth = 6.55f; attackGrowth = 0.35f; defenseGrowth = 1.45f; specialAttackGrowth = 0.35f; specialDefenseGrowth = 1.45f; speedGrowth = 0.65f;
		newpokescale(lv);
		learnableSkills = {
			{"Counter", "Fighting", "Physical", 0, 100, 20, 20, 1},
			{"Mirror Coat", "Psychic", "Special", 0, 100, 20, 20, 1},
			{"Safeguard", "Normal", "Status", 0, 100, 25, 25, 1},
			{"Destiny Bond", "Ghost", "Status", 0, 100, 5, 5, 15}
		};
		newpokeSkills();
	}
};

// --- 5. 치렁 (Chimecho) ---
class Chimecho : public Monster {
public:
	Chimecho(int lv) {
		name = "Chimecho";
		type = { "Psychic" };
		level = lv;
		hp = 14.0f; attack = 6.0f; defense = 7.0f; specialAttack = 9.0f; specialDefense = 8.0f; speed = 6.0f;
		hpGrowth = 2.25f; attackGrowth = 1.55f; defenseGrowth = 2.05f; specialAttackGrowth = 2.65f; specialDefenseGrowth = 2.45f; speedGrowth = 1.65f;
		newpokescale(lv);
		learnableSkills = {
			{"Confusion", "Psychic", "Special", 50, 100, 25, 25, 1}, {"Astonish", "Ghost", "Physical", 30, 100, 15, 15, 4},
			{"Growl", "Normal", "Status", 0, 100, 40, 40, 7}, {"Psiwave", "Psychic", "Special", 0, 100, 15, 15, 10},
			{"Take Down", "Normal", "Physical", 90, 85, 20, 20, 13}, {"Extrasensory", "Psychic", "Special", 80, 100, 20, 20, 16},
			{"Heal Bell", "Normal", "Status", 0, 100, 5, 5, 19}, {"Safeguard", "Normal", "Status", 0, 100, 25, 25, 22},
			{"Uproar", "Normal", "Special", 90, 100, 10, 10, 25}, {"Psychic", "Psychic", "Special", 90, 100, 10, 10, 32},
			{"Healing Wish", "Psychic", "Status", 0, 100, 10, 10, 38}, {"Synchronoise", "Psychic", "Special", 120, 100, 10, 10, 44}
		};
		newpokeSkills();
	}
};

// --- 6. 딥상어동 (Gible) ---
class Gible : public Monster {
public:
	Gible(int lv) {
		name = "Gible";
		type = { "Dragon", "Ground" };
		level = lv;
		hp = 12.0f; attack = 7.0f; defense = 5.0f; specialAttack = 5.0f; specialDefense = 5.0f; speed = 5.0f;
		hpGrowth = 2.45f; attackGrowth = 2.35f; defenseGrowth = 1.45f; specialAttackGrowth = 1.25f; specialDefenseGrowth = 1.45f; speedGrowth = 1.35f;
		newpokescale(lv);
		learnableSkills = {
			{"Tackle", "Normal", "Physical", 40, 100, 35, 35, 1}, {"Sand Attack", "Ground", "Status", 0, 100, 15, 15, 3},
			{"Dragon Rage", "Dragon", "Special", 40, 100, 10, 10, 7}, {"Sand Tomb", "Ground", "Physical", 35, 85, 15, 15, 13},
			{"Take Down", "Normal", "Physical", 90, 85, 20, 20, 15}, {"Dragon Breath", "Dragon", "Special", 60, 100, 20, 20, 19},
			{"Slash", "Normal", "Physical", 70, 100, 20, 20, 23}, {"Dragon Claw", "Dragon", "Physical", 80, 100, 15, 15, 27},
			{"Dig", "Ground", "Physical", 80, 100, 10, 10, 31}, {"Dragon Rush", "Dragon", "Physical", 100, 75, 10, 10, 35},
			{"Sandstorm", "Rock", "Status", 0, 100, 10, 10, 40}, {"Draco Meteor", "Dragon", "Special", 130, 90, 5, 5, 48}
		};
		newpokeSkills();
	}
};

// --- 7. 브케인 (Cyndaquil) ---
class Cyndaquil : public Monster {
public:
	Cyndaquil(int lv) {
		name = "Cyndaquil";
		type = { "Fire" };
		level = lv;
		hp = 10.0f; attack = 5.0f; defense = 4.0f; specialAttack = 6.0f; specialDefense = 5.0f; speed = 7.0f;
		hpGrowth = 1.85f; attackGrowth = 1.15f; defenseGrowth = 0.95f; specialAttackGrowth = 1.65f; specialDefenseGrowth = 1.15f; speedGrowth = 1.65f;
		newpokescale(lv);
		learnableSkills = {
			{"Tackle", "Normal", "Physical", 40, 100, 35, 35, 1}, {"Leer", "Normal", "Status", 0, 100, 30, 30, 1},
			{"Smokescreen", "Normal", "Status", 0, 100, 20, 20, 6}, {"Ember", "Fire", "Special", 40, 100, 25, 25, 10},
			{"Quick Attack", "Normal", "Physical", 40, 100, 30, 30, 13}, {"Flame Wheel", "Fire", "Physical", 60, 100, 25, 25, 19},
			{"Defense Curl", "Normal", "Status", 0, 100, 40, 40, 22}, {"Swift", "Normal", "Special", 60, 100, 20, 20, 28},
			{"Lava Plume", "Fire", "Special", 80, 100, 15, 15, 31}, {"Flamethrower", "Fire", "Special", 90, 100, 15, 15, 37},
			{"Rollout", "Rock", "Physical", 30, 90, 20, 20, 40}, {"Eruption", "Fire", "Special", 150, 100, 5, 5, 46}
		};
		newpokeSkills();
	}
};

// --- 8. 엠페르트 (Empoleon) ---
class Empoleon : public Monster {
public:
	Empoleon(int lv) {
		name = "Empoleon";
		type = { "Water", "Steel" };
		level = lv;
		hp = 12.0f; attack = 6.0f; defense = 6.0f; specialAttack = 8.0f; specialDefense = 8.0f; speed = 5.0f;
		hpGrowth = 2.45f; attackGrowth = 1.85f; defenseGrowth = 2.15f; specialAttackGrowth = 2.85f; specialDefenseGrowth = 2.65f; speedGrowth = 1.45f;
		newpokescale(lv);
		learnableSkills = {
			{"Pound", "Normal", "Physical", 40, 100, 35, 35, 1}, {"Growl", "Normal", "Status", 0, 100, 40, 40, 1},
			{"Water Gun", "Water", "Special", 40, 100, 25, 25, 8}, {"Metal Claw", "Steel", "Physical", 50, 95, 35, 35, 11},
			{"Swagger", "Normal", "Status", 0, 85, 15, 15, 15}, {"Bubble Beam", "Water", "Special", 65, 100, 20, 20, 19},
			{"Bide", "Normal", "Status", 0, 100, 10, 10, 24}, {"Drill Peck", "Flying", "Physical", 80, 100, 20, 20, 28},
			{"Whirlpool", "Water", "Special", 35, 85, 15, 15, 33}, {"Mist", "Ice", "Status", 0, 100, 30, 30, 39},
			{"Flash Cannon", "Steel", "Special", 80, 100, 10, 10, 46}, {"Hydro Pump", "Water", "Special", 110, 80, 5, 5, 52}
		};
		newpokeSkills();
	}
};

// --- 9. 루카리오 (Lucario) ---
class Lucario : public Monster {
public:
	Lucario(int lv) {
		name = "Lucario";
		type = { "Fighting", "Steel" };
		level = lv;
		hp = 10.0f; attack = 8.0f; defense = 5.0f; specialAttack = 8.0f; specialDefense = 5.0f; speed = 7.0f;
		hpGrowth = 2.15f; attackGrowth = 3.25f; defenseGrowth = 1.85f; specialAttackGrowth = 3.15f; specialDefenseGrowth = 1.85f; speedGrowth = 2.65f;
		newpokescale(lv);
		learnableSkills = {
			{"Quick Attack", "Normal", "Physical", 40, 100, 30, 30, 8}, {"Detect", "Fighting", "Status", 0, 100, 5, 5, 8},
			{"Metal Claw", "Steel", "Physical", 50, 95, 35, 35, 5}, {"Counter", "Fighting", "Physical", 0, 100, 20, 20, 11},
			{"Force Palm", "Fighting", "Physical", 60, 100, 10, 10, 15}, {"Bone Rush", "Ground", "Physical", 25, 80, 10, 10, 19},
			{"Screech", "Normal", "Status", 0, 85, 40, 40, 24}, {"Aura Sphere", "Fighting", "Special", 80, 100, 20, 20, 29},
			{"Calm Mind", "Psychic", "Status", 0, 100, 20, 20, 33}, {"Dragon Pulse", "Dragon", "Special", 85, 100, 10, 10, 37},
			{"Extreme Speed", "Normal", "Physical", 80, 100, 5, 5, 42}, {"Close Combat", "Fighting", "Physical", 120, 100, 5, 5, 48}
		};
		newpokeSkills();
	}
};

// --- 10. 가디안 (Gardevoir) ---
class Gardevoir : public Monster {
public:
	Gardevoir(int lv) {
		name = "Gardevoir";
		type = { "Psychic", "Fairy" };
		level = lv;
		hp = 11.0f; attack = 6.0f; defense = 6.0f; specialAttack = 9.0f; specialDefense = 9.0f; speed = 7.0f;
		hpGrowth = 2.05f; attackGrowth = 1.55f; defenseGrowth = 1.65f; specialAttackGrowth = 3.25f; specialDefenseGrowth = 3.15f; speedGrowth = 2.15f;
		newpokescale(lv);
		learnableSkills = {
			{"Confusion", "Psychic", "Special", 50, 100, 25, 25, 1}, {"Disarming Voice", "Fairy", "Special", 40, 100, 15, 15, 1},
			{"Double Team", "Normal", "Status", 0, 100, 15, 15, 9}, {"Teleport", "Psychic", "Status", 0, 100, 20, 20, 12},
			{"Psybeam", "Psychic", "Special", 65, 100, 20, 20, 15}, {"Life Dew", "Water", "Status", 0, 100, 10, 10, 18},
			{"Calm Mind", "Psychic", "Status", 0, 100, 20, 20, 23}, {"Psychic", "Psychic", "Special", 90, 100, 10, 10, 30},
			{"Moonblast", "Fairy", "Special", 95, 100, 15, 15, 35}, {"Dream Eater", "Psychic", "Special", 100, 100, 15, 15, 41},
			{"Future Sight", "Psychic", "Special", 120, 100, 10, 10, 48}, {"Hypnosis", "Psychic", "Status", 0, 60, 20, 20, 53}
		};
		newpokeSkills();
	}
};

// --- 11. 한카리아스 (Garchomp) ---
class Garchomp : public Monster {
public:
	Garchomp(int lv) {
		name = "Garchomp";
		type = { "Dragon", "Ground" };
		level = lv;
		hp = 15.0f; attack = 9.0f; defense = 7.0f; specialAttack = 6.0f; specialDefense = 6.0f; speed = 8.0f;
		hpGrowth = 3.15f; attackGrowth = 3.55f; defenseGrowth = 2.45f; specialAttackGrowth = 1.85f; specialDefenseGrowth = 2.15f; speedGrowth = 2.75f;
		newpokescale(lv);
		learnableSkills = {
			{"Sand Tomb", "Ground", "Physical", 35, 85, 15, 15, 1}, {"Tackle", "Normal", "Physical", 40, 100, 35, 35, 1},
			{"Sand Attack", "Ground", "Status", 0, 100, 15, 15, 7}, {"Dragon Breath", "Dragon", "Special", 60, 100, 20, 20, 13},
			{"Slash", "Normal", "Physical", 70, 100, 20, 20, 19}, {"Dragon Claw", "Dragon", "Physical", 80, 100, 15, 15, 25},
			{"Dig", "Ground", "Physical", 80, 100, 10, 10, 32}, {"Crunch", "Dark", "Physical", 80, 100, 15, 15, 39},
			{"Dragon Rush", "Dragon", "Physical", 100, 75, 10, 10, 48}, {"Earthquake", "Ground", "Physical", 100, 100, 10, 10, 54}
		};
		newpokeSkills();
	}
};

// --- 12. 마기라스 (Tyranitar) ---
class Tyranitar : public Monster {
public:
	Tyranitar(int lv) {
		name = "Tyranitar";
		type = { "Rock", "Dark" };
		level = lv;
		hp = 14.0f; attack = 9.0f; defense = 8.0f; specialAttack = 7.0f; specialDefense = 7.0f; speed = 5.0f;
		hpGrowth = 2.85f; attackGrowth = 3.45f; defenseGrowth = 2.85f; specialAttackGrowth = 2.15f; specialDefenseGrowth = 2.55f; speedGrowth = 1.65f;
		newpokescale(lv);
		learnableSkills = {
			{"Rock Throw", "Rock", "Physical", 50, 90, 15, 15, 1}, {"Bite", "Dark", "Physical", 60, 100, 25, 25, 1},
			{"Stomp", "Normal", "Physical", 65, 100, 20, 20, 9}, {"Scary Face", "Normal", "Status", 0, 100, 10, 10, 12},
			{"Rock Slide", "Rock", "Physical", 75, 90, 10, 10, 18}, {"Crunch", "Dark", "Physical", 80, 100, 15, 15, 24},
			{"Payback", "Dark", "Physical", 50, 100, 10, 10, 31}, {"Stone Edge", "Rock", "Physical", 100, 80, 5, 5, 41},
			{"Earthquake", "Ground", "Physical", 100, 100, 10, 10, 48}, {"Hyper Beam", "Normal", "Special", 150, 90, 5, 5, 59}
		};
		newpokeSkills();
	}
};

#endif
