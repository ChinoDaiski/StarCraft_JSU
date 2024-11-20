#pragma once

enum class DIR { RIGHT, TOP_RIGHT, TOP, TOP_LEFT, LEFT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT, END };

enum class OBJID { BUILD, UNIT, BUTTON, ENEMY, BULLET, EFFECT, MINI_MAP, END };

enum class SCENEID { LOGO, MAINGAME, SINGLEPLAY, EDITOR, EXIT, WIN, LOSE, END };

enum class MOUSE_STATUS { IDLE, MOVE, ON_ALLIE, ON_NEUTRAL, ON_ENEMY, DRAG, END };

enum class TARGET { ALLIE, NEUTRAL, ENEMY, END };

// 타일 - dirt(움직일 수 있음), water(움직일 수 없음), creep(움직일 수 있음), none_move(움직일 수 있음), none_nomove(움직일 수 없음) 
enum class TERRAIN { DIRT, WATER, CREEP, NONE_MOVE, NONE_NOMOVE, END };

enum class UNIT_NAME {
	// 프로브
	Probe,

	// 질럿
	Zealot,

	//다크 템플러
	Dark_Templar,

	//드라군
	Dragon,

	//리버 
	Reaver,

	//셔틀 
	Shuttle,

	//스카웃 
	Scout,

	//아비터
	Arbiter,

	//아콘 
	Archon,

	//다크 아콘
	Dark_Archon,

	//옵저버
	Observer,

	//캐리어
	Carrier,

	//인터셉터
	Interceptor,

	//커세어
	Corsair,

	//하이 템플러 
	High_Templar,

	END
};

// 건물들의 이름
enum class BUILD {

	// 아바타 생산 건물
	Arbiter_Tribunal,

	// 가스 생산 건물
	Assimilator,

	// 발업 연구소
	Citadel_of_Adun,

	// 드라군, 공중 업그레이드
	Cybernetics_Core,

	// 캐리어 연구소
	Fleet_Beacon,

	// 포토캐논, 지상 업그레이드
	Forge,

	// 게이트웨이 - 질럿, 드라군, 하이템플러, 다크템플러
	Gateway,

	// 넥서스 - 프로브
	Nexus,

	// 옵저버
	Observatory,

	// 포토 캐논
	Photon_Cannon,

	// 파일런 - 인구 수
	Pylon,

	// 로보틱스 - 셔틀, 리버, 옵져버
	Robotics_Facility,

	// 옵져버 연구소
	Robotics_Support_Bay,

	// 쉴드 배터리
	Shield_Battery,

	// 스타게이트 - 스카웃, 커세어, 캐리어, 아비터
	Stargate,

	// 하이/다크 템플러, 템플러 연구소
	Tempar_Archives,

	END
};

// 유닛이 가지고 있는 버튼, 유닛을 누르게 되면 UI 오른쪽에 뜨는 버튼이다.
// 해당 버튼은 총 9개로 이루어져 있으며, 버튼의 배열은 유닛(class CUnit)이 들고 있다.
// 버튼은 누르거나 누르지 않거나 활성화가 되지 않았거나 3개로 이루어져 있다.

// 공격, (이동수단)태우기, 취소, 고급 구조물 건설, 홀드, (이동수단)내리기, 자원 채집, 움직이기,
// 일반 구조물 건설, 왕복하기(패트롤), 한번만 왔다갔다하기(랠리), 자원반환(자원 채집 계속하기 - 리턴), 멈추기
enum class BUTTON_ACTION {
	Attack, Boarding, Cancel, HBuild, Hold, Landing, Mining, Move,
	NBuild, Patrol, Rally, Return, Stop,
	END
};

enum class BUTTON_BUILD {
	Arbiter_Tribunal, Assimilator, Citadel_of_Adun, Cybernetics_Core, Fleet_Beacon,
	Forge, Gateway, Nexus, Observatory, Photon_Cannon, Pylon, Robotics_Facility,
	Robotics_Support_Bay, Shield_Battery, Stargate, Tempar_Archives,

	END
};

enum class BUTTON_SKILL {
	FeedBack, MindControl, Recall, ShildBattery_ShieldUp,
	StasisField, Storm, Wap, Illusion,

	END
};

enum class BUTTON_UNIT {
	Arbiter, Archon, Carrier, Corsair, DarkTemplar, Dark_Archon, Dragoon,
	HighTemplar, Interceptor, Observer, Probe, Reaver, Scout, Shuttle, Zealot,

	END
};

enum class BUTTON_UPGRADE {
	ArbiterMpUpgrade, ArbiterRecallUpgrade, ArbiterStasisFieldUpgrade, ArrArmorUpgrade, ArrAttUpgrade,
	ConfusionUpgrade, CorsairMpUp, DarkArchonMindControlUpgrade, DarkArchonMpUpgrade, DragonRangeUP,
	GroundArmorUpgrade, GroundAttUpgrade, GroundShildUpgrade, InterceptorCountUpgrade, ObserverSpeedUpgrade, ObserverVIewUpgrade,
	ReverAttUp, ReverScarup, ReverTongUp, ScoutSpeedUpgrade, ScoutViewUpgrade, SuttleSpeedUp,
	TemplarIllusionUpgrade, TemplarMpUpgrade, TemplarStormUpgrade, ZealotSpeedUP,

	END
};

enum class EFFECT {
	// 포톤, 아비터, 드라군 공격 불릿 이미지
	BALL, BALL_EXPLO,

	// 리버
	SCARAB, SCARAB_EXPLO, SCARAB_MOVE,

	// 스카웃
	SCOUT_AIR, SCOUT_GROUND,

	// 아칸
	SHOCKBALL, SHOCKWAVE,

	// 커세어
	CORSAIR_SPLASH, WEB,

	// 캐리어 - 인터셉터
	INTERCEP_EXPLO, INTERCEP_BULLET,

	// 아비터
	FROZEN, RECALL, STASIS,

	// 하이템플러
	HALLUCI, STORM,

	// 다크아칸
	FEEDBACK, MAELSTORM, MINDCONTROL,

	// 프로브
	PROBE_ATTACK,

	// 폭발
	EXPLOSION_L, EXPLOSION_M, EXPLOSION_S,

	// 건물 생산시
	CREATE_BUILD,

	// 건물 파괴시
	VESTIGE,

	// 다크 템플러 죽음
	DARK_TEMPLAR_DEAD,

	// 하템 죽음
	HIGH_TEMPLAR_DEAD,

	// 아콘 죽음
	ARCHON_DEAD,

	// 다크 아콘 죽음
	DARK_ARCHON_DEAD,

	// 질럿 죽음
	ZEALOT_DEAD,

	// 드라군 죽음
	DRAGON_DEAD,

	END
};

// 오브젝트 관계 - 아군/중립/적군
enum class RELATION { Alliance, Enemy, Netural, END };

// 해당 물체의 타입이 유닛인지 건물인지 판별하기 위한 값
enum class OBJ_TYPE { UNIT, BUILD, END };