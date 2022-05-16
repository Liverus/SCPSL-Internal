class ClassManager : public OBJECT {
public:
	OBJECT* GetRole() {
		typedef OBJECT* (*ClassManager_get_CurRole_t)(ClassManager* this_);
		return Function<ClassManager_get_CurRole_t>("Assembly-CSharp", "", "CharacterClassManager", "get_CurRole", 0)(this);
	}

	void SetNoclip(bool status) {
		this->SetValue<bool>("NoclipEnabled", &status);
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