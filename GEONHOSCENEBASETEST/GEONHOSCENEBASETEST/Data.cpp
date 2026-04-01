#include "Common.h"
#include "GameData.h"

using namespace std;

// 1. 플레이어 및 포켓몬 기본 정보
string g_playerName = "???";
string g_starterName = "None";
int g_currentFloor = 1;

// [해결] LNK 에러 방지를 위한 실제 객체 생성
Player g_player;
int g_playerGold = 500;

// 2. 가장 중요한 포켓몬 포인터
Pokemon* g_playerPoke = nullptr;
vector<Pokemon*> g_playerParty;
// 3. 몬스터 스폰 풀 (일반 12마리 + 전설 3마리)
vector<string> g_normalPool = {
	"Gastly", "Snorlax", "Magikarp", "Wobbuffet", "Chimecho", "Gible",
	"Cyndaquil", "Empoleon", "Lucario", "Bulbasaur", "Charmander", "Squirtle"
};
vector<string> g_legendaryPool = { "Suicune", "Lugia", "Rayquaza" };

// [해결] LNK2019 에러 방지를 위한 함수 구현
void initSpawnPool() {
	// 이미 위에서 vector로 선언되어 있으므로 비워두어도 빌드가 가능합니다.
}
