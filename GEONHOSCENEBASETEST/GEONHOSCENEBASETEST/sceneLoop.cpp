#include "Common.h"

// 다른 파일에 있는 4번(전투), 5번(상점) 호출
void scene4();
void scene5();

void sceneLoop() {
	// 게임 시작 시 한 번만 덱(Pool)을 섞어줍니다.
	initSpawnPool();

	while (g_currentFloor <= 15) {
		// 1. 전투 시작 (scene4 내부에서 spawnEnemy가 호출됨)
		scene4();

		// 2. 전투 결과 확인 (내 포켓몬이 쓰러졌으면 게임 오버)
		if (g_playerPoke->gethp() <= 0) {
			talk("시스템", "모험이 여기서 끝났습니다...");
			break;
		}

		// 3. 승리했다면 다음 단계로
		g_currentFloor++; // 층수 증가!

		if (g_currentFloor > 15) break; // 15층 클리어 시 탈출

		// 4. 상점 방문 여부 (선택 사항)
		talk("시스템", to_string(g_currentFloor) + "층에 도달했습니다. 상점에 들르겠습니까?");
		scene5(); // 상점 및 정비
	}
}
