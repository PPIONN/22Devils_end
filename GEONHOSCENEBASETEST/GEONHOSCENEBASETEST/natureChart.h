#pragma once
#include <string>
#include <map>
struct Nature {
	std::string name;
	std::string upStat;   // 1.1배 되는 스탯
	std::string downStat; // 0.9배 되는 스탯
};
static std::map<std::string, Nature> natureChart = {
	{"Hardy",   {"Hardy",   "", ""}},          // 변동 없음
	{"Lonely",  {"Lonely",  "attack", "defense"}},
	{"Brave",   {"Brave",   "attack", "speed"}},
	{"Adamant", {"Adamant", "attack", "specialAttack"}},
	{"Naughty", {"Naughty", "attack", "specialDefense"}},
	{"Bold",    {"Bold",    "defense", "attack"}},
	{"Docile",  {"Docile",  "", ""}},          // 변동 없음
	{"Relaxed", {"Relaxed", "defense", "speed"}},
	{"Impish",  {"Impish",  "defense", "specialAttack"}},
	{"Lax",     {"Lax",     "defense", "specialDefense"}},
	{"Timid",   {"Timid",   "speed", "attack"}},      // 고오스 추천 1 (스피드업)
	{"Hasty",   {"Hasty",   "speed", "defense"}},
	{"Serious", {"Serious", "", ""}},          // 변동 없음
	{"Jolly",   {"Jolly",   "speed", "specialAttack"}},
	{"Naive",   {"Naive",   "speed", "specialDefense"}},
	{"Modest",  {"Modest",  "specialAttack", "attack"}}, // 고오스 추천 2 (특공업)
	{"Mild",    {"Mild",    "specialAttack", "defense"}},
	{"Quiet",   {"Quiet",   "specialAttack", "speed"}},
	{"Bashful", {"Bashful", "", ""}},          // 변동 없음
	{"Rash",    {"Rash",    "specialAttack", "specialDefense"}},
	{"Calm",    {"Calm",    "specialDefense", "attack"}},
	{"Gentle",  {"Gentle",  "specialDefense", "defense"}},
	{"Sassy",   {"Sassy",   "specialDefense", "speed"}},
	{"Careful", {"Careful", "specialDefense", "specialAttack"}},
	{"Quirky",  {"Quirky",  "", ""}}           // 변동 없음
};
