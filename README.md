# 22Devils — Text Console RPG

> **C++ 콘솔로 만든 포켓몬식 턴제 RPG.**
> 스타팅 포켓몬 한 마리로 15층 탑을 오르며, 전투와 상점을 반복해 정상에 도달한다.

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91?style=flat-square&logo=visualstudio&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Windows%20Console-lightgrey?style=flat-square)
![Team](https://img.shields.io/badge/team-6%20people-orange?style=flat-square)

---

## 🎮 플레이 영상

[![플레이 영상](https://img.youtube.com/vi/2-kwdnVfkD4/maxresdefault.jpg)](https://www.youtube.com/watch?v=2-kwdnVfkD4)

> 위 이미지를 누르면 유튜브로 이동합니다. → https://www.youtube.com/watch?v=2-kwdnVfkD4

---

## 게임 개요

| | |
|---|---|
| **장르** | 턴제 RPG (텍스트 콘솔) |
| **플랫폼 / 언어** | Windows 콘솔 / C++ |
| **개발 기간** | 1주 |
| **인원** | 6인 (22조 붉은악마) |
| **클리어 조건** | 15층까지 올라가 보스를 꺾기 |
| **게임 오버** | 파트너 포켓몬이 쓰러지면 종료 |

한 층을 이길 때마다 층수가 오르고, 층 사이마다 상점에 들러 정비할 수 있다.
**5의 배수 층(5 · 10 · 15층)은 보스전**이며 이때는 도망칠 수 없다.

---

## 실행 방법

```bash
git clone https://github.com/PPIONN/22Devils-Text_Console_RPG.git
```

1. **Visual Studio 2022** (C++를 사용한 데스크톱 개발 워크로드) 설치
2. `GEONHOSCENEBASETEST/GEONHOSCENEBASETEST.sln` 열기 ← **최종 실행본**
3. 구성 `Debug` / 플랫폼 `x64` 로 `Ctrl + F5`

> 콘솔 폰트 크기·커서 숨김·창 크기는 `initConsole()`(Utils.cpp)이 실행 시 잡아 준다.
> 한글이 깨지면 콘솔 속성에서 글꼴을 굴림체 계열로 바꾸면 된다.

---

## 게임 흐름

`main.cpp` 한 장에 전체 흐름이 그대로 드러난다.

```cpp
int main() {
    initConsole(); // 콘솔 초기화 (Utils.cpp)

    scene1();      // 타이틀
    scene2();      // 오박사 / 이름 입력 / 스타팅 선택
    scene3();      // 탑 도착
    sceneLoop();   // 전투와 상점 무한 반복 루프
    scene6();      // 루프 종료 후 최종 엔딩

    return 0;
}
```

```
scene1  타이틀
  ↓
scene2  이름 입력 · 스타팅 포켓몬 선택
  ↓
scene3  탑 도착
  ↓
sceneLoop ┌─ scene4  전투 ──┐  (지면 게임 오버)
          │                 ↓
          └─ scene5  상점 ←─┘  층수 +1 · 15층까지 반복
  ↓
scene6  엔딩
```

---

## 핵심 시스템

### ⚔️ 전투 — 원작 공식을 그대로 옮긴 데미지 계산

```cpp
float damage = (((2.0f * level / 5.0f + 2.0f) * skill.power * (finalAtk / finalDef)) / 50.0f) + 2.0f;
damage *= eff;                                  // 타입 상성 (복합 타입은 곱연산)
if (hasSTAB) damage *= 1.5f;                    // 자속 보정
damage *= (float)(rand() % 16 + 85) / 100.0f;   // 난수 85 ~ 100%
```

- **타입 상성** — `TypeChart.h`. 복합 타입은 각 타입 배율을 곱해서 적용
- **자속 보정(STAB)** — 자기 타입과 기술 타입이 겹치면 1.5배
- **성격 보정** — `natureChart.h`. 성격에 따라 스탯이 오르고 내린다
- **명중 판정** — 기술마다 명중률을 굴려 빗나갈 수 있다
- **반동기** — 최대 체력의 25%를 자신이 되받는다
- **랭크 변화** — 공격·방어·특공·특방·스피드·명중·회피 7종. 꼬리 흔들기·울음소리 같은 변화기는 **깊은 복사로 따로 계산해 원본 종족값을 건드리지 않는다**

### 🎯 전투 메뉴

```
1. 싸운다   2. 가방   3. 포켓몬   4. 도망친다
```

| 메뉴 | 동작 |
|---|---|
| 싸운다 | 기술 4개 중 선택. 이름 / 타입 / 위력 / 명중 / PP를 함께 표시 |
| 가방 | 회복·강화 아이템 사용 |
| 포켓몬 | 파티 내 교체 (파트너 포인터를 갈아 끼운다) |
| 도망친다 | **70% 성공 / 30% 실패**, 실패하면 전투 속행. **보스전에서는 불가** |

### 👾 몬스터 스폰

`initSpawnPool()`이 게임 시작 시 풀을 한 번 섞고, 일반 풀과 전설 풀을 나눠 뽑는다.
같은 몬스터가 연달아 나오지 않도록 중복 방지를 걸었다.

### 🛒 상점 & 아이템

| 아이템 | 효과 | 가격 |
|---|---|---|
| Rare Candy | 레벨 업 | 500 G |
| HP Potion | HP 20 회복 | 100 G |
| Full HP Potion | HP 전체 회복 | 300 G |
| Power Potion | 공격력 +20 | 200 G |
| random exp | EXP 50~500 상자 | 100 G |
| random gold | GOLD 50~500 상자 | 100 G |

```
Buy()  1. 소지금 확인 → 부족하면 거절
       2. setmoney(-가격) 으로 차감
       3. AddItem("이름") 으로 인벤토리에 저장

Use()  1. HasItem() 으로 소지 확인
       2. 효과 적용 (HP 회복, 공격력 증가 등)
       3. RemoveItem() 으로 인벤토리에서 제거
```

> 처음에는 구매와 사용을 한 함수에 묶어 두었다가, 상점 시스템과 연계하면서 둘로 분리했다.

---

## 클래스 구조

```
struct Skill    이름 · 타입 · 분류 · 위력 · 명중 · PP · 습득 레벨

class Pokemon   공통 값(체력/공격/방어/특공/특방/스피드 + 성장치),
                성격, 레벨, EXP, 랭크 7종, 배울 수 있는 기술 / 현재 기술
                └ 정보를 부르고 저장하고 행동하는 함수 (set / get / useSkill …)

class Monster : public Pokemon   자식은 고유 값만 채우면 된다 → 찍어내듯 확장

class Player    소지금(시작 500G) · 레벨 · EXP · 인벤토리 · 파티

class Item      구매 / 사용 / 소지 확인
```

---

## 프로젝트 구조

```
22Devils-Text_Console_RPG/
├── GEONHOSCENEBASETEST/          ★ 최종 실행본
│   └── GEONHOSCENEBASETEST/
│       ├── main.cpp                게임 진입점
│       ├── sceneLoop.cpp           전투 ↔ 상점 15층 루프
│       ├── scene1~6.cpp            타이틀 · 스타팅 · 탑 · 전투 · 상점 · 엔딩
│       ├── Common.h                전방 선언 + 전역 변수 (공용 저장소)
│       ├── Data.cpp                전역 변수 본체
│       ├── GameData.h              Skill / Pokemon / Monster / Player / Item 설계도
│       ├── PokemonData.h           포켓몬 종족값 · 기술 테이블
│       ├── StarterData.h           스타팅 포켓몬
│       ├── BossData.h              층별 보스
│       ├── TypeChart.h             타입 상성표
│       ├── natureChart.h           성격 보정표
│       ├── pokemon.cpp             데미지 · 명중 · 랭크 계산
│       ├── Player.cpp / Item.cpp   플레이어 · 아이템 로직
│       └── Utils.cpp               콘솔 제어 (goToXY / talk / initConsole …)
│
├── 22Devils-Text_Console_RPG/    통합을 시도했던 이전 트리
├── GEONHOSCENE/ · Ghost/ · battlesystem/
├── geonho/ · main_conf/ · randomtest/ · Main/
                                  각자 맡은 부분을 따로 굴려 보던 작업 폴더
```

> 폴더가 여러 개인 것은 정리가 덜 된 게 아니라 **개발 과정 그 자체**다.
> 처음에 "각자 실행되게 만들고 나중에 합치자"로 시작했다가 통합에 실패했고,
> 그 흔적을 지우지 않고 남겨 두었다. 아래 회고에 이어진다.

---

## 팀

**22조 붉은악마** · 6인

| 팀원 | |
|---|---|
| 오채율 · 신건호 · 이현준 · 노용수 · 배건우 · 이채호 | 몬스터 3 · 아이템 1 · 시스템 1 · 플레이어 1 로 분배 |

---

## 개발 과정에서 겪은 것

**1. 목표가 공유되지 않으면 코드는 합쳐지지 않는다**
포켓몬 내부 스탯까지 구현해 놓고 보니, 모든 포켓몬이 공통으로 쓸 부모 클래스를 **누가 만들지**가 정해져 있지 않았다.
한 파일을 여럿이 만지면 충돌하니 "각자 실행되게 만들고 합치자"로 갔는데 —
합치는 순간 실행조차 되지 않았다. 함수·변수명이 서로 다르고, 누구는 무한 루프를 전제로,
누구는 층별로 출현 몹을 정해 두는 구조를 전제로 짜고 있었다.
**같은 목표를 말로만 공유했지 인터페이스로 고정하지 않은 것이 원인이었다.**

**2. Git은 돌아가는데 결과물이 다르다**
push는 되고 있었는데 pull을 해도 팀원과 파일 내용이 달랐다.
서로의 영역을 침범할까 봐, 무엇을 도와야 할지 몰라서 소통이 애매하게 끝나는 일이 반복됐다.

**3. 결국 릴레이로 완성했다**
일단 돌아가는 실행 파일을 하나 만들고, 조원들이 만들어 둔 내용을 기반으로 새로 이어 붙였다.
누가 끝내면 다음 사람이 이어받는 릴레이 형식으로 파일이 갱신됐다.
시간 허비는 컸지만 포켓몬 로직 → 아이템 로직 → 전투 로직 → 플레이어·몬스터 로직 → 씬 연출까지 완주했다.

**4. 다음에 고칠 것**
지금은 **기술 이름을 문자열로 비교해** 변화기 로직을 태우고 있다.
기술 번호(ID)로 분기했다면 더 빠르고 오타에도 안전했을 것이다.

---

## 고지

학습 목적으로 만든 비상업 습작입니다.
포켓몬 관련 명칭·설정의 권리는 The Pokémon Company / Nintendo / Game Freak 에 있으며,
이 저장소는 어떤 원작 리소스도 포함하지 않습니다.
