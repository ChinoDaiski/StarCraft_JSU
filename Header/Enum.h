#pragma once

enum class DIR { RIGHT, TOP_RIGHT, TOP, TOP_LEFT, LEFT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT, END };

enum class OBJID { BUILD, UNIT, BUTTON, ENEMY, BULLET, EFFECT, MINI_MAP, END };

enum class SCENEID { LOGO, MAINGAME, SINGLEPLAY, EDITOR, EXIT, WIN, LOSE, END };

enum class MOUSE_STATUS { IDLE, MOVE, ON_ALLIE, ON_NEUTRAL, ON_ENEMY, DRAG, END };

enum class TARGET { ALLIE, NEUTRAL, ENEMY, END };

// Ÿ�� - dirt(������ �� ����), water(������ �� ����), creep(������ �� ����), none_move(������ �� ����), none_nomove(������ �� ����) 
enum class TERRAIN { DIRT, WATER, CREEP, NONE_MOVE, NONE_NOMOVE, END };

enum class UNIT_NAME {
	// ���κ�
	Probe,

	// ����
	Zealot,

	//��ũ ���÷�
	Dark_Templar,

	//���
	Dragon,

	//���� 
	Reaver,

	//��Ʋ 
	Shuttle,

	//��ī�� 
	Scout,

	//�ƺ���
	Arbiter,

	//���� 
	Archon,

	//��ũ ����
	Dark_Archon,

	//������
	Observer,

	//ĳ����
	Carrier,

	//���ͼ���
	Interceptor,

	//Ŀ����
	Corsair,

	//���� ���÷� 
	High_Templar,

	END
};

// �ǹ����� �̸�
enum class BUILD {

	// �ƹ�Ÿ ���� �ǹ�
	Arbiter_Tribunal,

	// ���� ���� �ǹ�
	Assimilator,

	// �߾� ������
	Citadel_of_Adun,

	// ���, ���� ���׷��̵�
	Cybernetics_Core,

	// ĳ���� ������
	Fleet_Beacon,

	// ����ĳ��, ���� ���׷��̵�
	Forge,

	// ����Ʈ���� - ����, ���, �������÷�, ��ũ���÷�
	Gateway,

	// �ؼ��� - ���κ�
	Nexus,

	// ������
	Observatory,

	// ���� ĳ��
	Photon_Cannon,

	// ���Ϸ� - �α� ��
	Pylon,

	// �κ�ƽ�� - ��Ʋ, ����, ������
	Robotics_Facility,

	// ������ ������
	Robotics_Support_Bay,

	// ���� ���͸�
	Shield_Battery,

	// ��Ÿ����Ʈ - ��ī��, Ŀ����, ĳ����, �ƺ���
	Stargate,

	// ����/��ũ ���÷�, ���÷� ������
	Tempar_Archives,

	END
};

// ������ ������ �ִ� ��ư, ������ ������ �Ǹ� UI �����ʿ� �ߴ� ��ư�̴�.
// �ش� ��ư�� �� 9���� �̷���� ������, ��ư�� �迭�� ����(class CUnit)�� ��� �ִ�.
// ��ư�� �����ų� ������ �ʰų� Ȱ��ȭ�� ���� �ʾҰų� 3���� �̷���� �ִ�.

// ����, (�̵�����)�¿��, ���, ��� ������ �Ǽ�, Ȧ��, (�̵�����)������, �ڿ� ä��, �����̱�,
// �Ϲ� ������ �Ǽ�, �պ��ϱ�(��Ʈ��), �ѹ��� �Դٰ����ϱ�(����), �ڿ���ȯ(�ڿ� ä�� ����ϱ� - ����), ���߱�
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
	// ����, �ƺ���, ��� ���� �Ҹ� �̹���
	BALL, BALL_EXPLO,

	// ����
	SCARAB, SCARAB_EXPLO, SCARAB_MOVE,

	// ��ī��
	SCOUT_AIR, SCOUT_GROUND,

	// ��ĭ
	SHOCKBALL, SHOCKWAVE,

	// Ŀ����
	CORSAIR_SPLASH, WEB,

	// ĳ���� - ���ͼ���
	INTERCEP_EXPLO, INTERCEP_BULLET,

	// �ƺ���
	FROZEN, RECALL, STASIS,

	// �������÷�
	HALLUCI, STORM,

	// ��ũ��ĭ
	FEEDBACK, MAELSTORM, MINDCONTROL,

	// ���κ�
	PROBE_ATTACK,

	// ����
	EXPLOSION_L, EXPLOSION_M, EXPLOSION_S,

	// �ǹ� �����
	CREATE_BUILD,

	// �ǹ� �ı���
	VESTIGE,

	// ��ũ ���÷� ����
	DARK_TEMPLAR_DEAD,

	// ���� ����
	HIGH_TEMPLAR_DEAD,

	// ���� ����
	ARCHON_DEAD,

	// ��ũ ���� ����
	DARK_ARCHON_DEAD,

	// ���� ����
	ZEALOT_DEAD,

	// ��� ����
	DRAGON_DEAD,

	END
};

// ������Ʈ ���� - �Ʊ�/�߸�/����
enum class RELATION { Alliance, Enemy, Netural, END };

// �ش� ��ü�� Ÿ���� �������� �ǹ����� �Ǻ��ϱ� ���� ��
enum class OBJ_TYPE { UNIT, BUILD, END };