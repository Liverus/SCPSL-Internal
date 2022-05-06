enum class Team {
	SCP,
	MTF,
	CHAOS,
	SCIENTIST,
	CLASS_D,
	GUARD,
	TUTORIAL
};

enum class Role {
	None = -1,
	SCP_173,
	CLASS_D,
	SPECTATOR,
	SCP_106,
	NTF_SPECIALIST,
	SCP_049,
	SCIENTIST,
	SCP_079,
	CHAOS_CONSCRIPT,
	SCP_096,
	SCP_0492,
	NTF_SERGEANT,
	NTF_CAPTAIN,
	NTF_PRIVATE,
	TUTORIAL,
	FACILITY_GUARD,
	SCP_93953,
	SCP_93989,
	CHAOS_RIFLEMAN,
	CHAOS_REPRESSOR,
	CHAOS_MARAUDER
};

class ClassManager : public OBJECT {
public:
	OBJECT* GetRole() {
		typedef OBJECT* (*ClassManager_get_CurRole_t)(ClassManager* this_);
		return Function<ClassManager_get_CurRole_t>("Assembly-CSharp", "", "CharacterClassManager", "get_CurRole", 0)(this);
	}

	bool SetNoclip(bool status) {
		typedef bool (*ClassManager_SetNoclip_t)(ClassManager* this_, bool status);
		return Function<ClassManager_SetNoclip_t>("Assembly-CSharp", "", "CharacterClassManager", "SetNoclip", 1)(this, status);
	}

	bool IsAnySCP() {
		typedef bool (*ClassManager_IsAnyScp_t)(ClassManager* this_);
		return Function<ClassManager_IsAnyScp_t>("Assembly-CSharp", "", "CharacterClassManager", "IsAnyScp", 0)(this);
	}

	bool IsAlive() {
		typedef bool (*ClassManager_get_IsAlive_t)(ClassManager* this_);
		return Function<ClassManager_get_IsAlive_t>("Assembly-CSharp", "", "CharacterClassManager", "get_IsAlive", 0)(this);
	}

	//Team GetTeam() {
	//	auto role = GetRole();

	//	return role->GetValue<Team>("team");
	//}

	//ReferenceHub* GetHub() {
	//	return this->GetValue<ReferenceHub*>("_hub");
	//}
};