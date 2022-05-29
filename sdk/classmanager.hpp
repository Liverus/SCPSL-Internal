enum RoleType : byte
{
	None = -1,
	Scp173,
	ClassD,
	Spectator,
	Scp106,
	NtfSpecialist,
	Scp049,
	Scientist,
	Scp079,
	ChaosConscript,
	Scp096,
	Scp0492,
	NtfSergeant,
	NtfCaptain,
	NtfPrivate,
	Tutorial,
	FacilityGuard,
	Scp93953,
	Scp93989,
	ChaosRifleman,
	ChaosRepressor,
	ChaosMarauder
};

class ClassManager : public Object {
public:
	Object* GetRole() {
		typedef Object* (*ClassManager_get_CurRole_t)(ClassManager* this_);
		return Function<ClassManager_get_CurRole_t>("Assembly-CSharp", "", "CharacterClassManager", "get_CurRole", 0)(this);
	}

	void SetNoclip(bool* status) {
		this->SetValue<bool>("NoclipEnabled", status);
	}

	bool IsAnySCP() {
		typedef bool (*ClassManager_IsAnyScp_t)(ClassManager* this_);
		return Function<ClassManager_IsAnyScp_t>("Assembly-CSharp", "", "CharacterClassManager", "IsAnyScp", 0)(this);
	}

	bool IsAlive() {
		typedef bool (*ClassManager_get_IsAlive_t)(ClassManager* this_);
		return Function<ClassManager_get_IsAlive_t>("Assembly-CSharp", "", "CharacterClassManager", "get_IsAlive", 0)(this);
	}

	bool IsSpawnProtected() {
		return this->GetValue<bool>("SpawnProtected");
	}
	//Team GetTeam() {
	//	auto role = GetRole();

	//	return role->GetValue<Team>("team");
	//}

	//ReferenceHub* GetHub() {
	//	return this->GetValue<ReferenceHub*>("_hub");
	//}
};