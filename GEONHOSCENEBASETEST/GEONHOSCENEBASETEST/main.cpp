#include "Common.h"

int main() {
	initConsole(); // 초기화 (Utils.cpp)

	scene1();     // 타이틀
	scene2();     // 오박사/이름/스타팅
	scene3();     // 탑 도착
	sceneLoop();  // 전투와 상점 무한 반복 루프
	scene6();     // 루프 종료 후 최종 엔딩

	return 0;
}
