#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

// [순서 고정] GameData가 가장 먼저 와야 Pokemon 클래스를 인식합니다.
#include "GameData.h" 
#include "PokemonData.h"
#include "StarterData.h"
#include "BossData.h"

using namespace std;


// Utils.cpp 유틸리티 함수
void goToXY(int x, int y);
void setFontSize(int size);
void getActualSize(int& width, int& height);
void hideCursor();
void initConsole();
void talk(string name, string text);

// 씬 함수들
void scene1(); void scene2(); void scene3();
void scene4(); void scene5(); void scene6();
void sceneLoop();

// [추가] 스폰 시스템 초기화 함수 선언 (sceneLoop에서 사용)
void initSpawnPool();

// Data.cpp 전역 변수들 (실제 본체는 Data.cpp에 있음)
extern string g_playerName, g_starterName;
extern int g_playerGold, g_currentFloor;

// [핵심 추가] 객체 형태의 전역 변수 선언
extern Player g_player;        // 플레이어 객체 본체
extern Pokemon* g_playerPoke;  // 플레이어의 파트너 포켓몬 포인터
extern vector<Pokemon*> g_playerParty; // 플레이어의 파티 포켓몬

// [추가] 중복 방지 스폰 풀 (vector 에러 방지용)
extern vector<string> g_normalPool;
extern vector<string> g_legendaryPool;
