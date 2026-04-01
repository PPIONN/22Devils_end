#include <string>
#include <unordered_map>
#include <vector>

//class TypeChart {
//public:
//	static float getEffectiveness(std::string atk, std::string def) {
//		// [공격 타입] 기준 -> [방어 타입] 배율
//		if (atk == "Normal") { if (def == "Rock" || def == "Steel") return 0.5f; if (def == "Ghost") return 0.0f; }
//		if (atk == "Fire") { if (def == "Grass" || def == "Ice" || def == "Bug" || def == "Steel") return 2.0f; if (def == "Fire" || def == "Water" || def == "Rock" || def == "Dragon") return 0.5f; }
//		if (atk == "Water") { if (def == "Fire" || def == "Ground" || def == "Rock") return 2.0f; if (def == "Water" || def == "Grass" || def == "Dragon") return 0.5f; }
//		if (atk == "Grass") { if (def == "Water" || def == "Ground" || def == "Rock") return 2.0f; if (def == "Fire" || def == "Grass" || def == "Poison" || def == "Flying" || def == "Bug" || def == "Dragon" || def == "Steel") return 0.5f; }
//		if (atk == "Electric") { if (def == "Water" || def == "Flying") return 2.0f; if (def == "Electric" || def == "Grass" || def == "Dragon") return 0.5f; if (def == "Ground") return 0.0f; }
//		if (atk == "Ice") { if (def == "Grass" || def == "Ground" || def == "Flying" || def == "Dragon") return 2.0f; if (def == "Fire" || def == "Water" || def == "Ice" || def == "Steel") return 0.5f; }
//		if (atk == "Fighting") { if (def == "Normal" || def == "Ice" || def == "Rock" || def == "Dark" || def == "Steel") return 2.0f; if (def == "Poison" || def == "Flying" || def == "Psychic" || def == "Bug") return 0.5f; if (def == "Ghost") return 0.0f; }
//		if (atk == "Poison") { if (def == "Grass") return 2.0f; if (def == "Poison" || def == "Ground" || def == "Rock" || def == "Ghost") return 0.5f; if (def == "Steel") return 0.0f; }
//		if (atk == "Ground") { if (def == "Fire" || def == "Electric" || def == "Poison" || def == "Rock" || def == "Steel") return 2.0f; if (def == "Grass" || def == "Bug") return 0.5f; if (def == "Flying") return 0.0f; }
//		if (atk == "Flying") { if (def == "Grass" || def == "Fighting" || def == "Bug") return 2.0f; if (def == "Electric" || def == "Rock" || def == "Steel") return 0.5f; }
//		if (atk == "Psychic") { if (def == "Fighting" || def == "Poison") return 2.0f; if (def == "Psychic" || def == "Steel") return 0.5f; if (def == "Dark") return 0.0f; }
//		if (atk == "Bug") { if (def == "Grass" || def == "Psychic" || def == "Dark") return 2.0f; if (def == "Fire" || def == "Fighting" || def == "Poison" || def == "Flying" || def == "Ghost" || def == "Steel") return 0.5f; }
//		if (atk == "Rock") { if (def == "Fire" || def == "Ice" || def == "Flying" || def == "Bug") return 2.0f; if (def == "Fighting" || def == "Ground" || def == "Steel") return 0.5f; }
//		if (atk == "Ghost") { if (def == "Psychic" || def == "Ghost") return 2.0f; if (def == "Dark") return 0.5f; if (def == "Normal") return 0.0f; }
//		if (atk == "Dragon") { if (def == "Dragon") return 2.0f; if (def == "Steel") return 0.5f; }
//		if (atk == "Dark") { if (def == "Psychic" || def == "Ghost") return 2.0f; if (def == "Fighting" || def == "Dark") return 0.5f; }
//		if (atk == "Steel") { if (def == "Ice" || def == "Rock") return 2.0f; if (def == "Fire" || def == "Water" || def == "Electric" || def == "Steel") return 0.5f; }
//
//		return 1.0f; // 기본 무상성
//	}
//};
class TypeChart { // 기존 if문 하드코딩에서 unorderd_map 으로 고침 - 이현준 기존 코드의 리턴값을 해치지않음
private:
	static inline std::unordered_map<std::string, std::unordered_map<std::string, float>> chart = {
		{"Normal",   {{"Rock", 0.5f}, {"Steel", 0.5f}, {"Ghost", 0.0f}}},
		{"Fire",     {{"Grass", 2.0f}, {"Ice", 2.0f}, {"Bug", 2.0f}, {"Steel", 2.0f}, {"Fire", 0.5f}, {"Water", 0.5f}, {"Rock", 0.5f}, {"Dragon", 0.5f}}},
		{"Water",    {{"Fire", 2.0f}, {"Ground", 2.0f}, {"Rock", 2.0f}, {"Water", 0.5f}, {"Grass", 0.5f}, {"Dragon", 0.5f}}},
		{"Grass",    {{"Water", 2.0f}, {"Ground", 2.0f}, {"Rock", 2.0f}, {"Fire", 0.5f}, {"Grass", 0.5f}, {"Poison", 0.5f}, {"Flying", 0.5f}, {"Bug", 0.5f}, {"Dragon", 0.5f}, {"Steel", 0.5f}}},
		{"Electric", {{"Water", 2.0f}, {"Flying", 2.0f}, {"Electric", 0.5f}, {"Grass", 0.5f}, {"Dragon", 0.5f}, {"Ground", 0.0f}}},
		{"Ice",      {{"Grass", 2.0f}, {"Ground", 2.0f}, {"Flying", 2.0f}, {"Dragon", 2.0f}, {"Fire", 0.5f}, {"Water", 0.5f}, {"Ice", 0.5f}, {"Steel", 0.5f}}},
		{"Fighting", {{"Normal", 2.0f}, {"Ice", 2.0f}, {"Rock", 2.0f}, {"Dark", 2.0f}, {"Steel", 2.0f}, {"Poison", 0.5f}, {"Flying", 0.5f}, {"Psychic", 0.5f}, {"Bug", 0.5f}, {"Ghost", 0.0f}}},
		{"Poison",   {{"Grass", 2.0f}, {"Poison", 0.5f}, {"Ground", 0.5f}, {"Rock", 0.5f}, {"Ghost", 0.5f}, {"Steel", 0.0f}}},
		{"Ground",   {{"Fire", 2.0f}, {"Electric", 2.0f}, {"Poison", 2.0f}, {"Rock", 2.0f}, {"Steel", 2.0f}, {"Grass", 0.5f}, {"Bug", 0.5f}, {"Flying", 0.0f}}},
		{"Flying",   {{"Grass", 2.0f}, {"Fighting", 2.0f}, {"Bug", 2.0f}, {"Electric", 0.5f}, {"Rock", 0.5f}, {"Steel", 0.5f}}},
		{"Psychic",  {{"Fighting", 2.0f}, {"Poison", 2.0f}, {"Psychic", 0.5f}, {"Steel", 0.5f}, {"Dark", 0.0f}}},
		{"Bug",      {{"Grass", 2.0f}, {"Psychic", 2.0f}, {"Dark", 2.0f}, {"Fire", 0.5f}, {"Fighting", 0.5f}, {"Poison", 0.5f}, {"Flying", 0.5f}, {"Ghost", 0.5f}, {"Steel", 0.5f}}},
		{"Rock",     {{"Fire", 2.0f}, {"Ice", 2.0f}, {"Flying", 2.0f}, {"Bug", 2.0f}, {"Fighting", 0.5f}, {"Ground", 0.5f}, {"Steel", 0.5f}}},
		{"Ghost",    {{"Psychic", 2.0f}, {"Ghost", 2.0f}, {"Dark", 0.5f}, {"Normal", 0.0f}}},
		{"Dragon",   {{"Dragon", 2.0f}, {"Steel", 0.5f}}},
		{"Dark",     {{"Psychic", 2.0f}, {"Ghost", 2.0f}, {"Fighting", 0.5f}, {"Dark", 0.5f}}},
		{"Steel",    {{"Ice", 2.0f}, {"Rock", 2.0f}, {"Fire", 0.5f}, {"Water", 0.5f}, {"Electric", 0.5f}, {"Steel", 0.5f}}}
	};

public:
	static float getEffectiveness(const std::string& atk, const std::string& def) {
		// 1. 공격 타입 검색
		auto atk_it = chart.find(atk);
		if (atk_it != chart.end()) {
			// 2. 방어 타입 검색
			auto def_it = atk_it->second.find(def);
			if (def_it != atk_it->second.end()) {
				return def_it->second; // 상성 결과 반환 (2.0, 0.5, 0.0)
			}
		}
		return 1.0f; // 상성표에 없으면 무조건 1배 (Normal 효율)
	}
};
