#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 기술 구조체
struct Skill {
	string name; string type; string category;
	int power; int accuracy; int pp; int maxPp; int level;
};

// 포켓몬 클래스 (뼈대)
class Pokemon {
protected:
	string name;
	string nature = "Brave";
	std::vector<std::string> type;
	float hp, maxHp, attack, defense, specialAttack, specialDefense, speed;
	float hpGrowth, attackGrowth, defenseGrowth, specialAttackGrowth, specialDefenseGrowth, speedGrowth;
	int warattack, wardefense, warspecialAttack, warspecialDefense, warspeed; // -이현준 추가 전투 스탯
	int level, exp = 10;
	int atkRank = 0, defRank = 0, spatkRank = 0, spdefRank = 0, spdRank = 0, accRank = 0, evaRank = 0;
public:
	virtual ~Pokemon() {
		// 동적 할당된 내부 포인터가 있다면 여기서 delete
		// 지금은 특별히 없다면 비워둬도 되지만 'virtual'은 필수!
	}
	vector<Skill> learnableSkills;
	vector<Skill> currentSkills;


	//void sethp(float h) { hp = (h > maxHp) ? maxHp : (h < 1 ? 0 : h); }
	//void setattack(float a) { attack = a; }

	//float getdefense() { return defense; }
	//float getspecialDefense() { return specialDefense; }
	//float getmaxhp() { return maxHp; }
	//float getattack() { return attack; }
	//string getName() { return name; }
	//int getlevel() { return level; }
	//float gethp() { return hp; }
	inline string getName() const {	return name; }
	inline string getNature() const { return nature; }
	inline float getmaxhp() const	{	return (maxHp);	}
	inline float gethp() const {	return (hp);}
	inline float getattack() const {	return (attack);	}
	inline float getdefense() const {	return (defense);	}
	inline float getspecialAttack() const {	return (specialAttack);	}
	inline float getspecialDefense() const {	return (specialDefense);	}
	inline float getspeed() const {	return (speed);	}
	inline int getlevel() const {	return level;	}
	inline void setname(const std::string& name) { this->name = name;};
	//inline void setrealname(const std::string& realname) {	this->realname = realname;};
	inline void setlevel(const int level) {	this->level = level;	}
	//inline void setmaxhp(const float hp) {this->maxHp = hp;	}
	inline void sethp(const float h) { hp = (h > maxHp) ? maxHp : (h < 1 ? 0 : h); }
	inline void setattack(const float attack) {	this->attack = attack;	}
	inline void setdefense(const float defense) {this->defense = defense;}
	inline void setspecialAttack(const float specialAttack) {this->specialAttack = specialAttack;}
	inline void setspecialDefense(const float specialDefense) {this->specialDefense = specialDefense;}
	inline void setspeed(const float speed) {this->speed = speed;}
	void setwarstat(); // 이현준 추가. 전투스탯
	void newpokescale(int targetLevel);
	void levelup();
	int useSkill(int skillIdx, Pokemon& target);
	void updateSkills(); // 추가
	void newpokeSkills(); // 이 이름으로 통일합니다.
	void gainExp(int amount);
	std::string applyNatureEffect(std::string nName);


};

class Monster : public Pokemon {};

class Player {
public:
	int money = 500;
	int level = 1;
	int exp = 0;
	vector<string> inventory;

	void gainExp(int amount);
	void ShowStatus();
	void InventoryUI();
	int getmoney() const { return money; }
	void setmoney(int m) { money += m; }
	void AddItem(string itemName);
	bool HasItem(string itemName);
	void RemoveItem(string itemName);
};

class Item {
public:
	static void RareCandy(Player& player);
	static void BuyHPPotion(Player& player);
	static void UseHPPotion(Player& player, Pokemon* poke);
	static void BuyFHPPotion(Player& player);
	static void UseFHPPotion(Player& player, Pokemon* poke);
	static void BuyPowerPotion(Player& player);
	static void UsePowerPotion(Player& player, Pokemon* poke);
	//static void BuyArmorPotion(Player& player, Pokemon* poke);
	//static void UseArmorPotion(Player& player, Pokemon* poke);
	static void Userandomexp(Player& player);
	static void Userandomgold(Player& player);
	static void BuyMultiLens(Player& player);
};

// 전역 변수 선언 (외부 참조용)
extern Player g_player;
extern int g_playerGold;
void initSpawnPool();
